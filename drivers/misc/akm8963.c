/* drivers/misc/akm8963.c - akm8963 compass driver
 *
 * Copyright (C) 2007-2008 HTC Corporation.
 * Author: Hou-Kun Chen <houkun.chen@gmail.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

/*#define DEBUG*/
/*#define VERBOSE_DEBUG*/

#include <linux/device.h>
#include <linux/interrupt.h>
#include <linux/i2c.h>
#include <linux/slab.h>
#include <linux/irq.h>
#include <linux/miscdevice.h>
#include <linux/gpio.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/input.h>
#include <linux/workqueue.h>
#include <linux/freezer.h>
#include <linux/akm8963.h>
#include <linux/module.h>

/*++ Huize - 20121107 Add for getting device information ++*/
#include <linux/regulator/consumer.h>
#include <linux/sensors_mctl.h>
#include <linux/sensor_mgr.h>
/*-- Huize - 20121107 Add for getting device information --*/

#define AKM8963_DEBUG_IF	0
#define AKM8963_DEBUG_DATA	0

#define AKM_ACCEL_ITEMS 3
/* Wait timeout in millisecond */
#define AKM8963_DRDY_TIMEOUT	100

#define USE_IRQ
#define AKM8963_IRQ 83
#define AKM8963_RSTN 6

struct akm8963_data {
	struct i2c_client	*i2c;
	struct input_dev	*input;
	struct device		*class_dev;
	struct class		*compass;
	struct delayed_work	work;

	wait_queue_head_t	drdy_wq;
	wait_queue_head_t	open_wq;

	struct mutex sensor_mutex;
	int8_t	sense_data[SENSOR_DATA_SIZE];
	struct mutex accel_mutex;
	int16_t	accel_data[AKM_ACCEL_ITEMS];

	struct mutex	val_mutex;
	uint32_t	enable_flag;
	int64_t		delay[AKM_NUM_SENSORS];

	atomic_t	active;
	atomic_t	is_busy;
	atomic_t	drdy;
	atomic_t	suspend;

	char layout;
	char outbit;
	int	irq;
	int	rstn;
	struct regulator* vdd;
	struct regulator* vdd_i2c;
};

static struct akm8963_data *s_akm;

static bool akm8963_enable_mag_store(bool enable);
static bool akm8963_delay_mag_store(s64 delay);
static struct device_infor infor = {
	.name		= "Magnetic Field Sensor",
	.vendor		= "Asahi Kasei Microdevices",
	.maxRange	= 49152,
	.resolution = 0,
	.power		= 280,// ua
	.minDelay	= 10000,
};

static sensor_device MAGNETIC = {
	.name = "magnetic",
	.enable = false,
	.delay = -1,
	.debugLevel = 1,
	.setActive = akm8963_enable_mag_store,
	.setDelay = akm8963_delay_mag_store,
	.calibrate = NULL,
	.infor = &infor,
};


/***** I2C I/O function ***********************************************/
static int akm8963_i2c_rxdata(
	struct i2c_client *i2c,
	unsigned char *rxData,
	int length)
{
	struct i2c_msg msgs[] = {
	{
		.addr = i2c->addr,
		.flags = 0,
		.len = 1,
		.buf = rxData,
	},
	{
		.addr = i2c->addr,
		.flags = I2C_M_RD,
		.len = length,
		.buf = rxData,
	}, };
	unsigned char addr = rxData[0];

	if (i2c_transfer(i2c->adapter, msgs, 2) < 0) {
		sDump_err(MAGNETIC.debugLevel, "%s: transfer failed\n", __func__);
		return -EIO;
	}

	sDump_debug(MAGNETIC.debugLevel, "%s: RxData: len=%02x, addr=%02x, data=%02x\n", __func__,
		length, addr, rxData[0]);
	return 0;
}

static int akm8963_i2c_txdata(
	struct i2c_client *i2c,
	unsigned char *txData,
	int length)
{
	struct i2c_msg msg[] = {
	{
		.addr = i2c->addr,
		.flags = 0,
		.len = length,
		.buf = txData,
	}, };

	if (i2c_transfer(i2c->adapter, msg, 1) < 0) {
		sDump_err(MAGNETIC.debugLevel, "%s: transfer failed\n", __func__);
		return -EIO;
	}

	sDump_debug(MAGNETIC.debugLevel, "%s: TxData: len=%02x, addr=%02x data=%02x\n", __func__,
		length, txData[0], txData[1]);
	return 0;
}

static int akm8963_i2c_check_device(
	struct i2c_client *client)
{
	unsigned char buffer[2];
	int err;

	/* Set measure mode */
	buffer[0] = AK8963_REG_WIA;
	err = akm8963_i2c_rxdata(client, buffer, 1);
	if (err < 0) {
		sDump_err(MAGNETIC.debugLevel, "%s: Can not read WIA.\n", __func__);
		return err;
	}

	/* Check read data */
	if (buffer[0] != 0x48) {
		sDump_err(MAGNETIC.debugLevel, "%s: The device is not AK8963.\n", __func__);
		return -ENXIO;
	}

	return err;
}

/***** akm miscdevice functions *************************************/
static int AKECS_Open(struct inode *inode, struct file *file);
static int AKECS_Release(struct inode *inode, struct file *file);
static long AKECS_ioctl(struct file *file,
		unsigned int cmd, unsigned long arg);

static struct file_operations AKECS_fops = {
	.owner = THIS_MODULE,
	.open = AKECS_Open,
	.release = AKECS_Release,
	.unlocked_ioctl = AKECS_ioctl,
};

static struct miscdevice akm8963_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	/*++ Huize - 20120329 Add for naming general ++*/
	.name = "magnetic",
	/*-- Huize - 20120329 Add for naming general --*/
	.fops = &AKECS_fops,
};

static int AKECS_Set_CNTL1(
	struct akm8963_data *akm,
	unsigned char mode)
{
	unsigned char buffer[2];
	int err;

	/* Busy check */
	if (atomic_cmpxchg(&akm->is_busy, 0, 1) != 0) {
		sDump_err(MAGNETIC.debugLevel, "%s: device is busy.\n", __func__);
		return -EBUSY;
	}

	/* Set flag */
	atomic_set(&akm->drdy, 0);

	/* Set measure mode */
	buffer[0] = AK8963_REG_CNTL1;
	buffer[1] = mode;
	err = akm8963_i2c_txdata(akm->i2c, buffer, 2);
	if (err < 0) {
		sDump_err(MAGNETIC.debugLevel, "%s: Can not set CNTL.\n", __func__);
		atomic_set(&akm->is_busy, 0);
	} else {
		sDump_debug(MAGNETIC.debugLevel, "Mode is set to (%d).\n", mode);
	}

	return err;
}

