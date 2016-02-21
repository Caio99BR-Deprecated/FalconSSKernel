/*
 * Copyright (C) 2013 Arima Communications.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

//ALERT:relocate gps_elna.c under .\kernel\drivers\misc

/*
* Makefile//TODO:Here is makefile reference
* obj-$(CONFIG_GPS_ELNA)+= gps_elna.o
*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/i2c.h>
#include <linux/irq.h>
#include <linux/jiffies.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/miscdevice.h>
#include <linux/spinlock.h>
#include <linux/gps_elna.h>

#include <linux/of_gpio.h>
#include <linux/regulator/consumer.h>


//TODO:replace and include corresponding head file for VEN/IRQ/FIRM I/O configuration
//#include <plat/gpio-core.h>
//#include <plat/gpio-cfg.h>
//#include <plat/gpio-cfg-helpers.h>


//#define pr_err printk
//#define pr_debug printk
//#define pr_warning printk

#define DRIVER_AUTHOR "Murphy Ou"
#define DRIVER_NAME GPS_ELNA_DEVICE_NAME

// 1: enable, 0: disable
#define GPS_ELNA_REGULATOR_L16_ENABLE  0  //PDP1, PDP2 uses L16
#define GPS_ELNA_REGULATOR_L19_ENABLE  1  //DP uses L19

/* LDO16 voltage @3.0 V */
#define MXT_ELNA_L16_VTG_MIN_UV     3000000
#define MXT_ELNA_L16_VTG_MAX_UV     3000000
#define MXT_ELNA_L16_ACTIVE_LOAD_UA	600000   //600 mA
#define MXT_ELNA_L16_LPM_LOAD_UA		10

/* LDO19 voltage @2.85 V */
#define MXT_ELNA_L19_VTG_MIN_UV     2850000
#define MXT_ELNA_L19_VTG_MAX_UV     2850000
#define MXT_ELNA_L19_ACTIVE_LOAD_UA	600000   //600 mA
#define MXT_ELNA_L19_LPM_LOAD_UA		10


#define MAX_BUFFER_SIZE	512


typedef struct GPS_ELNA_CTRL_BLOCK_Tag
{
	wait_queue_head_t read_wq;
	struct mutex      read_mutex;
	//struct i2c_client *client;
	struct miscdevice gps_elna_device;
	//unsigned int      ven_gpio;
	//unsigned int      firm_gpio;
	//unsigned int      irq_gpio;
	//bool              irq_enabled;
	spinlock_t        irq_enabled_lock;

  struct device     *dev;
  unsigned int      gpio_enable;
  enum of_gpio_flags  gpio_enable_flag;
  struct regulator  *vcc_elna_l16;
  struct regulator  *vcc_elna_l19;
  
} GPS_ELNA_CTRL_BLOCK_T;


static int gps_elna_power_on_l16(GPS_ELNA_CTRL_BLOCK_T *data, bool on);
static int gps_elna_power_on_l19(GPS_ELNA_CTRL_BLOCK_T *data, bool on);


static ssize_t gps_elna_dev_read(struct file *filp, char __user *buf, size_t count, loff_t *offset)
{
  struct miscdevice *m = filp->private_data;
  GPS_ELNA_CTRL_BLOCK_T *gps_elna_ctrl_block = container_of(m, GPS_ELNA_CTRL_BLOCK_T, gps_elna_device); 
	char tmp[MAX_BUFFER_SIZE];
	int ret,i;

	if (count > MAX_BUFFER_SIZE)
		count = MAX_BUFFER_SIZE;

	printk("%s : reading %zu bytes.\n", __func__, count);

	mutex_lock(&gps_elna_ctrl_block->read_mutex);
	/* Read data */
	//ret = i2c_master_recv(gps_elna_ctrl_block->client, tmp, count);
	ret = count;
	mutex_unlock(&gps_elna_ctrl_block->read_mutex);

	if (ret < 0) 
	{
		pr_err("%s: i2c_master_recv returned %d\n", __func__, ret);
		return ret;
	}
	if (ret > count) 
	{
		pr_err("%s: received too many bytes from i2c (%d)\n", __func__, ret);
		return -EIO;
	}
	if (copy_to_user(buf, tmp, ret)) 
	{
		pr_warning("%s : failed to copy to user space\n", __func__);
		return -EFAULT;
	}
	
	printk("IFD->PC:");
	for(i = 0; i < ret; i++)
	{
		printk(" %02X", tmp[i]);
	}
	printk("\n");
	
	return ret;
}

