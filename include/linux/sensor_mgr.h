/*
 * Generic Sensor Device Manager
 *
 * Copyright (C) 2013 Huize Weng <huizeweng@arimacomm.com.tw>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef __LINUX_SENSOR_H_INCLUDED
#define __LINUX_SENSOR_H_INCLUDED

#define __BIN_ATTR(name_, mode_, size_, private_, read_, write_) { \
		.attr    = { .name = __stringify(name_), .mode = mode_ }, \
		.size    = size_, \
		.private = private_, \
		.read    = read_, \
		.write   = write_, \
}

#define sDump_alert(dLevel, fmt, ...) ({\
	pr_alert(fmt, ##__VA_ARGS__);\
})
#define sDump_err(dLevel, fmt, ...) ({\
	if(dLevel > 0) pr_err(fmt, ##__VA_ARGS__);\
})
#define sDump_warn(dLevel, fmt, ...) ({\
	if(dLevel > 1) pr_warn(fmt, ##__VA_ARGS__);\
})
#define sDump_notice(dLevel, fmt, ...) ({\
	if(dLevel > 2) pr_notice(fmt, ##__VA_ARGS__);\
})
#define sDump_info(dLevel, fmt, ...) ({\
	if(dLevel > 3) pr_info(fmt, ##__VA_ARGS__);\
})
#define sDump_debug(dLevel, fmt, ...) ({\
	if(dLevel > 4) printk(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__);\
})

struct device;
struct device_infor;

typedef enum{
	Read = 0,
	Write = 1,
}Action;

typedef struct sensor_device{
	const char*	name;
	void* 		sensor;
	bool		enable;
	s64			delay;
	u32			debugLevel;

	bool	(*setActive)(bool enable);
	bool	(*setDelay)(s64 delay);
	bool	(*calibrate)(Action action, void* buf, ssize_t size);
	void	(*internalDump)(char* buf);

	struct device*			dev;
	struct device_infor*	infor;
	struct mutex			mutex;
}sensor_device;

extern int sensor_device_register(struct device* parent, sensor_device* cdev);
extern void sensor_device_unregister(sensor_device* cdev);

#endif		/* __LINUX_SENSOR_H_INCLUDED */
