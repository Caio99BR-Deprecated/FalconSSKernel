/* arch/arm/mach-msm/last_ssr_kmsg.c
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
#include <linux/syslog.h>

#define KLOG_BUF_SHIFT	17	/* CONFIG_LOG_BUF_SHIFT from our kernel */
#define KLOG_BUF_LEN	(1 << KLOG_BUF_SHIFT)
static char last_ssr_kmsg_buffer[KLOG_BUF_LEN + 1];
static struct proc_dir_entry *last_ssr_kmsg_entry;

static ssize_t last_ssr_kmsg_read(struct file *file, char __user *buf,
			size_t len, loff_t *offset)
{
	loff_t pos = *offset;
	ssize_t count;
	ssize_t size = strlen(last_ssr_kmsg_buffer);

	if (pos >= size)
		return 0;

	count = min(len, (size_t)(size - pos));
	if (copy_to_user(buf, last_ssr_kmsg_buffer + pos, count)) {
		pr_err("%s: copy to user failed\n", __func__);
		return -EFAULT;
	}

	*offset += count;
	return count;
}

static struct file_operations last_ssr_kmsg_fops = {
	.read = last_ssr_kmsg_read,
	.llseek = default_llseek,
};

static void last_ssr_kmsg_init(struct module *owner)
{
	if (last_ssr_kmsg_fops.owner) {
		pr_err("%s: already claimed\n", __func__);
		return;
	}

	last_ssr_kmsg_entry = create_proc_entry("last_ssr_kmsg", S_IFREG | S_IRUGO, NULL);
	if (!last_ssr_kmsg_entry) {
		pr_err("%s: could not create proc entry for ssr kmsg\n",
				__func__);
		return;
	}

	pr_err("%s: last ssr kmsg is %d bytes long\n", __func__,
		strlen(last_ssr_kmsg_buffer));
	last_ssr_kmsg_fops.owner = owner;
	last_ssr_kmsg_entry->proc_fops = &last_ssr_kmsg_fops;
	last_ssr_kmsg_entry->size = strlen(last_ssr_kmsg_buffer);
}

void last_ssr_kmsg_write(void)
{
	memset(last_ssr_kmsg_buffer, 0, sizeof(last_ssr_kmsg_buffer));
	do_syslog(SYSLOG_ACTION_READ_ALL, last_ssr_kmsg_buffer, KLOG_BUF_LEN, SYSLOG_FROM_FILE);
	last_ssr_kmsg_entry->size = strlen(last_ssr_kmsg_buffer);
}
EXPORT_SYMBOL(last_ssr_kmsg_write);

static int __init last_ssr_kmsg_module_init(void)
{
	last_ssr_kmsg_init(THIS_MODULE);
	return 0;
}

postcore_initcall(last_ssr_kmsg_module_init);
