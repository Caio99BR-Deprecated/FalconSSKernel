/* Proximity / Light Sensor
 *
 * Copyright (c) 2013-2014, HuizeWeng@Arimacomm Crop. All rights reserved.
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
#include <linux/pls_common.h>
#include <linux/random.h>
#include <linux/math64.h>

#define EPL6881_DRIVER_NAME "epl6881"

#define THRESHOLD_LEVEL 380
#define THRESHOLD_RANGE (THRESHOLD_LEVEL << 1)

enum{
	PLSENSOR_REG_COMMANDI			= 0x00 << 3,
	PLSENSOR_REG_COMMANDII			= 0x01 << 3,
	PLSENSOR_REG_INT_HT_LSB			= 0x02 << 3,
	PLSENSOR_REG_INT_HT_MSB			= 0x03 << 3,
	PLSENSOR_REG_INT_LT_LSB			= 0x04 << 3,
	PLSENSOR_REG_INT_LT_MSB			= 0x05 << 3,
	PLSENSOR_REG_THRESHOLD_LIMIT	= 0x06 << 3,
	PLSENSOR_REG_CONTROL_SETTINGI	= 0x07 << 3,
	PLSENSOR_REG_CONTROL_SETTINGII	= 0x09 << 3,
	PLSENSOR_REG_GOMID_SETTING		= 0x0A << 3,
	PLSENSOR_REG_GOLOW_SETTING		= 0x0B << 3,
	PLSENSOR_REG_CHIP_STATE			= 0x0D << 3,
	PLSENSOR_REG_CH0DATA_LSB		= 0x0E << 3,
	PLSENSOR_REG_CH0DATA_MSB		= 0x0F << 3,
	PLSENSOR_REG_CH1DATA_LSB		= 0x10 << 3,
	PLSENSOR_REG_CH1DATA_MSB		= 0x11 << 3,
	PLSENSOR_REG_REVISIONCODE_LSB	= 0x13 << 3,
	PLSENSOR_REG_REVISIONCODE_MSB	= 0x14 << 3,
};

static bool proximity_setActive(bool);
static bool proximity_calibrate(Action, void*, ssize_t);
static void proximity_dump(char* buf);
static bool light_setActive(bool);
static bool light_calibrate(Action, void*, ssize_t);
static bool light_setDelay(s64 delay);
static void light_dump(char* buf);

static struct device_infor infor[] = {
	{
		.name		= "Proximity Sensor",
		.vendor		= "ELAN Microelectronics Corp.",
		.maxRange	= PROXIMITY_UNDETECTED,
		.resolution	= PROXIMITY_UNDETECTED - PROXIMITY_DETECTED,//
		.power		= 350,// uA
		.minDelay	= 0,
	},
	{
		.name		= "Light Sensor",
		.vendor		= "ELAN Microelectronics Corp.",
		.maxRange	= 25000,
		.resolution	= 1024,// 25000 / 1024
		.power		= 350,// uA
		.minDelay	= 150,
	},
};

static sensor_device p_dev = {
	.name = "proximity",
	.debugLevel = 1,
	.enable = false,
	.delay = 0L,
	.setActive = proximity_setActive,
	.setDelay = NULL,
	.calibrate = proximity_calibrate,
	.internalDump = proximity_dump,
	.infor = &infor[0],
};

static sensor_device l_dev = {
	.name = "light",
	.debugLevel = 1,
	.enable = false,
	.delay = 0L,
	.setActive = light_setActive,
	.setDelay = light_setDelay,
	.calibrate = light_calibrate,
	.internalDump = light_dump,
	.infor = &infor[1],
};

// Dynamic stability threshold
#define DST_FILTER	4
#define DST_IGNORE	DST_FILTER << 2
int dstMinValue = DEFAULT_THRESHOLD;
u8 dstCount = 0;
int autoMinValue = DEFAULT_THRESHOLD;

/* ---------------------------------------------------------------------------------------- *
   Input device interface
 * ---------------------------------------------------------------------------------------- */

