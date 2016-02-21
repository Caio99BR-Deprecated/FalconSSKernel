/* Accelerometer-sensor
 *
 * Copyright (c) 2013-2014, HuizeWeng@Arimacomm Corp. All rights reserved.
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

#undef ACCELEROMETER_IRQ_USED
#define ACCELEROMETER_IRQ_USED

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/input.h>
#include <linux/mutex.h>
#include <linux/gpio.h>
#include <linux/i2c.h>
#include <linux/workqueue.h>
#include <linux/delay.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/ioctl.h>
#include <mach/vreg.h>
#include <linux/accelerometer_common.h>
#include <linux/log2.h>
#include <linux/random.h>

#define BMA250E_DRIVER_NAME "bma250e"
#define BMA250E_INTERRUPT 81

static u8 BMA250E_PMU_BW_CAMMAND;
static unsigned long originalTime;

#define	BMA250E_BGW_CHIPID			0X00
#define BMA250E_ACCD_X_LSB			0X02
#define BMA250E_ACCD_X_MSB			0X03
#define BMA250E_ACCD_Y_LSB			0X04
#define BMA250E_ACCD_Y_MSB			0X05
#define BMA250E_ACCD_Z_LSB			0X06
#define BMA250E_ACCD_Z_MSB			0X07
#define BMA250E_RESERVED			0X08
#define BMA250E_INT_STATUS_0		0X09
#define BMA250E_INT_STATUS_1		0X0A
#define BMA250E_INT_STATUS_2		0X0B
#define BMA250E_INT_STATUS_3		0X0C
#define BMA250E_FIFO_STATUS			0X0E
#define BMA250E_PMU_RANGE			0X0F
#define BMA250E_PMU_BW				0X10
#define BMA250E_PMU_LPW				0X11
#define BMA250E_PMU_LOW_NOISE		0X12
#define BMA250E_ACCD_HBW			0X13
#define BMA250E_BGW_SOFTRESET		0X14
#define BMA250E_INT_EN_0			0X16
#define BMA250E_INT_EN_1			0X17
#define BMA250E_INT_EN_2			0X18
#define BMA250E_INT_MAP_0			0X19
#define BMA250E_INT_MAP_1			0X1A
#define BMA250E_INT_MAP_2			0X1B
#define BMA250E_INT_SRC				0X1E
#define BMA250E_INT_OUT_CTRL		0X20
#define BMA250E_INT_RST_LATCH		0X21
#define BMA250E_INT_0				0X22
#define BMA250E_INT_1				0X23
#define BMA250E_INT_2				0X24
#define BMA250E_INT_3				0X25
#define BMA250E_INT_4				0X26
#define BMA250E_INT_5				0X27
#define BMA250E_INT_6				0X28
#define BMA250E_INT_7				0X29
#define BMA250E_INT_8				0X2A
#define BMA250E_INT_9				0X2B
#define BMA250E_INT_A				0X2C
#define BMA250E_INT_B				0X2D
#define BMA250E_INT_C				0X2E
#define BMA250E_INT_D				0X2F
#define BMA250E_FIFO_CONFIG_0		0X30
#define BMA250E_PMU_SELF_TEST		0X32
#define BMA250E_TRIM_NVM_CTRL		0X33
#define BMA250E_BGW_SPI3_WDT		0X34
#define BMA250E_OFC_CTRL			0X36
#define BMA250E_OFC_SETTING			0X37
#define BMA250E_OFC_OFFSET_X		0X38
#define BMA250E_OFC_OFFSET_Y		0X39
#define BMA250E_OFC_OFFSET_Z		0X3A
#define BMA250E_TRIM_GP0			0X3B
#define BMA250E_TRIM_GP1			0X3C
#define BMA250E_FIFO_CONFIG_1		0X3E
#define BMA250E_FIFO_DATA			0X3F

static bool bma250e_setActive(bool enable);
static bool bma250e_setDelay(s64 delay);
static bool bma250e_calibrate(Action action, void* buf, ssize_t size);
static void bma250e_dump(char* buf);

static struct device_infor infor = {
	.name		= "Accelerometer Sensor",
	.vendor		= "Bosch Sensortec",
	.maxRange	= 2,// 2G
	.resolution	= 512,// 2G / 512
	.power		= 139,// uA
	.minDelay	= 10000,
};

static sensor_device BMA250E = {
	.name = "accelerometer",
	.enable = false,
	.delay = -1,
	.debugLevel = 1,
	.setActive = bma250e_setActive,
	.setDelay = bma250e_setDelay,
	.calibrate = bma250e_calibrate,
	.internalDump = bma250e_dump,
	.infor = &infor,
};

/* ---------------------------------------------------------------------------------------- *
   Input device interface
 * ---------------------------------------------------------------------------------------- */