static ssize_t gps_elna_dev_write(struct file *filp, const char __user *buf, size_t count, loff_t *offset)
{
  //struct miscdevice *m = filp->private_data;
  //GPS_ELNA_CTRL_BLOCK_T *gps_elna_ctrl_block = container_of(m, GPS_ELNA_CTRL_BLOCK_T, gps_elna_device); 
	char tmp[MAX_BUFFER_SIZE];
	int ret,i;


	if (count > MAX_BUFFER_SIZE)
	{
		count = MAX_BUFFER_SIZE;
	}
	if (copy_from_user(tmp, buf, count)) 
	{
		pr_err("%s : failed to copy from user space\n", __func__);
		return -EFAULT;
	}

	printk("%s : writing %zu bytes.\n", __func__, count);
  
	/* Write data */
	//ret = i2c_master_send(gps_elna_ctrl_block->client, tmp, count);
	ret = count;
	if (ret != count) 
	{
		pr_err("%s : i2c_master_send returned %d\n", __func__, ret);
		ret = -EIO;
	}
	printk("PC->IFD:");
	for(i = 0; i < count; i++)
	{
		printk(" %02X", tmp[i]);
	}
	printk("\n");
	
	return ret;
}

static int gps_elna_dev_open(struct inode *inode, struct file *filp)
{
  struct miscdevice *m = filp->private_data;
  GPS_ELNA_CTRL_BLOCK_T *gps_elna_ctrl_block = container_of(m, GPS_ELNA_CTRL_BLOCK_T, gps_elna_device); 


  printk("[GPS_DBG] - gps_elna_dev_open(), private_data = 0x%x\n", (int)gps_elna_ctrl_block);

	pr_debug("%s : %d,%d\n", __func__, imajor(inode), iminor(inode));

	return 0;
}

static long gps_elna_dev_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
  struct miscdevice *m = filp->private_data;
  GPS_ELNA_CTRL_BLOCK_T *gps_elna_ctrl_block = container_of(m, GPS_ELNA_CTRL_BLOCK_T, gps_elna_device); 


  switch (cmd)
  {
    case GPS_ELNA_SET_PWR:
    {
      if (arg == 1)
      {
        /* power on */
        printk("[GPS_DBG] - %s power on\n", __func__);

        if (GPS_ELNA_REGULATOR_L16_ENABLE)
          gps_elna_power_on_l16(gps_elna_ctrl_block, true);

        if (GPS_ELNA_REGULATOR_L19_ENABLE)
          gps_elna_power_on_l19(gps_elna_ctrl_block, true);

        //msleep(10);
      }
      else if (arg == 0)
      {
        /* power off */
        printk("[GPS_DBG] - %s power off\n", __func__);

        if (GPS_ELNA_REGULATOR_L16_ENABLE)
          gps_elna_power_on_l16(gps_elna_ctrl_block, false);

        if (GPS_ELNA_REGULATOR_L19_ENABLE)
          gps_elna_power_on_l19(gps_elna_ctrl_block, false);

        //msleep(50);
      }
      else
      {
        pr_err("%s bad arg %u\n", __func__, (unsigned int)arg);
        return -EINVAL;
      }
      
      break;
    }
    default:
    {
      pr_err("%s bad ioctl %u\n", __func__, cmd);
      return -EINVAL;
    }
  }
  
  return 0;
}

