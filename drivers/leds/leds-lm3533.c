/*
 * License Terms: GNU General Public License v2
 *
 * Simple driver for National Semiconductor LM3533 LEDdriver chip
 *
 *
 * based on leds-lp3944.c 
 */

#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/slab.h>
#include <linux/leds.h>
#include <linux/mutex.h>
#include <linux/workqueue.h>
#include <linux/leds-lm3533.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/time.h>

#define LM3533_DRIVER_NAME "lm3533_leds"

static struct i2c_client* lm3533_client = NULL;
static struct workqueue_struct* LED_WorkQueue = NULL;

static struct workqueue_struct* bt_connected_wq;  
static struct delayed_work BT_connected;

static u8 lcm_has_on;
static int keep_backlight_brightness = 255;
static u8 backlight_has_on;
static int log_flag_setting = 0;

u8 brightness_table[]= {
    0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
    0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
    0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
    0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
    0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
    0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
    0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
    0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,
    0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,
    0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
    0xB0,0xB2,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
    0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
    0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
    0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
    0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF
};

static struct lm3533_platform_data lm3533_leds_data = {
    .leds_size = LM3533_LEDS_MAX,
    .leds = {
        [0] = {
            .name = "lm3533-light-sns",
        },
        [1] = {
            .name = "notification",
        },
        [2] = {
            .name = "lm3533-light-backlight",
        },
    }
};

struct rgb_brightness {
    int light_red;
    int light_green;
    int light_blue;
};

/* Saved data */
struct lm3533_led_data {
    u8 id;
    u8 keep_on_triggered_next;
    u8 keep_on_triggered_now;
    int lm3533_led_brightness;
    unsigned long fade_time;
    unsigned long keep_on_time;
    unsigned long keep_off_time;
    unsigned long lm3533_rgb_brightness;    
    struct led_classdev ldev;
    struct i2c_client *client;
    struct delayed_work thread;
    struct delayed_work thread_register_keep;
    struct delayed_work thread_set_keep;
    unsigned int debug_flag;    
};

struct lm3533_data {
    struct mutex lock;
    struct i2c_client *client;
    struct lm3533_led_data leds[LM3533_LEDS_MAX];
};

static int theme_color = 27903;