static void mailbox(const Package* const package)
{
	bool err = !strncmp(package->content, "ERROR", strlen("ERROR"));
	bool active = strncmp(package->content, "NOTACTIVE", strlen("NOTACTIVE"));
	PLSensor* data = i2c_get_clientdata(this_client);
	Light* light = (data) ? &data->light: NULL;
	if(!light){
		sDump_alert(l_dev.debugLevel, "%s Light is NULL\n", __func__);
		return;
	}
	switch(package->category){
		case RLSensorConst:
			if(!active){
				light_resetConst(DEFAULT_LIGHT_CONST);
				break;
			}
		case WLSensorConst:
			if(!err){
				mutex_lock(&data->mutex);
				memcpy(&(light->sdata.Const), package->content, sizeof(int));
				mutex_unlock(&data->mutex);
			}
			sDump_notice(l_dev.debugLevel, "Light Const : %d\n", light->sdata.Const);
			break;
		default:
			break;
	}
}

static deliverAddress address = {
	.name				= "PLsensor",
	.mailbox			= mailbox,
	.receivedCategory	= RLSensorConst | WLSensorConst,
};

static bool epl6881_setSleepTime(void)
{
	PLSensor* data = i2c_get_clientdata(this_client);
	Proximity* prox = &data->proximity;
	Light* light = &data->light;
	u16 workTime = 4 * prox->enabled + 8 * light->enabled;

	if(prox->enabled || light->enabled){
		LisReady = PisReady = false;
		Lneed2Reset = Pneed2Reset = false;
		Pneed2ChangeState = false;
		LignoreCount = 0;
		switch(workTime){
			case 4:
				SleepTime = msecs_to_jiffies(150 - 40);
				break;
			case 8:
				SleepTime = msecs_to_jiffies(light->delay - 90);
				break;
			case 12:
				light->ignorecount = div_s64(light->delay, 150);
				--light->ignorecount;
				// Proximity woring time : 40 msecs
				// Light working time : 90 msecs
				SleepTime = msecs_to_jiffies(20);
				break;
			default:
				return false;
		}
	}else{
		SleepTime = msecs_to_jiffies(150);
	}
	return true;
}

static int epl6881_enable(WorkType wType)
{
	int rc = 0;
	PLSensor* data = i2c_get_clientdata(this_client);
	Proximity* prox = &data->proximity;
	Light* light = &data->light;
	sDump_debug(max(p_dev.debugLevel, l_dev.debugLevel), "%s ++\n", __func__);

	// Stop all work
	atomic_set(&data->flushqueue, 1);
	cancel_delayed_work_sync(&data->dw2);
	cancel_delayed_work_sync(&data->dw);
	flush_workqueue(PLSensor_WorkQueue);

	switch(wType){
		case PROXIMITY:
			if(prox->enabled == false){
				mutex_lock(&data->mutex);
				prox->enabled = true;
				prox->sdata.Value = -1;
				prox->sdata.State = PROXIMITY_STATE_UNKNOWN;
				mutex_unlock(&data->mutex);
				dstCount = 0;
				autoMinValue = dstMinValue = DEFAULT_THRESHOLD;
				rc = 1;
			}
			break;
		case LIGHT:
			if(light->enabled == false){
				mutex_lock(&data->mutex);
				light->enabled = true;
				light->ignorecount = -1;
				light->delay = 200;
				light->sdata.Value = -10000;
				mutex_unlock(&data->mutex);
				rc = 1;
			}
			break;
		default:
			return 0;
	}

	epl6881_setSleepTime();
	// It needs to work, if true.
	if((prox->enabled || light->enabled)){
		atomic_set(&data->flushqueue, 0);
		queue_delayed_work(PLSensor_WorkQueue, &data->dw, 0);
	}

	sDump_debug(max(p_dev.debugLevel, l_dev.debugLevel), "%s rc : %d--\n", __func__, rc);
	return true;
}

static int epl6881_disable(WorkType wType)
{
	int rc = 0;
	PLSensor* data = i2c_get_clientdata(this_client);
	Proximity* prox = &data->proximity;
	Light* light = &data->light;
	sDump_debug(max(p_dev.debugLevel, l_dev.debugLevel), "%s ++\n", __func__);

	// Stop all work
	atomic_set(&data->flushqueue, 1);
	cancel_delayed_work_sync(&data->dw2);
	cancel_delayed_work_sync(&data->dw);
	flush_workqueue(PLSensor_WorkQueue);

	switch(wType){
		case PROXIMITY:
			if(prox->enabled == true){
				mutex_lock(&data->mutex);
				prox->enabled = false;
				prox->sdata.Value = -1;
				prox->sdata.State = PROXIMITY_STATE_UNKNOWN;
				mutex_unlock(&data->mutex);
				rc = 1;
			}
			break;
		case LIGHT:
			if(light->enabled == true){
				mutex_lock(&data->mutex);
				light->enabled = false;
				light->ignorecount = -1;
				light->delay = 200;
				light->sdata.Value = -10000;
				mutex_unlock(&data->mutex);
				rc = 1;
			}
			break;
		default:
			return 0;
	}

	epl6881_setSleepTime();
	// It needs to work, if true.
	if((prox->enabled || light->enabled)){
		atomic_set(&data->flushqueue, 0);
		queue_delayed_work(PLSensor_WorkQueue, &data->dw, 0);
	}

	sDump_debug(max(p_dev.debugLevel, l_dev.debugLevel), "%s rc : %d--\n", __func__, rc);
	return true;
}