static const struct file_operations gps_elna_dev_fops = 
{
	.owner	= THIS_MODULE,
	.llseek	= no_llseek,
	.read	= gps_elna_dev_read,
	.write	= gps_elna_dev_write,
	.open	= gps_elna_dev_open,
	.unlocked_ioctl = gps_elna_dev_ioctl,
};

static int gps_elna_set_optimum_mode_check(struct regulator *reg, int load_uA)
{
	return (regulator_count_voltages(reg) > 0) ?
		regulator_set_optimum_mode(reg, load_uA) : 0;
}

static int gps_elna_power_on_l16(GPS_ELNA_CTRL_BLOCK_T *data, bool on)
{
	int rc;

	if (on == false)
  {
    printk("[GPS_DBG] - gps_elna_power_on_l16(), on = false.\n");
		goto power_off;
  }
  
  printk("[GPS_DBG] - gps_elna_power_on_l16(), on = true.\n");

  //L16
	rc = gps_elna_set_optimum_mode_check(data->vcc_elna_l16, MXT_ELNA_L16_ACTIVE_LOAD_UA);
  
	if (rc < 0) {
		dev_err(data->dev,
			"Regulator vcc_elna_l16 set_opt failed rc=%d\n", rc);
    
    printk("[GPS_DBG] - gps_elna_set_optimum_mode_check(), vcc_elna_l16 - fail.\n");
    
		return rc;
	}

	rc = regulator_enable(data->vcc_elna_l16);
  
	if (rc) {
		dev_err(data->dev,
			"Regulator vcc_elna_l16 enable failed rc=%d\n", rc);
    
    printk("[GPS_DBG] - regulator_enable(), vcc_elna_l16 - fail.\n");
    
		goto error_reg_en_vcc_elna_l16;
	}

  //msleep(150);
  printk("[GPS_DBG] - gps_elna_power_on_l16(), on = true, OK.\n");
  
	return 0;

error_reg_en_vcc_elna_l16:
	gps_elna_set_optimum_mode_check(data->vcc_elna_l16, 0);
  
	return rc;

power_off:
	gps_elna_set_optimum_mode_check(data->vcc_elna_l16, 0);
	regulator_disable(data->vcc_elna_l16);

	//msleep(50);
	printk("[GPS_DBG] - gps_elna_power_on_l16(), on = false, OK.\n");
  
	return 0;
}

static int gps_elna_power_on_l19(GPS_ELNA_CTRL_BLOCK_T *data, bool on)
{
	int rc;

	if (on == false)
  {
    printk("[GPS_DBG] - gps_elna_power_on_l19(), on = false.\n");
		goto power_off;
  }
  
  printk("[GPS_DBG] - gps_elna_power_on_l19(), on = true.\n");

  //L19
	rc = gps_elna_set_optimum_mode_check(data->vcc_elna_l19, MXT_ELNA_L19_ACTIVE_LOAD_UA);
  
	if (rc < 0) {
		dev_err(data->dev,
			"Regulator vcc_elna_l19 set_opt failed rc=%d\n", rc);
    
    printk("[GPS_DBG] - gps_elna_set_optimum_mode_check(), vcc_elna_l19 - fail.\n");
    
		return rc;
	}

	rc = regulator_enable(data->vcc_elna_l19);
  
	if (rc) {
		dev_err(data->dev,
			"Regulator vcc_elna_l19 enable failed rc=%d\n", rc);
    
    printk("[GPS_DBG] - regulator_enable(), vcc_elna_l19 - fail.\n");
    
		goto error_reg_en_vcc_elna_l19;
	}

  //msleep(150);
  printk("[GPS_DBG] - gps_elna_power_on_l19(), on = true, OK.\n");
  
	return 0;

error_reg_en_vcc_elna_l19:
	gps_elna_set_optimum_mode_check(data->vcc_elna_l19, 0);
  
	return rc;

power_off:
	gps_elna_set_optimum_mode_check(data->vcc_elna_l19, 0);
	regulator_disable(data->vcc_elna_l19);

	//msleep(50);
	printk("[GPS_DBG] - gps_elna_power_on_l19(), on = false, OK.\n");
  
	return 0;
}

