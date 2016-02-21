/*
 *  Support forcing crash by long pressing power key
 *
 *  Copyright (c) 2013 Ferry Wu
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/input.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/timer.h>

static struct timer_list force_crash_timer;
#define FORACE_CRASH_TIMEOUT 30000

static void force_crash_timer_handler(unsigned long data)
{
	char *killer = NULL;
	pr_err("*************FORCE CRASH***************");
	*killer = 1;
}

static void force_crash_event(struct input_handle *handle, unsigned int type,
		        unsigned int code, int value)
{
	if ((type == EV_KEY) && (code == KEY_POWER)) {
		if (value) {
			mod_timer(&force_crash_timer, jiffies + msecs_to_jiffies(FORACE_CRASH_TIMEOUT));
		} else {
			del_timer(&force_crash_timer);
		}
	}
}

static int force_crash_connect(struct input_handler *handler,
					  struct input_dev *dev,
					  const struct input_device_id *id)
{
	struct input_handle *handle;
	int error;

	handle = kzalloc(sizeof(struct input_handle), GFP_KERNEL);
	if (!handle)
		return -ENOMEM;

	handle->dev = dev;
	handle->handler = handler;
	handle->name = "force-crash";

	error = input_register_handle(handle);
	if (error) {
		pr_err("Failed to register input power handler, error %d\n",
		       error);
		kfree(handle);
		return error;
	}

	error = input_open_device(handle);
	if (error) {
		pr_err("Failed to open input power device, error %d\n", error);
		input_unregister_handle(handle);
		kfree(handle);
		return error;
	}

	return 0;
}

static void force_crash_disconnect(struct input_handle *handle)
{
	input_close_device(handle);
	input_unregister_handle(handle);
	kfree(handle);
}

static const struct input_device_id force_crash_ids[] = {
	{
		.flags = INPUT_DEVICE_ID_MATCH_EVBIT,
		.evbit = { BIT_MASK(EV_KEY) },
	},
	{ },
};

MODULE_DEVICE_TABLE(input, force_crash_ids);

static struct input_handler force_crash_handler = {
	.event =	force_crash_event,
	.connect =	force_crash_connect,
	.disconnect =	force_crash_disconnect,
	.name =		"force-crash",
	.id_table =	force_crash_ids,
};

static int __init force_crash_init(void)
{
	init_timer(&force_crash_timer);
	force_crash_timer.function = force_crash_timer_handler;
	return input_register_handler(&force_crash_handler);
}

static void __exit force_crash_exit(void)
{
	del_timer_sync(&force_crash_timer);
	input_unregister_handler(&force_crash_handler);
}

module_init(force_crash_init);
module_exit(force_crash_exit);

MODULE_AUTHOR("Ferry Wu <ferrywu@arimacomm.com.tw>");
MODULE_DESCRIPTION("Support forcing crash by long pressing power key");
MODULE_LICENSE("GPL");