static bool proximity_setActive(bool enable)
{
	return (enable) ? epl6881_enable(PROXIMITY) : epl6881_disable(PROXIMITY);
}

static bool light_setActive(bool enable)
{
	return (enable) ? epl6881_enable(LIGHT) : epl6881_disable(LIGHT);
}

static bool light_setDelay(s64 delay)
{
	PLSensor* data = i2c_get_clientdata(this_client);
	Light* light = &data->light;
	sDump_debug(l_dev.debugLevel, "%s ++\n", __func__);
	mutex_lock(&data->mutex);
	light->delay = (delay >= 150) ? delay : 150;
	mutex_unlock(&data->mutex);
	epl6881_setSleepTime();
	sDump_debug(l_dev.debugLevel, "%s --\n", __func__);
	return true;
}

static bool proximity_calibrate(Action action, void* buf, ssize_t size)
{
	bool sucessful = false;
	Sensor_Calibrate_Infor* inf = (Sensor_Calibrate_Infor *) buf;
	PLSensor* data = i2c_get_clientdata(this_client);
	Proximity* prox = &data->proximity;

	switch(action){
		case Write:
			if(inf->job == PROXIMITY_THRESHOLD_SET){
				int Value = inf->p_infor.Value;
				if(prox->enabled && !data->suspend &&
					proximity_resetThreshold(Value + THRESHOLD_LEVEL, THRESHOLD_LEVEL) >= THRESHOLD_LEVEL){
					sucessful = true;
				}
			}
			break;
		case Read:
			inf->job = PROXIMITY_INFORMATION_GET;
			if(prox->enabled && !data->suspend){
				memcpy(&(inf->p_infor), &(prox->sdata), sizeof(ProximityInfor));
			}else{
				ProximityInfor pi = {
					.Value			= -1,
					.State			= PROXIMITY_STATE_UNKNOWN,
					.Threshold_L	= DEFAULT_THRESHOLD,
					.Threshold_H	= DEFAULT_THRESHOLD,
				};
				memcpy(&(inf->p_infor), &pi, sizeof(ProximityInfor));
			}
			sucessful = true;
			break;
		default :
			break;
	}
	return sucessful;
}

static bool light_calibrate(Action action, void* buf, ssize_t size)
{
	bool sucessful = false;
	Sensor_Calibrate_Infor* inf = (Sensor_Calibrate_Infor *) buf;
	PLSensor* data = i2c_get_clientdata(this_client);
	Light* light = &data->light;

	switch(action){
		case Write:
			if(inf->job == LIGHT_CONST_SET){
				int Const = inf->l_infor.Const;
				if(light->enabled && !data->suspend){
					sucessful = light_resetConst(Const);
				}
			}
			break;
		case Read:
			inf->job = LIGHT_INFORMATION_GET;
			if(light->enabled && !data->suspend){
				memcpy(&(inf->l_infor), &(light->sdata), sizeof(LightInfor));
			}else{
				LightInfor li = {
					.Value		= -1,
					.Channel_0	= LIGHT_UNKNOWN_SOURCE,
					.Channel_1	= LIGHT_UNKNOWN_SOURCE,
					.Const		= 0,
				};
				memcpy(&(inf->l_infor), &li, sizeof(LightInfor));
			}
			sucessful = true;
			break;
		default:
			break;
	}

	return sucessful;
}

