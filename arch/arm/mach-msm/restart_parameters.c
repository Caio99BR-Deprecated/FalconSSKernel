/* arch/arm/mach-msm/restart_parameters.c
 *
 * Get parameters passed by SBL1 before restart
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

#define RESTART_REASON_OFFSET 0

static void *restart_parameters_base;
static size_t restart_parameters_max;

int msm_get_crash_status(void)
{
	if ((restart_parameters_base) && (restart_parameters_max > RESTART_REASON_OFFSET)) {
		int *reason = (int *)(restart_parameters_base + RESTART_REASON_OFFSET);
		pr_info("crash_status: restart_reason %08x\n", *reason);
		if (*reason == 0xc0dedead) {
			return 1;
		}
	}
	return 0;
}
EXPORT_SYMBOL(msm_get_crash_status);

static int __devinit restart_parameters_probe(struct platform_device *pdev)
{
	int of_ret = 0;
	u32 of_val[2];

	if (!(pdev->dev.of_node)) {
		pr_err("%s: device tree not enabled\n", __func__);
		return -EFAULT;
	}

	of_ret = of_property_read_u32_array(pdev->dev.of_node, "qcom,memory-fixed", of_val, 2);
	if (of_ret) {
		pr_err("%s: device tree configuration error\n", __func__);
		return -EFAULT;
	}

	restart_parameters_base = ioremap(of_val[0], of_val[1]);
	restart_parameters_max = of_val[1];

	return 0;
}

static struct of_device_id restart_parameters_dt_match[] = {
	{	.compatible = "qcom,restart-parameters",
	},
	{}
};

static struct platform_driver restart_parameters_driver = {
	.driver		= {
		.name	= "restart_parameters",
		.of_match_table = restart_parameters_dt_match,
	},
	.probe = restart_parameters_probe,
};

static int __init restart_parameters_module_init(void)
{
	return platform_driver_register(&restart_parameters_driver);
}

postcore_initcall(restart_parameters_module_init);
