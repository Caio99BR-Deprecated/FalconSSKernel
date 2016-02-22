/*
 * Copyright (C) 2013-2014 Arima Communications Crop.
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

#ifndef _ACCELEROMETER_COMMOM_H_
#define _ACCELEROMETER_COMMOM_H_

#include <linux/types.h>
#include <linux/sensors_mctl.h>
#include <linux/sensor_mgr.h>
#include <mach/oem_rapi_client.h>
#include <linux/postoffice.h>

// Smoothed raw data
// FILTER_SIZE must be 2^N, which N >= 0 and Integer
#define FILTER_SIZE		(u32)4
#define FILTER_INDEX	(u32)(FILTER_SIZE - 1)
#define FILTER_SIZEBIT	(u32)(FILTER_SIZE >> 1)

typedef struct AccelerometerData{
	int X;
	int Y;
	int Z;
}AccelerometerData;

typedef struct Accelerometer{
	struct input_dev*		input;
	struct mutex			mutex;
	struct delayed_work		dw;
	#ifdef ACCELEROMETER_IRQ_USED
	int						irq;
	bool					irq_work;
	#endif
	AccelerometerData		sdata;
	AccelerometerAxisOffset	odata;
	bool					enabled;
	bool					suspend;
}Accelerometer;

enum{
	NORMAL_MODE		= 0X0A,
	INTERRUPT_MODE	= 0X0B,
	SPECIAL_MODE	= 0X0C,
};

static u8 WorkMode = NORMAL_MODE;
static u8 POWER_MODE_CAMMAND;

// It needs to reset memory
static struct i2c_client* this_client = NULL;
static struct workqueue_struct* Accelerometer_WorkQueue = NULL;
static unsigned long SleepTime = 0;
static u8 i2cData[6];
static u8 queueIndex = 0;
static u8 ignoreCount = 0;
static AccelerometerData rawData;
static AccelerometerData averageData;
static AccelerometerData queueData[FILTER_SIZE];

static bool accelerometer_resetAxisOffset(s16 x, s16 y, s16 z)
{
	AccelerometerAxisOffset offset = {
		.X = x,
		.Y = y,
		.Z = z,
	};
	Package* package = kzalloc(sizeof(Package), GFP_KERNEL);
	package->category = WGSensorOffset;
	memcpy(package->content, &offset, sizeof(AccelerometerAxisOffset));
	postoffice_sendPackage(package);
	kfree(package);

	return true;
}

static bool accelerometer_readAxisOffset(const uint32_t msleep)
{
	Package* package = kzalloc(sizeof(Package), GFP_KERNEL);
	package->category = RGSensorOffset;
	postoffice_sendPackageDelayed(package, msleep);
	kfree(package);
	return true;
}

#endif