static int AKECS_Set_PowerDown(
	struct akm8963_data *akm)
{
	unsigned char buffer[2];
	int err;

	/* Set measure mode */
	buffer[0] = AK8963_REG_CNTL1;
	buffer[1] = AK8963_MODE_POWERDOWN;
	err = akm8963_i2c_txdata(akm->i2c, buffer, 2);
	if (err < 0) {
		sDump_err(MAGNETIC.debugLevel, "%s: Can not set to measurement mode.\n", __func__);
		atomic_set(&akm->is_busy, 0);
	} else {
		sDump_debug(MAGNETIC.debugLevel, "Powerdown mode is set.\n");
	}

	/* Set to initial status. */
	atomic_set(&akm->is_busy, 0);
	atomic_set(&akm->drdy, 0);

	return err;
}

static int AKECS_Reset(
	struct akm8963_data *akm,
	int hard)
{
	unsigned char buffer[2];
	int err = 0;

	if (hard != 0) {
		gpio_set_value(akm->rstn, 0);
		udelay(5);
		gpio_set_value(akm->rstn, 1);
	} else {
		/* Set measure mode */
		buffer[0] = AK8963_REG_CNTL2;
		buffer[1] = 0x01;
		err = akm8963_i2c_txdata(akm->i2c, buffer, 2);
		if (err < 0) {
			sDump_err(MAGNETIC.debugLevel, "%s: Can not set SRST bit.\n", __func__);
		} else {
			sDump_debug(MAGNETIC.debugLevel, "Soft reset is done.\n");
		}
	}

	/* Device will be accessible 100 us after */
	usleep(100);

	return err;
}

static int AKECS_SetMode(
	struct akm8963_data *akm,
	unsigned char mode)
{
	int err;

	switch (mode & 0x0F) {
	case AK8963_MODE_SNG_MEASURE:
	case AK8963_MODE_SELF_TEST:
	case AK8963_MODE_FUSE_ACCESS:
		err = AKECS_Set_CNTL1(akm, mode);
		if ((err >= 0) && (akm->irq == 0)) {
			schedule_delayed_work(
				&akm->work,
				usecs_to_jiffies(AK8963_MEASUREMENT_TIME_US));
		}
		break;
	case AK8963_MODE_POWERDOWN:
		err = AKECS_Set_PowerDown(akm);
		break;
	default:
		sDump_err(MAGNETIC.debugLevel, "%s: Unknown mode(%d).\n", __func__, mode);
		return -EINVAL;
	}

	/* wait at least 100us after changing mode */
	usleep(100);

	return err;
}

/* This function will block a process until the latest measurement
 * data is available.
 */
static int AKECS_GetData(
	struct akm8963_data *akm,
	char *rbuf,
	int size)
{
	int err;
	err = wait_event_interruptible_timeout(
			akm->drdy_wq,
			atomic_read(&akm->drdy),
			AKM8963_DRDY_TIMEOUT);

	if (err < 0) {
		sDump_err(MAGNETIC.debugLevel, "%s: wait_event failed (%d).\n", __func__, err);
		return -1;
	}
	if (!atomic_read(&akm->drdy)) {
		sDump_err(MAGNETIC.debugLevel, "%s: DRDY is not set.\n", __func__);
		return -1;
	}

	mutex_lock(&akm->sensor_mutex);
	memcpy(rbuf, akm->sense_data, size);
	atomic_set(&akm->drdy, 0);
	mutex_unlock(&akm->sensor_mutex);

	return 0;
}

static void AKECS_SetYPR(
	struct akm8963_data *akm,
	int *rbuf)
{
	uint32_t ready;
	sDump_debug(MAGNETIC.debugLevel, "AKM8963 %s: flag =0x%X\n", __func__,
		rbuf[0]);
	sDump_debug(MAGNETIC.debugLevel, "  Acceleration[LSB]: %6d,%6d,%6d stat=%d\n",
		rbuf[1], rbuf[2], rbuf[3], rbuf[4]);
	sDump_debug(MAGNETIC.debugLevel, "  Geomagnetism[LSB]: %6d,%6d,%6d stat=%d\n",
		rbuf[5], rbuf[6], rbuf[7], rbuf[8]);
	sDump_debug(MAGNETIC.debugLevel, "  Orientation[YPR] : %6d,%6d,%6d\n",
		rbuf[9], rbuf[10], rbuf[11]);

	/* No events are reported */
	if (!rbuf[0]) {
		sDump_debug(MAGNETIC.debugLevel, "Don't waste a time.\n");
		return;
	}

	mutex_lock(&akm->val_mutex);
	ready = (akm->enable_flag & (uint32_t)rbuf[0]);
	mutex_unlock(&akm->val_mutex);

	/* Report acceleration sensor information */
	if (ready & ACC_DATA_READY) {
		input_report_abs(akm->input, ABS_X, rbuf[1]);
		input_report_abs(akm->input, ABS_Y, rbuf[2]);
		input_report_abs(akm->input, ABS_Z, rbuf[3]);
		input_report_abs(akm->input, ABS_THROTTLE, rbuf[4]);
	}
	/* Report magnetic vector information */
	if (ready & MAG_DATA_READY) {
		input_report_abs(akm->input, ABS_RX, rbuf[5]);
		input_report_abs(akm->input, ABS_RY, rbuf[6]);
		input_report_abs(akm->input, ABS_RZ, rbuf[7]);
		input_report_abs(akm->input, ABS_RUDDER, rbuf[8]);
	}
	/* Report orientation sensor information */
	if (ready & ORI_DATA_READY) {
		input_report_abs(akm->input, ABS_HAT0X, rbuf[9]);
		input_report_abs(akm->input, ABS_HAT0Y, rbuf[10]);
		input_report_abs(akm->input, ABS_HAT1X, rbuf[11]);
		input_report_abs(akm->input, ABS_HAT1Y, rbuf[4]);
	}

	input_sync(akm->input);
}

static int AKECS_GetOpenStatus(
	struct akm8963_data *akm)
{
	return wait_event_interruptible(
			akm->open_wq, (atomic_read(&akm->active) != 0));
}