static int proxmity_reportData(PLSensor* data){
	Proximity* prox = &data->proximity;
	u8 State = PROXIMITY_STATE_UNKNOWN;
	int Value = (i2cData[3] << 8) | i2cData[2];

	int Threshold = (prox->sdata.State != PROXIMITY_STATE_TRUE) ? prox->sdata.Threshold_H : prox->sdata.Threshold_L;
	State = (Value > Threshold) ? PROXIMITY_STATE_TRUE : PROXIMITY_STATE_FALSE;

	mutex_lock(&data->mutex);
	prox->sdata.Value = Value;
	if(State != prox->sdata.State){
		if(Pneed2ChangeState == true){
			prox->sdata.State = State;
			input_report_abs(prox->input, ABS_DISTANCE, (State) ? PROXIMITY_DETECTED : PROXIMITY_UNDETECTED);
			input_sync(prox->input);
			sDump_notice(p_dev.debugLevel, "%s state : %s\n", __func__, (State) ? "True" : "False");
		}
		Pneed2ChangeState = !Pneed2ChangeState;
	}else{
		Pneed2ChangeState = false;
	}
	mutex_unlock(&data->mutex);

	sDump_info(p_dev.debugLevel, "%s Threshold :%d, Value : %d\n", __func__, Threshold, Value);
	return Value;
}

static int light_reportData(PLSensor* data){
	Light* light = &data->light;
	int Value = 0;
	uint16_t CH0 = (i2cData[1] << 8) | i2cData[0];
	uint16_t CH1 = (i2cData[3] << 8) | i2cData[2];

	sDump_debug(l_dev.debugLevel, "%s channel 0 : %hu\n", __func__, CH0);
	sDump_debug(l_dev.debugLevel, "%s channel 1 : %hu\n", __func__, CH1);

	mutex_lock(&data->mutex);
	if(CH0 < 60000 && CH1 < 60000){
		Value = (CH0 > 0) ? (CH1 * light->sdata.Const) : (random32() & 31);
		light->sdata.Value = Value;
		// If ignorecount is -1, there has no need to ignore
		if(light->ignorecount == -1 || LignoreCount == 0){
			input_report_abs(light->input, ABS_MISC, light->sdata.Value);
			input_sync(light->input);
		}
		LignoreCount = ((LignoreCount < light->ignorecount) ? (LignoreCount + 1) : 0);
		sDump_info(l_dev.debugLevel, "%s Lux : %d\n", __func__, light->sdata.Value);
	}else{
		light->sdata.Value = -10000;
		sDump_debug(l_dev.debugLevel, "%s Out of Range\n", __func__);
	}
	light->sdata.Channel_0 = CH0;
	light->sdata.Channel_1 = CH1;
	mutex_unlock(&data->mutex);

	return Value;
}

// Dynamic stability threshold
static void epl6881_DST(const PLSensor* data, const int Value){
	const int Threshold = data->proximity.sdata.Threshold_H;
	const int Threshold_L = data->proximity.sdata.Threshold_L;
	if(Value < 0 || Threshold == DEFAULT_THRESHOLD){
		sDump_info(p_dev.debugLevel, "%s Invalid\n", __func__);
		return;
	}
	// Count is equal to DST_IGNORE or
    // over P_min + 9 x THRESHOLD_LEVEL means nothing to do
	if(dstCount == DST_IGNORE || ((THRESHOLD_RANGE << 2) + Threshold) < Value){
		sDump_info(p_dev.debugLevel, "%s No process\n", __func__);
		return;
	}
	if(dstCount < DST_FILTER){
		dstMinValue = min(dstMinValue, Value);
		++dstCount;
	}else{
		// minValue is bigger than Threshold_L means it needs to reset
		if(dstMinValue > Threshold_L){
			proximity_resetThreshold(dstMinValue + THRESHOLD_LEVEL, THRESHOLD_LEVEL);
			sDump_info(p_dev.debugLevel, "%s Trigger DST\n", __func__);
		}
		dstCount = DST_IGNORE;
	}
}

static void epl6881_autoCalibrate(const PLSensor* data, const int Value){
	const int Threshold = data->proximity.sdata.Threshold_H;
	// Auto-calibrate
	if(Value < 0 || ((Value + THRESHOLD_RANGE) > Threshold)){
		Pneed2Reset = false;
		autoMinValue = DEFAULT_THRESHOLD;
	}else{
		autoMinValue = min(autoMinValue, Value);
		(Pneed2Reset) ? proximity_resetThreshold(autoMinValue + THRESHOLD_LEVEL, THRESHOLD_LEVEL) : 0;
		Pneed2Reset = !Pneed2Reset;
	}
}