static ssize_t lm3533_fade_time_write(struct device *dev,
                    struct device_attribute *attr,
                    const char *buf, size_t count)
{
    struct led_classdev *led_cdev = dev_get_drvdata(dev);    
    struct lm3533_led_data *led = container_of(led_cdev, struct lm3533_led_data, ldev);
    static unsigned long fade_time;
    u8 fade_data[6];
    if (strict_strtoul(buf, 10, &fade_time))
        return -EINVAL;
    if(log_flag_setting){
        printk(KERN_EMERG "%s: %s, %lu \n",__func__, led_cdev->name, fade_time);}
    led->fade_time = fade_time;    
    i2c_smbus_write_byte_data(lm3533_client,LM3533_CONTROL_ENABLE,0x1D); //20130930 tracy change from 0x1c to 0x1d for black screen when led dimming 
    i2c_smbus_write_byte_data(lm3533_client,LM3533_PATTERN_GENERATOR_ENABLE_ALS_SCALING_CONTROL,0x3F);
	if (fade_time == 500) {
        fade_data[0]=0x00;
        fade_data[1]=0x00;
        fade_data[2]=0x00;
        fade_data[3]=0x00;
        fade_data[4]=0x02;    // 20131224 tracy modify for fade time  register ++
        fade_data[5]=0x03;   // 20131224 tracy modify for fade time  register --
        i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_PATTERN_GENERATOR_1_DELAY,6,fade_data);
        i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_PATTERN_GENERATOR_2_DELAY,6,fade_data);
        i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_PATTERN_GENERATOR_3_DELAY,6,fade_data);
    } else if (fade_time == 3500) {
        fade_data[0]=0x00;
        fade_data[1]=0x00;
        fade_data[2]=0x58;
        fade_data[3]=0x00;
        fade_data[4]=0x02;
        fade_data[5]=0x03;
        i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_PATTERN_GENERATOR_1_DELAY,6,fade_data);
        i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_PATTERN_GENERATOR_2_DELAY,6,fade_data);
        i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_PATTERN_GENERATOR_3_DELAY,6,fade_data);
    } else if (fade_time == 200) {
	queue_delayed_work(bt_connected_wq, &BT_connected, msecs_to_jiffies(5500));
        fade_data[0]=0x00;
        fade_data[1]=0x52;
        fade_data[2]=0x00;
        fade_data[3]=0x00;
        fade_data[4]=0x01;
        fade_data[5]=0x04;
        i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_PATTERN_GENERATOR_1_DELAY,6,fade_data);
        i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_PATTERN_GENERATOR_2_DELAY,6,fade_data);
        i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_PATTERN_GENERATOR_3_DELAY,6,fade_data);
    } else if (fade_time == 300) {
        fade_data[0]=0x00;            
        fade_data[1]=0x00;
        fade_data[2]=0x00;
        fade_data[3]=0x00;
        fade_data[4]=0x01;
        fade_data[5]=0x03;
        i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_PATTERN_GENERATOR_1_DELAY,6,fade_data);
        i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_PATTERN_GENERATOR_2_DELAY,6,fade_data);
        i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_PATTERN_GENERATOR_3_DELAY,6,fade_data);
    } else if (fade_time == 625) {
        fade_data[0]=0x00;
        fade_data[1]=0x00;
        fade_data[2]=0x00;
        fade_data[3]=0x00;
        fade_data[4]=0x02;
        fade_data[5]=0x02;
        i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_PATTERN_GENERATOR_1_DELAY,6,fade_data);
        i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_PATTERN_GENERATOR_2_DELAY,6,fade_data);
        i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_PATTERN_GENERATOR_3_DELAY,6,fade_data);
    } else if (fade_time == 100) {
        fade_data[0]=0x4B;
        fade_data[1]=0x4B;
        fade_data[2]=0x07;
        fade_data[3]=0x00;
        fade_data[4]=0x00;
        fade_data[5]=0x00;
        i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_PATTERN_GENERATOR_1_DELAY,6,fade_data);
        i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_PATTERN_GENERATOR_2_DELAY,6,fade_data);
        i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_PATTERN_GENERATOR_3_DELAY,6,fade_data);
    } else {
        if(log_flag_setting)
            printk(KERN_INFO "%s: dimming disable: %lu \n",__func__, fade_time);
        i2c_smbus_write_byte_data(lm3533_client,LM3533_PATTERN_GENERATOR_ENABLE_ALS_SCALING_CONTROL,0x00);
    }
    return count;
}

static ssize_t lm3533_runtime_fade_time_write(struct device *dev,
                    struct device_attribute *attr,
                    const char *buf, size_t count)
{
    struct led_classdev *led_cdev = dev_get_drvdata(dev);    
    static unsigned long runtime_fade_time;

    if (strict_strtoul(buf, 10, &runtime_fade_time))
        return -EINVAL;
    if(log_flag_setting)
        printk(KERN_EMERG "%s: %s, %lu \n",__func__, led_cdev->name, runtime_fade_time);

    return count;
}
//20130924 tracy add for SNS and notification blue led dimming++
static ssize_t lm3533_blink_write(struct device *dev,
                    struct device_attribute *attr,
                    const char *buf, size_t count)
{    
    static unsigned long blinking;
    u8 blink_data[6];    
        
    if (strict_strtoul(buf, 10, &blinking))
        return -EINVAL;    
    
    i2c_smbus_write_byte_data(lm3533_client,LM3533_BRIGHTNESS_REGISTER_F,0xFF); //Arima alvin 20131022 modified 0xAF -> 0xFF
    
    i2c_smbus_write_byte_data(lm3533_client,LM3533_CONTROL_ENABLE,0x21); //20130930 tracy change from 0x20 to 0x21 for black screen when led dimming
    blink_data[0]=0x62; //Arima alvin 20131022 modified 0x4B -> 0x62
    blink_data[1]=0x62; //Arima alvin 20131022 modified 0x4B -> 0x62
    blink_data[2]=0x07;
    blink_data[3]=0x00;
    blink_data[4]=0x00;
    blink_data[5]=0x00;    

    i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_PATTERN_GENERATOR_4_DELAY,6,blink_data);
    i2c_smbus_write_byte_data(lm3533_client,LM3533_PATTERN_GENERATOR_ENABLE_ALS_SCALING_CONTROL,0xC0);
    //i2c_smbus_write_byte_data(lm3533_client,LM3533_BRIGHTNESS_REGISTER_F,0xAF);
        
    
    return count;
}
//20130924 tracy add for SNS and notification blue led dimming--
//20131121 tracy add for change sns led color as theme color ++
static ssize_t lm3533_theme_write(struct device *dev,
                    struct device_attribute *attr,
                    const char *buf, size_t count)
{    
    static unsigned long theme;

    if (strict_strtoul(buf, 10, &theme))
        return -EINVAL;    
    
    theme_color=theme;

    printk(KERN_EMERG "%s:  %d \n",__func__, theme_color);
    	      
    return count;
}