static int AKECS_GetCloseStatus(
	struct akm8963_data *akm)
{
	return wait_event_interruptible(
			akm->open_wq, (atomic_read(&akm->active) <= 0));
}

static int AKECS_Open(struct inode *inode, struct file *file)
{
	file->private_data = s_akm;
	return nonseekable_open(inode, file);
}

static int AKECS_Release(struct inode *inode, struct file *file)
{
	return 0;
}

static long
AKECS_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	void __user *argp = (void __user *)arg;
	struct akm8963_data *akm = file->private_data;

	/* NOTE: In this function the size of "char" should be 1-byte. */
	char i2c_buf[RWBUF_SIZE];		/* for READ/WRITE */
	int8_t sensor_buf[SENSOR_DATA_SIZE];/* for GETDATA */
	int32_t ypr_buf[YPR_DATA_SIZE];	/* for SET_YPR */
	int16_t acc_buf[3];				/* for GET_ACCEL */
	int64_t delay[AKM_NUM_SENSORS];	/* for GET_DELAY */
	char mode;			/* for SET_MODE*/
	char layout;		/* for GET_LAYOUT */
	char outbit;		/* for GET_OUTBIT */
	int status;			/* for OPEN/CLOSE_STATUS */
	int ret = -1;		/* Return value. */

	memset(i2c_buf, 0, RWBUF_SIZE);

	switch (cmd) {
	case ECS_IOCTL_READ:
	case ECS_IOCTL_WRITE:
		if (argp == NULL) {
			sDump_err(MAGNETIC.debugLevel, "invalid argument.\n");
			return -EINVAL;
		}
		if (copy_from_user(&i2c_buf, argp, sizeof(i2c_buf))) {
			sDump_err(MAGNETIC.debugLevel, "copy_from_user failed.\n");
			return -EFAULT;
		}
		break;
	case ECS_IOCTL_SET_MODE:
		if (argp == NULL) {
			sDump_err(MAGNETIC.debugLevel, "invalid argument.\n");
			return -EINVAL;
		}
		if (copy_from_user(&mode, argp, sizeof(mode))) {
			sDump_err(MAGNETIC.debugLevel, "copy_from_user failed.\n");
			return -EFAULT;
		}
		break;
	case ECS_IOCTL_SET_YPR:
		if (argp == NULL) {
			sDump_err(MAGNETIC.debugLevel, "invalid argument.\n");
			return -EINVAL;
		}
		if (copy_from_user(&ypr_buf, argp, sizeof(ypr_buf))) {
			sDump_err(MAGNETIC.debugLevel, "copy_from_user failed.\n");
			return -EFAULT;
		}
		break;
	case ECS_IOCTL_GETDATA:
	case ECS_IOCTL_GET_OPEN_STATUS:
	case ECS_IOCTL_GET_CLOSE_STATUS:
	case ECS_IOCTL_GET_DELAY:
	case ECS_IOCTL_GET_LAYOUT:
	case ECS_IOCTL_GET_OUTBIT:
	case ECS_IOCTL_GET_ACCEL:
		/* Just check buffer pointer */
		if (argp == NULL) {
			sDump_err(MAGNETIC.debugLevel, "invalid argument.\n");
			return -EINVAL;
		}
		break;
	default:
		break;
	}

	switch (cmd) {
	case ECS_IOCTL_READ:
		sDump_debug(MAGNETIC.debugLevel, "IOCTL_READ called.\n");
		if ((i2c_buf[0] < 1) || (i2c_buf[0] > (RWBUF_SIZE-1))) {
			sDump_err(MAGNETIC.debugLevel, "invalid argument.\n");
			return -EINVAL;
		}
		ret = akm8963_i2c_rxdata(akm->i2c, &i2c_buf[1], i2c_buf[0]);
		if (ret < 0)
			return ret;
		break;
	case ECS_IOCTL_WRITE:
		sDump_debug(MAGNETIC.debugLevel, "IOCTL_WRITE called.\n");
		if ((i2c_buf[0] < 2) || (i2c_buf[0] > (RWBUF_SIZE-1))) {
			sDump_err(MAGNETIC.debugLevel, "invalid argument.\n");
			return -EINVAL;
		}
		ret = akm8963_i2c_txdata(akm->i2c, &i2c_buf[1], i2c_buf[0]);
		if (ret < 0)
			return ret;
		break;
	case ECS_IOCTL_SET_MODE:
		sDump_debug(MAGNETIC.debugLevel, "IOCTL_SET_MODE called.\n");
		ret = AKECS_SetMode(akm, mode);
		if (ret < 0)
			return ret;
		break;
	case ECS_IOCTL_GETDATA:
		sDump_debug(MAGNETIC.debugLevel, "IOCTL_GETDATA called.\n");
		ret = AKECS_GetData(akm, sensor_buf, SENSOR_DATA_SIZE);
		if (ret < 0)
			return ret;
		break;
	case ECS_IOCTL_SET_YPR:
		sDump_debug(MAGNETIC.debugLevel, "IOCTL_SET_YPR called.\n");
		AKECS_SetYPR(akm, ypr_buf);
		break;
	case ECS_IOCTL_GET_OPEN_STATUS:
		sDump_debug(MAGNETIC.debugLevel, "IOCTL_GET_OPEN_STATUS called.\n");
		ret = AKECS_GetOpenStatus(akm);
		if (ret < 0) {
			sDump_err(MAGNETIC.debugLevel,
				"Get Open returns error (%d).\n", ret);
		}
		break;
	case ECS_IOCTL_GET_CLOSE_STATUS:
		sDump_debug(MAGNETIC.debugLevel, "IOCTL_GET_CLOSE_STATUS called.\n");
		ret = AKECS_GetCloseStatus(akm);
		if (ret < 0) {
			sDump_err(MAGNETIC.debugLevel,
				"Get Close returns error (%d).", ret);
		}
		break;
	case ECS_IOCTL_GET_DELAY:
		sDump_debug(MAGNETIC.debugLevel, "IOCTL_GET_DELAY called.\n");
		mutex_lock(&akm->val_mutex);
		delay[0] = akm->delay[0];
		delay[1] = akm->delay[1];
		delay[2] = akm->delay[2];
		mutex_unlock(&akm->val_mutex);
		break;
	case ECS_IOCTL_GET_LAYOUT:
		sDump_debug(MAGNETIC.debugLevel, "IOCTL_GET_LAYOUT called.\n");
		layout = akm->layout;
		break;
	case ECS_IOCTL_GET_OUTBIT:
		sDump_debug(MAGNETIC.debugLevel, "IOCTL_GET_OUTBIT called.\n");
		outbit = akm->outbit;
		break;
	case ECS_IOCTL_RESET:
		ret = AKECS_Reset(akm, akm->rstn);
		if (ret < 0)
			return ret;
		break;
	case ECS_IOCTL_GET_ACCEL:
		sDump_debug(MAGNETIC.debugLevel, "IOCTL_GET_ACCEL called.\n");
		mutex_lock(&akm->accel_mutex);
		acc_buf[0] = akm->accel_data[0];
		acc_buf[1] = akm->accel_data[1];
		acc_buf[2] = akm->accel_data[2];
		mutex_unlock(&akm->accel_mutex);
		break;
	default:
		return -ENOTTY;
	}

	switch (cmd) {
	case ECS_IOCTL_READ:
		if (copy_to_user(argp, &i2c_buf, i2c_buf[0]+1)) {
			sDump_err(MAGNETIC.debugLevel, "copy_to_user failed.\n");
			return -EFAULT;
		}
		break;
	case ECS_IOCTL_GETDATA:
		if (copy_to_user(argp, &sensor_buf, sizeof(sensor_buf))) {
			sDump_err(MAGNETIC.debugLevel, "copy_to_user failed.\n");
			return -EFAULT;
		}
		break;
	case ECS_IOCTL_GET_OPEN_STATUS:
	case ECS_IOCTL_GET_CLOSE_STATUS:
		status = atomic_read(&akm->active);
		if (copy_to_user(argp, &status, sizeof(status))) {
			sDump_err(MAGNETIC.debugLevel, "copy_to_user failed.\n");
			return -EFAULT;
		}
		break;
	case ECS_IOCTL_GET_DELAY:
		if (copy_to_user(argp, &delay, sizeof(delay))) {
			sDump_err(MAGNETIC.debugLevel, "copy_to_user failed.\n");
			return -EFAULT;
		}
		break;
	case ECS_IOCTL_GET_LAYOUT:
		if (copy_to_user(argp, &layout, sizeof(layout))) {
			sDump_err(MAGNETIC.debugLevel, "copy_to_user failed.\n");
			return -EFAULT;
		}
		break;
	case ECS_IOCTL_GET_OUTBIT:
		if (copy_to_user(argp, &outbit, sizeof(outbit))) {
			sDump_err(MAGNETIC.debugLevel, "copy_to_user failed.\n");
			return -EFAULT;
		}
		break;
	case ECS_IOCTL_GET_ACCEL:
		if (copy_to_user(argp, &acc_buf, sizeof(acc_buf))) {
			sDump_err(MAGNETIC.debugLevel, "copy_to_user failed.\n");
			return -EFAULT;
		}
		break;
	default:
		break;
	}

	return 0;
}