static bool epl6881_type_setting(WorkType wType)
{
	int err = 0;
	switch(wType){
		case PROXIMITY:
			/**
			 *  CYCLE: 011b, CYCLE_value: 8
			 *  GAINS: 11b, Low gain
			 *  INTEG: 0101b, PS_INTEG_VALUE: 144
			 *  RADC:  01b, RADC_value: 1024
			 */
			err = i2c_smbus_write_byte_data(this_client, PLSENSOR_REG_COMMANDI, 0x77);
			err |= i2c_smbus_write_byte_data(this_client, PLSENSOR_REG_COMMANDII, 0x51);
			err |= i2c_smbus_write_byte_data(this_client, PLSENSOR_REG_GOMID_SETTING, 0XAF);
			err |= i2c_smbus_write_byte_data(this_client, PLSENSOR_REG_GOLOW_SETTING, 0xAF);
			err |= i2c_smbus_write_byte_data(this_client, PLSENSOR_REG_CONTROL_SETTINGI, 0x04);
			usleep(40000);
			break;
		case LIGHT:
			/**
			 *  CYCLE: 100b, CYCLE_value: 16
			 *  GAINS: 10b, Auto-gain
			 *  INTEG: 0111b, ALS_INTEG_VALUE: 512
			 *  RADC:  01b, RADC_value: 1024
			 */
			err = i2c_smbus_write_byte_data(this_client, PLSENSOR_REG_COMMANDI, 0x92);
			err |= i2c_smbus_write_byte_data(this_client, PLSENSOR_REG_COMMANDII, 0x71);
			err |= i2c_smbus_write_byte_data(this_client, PLSENSOR_REG_GOMID_SETTING, 0X1E);
			err |= i2c_smbus_write_byte_data(this_client, PLSENSOR_REG_GOLOW_SETTING, 0x1E);
			err |= i2c_smbus_write_byte_data(this_client, PLSENSOR_REG_CONTROL_SETTINGI, 0x04);
			break;
		default:
			sDump_err(max(p_dev.debugLevel, l_dev.debugLevel), "%s error case\n", __func__);
			return false;
	}

	return (!err) ? true : false;
}

static bool epl6881_readData(WorkType wType)
{
	u16 cmp = 0;
	u8 i2cIsFine = false;
	u8 stateIsFine = false;
	memset(i2cData, 0, sizeof(i2cData));
	switch(wType){
		case PROXIMITY:
			cmp = 0x02;
			break;
		case LIGHT:
			cmp = 0x04;
			break;
		default:
			sDump_err(max(p_dev.debugLevel, l_dev.debugLevel), "%s error case", __func__);
			return false;
	}

	stateIsFine = !(i2c_smbus_read_byte_data(this_client, PLSENSOR_REG_CHIP_STATE) & cmp);
	i2cIsFine = (i2c_smbus_read_i2c_block_data(this_client, PLSENSOR_REG_CH0DATA_LSB | 0x03, 4, &i2cData[0]) == 4);

	if(!stateIsFine || !i2cIsFine){
		sDump_err(max(p_dev.debugLevel, l_dev.debugLevel), "%s wType : %d, state : %d\n", __func__, wType, stateIsFine);
		sDump_err(max(p_dev.debugLevel, l_dev.debugLevel), "%s wType : %d, i2c : %d\n", __func__, wType, i2cIsFine);
	}

	return i2cIsFine && stateIsFine;
}

static void epl6881_errorTrans(PLSensor* data, WorkType wType)
{
	switch(wType){
		case PROXIMITY:
		{
			Proximity* prox = &data->proximity;
			mutex_lock(&data->mutex);
			prox->sdata.Value = ERROR_TRANSACTION;
			prox->sdata.State = PROXIMITY_STATE_UNKNOWN;
			mutex_unlock(&data->mutex);
			sDump_alert(p_dev.debugLevel, "%s Proximity, try to reset chip\n", __func__);
		}
		break;
		case LIGHT:
		{
			Light* light = &data->light;
			mutex_lock(&data->mutex);
			light->sdata.Value = ERROR_TRANSACTION * 10000;
			mutex_unlock(&data->mutex);
			sDump_alert(true, "%s Light, try to reset chip\n", __func__);
		}
		break;
		default:
			sDump_err(max(p_dev.debugLevel, l_dev.debugLevel), "%s error case\n", __func__);
			return;
	}
	// reset chip
	i2c_smbus_write_byte_data(this_client, PLSENSOR_REG_CONTROL_SETTINGI, 0x00);
}