static void mailbox(const Package* const package)
{
	bool err = !strncmp(package->content, "ERROR", strlen("ERROR"));
	bool active = strncmp(package->content, "NOTACTIVE", strlen("NOTACTIVE"));
	Accelerometer* data = i2c_get_clientdata(this_client);
	if(!data){
		sDump_alert(BMA250E.debugLevel, "%s Accelerometer is NULL\n", __func__);
		return;
	}
	switch(package->category){
		case RGSensorOffset:
			if(!active){
				// Do reset.
				// It means that accelerometer axis offset
				// hasn't been setted yet.
				accelerometer_resetAxisOffset(0, 0, 0);
				break;
			}
		case WGSensorOffset:
			if(!err){
				mutex_lock(&data->mutex);
				memcpy(&(data->odata), package->content, sizeof(AccelerometerAxisOffset));
				mutex_unlock(&data->mutex);
			}
			sDump_notice(BMA250E.debugLevel, "Accelerometer AxisOffset ==> X : %d, Y : %d, Z : %d\n", data->odata.X, data->odata.Y, data->odata.Z);
			break;
		default:
			break;
	}
}

static deliverAddress address = {
	.name				= "AccelerometerSensor",
	.mailbox			= mailbox,
	.receivedCategory	= RGSensorOffset | WGSensorOffset,
};

#ifdef ACCELEROMETER_IRQ_USED
static irqreturn_t bma250e_irq(int irq, void* handle)
{
	Accelerometer* data = i2c_get_clientdata(this_client);
	sDump_debug(BMA250E.debugLevel, "%s ++\n", __func__);

	if(!data->suspend && data->enabled){
		data->irq_work = false;
		disable_irq_nosync(data->irq);
		if(WorkMode == SPECIAL_MODE){
			queueIndex = ignoreCount = 0;
			memset(queueData, 0, sizeof(queueData));
		}
		queue_delayed_work(Accelerometer_WorkQueue, &data->dw, 0);
	}

	sDump_debug(BMA250E.debugLevel, "%s --\n", __func__);
	return IRQ_HANDLED;
}

static void bma250e_enable_irq(Accelerometer* data)
{
	mutex_lock(&data->mutex);
	if(data->irq != -1 && !data->irq_work){
		enable_irq(data->irq);
		data->irq_work = true;
	}
	mutex_unlock(&data->mutex);
}

static void bma250e_interrupt_release(Accelerometer* data)
{
	if(data->irq != -1){
		// If use IRQ, interrupt may be triggered still.
		// Processing the last interrupt event
		flush_workqueue(Accelerometer_WorkQueue);
		// Enable IRQ, if irq's state was disabled.
		// Just to do IRQ balance
		bma250e_enable_irq(data);
		mutex_lock(&data->mutex);
		free_irq(data->irq, data);
		data->irq = -1;
		mutex_unlock(&data->mutex);
		gpio_free(BMA250E_INTERRUPT);
	}
}

static bool bma250e_interrupt_request(Accelerometer* data)
{
	int irq = -1;
	gpio_tlmm_config(GPIO_CFG(BMA250E_INTERRUPT, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_DOWN, GPIO_CFG_2MA), GPIO_CFG_ENABLE);
	if(gpio_request(BMA250E_INTERRUPT, "bma250e_gpio_request") != 0){
		sDump_alert(BMA250E.debugLevel, "%s failed to request gpio\n", __func__);
		return false;
	}
	if(gpio_direction_input(BMA250E_INTERRUPT) < 0){
		sDump_alert(BMA250E.debugLevel, "%s failed to config the interrupt pin\n", __func__);
		gpio_free(BMA250E_INTERRUPT);
		return false;
	}

	irq = gpio_to_irq(BMA250E_INTERRUPT);
	if(irq < 0){
		sDump_alert(BMA250E.debugLevel, "%s gpio to irq failed\n", __func__);
		gpio_free(BMA250E_INTERRUPT);
		return false;
	}

	if(request_irq(irq, bma250e_irq, IRQF_TRIGGER_RISING, "BMA250E_SENSOR", data) < 0){
		sDump_alert(BMA250E.debugLevel, "%s irq %d busy?\n", __func__, irq);
		gpio_free(BMA250E_INTERRUPT);
		return false;
	}

	mutex_lock(&data->mutex);
	data->irq = irq;
	mutex_unlock(&data->mutex);
	sDump_debug(BMA250E.debugLevel, "%s :request_irq finished\n", __func__);
	return true;
}