/***** akm sysfs functions ******************************************/
static int create_device_attributes(
	struct device *dev,
	struct device_attribute *attrs)
{
	int i;
	int err = 0;

	for (i = 0 ; NULL != attrs[i].attr.name ; ++i) {
		err = device_create_file(dev, &attrs[i]);
		if (0 != err)
			break;
	}

	if (0 != err) {
		for (; i >= 0 ; --i)
			device_remove_file(dev, &attrs[i]);
	}

	return err;
}

static void remove_device_attributes(
	struct device *dev,
	struct device_attribute *attrs)
{
	int i;

	for (i = 0 ; NULL != attrs[i].attr.name ; ++i)
		device_remove_file(dev, &attrs[i]);
}

static int create_device_binary_attributes(
	struct kobject *kobj,
	struct bin_attribute *attrs)
{
	int i;
	int err = 0;

	err = 0;

	for (i = 0 ; NULL != attrs[i].attr.name ; ++i) {
		err = sysfs_create_bin_file(kobj, &attrs[i]);
		if (0 != err)
			break;
	}

	if (0 != err) {
		for (; i >= 0 ; --i)
			sysfs_remove_bin_file(kobj, &attrs[i]);
	}

	return err;
}

static void remove_device_binary_attributes(
	struct kobject *kobj,
	struct bin_attribute *attrs)
{
	int i;

	for (i = 0 ; NULL != attrs[i].attr.name ; ++i)
		sysfs_remove_bin_file(kobj, &attrs[i]);
}

static bool get_value_as_int(char const *buf, size_t size, int *value)
{
	long tmp;

	if (size == 0)
		return false;

	/* maybe text format value */
	if ((buf[0] == '0') && (size > 1)) {
		if ((buf[1] == 'x') || (buf[1] == 'X')) {
			/* hexadecimal format */
			if (0 != strict_strtol(buf, 16, &tmp))
				return false;
		} else {
			/* octal format */
			if (0 != strict_strtol(buf, 8, &tmp))
				return false;
		}
	} else {
		/* decimal format */
		if (0 != strict_strtol(buf, 10, &tmp))
			return false;
	}

	if (tmp > INT_MAX)
		return false;

	*value = tmp;

	return true;
}

static bool get_value_as_int64(char const *buf, size_t size, long long *value)
{
	long long tmp;

	if (size == 0)
		return false;

	/* maybe text format value */
	if ((buf[0] == '0') && (size > 1)) {
		if ((buf[1] == 'x') || (buf[1] == 'X')) {
			/* hexadecimal format */
			if (0 != strict_strtoll(buf, 16, &tmp))
				return false;
		} else {
			/* octal format */
			if (0 != strict_strtoll(buf, 8, &tmp))
				return false;
		}
	} else {
		/* decimal format */
		if (0 != strict_strtoll(buf, 10, &tmp))
			return false;
	}

	if (tmp > LLONG_MAX)
		return false;

	*value = tmp;

	return true;
}

/*********************************************************************
 *
 * SysFS attribute functions
 *
 * directory : /sys/class/compass/magnetic/
 * files :
 *  - enable_acc [rw] [t] : enable flag for accelerometer
 *  - enable_mag [rw] [t] : enable flag for magnetometer
 *  - enable_ori [rw] [t] : enable flag for orientation
 *  - delay_acc  [rw] [t] : delay in nanosecond for accelerometer
 *  - delay_mag  [rw] [t] : delay in nanosecond for magnetometer
 *  - delay_ori  [rw] [t] : delay in nanosecond for orientation
 *  - accel	     [w]  [b] : accelerometer data
 *
 * debug :
 *  - mode       [w]  [t] : AK8963's mode
 *  - bdata      [r]  [t] : raw data
 *  - asa        [r]  [t] : FUSEROM data
 *
 * [b] = binary format
 * [t] = text format
 */

