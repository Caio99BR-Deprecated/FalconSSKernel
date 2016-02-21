/*
 * Copyright (C) 2011-2014 Arima Communications Crop.
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

#ifndef _SENSORS_MCTL_H_
#define _SENSORS_MCTL_H_

#include <linux/types.h>
#include <linux/ioctl.h>

enum Sensor_Calibrate_Job{
	/* Add events for processing */
	ACCELEROMETER_AXISOFFSET_SET = 0,
	ACCELEROMETER_AXISOFFSET_INIT_SET,
	PROXIMITY_THRESHOLD_SET,
	PROXIMITY_INFORMATION_GET,
	LIGHT_CONST_SET,
	LIGHT_INFORMATION_GET,
	MAX_CALIBRATE_JOB_SIZE,
};

#define SENSOR_CALIBRATE_JOB_SIZE MAX_CALIBRATE_JOB_SIZE

typedef struct ProximityInfor{
	/* Current proximity ADC value on proximity sensor */
	int Value;
	/* Current state on proximity sensor */
	uint8_t State;
	/* Current threshold_l on proximity sensor */
	uint16_t Threshold_L;
	/* Current threshold_h on proximity sensor */
	uint16_t Threshold_H;
}ProximityInfor;

typedef struct LightInfor{
	/* Current LUX value on light sensor */
	int Value;
	/* Current Channel 0 value on light sensor */
	uint16_t Channel_0;
	/* Current Channel 1 value on light snesor */
	uint16_t Channel_1;
	/* Current Const value on light sensor, 10000x magnification */
	int Const;
}LightInfor;

typedef struct AccelerometerAxisOffset{
	short X;
	short Y;
	short Z;
}AccelerometerAxisOffset;

typedef struct Sensor_Calibrate_Infor{
	/* Identification */
	enum Sensor_Calibrate_Job job;
	union{
		/* The Accelerometer axis offset for calibrating */
		AccelerometerAxisOffset a_axisoffset;
		/* The Proximity information structure for setting/getting */
		ProximityInfor p_infor;
		/* The Light information structure for setting/getting */
		LightInfor l_infor;
	};
	/* Reserved */
	char* sensor_String;
}Sensor_Calibrate_Infor;

struct device_infor{
	char			name[32];
	char			vendor[32];
	unsigned short	maxRange;
	unsigned short	resolution;
	unsigned short	power;
	int32_t			minDelay;
};

#endif
