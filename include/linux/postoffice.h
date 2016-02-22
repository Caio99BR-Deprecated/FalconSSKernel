/*
 * PostOffice Interface
 *
 * Copyright (C) 2013 - 2014 Huize Weng <huizeweng@arimacomm.com.tw>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef __LINUX_POSTOFFICE_H_INCLUDED
#define __LINUX_POSTOFFICE_H_INCLUDED

// Max number of Category is 33
typedef enum{
	// System events
	InnerInterrupt	= 0,
	ReadyToWork		= 1 << 0,
	// Customize events
	RGSensorOffset	= 1 << 1,
	WGSensorOffset	= 1 << 2,
	RLSensorConst 	= 1 << 3,
	WLSensorConst	= 1 << 4,
	Tmp000000001	= 1 << 5,
	Tmp000000002	= 1 << 6,
	Tmp000000003	= 1 << 7,
	// Special events for receiving all
	AllPackage		= 0XFFFFFFFF,
}Category;

#define CONTENT_SIZE 24

typedef struct Package{
	Category	category;
	char		content[CONTENT_SIZE];
}Package;

typedef struct deliverAddress{
	const char*			name;
	uint32_t			receivedCategory;
	/* Package will be delivered to mailbox.
	 * NOTE: DO NOT set any block in this callback.
	 */
	void(*mailbox)(const Package* const package);
}deliverAddress;

extern void postoffice_sendPackage(const Package* package);
extern void postoffice_sendPackageDelayed(const Package* package, const unsigned int msleep);
extern void postoffice_sendLocalPackageDelayed(const Package* package, const unsigned int msleep);
extern int postoffice_registerAddress(deliverAddress* address);
extern void postoffice_unregisterAddress(deliverAddress* address);

#endif		/* __LINUX_POSTOFFICE_H_INCLUDED */