/***** sysfs enable *************************************************/
static void akm8963_sysfs_update_active_status(
	struct akm8963_data *akm)
{
	uint32_t en;
	mutex_lock(&akm->val_mutex);
	en = akm->enable_flag;
	mutex_unlock(&akm->val_mutex);

	if (en == 0) {
		if (atomic_cmpxchg(&akm->active, 1, 0) == 1) {
			wake_up(&akm->open_wq);
			//dev_dbg(akm->class_dev, "Deactivated");
		}
	} else {
		if (atomic_cmpxchg(&akm->active, 0, 1) == 0) {
			wake_up(&akm->open_wq);
			//dev_dbg(akm->class_dev, "Activated");
		}
	}
	sDump_debug(MAGNETIC.debugLevel,
		"Status updated: enable=0x%X, active=%d\n",
		en, atomic_read(&akm->active));
}

static ssize_t akm8963_sysfs_enable_show(
	struct akm8963_data *akm, char *buf, int pos)
{
	int flag;

	mutex_lock(&akm->val_mutex);
	flag = ((akm->enable_flag >> pos) & 1);
	mutex_unlock(&akm->val_mutex);

	return sprintf(buf, "%d\n", flag);
}

static ssize_t akm8963_sysfs_enable_store(
	struct akm8963_data *akm, char const *buf, size_t count, int pos)
{
	int en = 0;

	if (NULL == buf)
		return -EINVAL;

	if (0 == count)
		return 0;

	if (false == get_value_as_int(buf, count, &en))
		return -EINVAL;

	en = en ? 1 : 0;

	mutex_lock(&akm->val_mutex);
	akm->enable_flag &= ~(1<<pos);
	akm->enable_flag |= ((uint32_t)(en))<<pos;
	mutex_unlock(&akm->val_mutex);

	akm8963_sysfs_update_active_status(akm);

	return count;
}

/***** Acceleration ***/
static ssize_t akm8963_enable_acc_show(
	struct device *dev, struct device_attribute *attr, char *buf)
{
	return akm8963_sysfs_enable_show(
		s_akm, buf, ACC_DATA_FLAG);
}
static ssize_t akm8963_enable_acc_store(
	struct device *dev, struct device_attribute *attr,
	char const *buf, size_t count)
{
	return akm8963_sysfs_enable_store(
		s_akm, buf, count, ACC_DATA_FLAG);
}

/***** Magnetic field ***/
static bool akm8963_enable_mag_store(bool enable)
{
	char buf[2] = {'\0', '\0'};
	buf[0] = (enable) ? '1' : '0';
	akm8963_sysfs_enable_store(s_akm, buf, 1, MAG_DATA_FLAG);
	return true;
}

/***** Orientation ***/
static ssize_t akm8963_enable_ori_show(
	struct device *dev, struct device_attribute *attr, char *buf)
{
	return akm8963_sysfs_enable_show(
		s_akm, buf, ORI_DATA_FLAG);
}
static ssize_t akm8963_enable_ori_store(
	struct device *dev, struct device_attribute *attr,
	char const *buf, size_t count)
{
	return akm8963_sysfs_enable_store(
		s_akm, buf, count, ORI_DATA_FLAG);
}

/***** sysfs delay **************************************************/
static ssize_t akm8963_sysfs_delay_show(
	struct akm8963_data *akm, char *buf, int pos)
{
	int64_t val;

	mutex_lock(&akm->val_mutex);
	val = akm->delay[pos];
	mutex_unlock(&akm->val_mutex);

	return sprintf(buf, "%lld\n", val);
}

static ssize_t akm8963_sysfs_delay_store(
	struct akm8963_data *akm, char const *buf, size_t count, int pos)
{
	long long val = 0;

	if (NULL == buf)
		return -EINVAL;

	if (0 == count)
		return 0;

	if (false == get_value_as_int64(buf, count, &val))
		return -EINVAL;

	mutex_lock(&akm->val_mutex);
	akm->delay[pos] = val;
	mutex_unlock(&akm->val_mutex);

	return count;
}

/***** Accelerometer ***/
static ssize_t akm8963_delay_acc_show(
	struct device *dev, struct device_attribute *attr, char *buf)
{
	return akm8963_sysfs_delay_show(
		s_akm, buf, ACC_DATA_FLAG);
}
static ssize_t akm8963_delay_acc_store(
	struct device *dev, struct device_attribute *attr,
	char const *buf, size_t count)
{
	return akm8963_sysfs_delay_store(
		s_akm, buf, count, ACC_DATA_FLAG);
}

/***** Magnetic field ***/

static bool akm8963_delay_mag_store(s64 delay)
{
	char buf[20];
	snprintf(buf, sizeof(buf), "%lld", delay);
	akm8963_sysfs_delay_store(s_akm, buf, strlen(buf), MAG_DATA_FLAG);
	return true;
}

/***** Orientation ***/
static ssize_t akm8963_delay_ori_show(
	struct device *dev, struct device_attribute *attr, char *buf)
{
	return akm8963_sysfs_delay_show(
		s_akm, buf, ORI_DATA_FLAG);
}
static ssize_t akm8963_delay_ori_store(
	struct device *dev, struct device_attribute *attr,
	char const *buf, size_t count)
{
	return akm8963_sysfs_delay_store(
		s_akm, buf, count, ORI_DATA_FLAG);
}


/***** accel (binary) ***/
static ssize_t akm8963_bin_accel_write(
	struct file *file,
	struct kobject *kobj,
	struct bin_attribute *attr,
			char *buf,
			loff_t pos,
			size_t size)
{
	struct akm8963_data *akm = s_akm;
	int16_t *accel_data;

	if (size == 0)
		return 0;

	accel_data = (int16_t*)buf;

	mutex_lock(&akm->accel_mutex);
	akm->accel_data[0] = accel_data[0];
	akm->accel_data[1] = accel_data[1];
	akm->accel_data[2] = accel_data[2];
	mutex_unlock(&akm->accel_mutex);

	return size;
}