static ssize_t lm3533_button2_write(struct device *dev,
                    struct device_attribute *attr,
                    const char *buf, size_t count)
{    
    static unsigned long button2;
	  u8 button2_data[3];
    if (strict_strtoul(buf, 10, &button2))
        return -EINVAL;    
if(button2==1)
{
    printk(KERN_EMERG "%s: on  %d \n",__func__, theme_color);
    button2_data[0] = brightness_table[( theme_color>>16)&255];  //red led    (SNS light setting)
    button2_data[1] = brightness_table[( theme_color>>8)&255];
    button2_data[2] = brightness_table[( theme_color)&255];
    i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_BRIGHTNESS_REGISTER_C,3,button2_data);
}
else
{
   printk(KERN_EMERG "%s: off \n",__func__);
    button2_data[0] = brightness_table[(0x00)&255];  //red led    (SNS light setting)
    button2_data[1] = brightness_table[(0x00)&255];
    button2_data[2] = brightness_table[(0x00)&255];
    i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_BRIGHTNESS_REGISTER_C,3,button2_data);
}
    return count;
}
//20131121 tracy add for change sns led color as theme color --

static ssize_t lm3533_rgb_brightness_write(struct device *dev,
                    struct device_attribute *attr,
                    const char *buf, size_t count)
{
    struct led_classdev *led_cdev = dev_get_drvdata(dev);    
    struct lm3533_led_data *led = container_of(led_cdev, struct lm3533_led_data, ldev);
    u8 sns_data[3];
    static unsigned long rgb_brightness;

    if (strict_strtoul(buf, 10, &rgb_brightness))
        return -EINVAL;    

    
        led->lm3533_rgb_brightness = rgb_brightness;
    
    if(log_flag_setting){
    printk(KERN_EMERG "%s: %s, %lu \n",__func__, led_cdev->name, rgb_brightness);}

    /*++this function is for keep on time ++*/    
        
    cancel_delayed_work_sync(&led->thread_register_keep);
    cancel_delayed_work_sync(&led->thread_set_keep);

    sns_data[0] = brightness_table[(rgb_brightness>>16)&255];  //red led    (SNS light setting)
    sns_data[1] = brightness_table[(rgb_brightness>>8)&255];
    sns_data[2] = brightness_table[(rgb_brightness)&255];
    i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_BRIGHTNESS_REGISTER_C,3,sns_data);
    memset(sns_data,0,3);
    i2c_smbus_read_i2c_block_data(lm3533_client,LM3533_BRIGHTNESS_REGISTER_C,3,sns_data);

    if(log_flag_setting){        
        printk(KERN_EMERG "sns_data[0] = %d , sns_data[1] = %d , sns_data[2]=%d  ",sns_data[0],sns_data[1],sns_data[2]);
    }

    queue_delayed_work(LED_WorkQueue, &led->thread, msecs_to_jiffies(10));

    return count;
}


static int lm3533_led_set(struct lm3533_led_data *led,unsigned long brightness);
static ssize_t lm3533_charger_brightness_write(struct device *dev,
                    struct device_attribute *attr,
                    const char *buf, size_t count)
{
    struct led_classdev *led_cdev = dev_get_drvdata(dev);    
    struct lm3533_led_data *led = container_of(led_cdev, struct lm3533_led_data, ldev);
    static unsigned long charger_brightness;

    if (strict_strtoul(buf, 10, &charger_brightness))
        return -EINVAL;    

    if(led->id==2)
    {
        led->lm3533_led_brightness = charger_brightness;
              if(log_flag_setting){
        printk(KERN_EMERG "%s: %s, %lu \n",__func__, led_cdev->name, charger_brightness);}
        lm3533_led_set(led,led->lm3533_led_brightness);
    }

    return count;
}