static void epl6881_work_func(struct work_struct* work)
{
	int Value = 0;
	PLSensor* data = i2c_get_clientdata(this_client);
	Proximity* prox = &data->proximity;
	Light* light = &data->light;

	sDump_debug(max(p_dev.debugLevel, l_dev.debugLevel), "%s ++\n", __func__);

	if(atomic_read(&data->flushqueue) || data->suspend){
		sDump_warn(max(p_dev.debugLevel, l_dev.debugLevel), "%s flush queue or system had been suspend\n", __func__);
		return;
	}

	if(light->enabled){
		if(LisReady && epl6881_readData(LIGHT)){
			light_reportData(data);
		}else{
			epl6881_errorTrans(data, LIGHT);
		}
	}

	if(prox->enabled){
		PisReady = epl6881_type_setting(PROXIMITY);
		if(PisReady && epl6881_readData(PROXIMITY)){
			Value = proxmity_reportData(data);
			epl6881_autoCalibrate(data, Value);
			epl6881_DST(data, Value);
		}else{
			epl6881_errorTrans(data, PROXIMITY);
		}
	}

	// It needs to check current state for avoiding async, so lock it.
	mutex_lock(&data->mutex);
	Value = (prox->enabled || light->enabled);
	mutex_unlock(&data->mutex);

	if(Value == 1){
		queue_delayed_work(PLSensor_WorkQueue, (light->enabled) ? &data->dw2 : &data->dw, SleepTime);
	}else{
		sDump_warn(max(p_dev.debugLevel, l_dev.debugLevel), "%s There has no need to re-queue\n", __func__);
	}

	sDump_debug(max(p_dev.debugLevel, l_dev.debugLevel), "%s --\n", __func__);
}

static void light_work_func(struct work_struct* work){
	PLSensor* data = i2c_get_clientdata(this_client);
	Light* light = &data->light;
	u32 delay = 0;
	sDump_debug(l_dev.debugLevel, "%s ++\n", __func__);

	if(atomic_read(&data->flushqueue)){
		sDump_warn(l_dev.debugLevel, "%s flush queue\n", __func__);
		return;
	}

	if(light->enabled){
		LisReady = epl6881_type_setting(LIGHT);
		delay = (LisReady) ? msecs_to_jiffies(90) : 0;
	}
	queue_delayed_work(PLSensor_WorkQueue, &data->dw, delay);
	sDump_debug(l_dev.debugLevel, "%s enable %d--\n", __func__, light->enabled);
}

static void proximity_dump(char* buf)
{
	PLSensor* data = i2c_get_clientdata(this_client);
	Proximity* prox = &data->proximity;
	snprintf(buf, 32, "%s \n", __func__);
	snprintf(buf + strlen(buf), 32, "PisReady : %u \n", PisReady);
	snprintf(buf + strlen(buf), 32, "Pneed2Reset : %u \n", Pneed2Reset);
	snprintf(buf + strlen(buf), 32, "Pneed2ChangeState : %u \n", Pneed2ChangeState);
	snprintf(buf + strlen(buf), 32, "SleepTime : %u \n", jiffies_to_msecs(SleepTime));
	snprintf(buf + strlen(buf), 32, "suspend : %u \n", data->suspend);
	snprintf(buf + strlen(buf), 32, "enabled : %u \n", prox->enabled);
}

static void light_dump(char* buf)
{
	PLSensor* data = i2c_get_clientdata(this_client);
	Light* light = &data->light;
	snprintf(buf, 32, "%s \n", __func__);
	snprintf(buf + strlen(buf), 32, "LisReady : %u \n", LisReady);
	snprintf(buf + strlen(buf), 32, "Lneed2Reset : %u \n", Lneed2Reset);
	snprintf(buf + strlen(buf), 32, "LignoreCount : %u \n", LignoreCount);
	snprintf(buf + strlen(buf), 32, "SleepTime : %u \n", jiffies_to_msecs(SleepTime));
	snprintf(buf + strlen(buf), 32, "suspend : %u \n", data->suspend);
	snprintf(buf + strlen(buf), 32, "enabled : %u \n", light->enabled);
}