#ifdef AKM8963_DEBUG_IF
static ssize_t akm8963_mode_store(
	struct device *dev, struct device_attribute *attr,
	char const *buf, size_t count)
{
	struct akm8963_data *akm = s_akm;
	int mode = 0;

	if (NULL == buf)
		return -EINVAL;

	if (0 == count)
		return 0;

	if (false == get_value_as_int(buf, count, &mode))
		return -EINVAL;

	if (AKECS_SetMode(akm, mode) < 0)
		return -EINVAL;

	return 1;
}

static ssize_t akm8963_bdata_show(
	struct device *dev, struct device_attribute *attr, char *buf)
{
	struct akm8963_data *akm = s_akm;
	char rbuf[SENSOR_DATA_SIZE];

	mutex_lock(&akm->sensor_mutex);
	memcpy(&rbuf, akm->sense_data, sizeof(rbuf));
	mutex_unlock(&akm->sensor_mutex);

	return sprintf(buf,
		"0x%02X,0x%02X,0x%02X,0x%02X,"
		"0x%02X,0x%02X,0x%02X,0x%02X\n",
		rbuf[0],rbuf[1],rbuf[2],rbuf[3],
		rbuf[4],rbuf[5],rbuf[6],rbuf[7]);
}

static ssize_t akm8963_asa_show(
	struct device *dev, struct device_attribute *attr, char *buf)
{
	struct akm8963_data *akm = s_akm;
	int err;
	unsigned char asa[3];

	err = AKECS_SetMode(akm, AK8963_MODE_FUSE_ACCESS);
	if (err < 0)
		return err;

	asa[0] = AK8963_FUSE_ASAX;
	err = akm8963_i2c_rxdata(akm->i2c, asa, 3);
	if (err < 0)
		return err;

	err = AKECS_SetMode(akm, AK8963_MODE_POWERDOWN);
	if (err < 0)
		return err;

	return sprintf(buf, "0x%02X,0x%02X,0x%02X\n",
		asa[0], asa[1], asa[2]);
}
#endif

static struct device_attribute akm8963_attributes[] = {
	__ATTR(enable_acc, 0660, akm8963_enable_acc_show, akm8963_enable_acc_store),
	__ATTR(enable_ori, 0660, akm8963_enable_ori_show, akm8963_enable_ori_store),
	__ATTR(delay_acc,  0660, akm8963_delay_acc_show,  akm8963_delay_acc_store),
	__ATTR(delay_ori,  0660, akm8963_delay_ori_show,  akm8963_delay_ori_store),
#ifdef AKM8963_DEBUG_IF
	__ATTR(mode,  0220, NULL, akm8963_mode_store),
	__ATTR(bdata, 0440, akm8963_bdata_show, NULL),
	__ATTR(asa,   0440, akm8963_asa_show, NULL),
#endif
	__ATTR_NULL,
};

#define __BIN_ATTR_NULL \
	{ \
		.attr   = { .name = NULL }, \
	}

static struct bin_attribute akm8963_bin_attributes[] = {
	__BIN_ATTR(accel, 0220, 6, NULL, NULL, akm8963_bin_accel_write),
	__BIN_ATTR_NULL
};

static char const *const compass_class_name = "compass";
/*++ Huize - 20120329 Add for naming general ++*/
static char const *const akm8963_device_name = "magnetic";
/*-- Huize - 20120329 Add for naming general --*/
static char const *const device_link_name = "i2c";
static dev_t const akm8963_device_dev_t = MKDEV(MISC_MAJOR, 240);

/***** akm input device functions ***********************************/
static int akm8963_input_init(
	struct input_dev **input)
{
	int err = 0;

	/* Declare input device */
	*input = input_allocate_device();
	if (!*input)
		return -ENOMEM;

	/* Setup input device */
	set_bit(EV_ABS, (*input)->evbit);
	/* Accelerometer (720 x 16G)*/
	input_set_abs_params(*input, ABS_X,
			-11520, 11520, 0, 0);
	input_set_abs_params(*input, ABS_Y,
			-11520, 11520, 0, 0);
	input_set_abs_params(*input, ABS_Z,
			-11520, 11520, 0, 0);
	input_set_abs_params(*input, ABS_THROTTLE,
			0, 3, 0, 0);
	/* Magnetic field (-81900, 81900) -> limited to 16bit*/
	input_set_abs_params(*input, ABS_RX,
			-32768, 32767, 0, 0);
	input_set_abs_params(*input, ABS_RY,
			-32768, 32767, 0, 0);
	input_set_abs_params(*input, ABS_RZ,
			-32768, 32767, 0, 0);
	input_set_abs_params(*input, ABS_RUDDER,
			0, 3, 0, 0);
	/* Orientation (yaw:0,360 pitch:-180,180 roll:-90,90) */
	input_set_abs_params(*input, ABS_HAT0X,
			0, 23040, 0, 0);
	input_set_abs_params(*input, ABS_HAT0Y,
			-11520, 11520, 0, 0);
	input_set_abs_params(*input, ABS_HAT1X,
			-5760, 5760, 0, 0);
	input_set_abs_params(*input, ABS_HAT1Y,
			0, 3, 0, 0);

	/* Set name */
	(*input)->name = "compass";

	/* Register */
	err = input_register_device(*input);
	if (err) {
		input_free_device(*input);
		return err;
	}

	return err;
}

/***** akm functions ************************************************/

static irqreturn_t akm8963_irq(int irq, void *handle)
{
	struct akm8963_data *akm = handle;
	char buffer[SENSOR_DATA_SIZE];
	int err;

	memset(buffer, 0, sizeof(buffer));
	buffer[0] = AK8963_REG_ST1;
	err = akm8963_i2c_rxdata(akm->i2c, buffer, SENSOR_DATA_SIZE);
	if (err < 0) {
		sDump_err(MAGNETIC.debugLevel, "%s failed.\n", __func__);
		goto work_func_end;
	}
	/* Check ST bit */
	if ((buffer[0] & 0x01) != 0x01) {
		sDump_err(MAGNETIC.debugLevel, "%s ST is not set.\n", __func__);
		goto work_func_end;
	}

	mutex_lock(&akm->sensor_mutex);
	memcpy(akm->sense_data, buffer, SENSOR_DATA_SIZE);
	mutex_unlock(&akm->sensor_mutex);

	atomic_set(&akm->drdy, 1);
	atomic_set(&akm->is_busy, 0);
	wake_up(&akm->drdy_wq);

work_func_end:
	return IRQ_HANDLED;
}