static void bma250e_interrupt_duration(unsigned long arg)
{
	switch(ilog2(arg))
	{
		case 3:
			POWER_MODE_CAMMAND = (arg > 10) ? 0X52 : 0X4C;
			BMA250E_PMU_BW_CAMMAND = 0X0B;// Setting Bandwith 62.5 HZ, updated time 8ms
		break;
		case 4:
			POWER_MODE_CAMMAND = (arg > 24) ? 0X54 : 0X4C;
			BMA250E_PMU_BW_CAMMAND = 0X0A;// Setting Bandwith 31.25 HZ, updated time 16ms
		break;
		case 5:
			POWER_MODE_CAMMAND = (arg > 48) ? 0X56 : 0X4C;
			BMA250E_PMU_BW_CAMMAND = 0X09;// Setting Bandwith 15.63 HZ, updated time 32ms
		break;
		case 6:
			POWER_MODE_CAMMAND = 0X00;
			BMA250E_PMU_BW_CAMMAND = 0X08;// Setting Bandwith 7.81 HZ, updated time 64ms
		break;
		case 14:
			WorkMode = SPECIAL_MODE;
			POWER_MODE_CAMMAND = 0X00;
			BMA250E_PMU_BW_CAMMAND = 0X0A;// Setting Bandwith 31.25 HZ, updated time 16ms
		break;
		default :
			WorkMode = NORMAL_MODE;
			bma250e_interrupt_release(i2c_get_clientdata(this_client));
		break;
	}
}

static int bma250e_irqSetting(u8 en0, u8 en1, u8 map0, u8 map1)
{
	int rc = 0;
	if(WorkMode == NORMAL_MODE) return rc;
	rc |= i2c_smbus_write_byte_data(this_client, BMA250E_INT_EN_0, en0);
	rc |= i2c_smbus_write_byte_data(this_client, BMA250E_INT_EN_1, en1);
	rc |= i2c_smbus_write_byte_data(this_client, BMA250E_INT_MAP_0, map0);
	rc |= i2c_smbus_write_byte_data(this_client, BMA250E_INT_MAP_1, map1);
	// Reset Interrupt
	rc |= i2c_smbus_write_byte_data(this_client, BMA250E_INT_RST_LATCH, 0X8B);
	return rc;
}
#endif

static int bma250e_type_setting(bool open)
{
	int rc = 0;
	queueIndex = ignoreCount = 0;
	memset(queueData, 0, sizeof(queueData));
	if(open){
		#ifdef ACCELEROMETER_IRQ_USED
		u8 irq_en[2] = {0, 0};
		u8 irq_map[2] = {0, 0};
		#endif
		// Setting Operation mode
		rc |= i2c_smbus_write_byte_data(this_client, BMA250E_PMU_LPW, POWER_MODE_CAMMAND);
		usleep(3500);
		// Setting bandwith
		rc |= i2c_smbus_write_byte_data(this_client, BMA250E_PMU_BW, BMA250E_PMU_BW_CAMMAND);
		#ifdef ACCELEROMETER_IRQ_USED
		switch(WorkMode){
			case SPECIAL_MODE:
				irq_en[0] = 0X47;
				irq_map[0] = 0X44;
				break;
			case INTERRUPT_MODE:
				irq_en[1] = 0X10;
				irq_map[1] = 0X01;
				break;
			default:
				break;
		}
		rc |= bma250e_irqSetting(irq_en[0], irq_en[1], irq_map[0], irq_map[1]);
		rc |= i2c_smbus_write_byte_data(this_client, BMA250E_INT_6, (WorkMode != SPECIAL_MODE) ? 0X14 : 0X02);
		#endif
	}else{
		// Setting Suspend mode
		rc |= i2c_smbus_write_byte_data(this_client, BMA250E_PMU_LPW, 0X80);
		#ifdef ACCELEROMETER_IRQ_USED
		rc |= bma250e_irqSetting(0, 0, 0, 0);
		usleep(3500);
		#endif
	}
	return rc;
}

