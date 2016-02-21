/* arch/arm/mach-msm/ramdump_proc_files.c
 *
 * Ramdump releated proc files
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
#include <linux/io.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/of.h>

static void *productinfo_base;
static size_t productinfo_max;
static struct proc_dir_entry *productinfo_entry;

static ssize_t productinfo_read(struct file *file, char __user *buf,
			size_t len, loff_t *offset)
{
	loff_t pos = *offset;
	ssize_t count;
	size_t size;

	size = strlen(productinfo_base);
	if (pos >= size)
		return 0;

	count = min(len, (size_t)(size - pos));
	if (copy_to_user(buf, productinfo_base + pos, count)) {
		pr_err("%s: copy to user failed\n", __func__);
		return -EFAULT;
	}

	*offset += count;
	return count;
}

static ssize_t productinfo_write(struct file *file, const char __user *buf,
			size_t len, loff_t *offset)
{
	loff_t pos = *offset;
	ssize_t count;

	if (pos >= productinfo_max)
		return 0;

	count = min(len, (size_t)(productinfo_max - pos));
	if (copy_from_user(productinfo_base + pos, buf, count)) {
		pr_err("%s: copy from user failed\n", __func__);
		return -EFAULT;
	}

	*offset += count;
	*((char *)(productinfo_base+pos+count)) = 0;
	productinfo_entry->size = strlen(productinfo_base);
	return count;
}

static struct file_operations productinfo_fops = {
	.read = productinfo_read,
	.write = productinfo_write,
	.llseek = default_llseek,
};

static int __devinit productinfo_probe(struct platform_device *pdev)
{
	int of_ret = 0;
	u32 of_val[2];

	if (!(pdev->dev.of_node)) {
		pr_err("%s: device tree not enabled\n", __func__);
		return -EFAULT;
	}

	if (productinfo_fops.owner) {
		pr_err("%s: already claimed\n", __func__);
		return -EFAULT;
	}

	of_ret = of_property_read_u32_array(pdev->dev.of_node, "qcom,memory-fixed", of_val, 2);
	if (of_ret) {
		pr_err("%s: device tree configuration error\n", __func__);
		return -EFAULT;
	}

	productinfo_base = ioremap(of_val[0], of_val[1]);
	productinfo_max = of_val[1] - 1;

	productinfo_entry = create_proc_entry("productinfo", S_IFREG | S_IRUGO | S_IWUSR | S_IWGRP, NULL);
	if (!productinfo_entry) {
		pr_err("%s: could not create proc entry for productinfo\n",
				__func__);
		return -EFAULT;
	}

	productinfo_fops.owner = THIS_MODULE;
	productinfo_entry->proc_fops = &productinfo_fops;
	productinfo_entry->size = strlen(productinfo_base);

	return 0;
}

static struct of_device_id productinfo_dt_match[] = {
	{	.compatible = "qcom,productinfo",
	},
	{}
};

static struct platform_driver productinfo_driver = {
	.driver		= {
		.name	= "productinfo",
		.of_match_table = productinfo_dt_match,
	},
	.probe = productinfo_probe,
};

static int __init productinfo_module_init(void)
{
	return platform_driver_register(&productinfo_driver);
}

postcore_initcall(productinfo_module_init);

static void *ramdumpinfo_base;
static size_t ramdumpinfo_max;
static struct proc_dir_entry *ramdumpinfo_entry;

static ssize_t ramdumpinfo_read(struct file *file, char __user *buf,
			size_t len, loff_t *offset)
{
	loff_t pos = *offset;
	ssize_t count;
	size_t size;

	size = strlen(ramdumpinfo_base);
	if (pos >= size)
		return 0;

	count = min(len, (size_t)(size - pos));
	if (copy_to_user(buf, ramdumpinfo_base + pos, count)) {
		pr_err("%s: copy to user failed\n", __func__);
		return -EFAULT;
	}

	*offset += count;
	return count;
}

static ssize_t ramdumpinfo_write(struct file *file, const char __user *buf,
			size_t len, loff_t *offset)
{
	loff_t pos = *offset;
	ssize_t count;

	if (pos >= ramdumpinfo_max)
		return 0;

	count = min(len, (size_t)(ramdumpinfo_max - pos));
	if (copy_from_user(ramdumpinfo_base + pos, buf, count)) {
		pr_err("%s: copy from user failed\n", __func__);
		return -EFAULT;
	}

	*offset += count;
	*((char *)(ramdumpinfo_base+pos+count)) = 0;
	ramdumpinfo_entry->size = strlen(ramdumpinfo_base);
	return count;
}

static struct file_operations ramdumpinfo_fops = {
	.read = ramdumpinfo_read,
	.write = ramdumpinfo_write,
	.llseek = default_llseek,
};

static int __devinit ramdumpinfo_probe(struct platform_device *pdev)
{
	int of_ret = 0;
	u32 of_val[2];

	if (!(pdev->dev.of_node)) {
		pr_err("%s: device tree not enabled\n", __func__);
		return -EFAULT;
	}

	if (ramdumpinfo_fops.owner) {
		pr_err("%s: already claimed\n", __func__);
		return -EFAULT;
	}

	of_ret = of_property_read_u32_array(pdev->dev.of_node, "qcom,memory-fixed", of_val, 2);
	if (of_ret) {
		pr_err("%s: device tree configuration error\n", __func__);
		return -EFAULT;
	}

	ramdumpinfo_base = ioremap(of_val[0], of_val[1]);
	ramdumpinfo_max = of_val[1] - 1;

	ramdumpinfo_entry = create_proc_entry("ramdumpinfo", S_IFREG | S_IRUGO | S_IWUSR | S_IWGRP, NULL);
	if (!ramdumpinfo_entry) {
		pr_err("%s: could not create proc entry for ramdumpinfo\n",
				__func__);
		return -EFAULT;
	}

	ramdumpinfo_fops.owner = THIS_MODULE;
	ramdumpinfo_entry->proc_fops = &ramdumpinfo_fops;
	ramdumpinfo_entry->size = strlen(ramdumpinfo_base);

	return 0;
}

static struct of_device_id ramdumpinfo_dt_match[] = {
	{	.compatible = "qcom,ramdumpinfo",
	},
	{}
};

static struct platform_driver ramdumpinfo_driver = {
	.driver		= {
		.name	= "ramdumpinfo",
		.of_match_table = ramdumpinfo_dt_match,
	},
	.probe = ramdumpinfo_probe,
};

static int __init ramdumpinfo_module_init(void)
{
	return platform_driver_register(&ramdumpinfo_driver);
}

postcore_initcall(ramdumpinfo_module_init);