static ssize_t lm3533_debug_flag_write (struct device *dev,
                    struct device_attribute *attr,
                    const char *buf, size_t count)
{
    struct led_classdev *led_cdev = dev_get_drvdata(dev);    
    struct lm3533_led_data *led = container_of(led_cdev, struct lm3533_led_data, ldev);
    static unsigned long debug_flag;

    if (strict_strtoul(buf, 10, &debug_flag))
        return -EINVAL;

    printk(KERN_EMERG "%s: Enter LED Debug Mode \n",__func__);

    log_flag_setting=((debug_flag==1)?1:0);
    
    led->debug_flag = debug_flag;    
            
    return count;
}
//20130717 tracy modify unused led code++
static DEVICE_ATTR(debug_flag , 0644 , NULL , lm3533_debug_flag_write);
static DEVICE_ATTR(fade_time , 0644 , NULL , lm3533_fade_time_write);
static DEVICE_ATTR(runtime_fade_time , 0644 , NULL , lm3533_runtime_fade_time_write);
static DEVICE_ATTR(rgb_brightness , 0644 , NULL , lm3533_rgb_brightness_write);
static DEVICE_ATTR(charger_brightness , 0644 , NULL , lm3533_charger_brightness_write);
//20130924 tracy add for SNS and notification blue led dimming++
static DEVICE_ATTR(blinking , 0644 , NULL , lm3533_blink_write);
//20131121 tracy add for change sns led color as theme color ++
static DEVICE_ATTR(theme , 0644 , NULL , lm3533_theme_write);
static DEVICE_ATTR(button2 , 0644 , NULL , lm3533_button2_write);

static struct attribute *lm3533_attributes[] = {
    &dev_attr_fade_time.attr,
    &dev_attr_runtime_fade_time.attr,    
    &dev_attr_rgb_brightness.attr,
    &dev_attr_debug_flag.attr,
    &dev_attr_blinking.attr,
    &dev_attr_theme.attr,
    &dev_attr_button2.attr,
    NULL
};
//20131121 tracy add for change sns led color as theme color --
//20130924 tracy add for SNS and notification blue led dimming--

static struct attribute_group lm3533_attribute_group = {
    .attrs = lm3533_attributes
};


static struct attribute *lm3533_backlight_attributes[] = {
    &dev_attr_fade_time.attr,
    &dev_attr_runtime_fade_time.attr,    
    &dev_attr_charger_brightness.attr,
    NULL
};

static struct attribute_group lm3533_backlight_attribute_group = {
    .attrs = lm3533_backlight_attributes
};

