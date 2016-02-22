/*
 * Copyright (C) 2012 Arima Communications Crop.
 * Author: Huize Weng <huizeweng@arimacomm.com.tw>
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

#ifndef _PLSensor_COMMOM_H_
#define _PLSensor_COMMOM_H_

#include <linux/types.h>
#include <linux/sensors_mctl.h>
#include <linux/sensor_mgr.h>
#include <mach/oem_rapi_client.h>
#include <linux/postoffice.h>

#define DEFAULT_THRESHOLD 0XFFFF
#define ERROR_TRANSACTION -9999

#define PROXIMITY_DETECTED 0
#define PROXIMITY_UNDETECTED 10

#define LIGHT_UNKNOWN_SOURCE 0XFFFF
#define DEFAULT_LIGHT_CONST 1072

enum{
	PROXIMITY_STATE_FALSE		= 0,
	PROXIMITY_STATE_TRUE		= 1,
	PROXIMITY_STATE_UNKNOWN		= 0xFF,
};

typedef enum{
	PROXIMITY		= 0,
	LIGHT			= 1,
}WorkType;

typedef struct Proximity{
	struct input_dev*		input;
	#ifdef PROXIMITY_IRQ_USED
	int						irq;
	#endif
	ProximityInfor			sdata;
	bool					enabled;
}Proximity;

typedef struct Light{
	struct input_dev*		input;
	LightInfor				sdata;
	bool					enabled;
	s64						delay;
	int						ignorecount;
}Light;

typedef struct PLSensor{
	struct mutex			mutex;
	struct delayed_work 	dw;
	struct delayed_work 	dw2;
	Proximity				proximity;
	Light					light;
	bool					suspend;
	atomic_t				flushqueue;
}PLSensor;

// It needs to reset memory
static struct i2c_client* this_client = NULL;
static struct workqueue_struct* PLSensor_WorkQueue = NULL;
static u8 i2cData[4];
static bool PisReady = false;
static bool LisReady = false;
static bool Pneed2Reset = false;
static bool Lneed2Reset = false;
static bool Pneed2ChangeState = false;
static int LignoreCount = 0;
static unsigned long SleepTime = 0;

static int proximity_resetThreshold(const int threshold, const int level)
{
	PLSensor* data = i2c_get_clientdata(this_client);
	Proximity* prox = (data) ? &data->proximity : NULL;
	int result = 0;

	if(prox == NULL) return -1;
	mutex_lock(&data->mutex);
	result = threshold;
	prox->sdata.Threshold_L = (result >= level) ? (result - (level >> 1)) : prox->sdata.Threshold_L;
	prox->sdata.Threshold_H = (result >= level) ? result : prox->sdata.Threshold_H;
	mutex_unlock(&data->mutex);
	return result;
}

static int proximity_readThreshold(const int level)
{
	PLSensor* data = i2c_get_clientdata(this_client);
	Proximity* prox = (data) ? &data->proximity : NULL;
	int result = -1;

	if(prox == NULL) return -1;
	result = prox->sdata.Threshold_H;
	if(result == DEFAULT_THRESHOLD){
		/**
		* Do reset. 
		* It means that proximity threshold hasn't been setted yet.
		*/
		result = proximity_resetThreshold(DEFAULT_THRESHOLD >> 2, level);
	}

	mutex_lock(&data->mutex);
	prox->sdata.Threshold_L = (result >= level) ? (result - (level >> 1)) : prox->sdata.Threshold_L;
	prox->sdata.Threshold_H = (result >= level) ? result : prox->sdata.Threshold_H;
	mutex_unlock(&data->mutex);
	return result;
}

static bool light_resetConst(const int Const)
{
	Package* package = kzalloc(sizeof(Package), GFP_KERNEL);
	package->category = WLSensorConst;
	memcpy(package->content, &Const, sizeof(int));
	postoffice_sendPackage(package);
	kfree(package);
	return true;
}

static void light_readConst(const uint32_t msleep)
{
	Package* package = kzalloc(sizeof(Package), GFP_KERNEL);
	package->category = RLSensorConst;
	postoffice_sendPackageDelayed(package, msleep);
	kfree(package);
}

#endif