static int epl6881_suspend(struct i2c_client* client, pm_message_t state)
{
	PLSensor* data = i2c_get_clientdata(client);
	Proximity* prox = &data->proximity;
	Light* light = &data->light;

	atomic_set(&data->flushqueue, 1);
	cancel_delayed_work_sync(&data->dw2);
	cancel_delayed_work_sync(&data->dw);
	flush_workqueue(PLSensor_WorkQueue);

	sDump_debug(max(p_dev.debugLevel, l_dev.debugLevel), "%s ++\n", __func__);

	mutex_lock(&data->mutex);
	data->suspend = true;
	if(prox->enabled){
		prox->sdata.Value = -1;
		prox->sdata.State = PROXIMITY_STATE_UNKNOWN;
	}
	if(light->enabled){
		light->sdata.Value = -10000;
	}
	LisReady = PisReady = false;
	Lneed2Reset = Pneed2Reset = false;
	Pneed2ChangeState = false;
	LignoreCount = 0;
	mutex_unlock(&data->mutex);

	atomic_set(&data->flushqueue, 0);
	sDump_debug(max(p_dev.debugLevel, l_dev.debugLevel), "%s --\n", __func__);
	return 0;// It needs to return 0, non-zero means has fault.
}

static int epl6881_resume(struct i2c_client* client)
{
	PLSensor* data = i2c_get_clientdata(client);
	Proximity* prox = &data->proximity;
	Light* light = &data->light;

	atomic_set(&data->flushqueue, 1);
	cancel_delayed_work_sync(&data->dw2);
	cancel_delayed_work_sync(&data->dw);
	flush_workqueue(PLSensor_WorkQueue);

	sDump_debug(max(p_dev.debugLevel, l_dev.debugLevel), "%s ++\n", __func__);

	mutex_lock(&data->mutex);
	data->suspend = false;
	if(prox->enabled){
		prox->sdata.Value = -1;
		prox->sdata.State = PROXIMITY_STATE_UNKNOWN;
	}
	if(light->enabled){
		light->sdata.Value = -10000;
	}
	mutex_unlock(&data->mutex);

	epl6881_setSleepTime();
	if(prox->enabled || light->enabled){
		atomic_set(&data->flushqueue, 0);
		queue_delayed_work(PLSensor_WorkQueue, &data->dw, 0);
	}

	sDump_debug(max(p_dev.debugLevel, l_dev.debugLevel), "%s\n", __func__);
	return 0;// It needs to return 0, non-zero means has fault.
}

