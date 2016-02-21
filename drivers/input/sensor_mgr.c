/*
  *Generic Sensor Device Manager
 *
  *Copyright (C) 2013 - 2014 Huize Weng <huizeweng@arimacomm.com.tw>
 *
  *This program is free software; you can redistribute it and/or modify
  *it under the terms of the GNU General Public License version 2 as
  *published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/ctype.h>
#include <linux/slab.h>
#include <linux/sensor_mgr.h>
#include <linux/sensors_mctl.h>

static struct class *sensor_class;

static ssize_t getInternalDump(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	sensor_device *sDev = dev_get_drvdata(dev);
	if (!sDev)
		return sprintf(buf, "%s\n", "No such device");
	sDev->internalDump(buf);
	snprintf(buf + strlen(buf), 8, "\n%s\n", "Done");
	return strlen(buf);
}

static ssize_t getSensorActive(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	sensor_device *sDev = dev_get_drvdata(dev);
	if (!sDev)
		return sprintf(buf, "%s\n", "No such device");
	return sprintf(buf, "%u\n", (uint32_t) sDev->enable);
}

static ssize_t setSensorActive(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t size)
{
	bool enabled = false;
	ssize_t ret = -EPERM;
	sensor_device *sDev = dev_get_drvdata(dev);
	if (!sDev || sscanf(buf, "%u", (uint32_t *) &enabled) != 1)
		return ret;
	if (enabled == true || enabled == false) {
		mutex_lock(&sDev->mutex);
		if (sDev->setActive && sDev->setActive(enabled)) {
			sDev->enable = enabled;
			ret = size;
		}
		mutex_unlock(&sDev->mutex);
	}
	return ret;
}

static ssize_t getSensorDumpLevel(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	sensor_device *sDev = dev_get_drvdata(dev);
	const char *infor = "Alert : 0\nError : 1\nWarn  : 2\nNotice: 3\nInfo  : 4\nDebug : 5\n";
	if (!sDev)
		return sprintf(buf, "%s\n", "No such device");
	return sprintf(buf, "%s=> Debug Level : %u\n", infor, sDev->debugLevel);
}

static ssize_t setSensorDumpLevel(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t size)
{
	u32 debugLevel = 0;
	ssize_t ret = -EPERM;
	sensor_device *sDev = dev_get_drvdata(dev);
	if (!sDev || sscanf(buf, "%u", (uint32_t *) &debugLevel) != 1)
		return ret;
	if (debugLevel < 6) {
		mutex_lock(&sDev->mutex);
		sDev->debugLevel = debugLevel;
		ret = size;
		mutex_unlock(&sDev->mutex);
	}
	return ret;
}

static ssize_t setSensorDelay(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t size)
{
	ssize_t ret = -EPERM;
	s64 delay = 0L;
	sensor_device *sDev = dev_get_drvdata(dev);
	if (!sDev || sscanf(buf, "%lld", &delay) != 1)
		return ret;
	mutex_lock(&sDev->mutex);
	if (sDev->setDelay && sDev->setDelay(delay)) {
		sDev->delay = delay;
		ret = size;
	}
	mutex_unlock(&sDev->mutex);
	return ret;
}

static ssize_t getSensorDelay(struct device *dev,
	struct device_attribute *attr, char *buf)
{
	sensor_device *sDev = dev_get_drvdata(dev);
	if (!sDev)
		return sprintf(buf, "%s\n", "No such device");
	return sprintf(buf, "%lld\n", sDev->delay);
}

static ssize_t getDeviceInfor(struct file *file, struct kobject *kobj,
	struct bin_attribute *attr, char *buf, loff_t pos, size_t size)
{
	struct device *dev = container_of(kobj, struct device, kobj);
	sensor_device *sDev = dev_get_drvdata(dev);
	ssize_t siz;
	if (!sDev)
		return -EPERM;
	mutex_lock(&sDev->mutex);
	if (sDev->infor)
		siz = memory_read_from_buffer(buf, size, &pos, sDev->infor, sizeof(*sDev->infor));
	else
		siz = 0;
	mutex_unlock(&sDev->mutex);
	return siz;
}

static ssize_t setCalibrate(struct file *file, struct kobject *kobj,
	struct bin_attribute *attr, char *buf, loff_t pos, size_t size)
{
	struct device *dev = container_of(kobj, struct device, kobj);
	sensor_device *sDev = dev_get_drvdata(dev);
	ssize_t siz = -EPERM;
	if (!sDev)
		return -EPERM;
	mutex_lock(&sDev->mutex);
	if (sDev->calibrate &&
		size == sizeof(Sensor_Calibrate_Infor) &&
		sDev->calibrate(Write, (void *) buf, size)) {
		siz = size;
	}
	mutex_unlock(&sDev->mutex);
	return siz;
}

static ssize_t getCalibrate(struct file *file, struct kobject *kobj,
	struct bin_attribute *attr, char *buf, loff_t pos, size_t size)
{
	struct device *dev = container_of(kobj, struct device, kobj);
	sensor_device *sDev = dev_get_drvdata(dev);
	ssize_t siz = -EPERM;
	if (!sDev)
		return -EPERM;
	memset(buf, 0, size);
	mutex_lock(&sDev->mutex);
	if (sDev->calibrate &&
		size == sizeof(Sensor_Calibrate_Infor) &&
		sDev->calibrate(Read, (void *) buf, size)) {
		siz = size;
	}
	mutex_unlock(&sDev->mutex);
	return siz;
}

static struct device_attribute sensor_class_attrs[] = {
	__ATTR(enable, 0660, getSensorActive, setSensorActive),
	__ATTR(delay, 0660, getSensorDelay, setSensorDelay),
	__ATTR(dumpLevel, 0660, getSensorDumpLevel, setSensorDumpLevel),
	__ATTR(dump, 0440, getInternalDump, NULL),
	__ATTR_NULL,
};

static struct bin_attribute sensor_class_bin_attrs[] = {
	__BIN_ATTR(deviceInfor, 0440, sizeof(struct device_infor), NULL, getDeviceInfor, NULL),
	__BIN_ATTR(calibrate, 0660, sizeof(Sensor_Calibrate_Infor), NULL, getCalibrate, setCalibrate),
	__ATTR_NULL,
};

static int sensor_suspend(struct device *dev, pm_message_t state)
{
	return 0;
}

static int sensor_resume(struct device *dev)
{
	return 0;
}

int sensor_device_register(struct device *parent, sensor_device *sDev)
{
	if (!sDev)
		return -EPERM;
	sDev->dev = device_create(sensor_class, parent, 0, sDev, "%s", sDev->name);

	if (IS_ERR(sDev->dev))
		return PTR_ERR(sDev->dev);

	mutex_init(&sDev->mutex);

	return 0;
}
EXPORT_SYMBOL_GPL(sensor_device_register);

void sensor_device_unregister(sensor_device *cdev)
{
	if (!cdev || !cdev->dev || IS_ERR(cdev->dev))
		return;
	device_unregister(cdev->dev);
}
EXPORT_SYMBOL_GPL(sensor_device_unregister);

static int __init sensor_mgr_init(void)
{
	sensor_class = class_create(THIS_MODULE, "sensors");
	if (IS_ERR(sensor_class))
		return PTR_ERR(sensor_class);
	sensor_class->suspend = sensor_suspend;
	sensor_class->resume = sensor_resume;
	sensor_class->dev_attrs = sensor_class_attrs;
	sensor_class->dev_bin_attrs = sensor_class_bin_attrs;
	return 0;
}

static void __exit sensor_mgr_exit(void)
{
	class_destroy(sensor_class);
}

subsys_initcall(sensor_mgr_init);
module_exit(sensor_mgr_exit);
MODULE_AUTHOR("Huize Weng");
MODULE_LICENSE("GPLv2");
MODULE_DESCRIPTION("Sensor Class Interface");