static int gps_elna_regulator_configure_l16(GPS_ELNA_CTRL_BLOCK_T *data, bool on)
{
	int rc = 0;

	if (on == false)
		goto hw_shutdown;

  //L16
	data->vcc_elna_l16 = regulator_get(data->dev, "vcc_elna_l16");
	if (IS_ERR(data->vcc_elna_l16)) {
		rc = PTR_ERR(data->vcc_elna_l16);
		dev_err(data->dev,
			"Regulator get failed vcc_elna_l16 rc=%d\n", rc);
		return rc;
	}

	if (regulator_count_voltages(data->vcc_elna_l16) > 0) {
		rc = regulator_set_voltage(data->vcc_elna_l16, MXT_ELNA_L16_VTG_MIN_UV,
							MXT_ELNA_L16_VTG_MAX_UV);
		if (rc) {
			dev_err(data->dev,
				"regulator set_vtg vcc_elna_l16 failed rc=%d\n", rc);
			goto error_set_vtg_vcc_elna_l16;
		}
	}

  printk(KERN_INFO "[GPS_DBG] - vcc_elna_l16-supply configuretion ok.");

	return 0;
  
error_set_vtg_vcc_elna_l16:
	regulator_put(data->vcc_elna_l16);

	return rc;

hw_shutdown:
	if (regulator_count_voltages(data->vcc_elna_l16) > 0)
		regulator_set_voltage(data->vcc_elna_l16, 0, MXT_ELNA_L16_VTG_MAX_UV);
  
	regulator_put(data->vcc_elna_l16);

	return 0;
}

static int gps_elna_regulator_configure_l19(GPS_ELNA_CTRL_BLOCK_T *data, bool on)
{
	int rc = 0;

	if (on == false)
		goto hw_shutdown;

  //L19
	data->vcc_elna_l19 = regulator_get(data->dev, "vcc_elna_l19");
	if (IS_ERR(data->vcc_elna_l19)) {
		rc = PTR_ERR(data->vcc_elna_l19);
		dev_err(data->dev,
			"Regulator get failed vcc_elna_l19 rc=%d\n", rc);
		return rc;
	}

	if (regulator_count_voltages(data->vcc_elna_l19) > 0) {
		rc = regulator_set_voltage(data->vcc_elna_l19, MXT_ELNA_L19_VTG_MIN_UV,
							MXT_ELNA_L19_VTG_MAX_UV);
		if (rc) {
			dev_err(data->dev,
				"regulator set_vtg vcc_elna_l19 failed rc=%d\n", rc);
			goto error_set_vtg_vcc_elna_l19;
		}
	}

  printk(KERN_INFO "[GPS_DBG] - vcc_elna_l19-supply configuretion ok.");

	return 0;
  
error_set_vtg_vcc_elna_l19:
	regulator_put(data->vcc_elna_l19);

	return rc;

hw_shutdown:
	if (regulator_count_voltages(data->vcc_elna_l19) > 0)
		regulator_set_voltage(data->vcc_elna_l19, 0, MXT_ELNA_L19_VTG_MAX_UV);
  
	regulator_put(data->vcc_elna_l19);

	return 0;
}


static int gps_elna_dts_parsing(GPS_ELNA_CTRL_BLOCK_T *data)
{
  struct device_node *np = NULL;


  if (!data)
    return -1;
  if (!data->dev)
    return -1;
  if (!(np = data->dev->of_node))
    return -1;
  
  data->gpio_enable = of_get_named_gpio_flags(np,
                                              "elna,enable-gpio",
                                              0,
                                              &(data->gpio_enable_flag));
  
  printk(KERN_INFO "[GPS_DBG] - gpio_enable = %d, gpio_enable_flag = %d\n",
         data->gpio_enable, (int)(data->gpio_enable_flag));

  if (GPS_ELNA_REGULATOR_L16_ENABLE)
    gps_elna_regulator_configure_l16(data, true);

  if (GPS_ELNA_REGULATOR_L19_ENABLE)
    gps_elna_regulator_configure_l19(data, true);

  return 0;
}