static int lm3533_led_set(struct lm3533_led_data *led,unsigned long brightness)
{
    
    u8 id = led->id;
    static int err;
    static int brightness_temp = 0;
    static int rgb_enable = 0;
    static u8 BANK_ENABLE= 0x01;
    static u8 BANK_ENABLE_ORIGINAL = 0x00;   
    //by major, 2014.06.10 ignore first backlight off event
    static int ignoreFirstBacklightOff_event = 1;
    
    switch (id) {
        
    case LM3533_LED0:            
        
        BANK_ENABLE = BANK_ENABLE &  35;      //100011    
        
        rgb_enable = 100*((brightness>>16)&255?1:0)+10*((brightness>>8)&255?1:0)+
            ((brightness)&255?1:0);

        i2c_smbus_write_byte_data(lm3533_client,LM3533_STARTUP_SHUTDOWN_RAMP_RATES,0x1B);
                
        switch (rgb_enable){            
        case SNS_NO:          // 000                
            break;
        case SNS_B:          //  100
            BANK_ENABLE = BANK_ENABLE |  16;      //010000
            
            break;
        case SNS_G:          //  010
            BANK_ENABLE = BANK_ENABLE |  8;      //001000
            
            break;
        case SNS_GB:    //110
            BANK_ENABLE = BANK_ENABLE |  24;      //011000
            
            break;
        case SNS_R:      //001    
            BANK_ENABLE = BANK_ENABLE |  4;      //000100
            
            break;    
        case SNS_RB:    //101
            BANK_ENABLE = BANK_ENABLE |  20;      //010100
            
            break;
        case SNS_RG:    //011
            BANK_ENABLE = BANK_ENABLE |  12;      //001100
            
            break;    
        case SNS_RGB:    //111
            BANK_ENABLE = BANK_ENABLE |  28;      //011100
            
            break;    
        default:
            break;    
        }            
        break;
        //20130722 tracy add for notification led++
    case LM3533_LED1:    // LVLED 4 BANK F

        //i2c_smbus_write_byte_data(lm3533_client,LM3533_STARTUP_SHUTDOWN_RAMP_RATES,0x1B);
        i2c_smbus_write_byte_data(lm3533_client,LM3533_STARTUP_SHUTDOWN_RAMP_RATES,0x00); //Arima Alvin modifed for BANK F
        //printk(KERN_EMERG "LM3533_STARTUP_SHUTDOWN_RAMP_RATES : 0x1B \n");
    
        if(brightness)    
        {
            BANK_ENABLE = BANK_ENABLE |33;        //100001
            
            if (err)
                printk(KERN_EMERG "notification on error \n");
        if(log_flag_setting){
            printk(KERN_EMERG "notification on \n");}
        }
        else
        { 
            BANK_ENABLE = BANK_ENABLE &  31;        //011111    
            if (err)
                printk(KERN_EMERG "notification off error \n");
        }    
        break;  
        
    case LM3533_LED2:  //HVLED               //[Arima Jim] Modify Runtime Ramp Rates for backlight
    
        if(led->lm3533_led_brightness)
        {            
            if(!brightness_temp)
            {
                brightness_temp = 1;    
                printk(KERN_EMERG "backlight on \n");}        
                i2c_smbus_write_byte_data(lm3533_client,LM3533_RUN_TIME_RAMP_RATES, (led->fade_time > 0) ? 0x08 : 0);
                (led->fade_time > 0) ? 0 : msleep(20);
                err = i2c_smbus_write_byte_data(led->client, LM3533_BRIGHTNESS_REGISTER_A,brightness_table[led->lm3533_led_brightness]);    //backlight offset            
                if (err)
                    printk(KERN_EMERG "backlight set error %d",err);
            }
            else
            {                
                /*by major, ignore the first one*/
                if(1 == ignoreFirstBacklightOff_event){
                     ignoreFirstBacklightOff_event = 0;

                     printk(KERN_EMERG "backlight off 1st  ignored\n");

	             break;
                     
                }
                brightness_temp = 0; 
                
                err = i2c_smbus_write_byte_data(led->client, LM3533_BRIGHTNESS_REGISTER_A,0x00);
                if (err)
                {
                    printk(KERN_EMERG "backlight off error %d \n",err);
                }
                printk(KERN_EMERG "backlight off \n");
		}                
        break;
    default:
        break;
    }//20130722 tracy add for notification led--
    
    if(BANK_ENABLE != BANK_ENABLE_ORIGINAL)
    {
        err =  i2c_smbus_write_byte_data(led->client, LM3533_CONTROL_ENABLE,BANK_ENABLE);    
        msleep(5);
        if (err)
            printk(KERN_EMERG "bank set error \n");
        #ifdef DEBUG
          if(log_flag_setting){
        printk(KERN_EMERG"BANK_ENABLE = 0x%x \n",BANK_ENABLE);}
        #endif
    }    
    BANK_ENABLE_ORIGINAL = BANK_ENABLE;
    
    #ifdef DEBUG
    printk(KERN_EMERG "%s: %s,  id:%d brightness:%lu \n",
        __func__, led->ldev.name, id, brightness);
    #endif

    return err;
}

static void lm3533_led_set_brightness(struct led_classdev *led_cdev,
                      enum led_brightness brightness)
{
    struct lm3533_led_data *led = container_of(led_cdev, struct lm3533_led_data, ldev);
    //20130722 tracy add for notification led++
    if(led->id==2)
        if(log_flag_setting){
            printk(KERN_EMERG "%s: %s, %d\n",__func__, led_cdev->name, brightness);
        }
    
    led->lm3533_led_brightness = brightness;