static int bma250e_enable(void)
{
	int rc = 0;
	Accelerometer* data = i2c_get_clientdata(this_client);
	sDump_debug(BMA250E.debugLevel, "%s ++\n", __func__);

	if(data->enabled == false){
		bma250e_type_setting(true);
		mutex_lock(&data->mutex);
		data->enabled = true;
		mutex_unlock(&data->mutex);
		rc = 1;
	}

	(rc == 1 && WorkMode == NORMAL_MODE) ? queue_delayed_work(Accelerometer_WorkQueue, &data->dw, msecs_to_jiffies(10)) : -1;
	sDump_debug(BMA250E.debugLevel, "%s, rc : %d--\n", __func__, rc);
	return true;
}

static int bma250e_disable(void)
{
	int rc = 0;
	Accelerometer* data = i2c_get_clientdata(this_client);
	sDump_debug(BMA250E.debugLevel, "%s ++\n", __func__);

	if(data->enabled == true){
		mutex_lock(&data->mutex);
		data->enabled = false;
		mutex_unlock(&data->mutex);
		if(WorkMode == NORMAL_MODE){
			cancel_delayed_work_sync(&data->dw);
			flush_workqueue(Accelerometer_WorkQueue);
		}

		bma250e_type_setting(false);
		#ifdef ACCELEROMETER_IRQ_USED
		bma250e_interrupt_release(data);
		#endif

		WorkMode = NORMAL_MODE;
		SleepTime = msecs_to_jiffies(200);
		originalTime = 200;
		POWER_MODE_CAMMAND = 0X4C;// Sleep duration 1ms
		BMA250E_PMU_BW_CAMMAND = 0X0B;// Setting Bandwith 62.5 HZ, updated time 8ms
		rc = 1;
	}

	sDump_debug(BMA250E.debugLevel, "%s, rc : %d--\n", __func__, rc);
	return true;
}

static void bma250e_commandSet(Accelerometer* data, unsigned long time)
{
	WorkMode = NORMAL_MODE;// Mode will be changed, if it needs.
	#ifdef ACCELEROMETER_IRQ_USED
	if((time == 16384 || time < 70) && bma250e_interrupt_request(data) == true){
		WorkMode = INTERRUPT_MODE;// Irq is ready, change mode.
		bma250e_interrupt_duration(time);
	}
	#endif
	if(WorkMode == NORMAL_MODE){
		POWER_MODE_CAMMAND = 0X4C;// Lower power enable, sleep duration 1ms
		BMA250E_PMU_BW_CAMMAND = 0X0B;// Setting Bandwith 62.5 HZ, updated time 8ms
	}
	SleepTime = msecs_to_jiffies(time);
}

static bool bma250e_setActive(bool enable)
{
	return (enable) ? bma250e_enable() : bma250e_disable();
}

static bool bma250e_setDelay(s64 delay)
{
	Accelerometer* data = i2c_get_clientdata(this_client);
	bool enabled = data->enabled;
	sDump_debug(BMA250E.debugLevel, "%s ++\n", __func__);

	delay = (delay >= 10) ? delay : 10;
	(enabled) ? bma250e_disable() : 0;
	originalTime = delay;

	bma250e_commandSet(data, delay);
	(enabled) ? bma250e_enable() : 0;

	sDump_debug(BMA250E.debugLevel, "%s --\n", __func__);
	return true;
}