/*
 * module load/unload record keeping
 */
static int __devinit gps_elna_probe(struct platform_device *pdev)
{
  int ret = 0;
  GPS_ELNA_CTRL_BLOCK_T *gps_elna_ctrl_block = NULL;


  gps_elna_ctrl_block = kzalloc(sizeof(GPS_ELNA_CTRL_BLOCK_T), GFP_KERNEL);
  if (gps_elna_ctrl_block == NULL) 
  {
    ret = -ENOMEM;
    goto err_exit;
  }
  
  memset(gps_elna_ctrl_block, 0x00, sizeof(GPS_ELNA_CTRL_BLOCK_T));
  
  gps_elna_ctrl_block->dev = &(pdev->dev);
  platform_set_drvdata(pdev, gps_elna_ctrl_block);

  if (gps_elna_dts_parsing(gps_elna_ctrl_block) != 0)
  {
    ret = -EINVAL;
    goto err_dts_parsing;
  }
  
  /* init mutex and queues */
  init_waitqueue_head(&gps_elna_ctrl_block->read_wq);
  mutex_init(&gps_elna_ctrl_block->read_mutex);
  spin_lock_init(&gps_elna_ctrl_block->irq_enabled_lock);

  gps_elna_ctrl_block->gps_elna_device.minor = MISC_DYNAMIC_MINOR;
  gps_elna_ctrl_block->gps_elna_device.name = GPS_ELNA_DEVICE_NAME;
  gps_elna_ctrl_block->gps_elna_device.fops = &gps_elna_dev_fops;

  ret = misc_register(&gps_elna_ctrl_block->gps_elna_device);
  if (ret) 
  {
    printk(KERN_INFO "[GPS_DBG] - misc_register failed\n");
    ret = -EINVAL;
    goto err_misc_register;
  }

  printk(KERN_INFO "[GPS_DBG] - misc_register ok\n");
  
  return 0;

//err_request_irq_failed:
//  misc_deregister(&gps_elna_ctrl_block->gps_elna_device);
err_misc_register:
  mutex_destroy(&gps_elna_ctrl_block->read_mutex);
err_dts_parsing:
  kfree(gps_elna_ctrl_block);
err_exit:
  //gpio_free(gps_elna_ctrl_block->irq_gpio);
  //gpio_free(gps_elna_ctrl_block->ven_gpio);
  //gpio_free(gps_elna_ctrl_block->firm_gpio);
  
  printk(KERN_INFO "[GPS_DBG] - error\n");
  
  return ret;
}

static const struct of_device_id gps_elna_ids[]  = {
  { .compatible = "arima,gps_elna" },
  {}
};

static struct platform_driver gps_elna_platform_driver = {
  .driver = {
    .name = DRIVER_NAME,
    .owner = THIS_MODULE,
    .of_match_table = gps_elna_ids,
  },
  .probe = gps_elna_probe,
};

static int __init gps_elna_dev_init(void)
{
  int ret = 0;
  
  
  printk(KERN_INFO "[GPS_DBG] - Loading GPS eLNA driver\n");
  
	ret = platform_driver_register(&gps_elna_platform_driver);
	if (ret)
  {
    printk(KERN_ERR "[GPS_DBG] - %s failed to load\n", __FUNCTION__);
	}
  
  return ret;
}

static void __exit gps_elna_dev_exit(void)
{
  printk(KERN_INFO "[GPS_DBG] - Unloading GPS eLNA driver\n");
  platform_driver_unregister(&gps_elna_platform_driver);
}


module_init(gps_elna_dev_init);
module_exit(gps_elna_dev_exit);

MODULE_AUTHOR("Murphy Ou");
MODULE_DESCRIPTION("GPS eLNA driver");
MODULE_LICENSE("GPL");