    if(led->id==2 && brightness==0) 
    {
        keep_backlight_brightness = 0;
        lcm_has_on=0; 
        backlight_has_on=0;
        led->lm3533_led_brightness=0;
        lm3533_led_set(led, 0);
    }
    else if(led->id==2&& brightness>0 )
    {
        if (lcm_has_on==1&& backlight_has_on==0&&brightness>0 ) 
        {
            lm3533_led_set(led, brightness);
            backlight_has_on=1;
        }            
        else if (lcm_has_on==1&& backlight_has_on==1&&brightness>0 )
        {
            lm3533_led_set(led, brightness);
        }
        else 
        {
            keep_backlight_brightness=brightness;
        }
    }
    else if(led->id==2)    
    {
        backlight_has_on = 0;
        lcm_has_on=0;
        led->lm3533_led_brightness=0;
        lm3533_led_set(led, 0);
        keep_backlight_brightness=0;
    }
    else if(led->id==1)
    {
        cancel_delayed_work_sync(&led->thread_register_keep);
        cancel_delayed_work_sync(&led->thread_set_keep);
        queue_delayed_work(LED_WorkQueue, &led->thread, msecs_to_jiffies(10));    
    }
    else
        queue_delayed_work(LED_WorkQueue, &led->thread, msecs_to_jiffies(10));        
}//20130722 tracy add for notification led--

static void lm3533_led_work(struct work_struct *work)
{
    struct lm3533_led_data *led = container_of(work, struct lm3533_led_data, thread.work);

    if(led->id == 0)
        lm3533_led_set(led, led->lm3533_rgb_brightness);
    else if(led->id==1)
        lm3533_led_set(led, (unsigned long)led->lm3533_led_brightness);

}
//20140110 tracy add for led flash once when bluetooth connected++
static void lm3533_led_btconnected_work(struct work_struct *work)
{
       u8 data[3];
	
	 data[0] = brightness_table[(0x00)&255];  
        data[1] = brightness_table[(0x00)&255];
        data[2] = brightness_table[(0x00)&255];
        i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_BRIGHTNESS_REGISTER_C,3,data);
        i2c_smbus_write_byte_data(lm3533_client,LM3533_PATTERN_GENERATOR_ENABLE_ALS_SCALING_CONTROL,0x00);	
	
}
//20140110 tracy add for led flash once when bluetooth connected--
void lm3533_backlight_control(unsigned long brightness)
{    

    struct lm3533_data *data = i2c_get_clientdata(lm3533_client);    
    //20130722 tracy add for notification led++
    struct lm3533_led_data *led2 = &data->leds[2];
    //20130816 tracy remove unused led code for 1020++
    led2->lm3533_led_brightness=brightness;
             
    lm3533_led_set(led2, led2->lm3533_led_brightness);
    //20130816 tracy remove unused led code for 1020--
    //20130722 tracy add for notification led--
    return;
}



static int lm3533_configure(struct i2c_client *client,
                struct lm3533_data *data,
                struct lm3533_platform_data *pdata)
{
    int i, err = 0;
    //int temp ; //20130702 tracy remove unused log
    