static bool bma250e_calibrate(Action action, void* buf, ssize_t size)
{
	bool sucessful = false;
	Sensor_Calibrate_Infor* inf = (Sensor_Calibrate_Infor *) buf;
	Accelerometer* data = i2c_get_clientdata(this_client);
	AccelerometerAxisOffset* offset = &(inf->a_axisoffset);

	switch(action){
		case Write:
		{
			switch(inf->job){
				case ACCELEROMETER_AXISOFFSET_SET:
					mutex_lock(&data->mutex);
					offset->X += data->odata.X;
					offset->Y += data->odata.Y;
					offset->Z += data->odata.Z;
					mutex_unlock(&data->mutex);
					sucessful = accelerometer_resetAxisOffset(offset->X, offset->Y, offset->Z);
					break;
				case ACCELEROMETER_AXISOFFSET_INIT_SET:
					sucessful = accelerometer_resetAxisOffset(0, 0, 0);
					break;
				default:
					break;
			}
			break;
		}
		default :
			break;
	}

	return sucessful;
}

static void bma250e_swReset(bool reStart, u16 gRange){
	sDump_err(BMA250E.debugLevel, "%s: reStart: %d, gRange: %d\n", __func__, reStart, gRange);
	bma250e_type_setting(false);
	accelerometer_readAxisOffset(0);
	i2c_smbus_write_byte_data(this_client, BMA250E_BGW_SOFTRESET, 0XB6);
	usleep(20000);
	// Setting Range
	i2c_smbus_write_byte_data(this_client, BMA250E_PMU_RANGE, gRange);
	usleep(10000);
	bma250e_type_setting(reStart);
}

// Return true if data ready to report
static bool bma250e_readData(void){
	memset(i2cData, 0, sizeof(i2cData));
	memset(&rawData, 0, sizeof(AccelerometerData));
	if(i2c_smbus_read_i2c_block_data(this_client, BMA250E_ACCD_X_LSB, 6, &i2cData[0]) != 6){
		bma250e_swReset(true, 0x03);
		return false;
	}
	rawData.Y = (i2cData[1] < 128) ? i2cData[1] : (i2cData[1] - 256);
	rawData.Y = ((rawData.Y << 2) + (i2cData[0] >> 6)) * 10000 >> 8;
	rawData.X = (i2cData[3] < 128) ? i2cData[3] : (i2cData[3] - 256);
	rawData.X = ((rawData.X << 2) + (i2cData[2] >> 6)) * 10000 >> 8;
	rawData.Z = (i2cData[5] < 128) ? i2cData[5] : (i2cData[5] - 256);
	rawData.Z = ((rawData.Z << 2) + (i2cData[4] >> 6)) * 10000 >> 8;
	memcpy(&(queueData[queueIndex]), &rawData, sizeof(AccelerometerData));
	queueIndex = (queueIndex < FILTER_INDEX) ? queueIndex + 1 : 0;
	ignoreCount = (ignoreCount < FILTER_SIZE) ? ignoreCount + 1 : FILTER_SIZE;
	#ifdef ACCELEROMETER_IRQ_USED
	if(WorkMode == SPECIAL_MODE){
		while(queueIndex <= FILTER_INDEX){
			memcpy(&(queueData[queueIndex]), &rawData, sizeof(AccelerometerData));
			++queueIndex;
		}
		ignoreCount = FILTER_SIZE;
		queueIndex = 0;
	}
	#endif
	return (ignoreCount == FILTER_SIZE);
}

static void bma250e_reportData(Accelerometer* data){
	u8 i = 0;
	memset(&averageData, 0, sizeof(AccelerometerData));
	for( ; i < FILTER_SIZE ; ++i){
		averageData.X += queueData[i].X >> FILTER_SIZEBIT;
		averageData.Y += queueData[i].Y >> FILTER_SIZEBIT;
		averageData.Z += queueData[i].Z >> FILTER_SIZEBIT;
	}
	mutex_lock(&data->mutex);
	averageData.Z += (random32() & 1);
	memcpy(&(data->sdata), &averageData, sizeof(AccelerometerData));
	mutex_unlock(&data->mutex);
	input_report_abs(data->input, ABS_X, data->sdata.X - data->odata.X);
	input_report_abs(data->input, ABS_Y, data->sdata.Y - data->odata.Y);
	input_report_abs(data->input, ABS_Z, (0 - data->sdata.Z) - data->odata.Z);
	input_sync(data->input);
	sDump_info(BMA250E.debugLevel, "%s X: %d, Y: %d, Z: %d\n", __func__, data->sdata.X, data->sdata.Y, data->sdata.Z);
}