static void akm8963_delayed_work(struct work_struct *work)
{
	struct akm8963_data *akm = container_of(
		work, struct akm8963_data, work.work);

	akm8963_irq(akm->irq, akm);
}

static int akm8963_suspend(struct device *dev)
{
	sDump_debug(MAGNETIC.debugLevel, "suspended\n");

	return 0;
}

static int akm8963_resume(struct device *dev)
{
	sDump_debug(MAGNETIC.debugLevel, "resumed\n");

	return 0;
}

static bool akm8963_setPower(struct device* dev, bool enable)
{
	int rc = 0;
	
	if(!s_akm) return false;
	if(enable == false) goto disable;

	rc = min(regulator_set_optimum_mode(s_akm->vdd, 15000), 
			regulator_set_optimum_mode(s_akm->vdd_i2c, 15000));
	if (rc < 0) {
		pr_err("Regulator vcc_ana set_opt failed rc = %d\n", rc);
		return false;
	}

	rc = regulator_enable(s_akm->vdd);
	rc |= regulator_enable(s_akm->vdd_i2c);
	if(rc){
		pr_err("Regulator vcc_ana enable failed rc=%d\n", rc);
		goto error_reg_en_vcc_ana;
	}

	usleep(30000);
	return true;

error_reg_en_vcc_ana:
	regulator_set_optimum_mode(s_akm->vdd, 0);
	regulator_set_optimum_mode(s_akm->vdd_i2c, 0);
	return false;

disable:
	regulator_set_optimum_mode(s_akm->vdd, 0);
	regulator_set_optimum_mode(s_akm->vdd_i2c, 0);
	if(s_akm->vdd)
		regulator_disable(s_akm->vdd);
	if(s_akm->vdd_i2c)
		regulator_disable(s_akm->vdd_i2c);
	s_akm->vdd= s_akm->vdd_i2c = NULL;
	return true;
}

static bool akm8963_powerSetting(struct device* dev, bool enable)
{
	int rc = 0;
	if(enable == false) goto disable;

	s_akm->vdd = regulator_get(dev, "vdd_ana");
	if(IS_ERR(s_akm->vdd)){
		pr_err("Regulator get failed vdd_ana rc = %ld\n", PTR_ERR(s_akm->vdd));
		s_akm->vdd = s_akm->vdd_i2c = NULL;
		return false;
	}

	s_akm->vdd_i2c = regulator_get(dev, "vcc_i2c");
	if(IS_ERR(s_akm->vdd_i2c)){
		pr_err("Regulator get failed vcc_i2c rc = %ld\n", PTR_ERR(s_akm->vdd_i2c));
		regulator_put(s_akm->vdd);
		s_akm->vdd = s_akm->vdd_i2c = NULL;
		return false;
	}

	rc = min(regulator_count_voltages(s_akm->vdd), 
		regulator_count_voltages(s_akm->vdd_i2c));
	if(rc < 0){
		pr_err("regulator count_vtg failed rc = %d\n", rc);
		goto error_count_vtg;
	}
	
	rc = regulator_set_voltage(s_akm->vdd, 2850000, 2850000);
	rc |= regulator_set_voltage(s_akm->vdd_i2c, 1800000, 1800000);
	if(rc){
		pr_err("regulator set_vtg failed rc = %d\n", rc);
		goto error_set_vtg;
	}
	return true;

error_set_vtg:
error_count_vtg:
	regulator_put(s_akm->vdd_i2c);
	regulator_put(s_akm->vdd);
	s_akm->vdd = s_akm->vdd_i2c = NULL;
	return false;
disable:
	if(!s_akm->vdd_i2c){
		if(regulator_count_voltages(s_akm->vdd_i2c) > 0){
			regulator_set_voltage(s_akm->vdd_i2c, 0, 1800000);
		}
		regulator_put(s_akm->vdd_i2c);
	}
	if(!s_akm->vdd){
		if(regulator_count_voltages(s_akm->vdd) > 0){
			regulator_set_voltage(s_akm->vdd, 0, 3300000);
		}
		regulator_put(s_akm->vdd);;
	}
	s_akm->vdd = s_akm->vdd_i2c = NULL;
	return true;
}

