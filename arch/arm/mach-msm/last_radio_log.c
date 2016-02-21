/* arch/arm/mach-msm/last_radio_log.c
 *
 * Extract the log from a modem crash though SMEM
 *
 * Copyright (C) 2007 Google, Inc.
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
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/of.h>

#include "smd_private.h"

static void *radio_log_base;
static size_t radio_log_size;

static size_t radio_log_max;
static struct proc_dir_entry *radio_log_entry;

extern void *smem_get_entry(unsigned id, unsigned *size);

static ssize_t last_radio_log_read(struct file *file, char __user *buf,
			size_t len, loff_t *offset)
{
	loff_t pos = *offset;
	ssize_t count;

	if (pos >= radio_log_size)
		return 0;

	count = min(len, (size_t)(radio_log_size - pos));
	if (copy_to_user(buf, radio_log_base + pos, count)) {
		pr_err("%s: copy to user failed\n", __func__);
		return -EFAULT;
	}

	*offset += count;
	return count;
}

static struct file_operations last_radio_log_fops = {
	.read = last_radio_log_read,
	.llseek = default_llseek,
};

void last_radio_log_write(void)
{
	char *x;
	int size = 0;

	x = smem_get_entry(SMEM_ERR_CRASH_LOG, &size);
	if (x != 0) {
		x[size - 1] = 0;
		pr_err("%s: CRASH LOG\n'%s'\n", __func__, x);
	}

	if (radio_log_base != NULL) {
		if (size > radio_log_max) {
			size = radio_log_max;
		}
		pr_err("%s:  copy %d byte to 0x%x\n", __func__, size, (unsigned)radio_log_base);
		memcpy(radio_log_base, x, size);
		((char *)radio_log_base)[size-1] = 0;
		radio_log_size = strlen((char *)radio_log_base);
		radio_log_entry->size = radio_log_size;
	}
}

EXPORT_SYMBOL(last_radio_log_write);

static int __devinit last_radio_log_probe(struct platform_device *pdev)
{
	int of_ret = 0;
	u32 of_val[2];

	if (!(pdev->dev.of_node)) {
		pr_err("%s: device tree not enabled\n", __func__);
		return -EFAULT;
	}

	if (last_radio_log_fops.owner) {
		pr_err("%s: already claimed\n", __func__);
		return -EFAULT;
	}

	of_ret = of_property_read_u32_array(pdev->dev.of_node, "qcom,memory-fixed", of_val, 2);
	if (of_ret) {
		pr_err("%s: device tree configuration error\n", __func__);
		return -EFAULT;
	}

	radio_log_base = ioremap(of_val[0], of_val[1]);
	radio_log_max = of_val[1];
	radio_log_size = strlen((char *)radio_log_base);

	radio_log_entry = create_proc_entry("last_amsslog", S_IFREG | S_IRUGO, NULL);
	if (!radio_log_entry) {
		pr_err("%s: could not create proc entry for radio log\n",
				__func__);
		return -EFAULT;
	}

	pr_err("%s: last radio log is %d bytes long\n", __func__,
		radio_log_size);
	last_radio_log_fops.owner = THIS_MODULE;
	radio_log_entry->proc_fops = &last_radio_log_fops;
	radio_log_entry->size = radio_log_size;

	return 0;
}

static struct of_device_id last_radio_log_dt_match[] = {
	{	.compatible = "qcom,last-radio-log",
	},
	{}
};

static struct platform_driver last_radio_log_driver = {
	.driver		= {
		.name	= "last_radio_log",
		.of_match_table = last_radio_log_dt_match,
	},
	.probe = last_radio_log_probe,
};

static int __init last_radio_log_module_init(void)
{
	return platform_driver_register(&last_radio_log_driver);
}

postcore_initcall(last_radio_log_module_init);