static void bma250e_work_func(struct work_struct* work)
{
	Accelerometer* data = i2c_get_clientdata(this_client);
	sDump_debug(BMA250E.debugLevel, "%s ++\n", __func__);

	if(data->suspend){
		sDump_warn(BMA250E.debugLevel, "%s system had been suspend\n", __func__);
	}

	if(data->enabled && bma250e_readData()){
		bma250e_reportData(data);
	}

	switch(WorkMode){
		case NORMAL_MODE:
			(data->enabled && !data->suspend) ?
			queue_delayed_work(Accelerometer_WorkQueue, &data->dw, SleepTime) : -1;
			break;
		#ifdef ACCELEROMETER_IRQ_USED
		case SPECIAL_MODE:
		case INTERRUPT_MODE:
			bma250e_enable_irq(data);
			break;
		#endif
	}

	sDump_debug(BMA250E.debugLevel, "%s --\n", __func__);
}

static void bma250e_dump(char* buf)
{
	Accelerometer* data = i2c_get_clientdata(this_client);
	snprintf(buf, 32, "%s\n", __func__);
	snprintf(buf + strlen(buf), 32, "enable : %u \n", data->enabled);
	snprintf(buf + strlen(buf), 32, "suspend : %u \n", data->suspend);
	#ifdef ACCELEROMETER_IRQ_USED
	snprintf(buf + strlen(buf), 32, "irq : %d \n", data->irq);
	snprintf(buf + strlen(buf), 32, "irq_work : %d \n", data->irq_work);
	#endif
	snprintf(buf + strlen(buf), 32, "originalTime : %lu \n", originalTime);
	snprintf(buf + strlen(buf), 32, "SleepTime : %u \n", jiffies_to_msecs(SleepTime));
	snprintf(buf + strlen(buf), 32, "WorkMode : %u \n", WorkMode);
	snprintf(buf + strlen(buf), 32, "queueIndex : %u\n", queueIndex);
	snprintf(buf + strlen(buf), 32, "ignoreCount : %u \n", ignoreCount);
	snprintf(buf + strlen(buf), 32, "POWER_MODE_CAMMAND : %u \n", POWER_MODE_CAMMAND);
	snprintf(buf + strlen(buf), 32, "BMA250E_PMU_BW_CAMMAND : %u \n", BMA250E_PMU_BW_CAMMAND);
}

static int bma250e_suspend(struct i2c_client* client, pm_message_t state)
{
	Accelerometer* data = i2c_get_clientdata(client);
	sDump_debug(BMA250E.debugLevel, "%s ++\n", __func__);

	mutex_lock(&data->mutex);
	data->suspend = true;
	mutex_unlock(&data->mutex);
	if(WorkMode == NORMAL_MODE){
		cancel_delayed_work_sync(&data->dw);
		flush_workqueue(Accelerometer_WorkQueue);
	}

	if(data->enabled){
		bma250e_type_setting(false);
		#ifdef ACCELEROMETER_IRQ_USED
		bma250e_interrupt_release(data);
		#endif
	}

	sDump_debug(BMA250E.debugLevel, "%s --\n", __func__);
	return 0;// It needs to return 0, non-zero means has fault.
}

static int bma250e_resume(struct i2c_client* client)
{
	Accelerometer* data = i2c_get_clientdata(client);
	sDump_debug(BMA250E.debugLevel, "%s ++\n", __func__);

	cancel_delayed_work_sync(&data->dw);
	mutex_lock(&data->mutex);
	data->suspend = false;
	mutex_unlock(&data->mutex);

	if(data->enabled){
		bma250e_commandSet(data, originalTime);
		bma250e_type_setting(true);
		(WorkMode == NORMAL_MODE) ? queue_delayed_work(Accelerometer_WorkQueue, &data->dw, SleepTime) : -1;
	}

	sDump_debug(BMA250E.debugLevel, "%s --\n", __func__);
	return 0;// It needs to return 0, non-zero means has fault.
}