int akm8963_interrupt_request(void){
	int irq = 0;
	gpio_tlmm_config(GPIO_CFG(AKM8963_IRQ, 0, GPIO_CFG_INPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	if(gpio_request(AKM8963_IRQ, "akm8963_irq") != 0){
		sDump_err(MAGNETIC.debugLevel,"%s: requset failed.\n", __func__);
		return 0;
	}

	if(gpio_direction_input(AKM8963_IRQ) < 0){
		sDump_alert(MAGNETIC.debugLevel, "%s failed to config the interrupt pin\n", __func__);
		gpio_free(AKM8963_IRQ);
		return 0;
	}

	irq = gpio_to_irq(AKM8963_IRQ);
	if(irq < 0){
		sDump_err(MAGNETIC.debugLevel, "%s gpio to irq failed\n", __func__);
		gpio_free(AKM8963_IRQ);
		return 0;
	}

	if(request_threaded_irq(irq, NULL,
			akm8963_irq, IRQF_TRIGGER_HIGH | IRQF_ONESHOT,
			dev_name(&s_akm->i2c->dev) , s_akm) < 0){
		sDump_err(MAGNETIC.debugLevel, "%s: request irq failed.\n", __func__);
		gpio_free(AKM8963_IRQ);
		return 0;
	}
	return irq;
}

int akm8963_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct akm8963_platform_data *pdata;
	int err = 0;
	int i;
	sDump_debug(MAGNETIC.debugLevel, "start probing.");

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		sDump_err(MAGNETIC.debugLevel, "%s: check_functionality failed.\n", __func__);
		err = -ENODEV;
		goto exit0;
	}

	/* Allocate memory for driver data */
	s_akm = kzalloc(sizeof(struct akm8963_data), GFP_KERNEL);
	if (!s_akm) {
		sDump_err(MAGNETIC.debugLevel, "%s: memory allocation failed.\n", __func__);
		err = -ENOMEM;
		goto exit0;
	}

	if(akm8963_powerSetting(&client->dev, true) == false){
		sDump_err(MAGNETIC.debugLevel, "%s power setting failed\n", __func__);
		goto exit1;
	}
	if(akm8963_setPower(&client->dev, true) == false){
		sDump_err(MAGNETIC.debugLevel, "%s enabled power failed\n", __func__);
		goto exit2;
	}

	/***** Set layout information *****/
	pdata = client->dev.platform_data;
	if (pdata) {
		/* Platform data is available. copy its value to local. */
		s_akm->layout = pdata->layout;
		s_akm->outbit = pdata->outbit;
		s_akm->rstn = pdata->gpio_RST;
	} else {
		/* Platform data is not available.
		   Layout and Outbit information should be set by each application. */
		sDump_debug(MAGNETIC.debugLevel, "%s: No platform data.\n", __func__);
		s_akm->layout = 0;
		s_akm->outbit = 0;
		s_akm->rstn = 0;
	}

    /***** Set Reset ***************/
	s_akm->rstn = AKM8963_RSTN;
	if(gpio_request(s_akm->rstn, "AKM8963_RESET")){
		sDump_debug(MAGNETIC.debugLevel, "%s: s_akm->rstn Fail !\n", __func__);
		goto exit3;
	}	

	if(gpio_tlmm_config(GPIO_CFG(s_akm->rstn, 0, GPIO_CFG_OUTPUT,
			GPIO_CFG_NO_PULL, GPIO_CFG_2MA), GPIO_CFG_ENABLE)){
			sDump_debug(MAGNETIC.debugLevel, "%s: s_akm->rstn Config Fail !\n", __func__);
		goto exit4;
	}

    gpio_set_value(s_akm->rstn, 1);
	usleep(10000);

	/***** I2C initialization *****/
	s_akm->i2c = client;
	/* check connection */
	err = akm8963_i2c_check_device(client);
	if (err < 0)
		goto exit4;
	/* set client data */
	i2c_set_clientdata(client, s_akm);

	/***** input *****/
	err = akm8963_input_init(&s_akm->input);
	if (err) {
		sDump_err(MAGNETIC.debugLevel,
			"%s: input_dev register failed\n", __func__);
		goto exit4;
	}
	input_set_drvdata(s_akm->input, s_akm);

	/**** initialize variables in akm8963_data *****/
	init_waitqueue_head(&s_akm->drdy_wq);
	init_waitqueue_head(&s_akm->open_wq);

	mutex_init(&s_akm->sensor_mutex);
	mutex_init(&s_akm->accel_mutex);
	mutex_init(&s_akm->val_mutex);

	atomic_set(&s_akm->active, 0);
	atomic_set(&s_akm->is_busy, 0);
	atomic_set(&s_akm->drdy, 0);
	atomic_set(&s_akm->suspend, 0);

	s_akm->enable_flag = 0;
	for (i=0; i<AKM_NUM_SENSORS; i++)
		s_akm->delay[i] = -1;

	/***** IRQ setup *****/
	s_akm->irq = client->irq = 0;
	#ifdef USE_IRQ
	s_akm->irq = client->irq = akm8963_interrupt_request();
	#endif

	if (s_akm->irq == 0) {
		sDump_debug(MAGNETIC.debugLevel, "%s: IRQ is not set.\n", __func__);
		/* Use timer to notify measurement end */
		INIT_DELAYED_WORK(&s_akm->work, akm8963_delayed_work);
	} 

	/***** misc *****/
	err = misc_register(&akm8963_dev);
	if (err) {
		sDump_err(MAGNETIC.debugLevel,
			"%s: akm8963_dev register failed\n", __func__);
		goto exit5;
	}

	/***** sysfs *****/
	err = sensor_device_register(&client->dev, &MAGNETIC);
	err |= create_device_attributes(
			MAGNETIC.dev,
			akm8963_attributes);
	err |= create_device_binary_attributes(
			&(MAGNETIC.dev->kobj),
			akm8963_bin_attributes);
	if (0 > err) {
		sDump_err(MAGNETIC.debugLevel,
			"%s: create sysfs failed.\n", __func__);
		goto exit6;
	}

	dev_info(&client->dev, "successfully probed.");
	return 0;

exit6:
	sensor_device_unregister(&MAGNETIC);
	misc_deregister(&akm8963_dev);
exit5:
	if(s_akm->irq){
		free_irq(s_akm->irq, s_akm);
		gpio_free(AKM8963_IRQ);
	}
	input_unregister_device(s_akm->input);
exit4:
	gpio_free(AKM8963_RSTN);
exit3:
exit2:
	akm8963_powerSetting(&client->dev, false);
exit1:
	kfree(s_akm);
exit0:
	return err;
}

static int akm8963_remove(struct i2c_client *client)
{
	struct akm8963_data *akm = i2c_get_clientdata(client);

	remove_device_binary_attributes(
			&(MAGNETIC.dev->kobj),
			akm8963_bin_attributes);
	remove_device_attributes(
			MAGNETIC.dev,
			akm8963_attributes);
	sensor_device_unregister(&MAGNETIC);
	if (misc_deregister(&akm8963_dev) < 0)
		sDump_err(MAGNETIC.debugLevel, "misc deregister failed.\n");
	if(akm->irq){
		free_irq(akm->irq, akm);
		gpio_free(AKM8963_IRQ);
	}
	input_unregister_device(akm->input);

	gpio_free(AKM8963_RSTN);
	akm8963_setPower(&client->dev, false);
	akm8963_powerSetting(&client->dev, false);

	kfree(akm);

	dev_info(&client->dev, "successfully removed.");
	return 0;
}

static const struct i2c_device_id akm8963_id[] = {
	{AKM8963_I2C_NAME, 0 },
	{ }
};

static const struct dev_pm_ops akm8963_pm_ops = {
	.suspend    = akm8963_suspend,
	.resume     = akm8963_resume,
};

#ifdef CONFIG_OF
static struct of_device_id match_table[] = {
	{ .compatible = "magnetic,akm8963",},
	{ },
};
#else
#define match_table NULL
#endif

static struct i2c_driver akm8963_driver = {
	.probe		= akm8963_probe,
	.remove 	= akm8963_remove,
	.id_table	= akm8963_id,
	.driver = {
		.name	= AKM8963_I2C_NAME,
		.pm		= &akm8963_pm_ops,
		.of_match_table = match_table,
	},
};

module_i2c_driver(akm8963_driver);

MODULE_AUTHOR("viral wang <viral_wang@htc.com>");
MODULE_DESCRIPTION("AKM8963 compass driver");
MODULE_LICENSE("GPL");