static int epl6881_probe(struct i2c_client* client, const struct i2c_device_id* id)
{
	PLSensor* Sensor = NULL;
	struct input_dev* input_dev[2] = {NULL, NULL};
	int err = 0;

	sDump_debug(max(p_dev.debugLevel, l_dev.debugLevel), "%s ++\n", __func__);

	usleep(10000);

	if(!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_READ_WORD_DATA)){
		sDump_alert(max(p_dev.debugLevel, l_dev.debugLevel), "%s i2c check functionality error\n", __func__);
		return -EIO;
	}

	Sensor = kzalloc(sizeof(PLSensor), GFP_KERNEL);

	input_dev[0] = input_allocate_device();
	input_dev[1] = input_allocate_device();

	if(!Sensor || !input_dev[0] || !input_dev[1]){
		err = -ENOMEM;
		sDump_alert(max(p_dev.debugLevel, l_dev.debugLevel), "%s memory alloc error\n", __func__);
		goto err_free_mem;
	}

	INIT_DELAYED_WORK(&Sensor->dw, epl6881_work_func);
	INIT_DELAYED_WORK(&Sensor->dw2, light_work_func);
	i2c_set_clientdata(client, Sensor);

	// Try to register proximity in input_dev
	input_dev[0]->name = "proximity";
	input_dev[0]->id.bustype = BUS_I2C;
	input_set_capability(input_dev[0], EV_ABS, ABS_MISC);
	input_set_abs_params(input_dev[0], ABS_DISTANCE, 0, 65535, 0, 0);
	input_set_drvdata(input_dev[0], Sensor);

	err = input_register_device(input_dev[0]);
	if(err){
		sDump_err(p_dev.debugLevel, "%s input_register_device proximity error\n", __func__);
		goto err_free_mem;
	}

	Sensor->proximity.input				= input_dev[0];
	Sensor->proximity.sdata.Value		= -1;
	Sensor->proximity.sdata.State		= PROXIMITY_STATE_UNKNOWN;
	Sensor->proximity.sdata.Threshold_L	= DEFAULT_THRESHOLD;
	Sensor->proximity.sdata.Threshold_H	= DEFAULT_THRESHOLD;

	// Try to register light in input_dev
	input_dev[1]->name = "light";
	input_dev[1]->id.bustype = BUS_I2C;
	input_set_capability(input_dev[1], EV_ABS, ABS_MISC);
	input_set_abs_params(input_dev[1], ABS_MISC, 0, 655350000, 0, 0);
	input_set_drvdata(input_dev[1], Sensor);
	err = input_register_device(input_dev[1]);
	if(err){
		sDump_alert(l_dev.debugLevel, "%s input_register_device light error\n", __func__);
		goto err_free_mem;
	}

	Sensor->light.input				= input_dev[1];
	Sensor->light.sdata.Value		= -1;
	Sensor->light.ignorecount		= -1;
	Sensor->light.delay				= 200;
	Sensor->light.sdata.Channel_0	= LIGHT_UNKNOWN_SOURCE;
	Sensor->light.sdata.Channel_1	= LIGHT_UNKNOWN_SOURCE;
	Sensor->light.sdata.Const		= DEFAULT_LIGHT_CONST;

	mutex_init(&Sensor->mutex);
	atomic_set(&Sensor->flushqueue, 1);

	LisReady = PisReady = false;
	Lneed2Reset = Pneed2Reset = false;
	Pneed2ChangeState = false;
	LignoreCount = 0;

	this_client = client;
	PLSensor_WorkQueue = create_singlethread_workqueue("PLSensor");

	if(sensor_device_register(&client->dev, &p_dev)){
		sDump_alert(p_dev.debugLevel, "%s input_register_device light error\n", __func__);
		goto err_pdev;
	}
	if(sensor_device_register(&client->dev, &l_dev)){
		sDump_alert(l_dev.debugLevel, "%s input_register_device light error\n", __func__);
		goto err_ldev;
	}

	proximity_readThreshold(THRESHOLD_LEVEL);// It needs to avoid deadlock.

	postoffice_registerAddress(&address);
	light_readConst(20000);

	epl6881_setSleepTime();

	i2c_smbus_read_byte_data(this_client, PLSENSOR_REG_COMMANDI);
	i2c_smbus_write_byte_data(this_client, PLSENSOR_REG_CONTROL_SETTINGII, 0x02);

	// Reset chip
	i2c_smbus_write_byte_data(this_client, PLSENSOR_REG_COMMANDI, 0x16);
	i2c_smbus_write_byte_data(this_client, PLSENSOR_REG_CONTROL_SETTINGI, 0x00);
	i2c_smbus_write_byte_data(this_client, PLSENSOR_REG_CONTROL_SETTINGI, 0x04);

	sDump_debug(max(p_dev.debugLevel, l_dev.debugLevel), "%s --\n", __func__);

	return 0;

	err_ldev:
		sensor_device_unregister(&l_dev);
		input_unregister_device(input_dev[1]);
		input_dev[1] = NULL;
	err_pdev:
		sensor_device_unregister(&p_dev);
		input_unregister_device(input_dev[0]);
		input_dev[0] = NULL;
	err_free_mem:
		if(!input_dev[0])
			input_free_device(input_dev[0]);
		if(!input_dev[1])
			input_free_device(input_dev[1]);
		kfree(Sensor);
	return err;
}

static int epl6881_remove(struct i2c_client* client)
{
	PLSensor* data = i2c_get_clientdata(client);

	destroy_workqueue(PLSensor_WorkQueue);
	postoffice_unregisterAddress(&address);
	sensor_device_unregister(&p_dev);
	sensor_device_unregister(&l_dev);
	input_unregister_device(data->proximity.input);
	input_unregister_device(data->light.input);
	kfree(data);

	return 0;
}

static void epl6881_shutdown(struct i2c_client* client)
{
	epl6881_disable(PROXIMITY);
	epl6881_disable(LIGHT);
}

static struct i2c_device_id epl6881_idtable[] = {
	{"epl6881", 0 },
	{ }
};

MODULE_DEVICE_TABLE(i2c, epl6881_idtable);

#ifdef CONFIG_OF
static struct of_device_id match_table[] = {
	{ .compatible = "proximity,epl6811",},
	{ },
};
#else
#define match_table NULL
#endif

static struct i2c_driver epl6881_driver = {
	.driver = {
		.owner	= THIS_MODULE,
		.name	= EPL6881_DRIVER_NAME,
		.of_match_table = match_table,
	},
	.id_table	= epl6881_idtable,
	.probe		= epl6881_probe,
	.remove		= epl6881_remove,
	.suspend	= epl6881_suspend,
	.resume		= epl6881_resume,
	.shutdown	= epl6881_shutdown,
};

module_i2c_driver(epl6881_driver);

MODULE_AUTHOR("HuizeWeng@Arimacomm");
MODULE_DESCRIPTION("Proxmity / Light Sensor EPL6881");
MODULE_LICENSE("GPLv2");