static int bma250e_probe(struct i2c_client* client, const struct i2c_device_id* id)
{
	Accelerometer* Sensor = NULL;
	struct input_dev* input_dev = NULL;
	int err = 0;
	sDump_debug(BMA250E.debugLevel, "%s ++\n", __func__);

	usleep(10000);

	if(!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_READ_WORD_DATA)){
		return -EIO;
	}

	if((err = i2c_smbus_read_byte_data(client, BMA250E_BGW_CHIPID)) != 0XF9){
		sDump_err(BMA250E.debugLevel, "BMA250E_BGW_CHIPID value = %d\n", err);
		return -ENODEV;
	}

	Sensor = kzalloc(sizeof(Accelerometer), GFP_KERNEL);

	input_dev = input_allocate_device();

	if(!Sensor || !input_dev){
		err = -ENOMEM;
		goto err_free_mem;
	}

	INIT_DELAYED_WORK(&Sensor->dw, bma250e_work_func);
	i2c_set_clientdata(client, Sensor);

	input_dev->name = "accelerometer";
	input_dev->id.bustype = BUS_I2C;

	input_set_capability(input_dev, EV_ABS, ABS_MISC);
	input_set_abs_params(input_dev, ABS_X, -5120000, 5120000, 0, 0);
	input_set_abs_params(input_dev, ABS_Y, -5120000, 5120000, 0, 0);
	input_set_abs_params(input_dev, ABS_Z, -5120000, 5120000, 0, 0);
	input_set_drvdata(input_dev, Sensor);

	err = input_register_device(input_dev);
	if(err){
		sDump_alert(BMA250E.debugLevel, "%s : input_register_device error\n", __func__);
		goto err_free_mem;
	}

	// Setting Range +/- 2G
	i2c_smbus_write_byte_data(client, BMA250E_PMU_RANGE, 0X03);
	// Setting Suspend mode
	i2c_smbus_write_byte_data(client, BMA250E_PMU_LPW, 0X80);

	#ifdef ACCELEROMETER_IRQ_USED
	Sensor->irq			= -1;
	Sensor->irq_work	= false;
	#endif
	Sensor->input		= input_dev;

	mutex_init(&Sensor->mutex);

	this_client = client;
	Accelerometer_WorkQueue = create_singlethread_workqueue(input_dev->name);
	SleepTime = msecs_to_jiffies(200);
	originalTime = 200;

	POWER_MODE_CAMMAND = 0X4C;// Lower power enable, sleep duration 1ms
	BMA250E_PMU_BW_CAMMAND = 0X0B;// Setting Bandwith 62.5 HZ, updated time 8ms
	WorkMode = NORMAL_MODE;

	if(sensor_device_register(&client->dev, &BMA250E))
		goto err;

	postoffice_registerAddress(&address);
	accelerometer_readAxisOffset(20000);

	sDump_debug(BMA250E.debugLevel, "%s --\n", __func__);
	return 0;

	err:
		sensor_device_unregister(&BMA250E);
		input_unregister_device(input_dev);
		input_dev = NULL;
	err_free_mem:
		if(input_dev != NULL)
			input_free_device(input_dev);
		kfree(Sensor);
	return err;
}

static int bma250e_remove(struct i2c_client* client)
{
	Accelerometer* data = i2c_get_clientdata(client);

	bma250e_disable();
	destroy_workqueue(Accelerometer_WorkQueue);
	postoffice_unregisterAddress(&address);
	sensor_device_unregister(&BMA250E);
	input_unregister_device(data->input);
	kfree(data);

	return 0;
}

static void bma250e_shutdown(struct i2c_client* client)
{
	bma250e_disable();
}

static struct i2c_device_id bma250e_idtable[] = {
	{"bma250e", 0 },
	{ }
};

MODULE_DEVICE_TABLE(i2c, bma250e_idtable);

#ifdef CONFIG_OF
static struct of_device_id match_table[] = {
	{ .compatible = "accelerometer,bma250e",},
	{ },
};
#else
#define match_table NULL
#endif

static struct i2c_driver bma250e_driver = {
	.driver = {
		.owner	= THIS_MODULE,
		.name	= BMA250E_DRIVER_NAME,
		.of_match_table = match_table,
	},
	.id_table	= bma250e_idtable,
	.probe		= bma250e_probe,
	.remove		= bma250e_remove,
	.suspend  	= bma250e_suspend,
	.resume   	= bma250e_resume,
	.shutdown	= bma250e_shutdown,
};

module_i2c_driver(bma250e_driver);

MODULE_AUTHOR("HuizeWeng@Arimacomm");
MODULE_DESCRIPTION("Accelerometer Sensor BMA250E");
MODULE_LICENSE("GPLv2");