    u8 LM3533_data[32];
    memset(LM3533_data,0,32);    

    
    LM3533_data[0]=0x00;
    LM3533_data[1]=0x00;
    LM3533_data[2]=0x00;
    LM3533_data[3]=0x00;
    LM3533_data[4]=0x00;
    LM3533_data[5]=0x00;
    err = i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_CONTROL_BANK_A_PWM_CONFIGURATION,6,LM3533_data);
    if(err)    
    {
        printk(KERN_NOTICE "LM3533_CONTROL_BANK_A_PWM_CONFIGURATION \n");
    };
    //20130905 tracy change for match the led requested current++
    LM3533_data[0]=0x13;
    LM3533_data[1]=0x13;
    LM3533_data[2]=0x13;
    LM3533_data[3]=0x13;   //20131107 tracy modify from 0x03 to 0x13 for increase notification blue light brightness
    //20130905 tracy change for match the led requested current--
    
    err = i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_CONTROL_BANK_C_FULL_SCALE_CURRENT,4,LM3533_data);
    if(err)    
    {
        printk(KERN_NOTICE "LM3533_CONTROL_BANK_C_FULL_SCALE_CURRENT \n");
    };
    //tracy modify for change mapping from exponential to linear++
    //20130905 tracy change for match the led requested current++
    LM3533_data[0]=0x02;
    LM3533_data[1]=0x0C;
    LM3533_data[2]=0x0C;
    LM3533_data[3]=0x0C;
    LM3533_data[4]=0x0C;   //20131107 tracy modify from 0x03 to 0x13 for increase notification blue light brightness
    //20130905 tracy change for match the led requested current--
    
    err = i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_CONTROL_BANK_A_B_BRIGHTNESS_CONFIGURATION,5,LM3533_data);//20130722 tracy add for notification led++

    if(err)    
    {
        printk(KERN_NOTICE "LM3533_CONTROL_BANK_A_B_BRIGHTNESS_CONFIGURATION \n");
    };    
    //tracy modify for change mapping from exponential to linear--
    
    LM3533_data[0]=0xAF;
    LM3533_data[1]=0xAF;
    LM3533_data[2]=0xAF;
    LM3533_data[3]=0xFF;  //20131107 tracy change for increase notification blue light brightness
    // brightness
    i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_BRIGHTNESS_REGISTER_C,4,LM3533_data);
         
    LM3533_data[0]=0x1B;  /*1B*/ 
    LM3533_data[1]=0x08;    
    i2c_smbus_write_i2c_block_data(lm3533_client,LM3533_STARTUP_SHUTDOWN_RAMP_RATES,2,LM3533_data);    

    err = i2c_smbus_write_byte_data(lm3533_client,LM3533_OVP_FREQUENCY_PWM_POLARITY,0x04);
    if(err)    
    {
        printk(KERN_NOTICE "LM3533_OVP_FREQUENCY_PWM_POLARITY \n");
    };
          
    memset(LM3533_data,0,32);
    i2c_smbus_read_i2c_block_data(lm3533_client,LM3533_CURRENT_SINK_OUTPUT_CONFIGURATION1,32,LM3533_data);
    
    memset(LM3533_data,0,32);
    i2c_smbus_read_i2c_block_data(lm3533_client,LM3533_ALS_DOWN_DELAY_CONTROL,32,LM3533_data);
    
    printk(KERN_NOTICE "0x%x",i2c_smbus_read_byte_data(lm3533_client,LM3533_CURRENT_SINK_OUTPUT_CONFIGURATION1));
    
    for (i = 0; i < pdata->leds_size; i++) {
        struct lm3533_led *pled = &pdata->leds[i];
        struct lm3533_led_data *led = &data->leds[i];
        led->client = client;
        led->id = i;            
                    
        led->ldev.name = pled->name;
        led->ldev.brightness_set = lm3533_led_set_brightness;
            
        INIT_DELAYED_WORK(&led->thread, lm3533_led_work);        
        INIT_DELAYED_WORK(&BT_connected, lm3533_led_btconnected_work);      //20140110 tracy add for led flash once when bluetooth connected++         
        err = led_classdev_register(&client->dev, &led->ldev);
        if (err < 0) {
            dev_err(&client->dev,
                "couldn't register LED %s\n",
                led->ldev.name);
            goto exit;
        }
        //20130722 tracy add for notification led++
        if(led->id != 2)
            err = sysfs_create_group(&led->ldev.dev->kobj,&lm3533_attribute_group);
        else
            err = sysfs_create_group(&led->ldev.dev->kobj,&lm3533_backlight_attribute_group);
        //20130722 tracy add for notification led--
        if (err < 0) {
            printk(KERN_EMERG "%s creat fail \n",__func__);
        }
            
        /* to expose the default value to userspace */
        //led->ldev.brightness = led->status;

        /* Set the default led status */
        /*++ Huize - 20120830 Add for setting fadat_time default value is 0xFF ++*/
        led->fade_time = 255;
        /*-- Huize - 20120830 Add for setting fadat_time default value is 0xFF --*/

        led->lm3533_led_brightness = 0;
        //err = lm3533_led_set(led, 0);
                
        if (err < 0) {
            dev_err(&client->dev,
            "%s couldn't set STATUS \n",
            led->ldev.name);
        goto exit;
        }                
    }    
    return 0;

exit:
    if (i > 0)
        for (i = i - 1; i >= 0; i--){                
            led_classdev_unregister(&data->leds[i].ldev);
            cancel_work_sync(&data->leds[i].thread.work);
            cancel_work_sync(&data->leds[i].thread_register_keep.work);
            cancel_work_sync(&data->leds[i].thread_set_keep.work);
    }        

    return err;
}


static int lm3533_probe(struct i2c_client *client,
                  const struct i2c_device_id *id)
{
    struct lm3533_platform_data *lm3533_pdata = &lm3533_leds_data;
    struct lm3533_data *data;
    int err;        

    //printk(KERN_EMERG "**********%s * client->addr = 0x%x  name=%s********\n",__func__,client->addr,client->name); //20130702 tracy remove unused log
    printk(KERN_NOTICE "%s : 0x%x",__func__,i2c_smbus_read_byte_data(client,LM3533_CURRENT_SINK_OUTPUT_CONFIGURATION1));    

    if (lm3533_pdata == NULL) {
        dev_err(&client->dev, "lm3533_probe no platform data\n");        
        printk(KERN_ERR "lm3533_probe no platform data\n");
        return -EINVAL;
    }

    /* Let's see whether this adapter can support what we need. */
    if (!i2c_check_functionality(client->adapter,
                I2C_FUNC_I2C)) {
        dev_err(&client->dev, "insufficient functionality!\n");    
        printk(KERN_ERR "lm3533_probe insufficient functionality\n");
        return -ENODEV;
    }        
    
    // read the default value to check if IC there
    if(i2c_smbus_read_byte_data(client,LM3533_CURRENT_SINK_OUTPUT_CONFIGURATION1) != 0x92)
    {
        gpio_set_value(18, 0);        // HW init again
        msleep(10);
        gpio_set_value(18, 1);
        msleep(5);

        if(i2c_smbus_read_byte_data(client,LM3533_CURRENT_SINK_OUTPUT_CONFIGURATION1) != 0x92)
        {
            printk(KERN_NOTICE "LM3533 initial value error \n");
            //return -ENODEV;
        }    
    }

    data = kzalloc(sizeof(struct lm3533_data), GFP_KERNEL);
    if (!data)
        return -ENOMEM;

    LED_WorkQueue = create_singlethread_workqueue(LM3533_DRIVER_NAME);
    bt_connected_wq = create_singlethread_workqueue("bt_connected_wq");  //20140110 tracy add for led flash once when bluetooth connected++

    data->client = client;
    lm3533_client = client;
    i2c_set_clientdata(client, data);

    mutex_init(&data->lock);

    err = lm3533_configure(client, data, lm3533_pdata);
    
    if (err < 0) {
        kfree(data);
        
    }

    dev_info(&client->dev, "lm3533 enabled\n");
    return 0;    

}

static int lm3533_remove(struct i2c_client *client)
{
    struct lm3533_platform_data *pdata = client->dev.platform_data;
    struct lm3533_data *data = i2c_get_clientdata(client);
    int i;

    printk(KERN_NOTICE "lm3533_remove \n");
    destroy_workqueue(LED_WorkQueue);

    for (i = 0; i < pdata->leds_size; i++)
    {
        led_classdev_unregister(&data->leds[i].ldev);
        cancel_work_sync(&data->leds[i].thread.work);
        cancel_work_sync(&data->leds[i].thread_register_keep.work);
        cancel_work_sync(&data->leds[i].thread_set_keep.work);
    }

    destroy_workqueue(bt_connected_wq);  //20140115 tracy add for led block after bluetooth connected
    kfree(data);

    return 0;
}

/* lm3533 i2c driver struct */
static const struct i2c_device_id lm3533_id[] = {
    {"lm3533_leds", 0},
    {}
};

MODULE_DEVICE_TABLE(i2c, lm3533_id);


#if 1  //tracy add for devices tree
static struct of_device_id ti_leds_lm3533_match_table[] = {
    { .compatible = "ti,lm3533_leds",},
    { },
};
#else
#define mxt_match_table NULL
#endif

static struct i2c_driver lm3533_driver = {
    .driver   = {
           .owner    = THIS_MODULE,    
           .name = LM3533_DRIVER_NAME,
           .of_match_table = ti_leds_lm3533_match_table,
    },
    .id_table   = lm3533_id,
     .probe      = lm3533_probe,
    .remove   = __devexit_p(lm3533_remove),        
};

static int __init lm3533_module_init(void)
{

    int init_int=0;

    gpio_request(18, "leds_lm3533_hwen");
    gpio_set_value(18, 1);

    init_int = i2c_add_driver(&lm3533_driver) ;

            
    printk(KERN_NOTICE "lm3533_module_init = %d \n",init_int);
    
    return init_int;
}

static void __exit lm3533_module_exit(void)
{
    i2c_del_driver(&lm3533_driver);
}

module_init(lm3533_module_init);
module_exit(lm3533_module_exit);

MODULE_DESCRIPTION("Back Light driver for LM3533");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Tracychui@Arimacomm");

