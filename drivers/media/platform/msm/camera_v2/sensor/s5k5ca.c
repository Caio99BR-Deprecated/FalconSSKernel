/* Copyright (c) 2011-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#include "msm_sensor.h"
#include "msm_cci.h"
#include "msm_camera_io_util.h"
#include "msm_camera_i2c_mux.h"

#define CONFIG_MSMB_CAMERA_DEBUG

#undef CDBG
#ifdef CONFIG_MSMB_CAMERA_DEBUG
#define CDBG(fmt, args...) pr_err(fmt, ##args)
#else
#define CDBG(fmt, args...) do { } while (0)
#endif

#define S5KCA_SENSOR_NAME "s5k5ca"
//#define PLATFORM_DRIVER_NAME "msm_camera_s5k5ca"
//#define s5k5ca_obj s5k5ca_##obj
DEFINE_MSM_MUTEX(s5k5ca_mut);
#define upgrate_setting 0
#define U_EV_1  1
#define U_EV_2  2
#define U_EV_3  3

static struct msm_sensor_ctrl_t s5k5ca_s_ctrl;
static int  HW_VERSION=0;
static int HW_VERSION_GPIO=0;
static int sensor_state = 0; // 0:init  1:preview  2:capture
static int global_current_brightness_state =0;
static int global_current_iso_state =0;
static int global_current_shutter_speed=0;//  0 do nothing; 1[2~3 fps];2[4~5 fps] ;3[6~7 fps];4 is  initial setting[7~15 fps]
static int reduce_party_cloudy_flag=0;
static int night_mode_flag=0;
static int night_mode_capture_flag=0;
static int night_mode_preview_flag=0;
static int current_scene_flag=0;
static struct msm_sensor_power_setting s5k5ca_power_setting[] = {
	{
		.seq_type = SENSOR_CLK,
		.seq_val = SENSOR_CAM_MCLK,
		.config_val = 24000000,
		.delay = 10,
	},

	{
		.seq_type = SENSOR_I2C_MUX,
		.seq_val = 0,
		.config_val = 0,
		.delay = 5,
	},
};
static struct msm_camera_i2c_reg_conf s5k5ca_recommend_settings[] = {
//#include "s5k5ca_yuv_mcnex_MCLK_19.2MHz.h"
#include "s5k5ca_yuv_mcnex_PVIMask_0x0012.h"
//#include "s5k5ca_yuv_mcnex.h"
};
#if 0
static struct msm_camera_i2c_reg_conf s5k5ca_start_settings[] = {
};

static struct msm_camera_i2c_reg_conf s5k5ca_stop_settings[] = {
};
#endif
/*
    CAM_WB_MODE_AUTO,
    CAM_WB_MODE_CUSTOM,
    CAM_WB_MODE_INCANDESCENT,
    CAM_WB_MODE_FLUORESCENT,
    CAM_WB_MODE_WARM_FLUORESCENT,
    CAM_WB_MODE_DAYLIGHT,
    CAM_WB_MODE_CLOUDY_DAYLIGHT,
    CAM_WB_MODE_TWILIGHT,
    CAM_WB_MODE_SHADE,
    CAM_WB_MODE_OFF,
    CAM_WB_MODE_MAX
*/
static struct msm_camera_i2c_reg_conf s5k5ca_wb_oem[][10] = {
	{{0x0028, 0x7000}, {0x002a, 0x04D2},  {0x0f12, 0x067F},},/*CAM_WB_MODE_AUTO*/

	{{0},},	/*CAM_WB_MODE_CUSTOM*/

	{{0x0028,0x7000}, {0x002A,0x04D2}, {0x0F12,0x0677}, {0x002A,0x04A0}, {0x0f12,0x0405}, 
	{0x0f12,0x0001}, {0x0f12,0x0400}, {0x0f12,0x0001},  {0x0f12,0x0810}, {0x0f12,0x0001},},	/*CAM_WB_MODE_INCANDESCENT*/

	{{0x0028,0x7000}, {0x002A,0x04D2}, {0x0F12,0x0677}, {0x002A,0x04A0}, {0x0F12,0x0460},
	{0x0F12,0x0001}, {0x0F12,0x0400}, {0x0F12,0x0001}, {0x0F12,0x073C}, {0x0F12,0x0001},},	/*CAM_WB_MODE_FLUORESCENT*/

	{{0},},	/*CAM_WB_MODE_WARM_FLUORESCENT*/

	{{0x0028,0x7000}, {0x002A,0x04D2}, {0x0F12,0x0677},  {0x002A,0x04A0}, {0x0f12,0x0510}, 
	{0x0f12,0x0001}, {0x0f12,0x0400}, {0x0f12,0x0001}, {0x0f12,0x05A0}, {0x0f12,0x0001},},	/*CAM_WB_MODE_DAYLIGHT */

	{{0x0028,0x7000}, {0x002A,0x04D2}, {0x0F12,0x0677}, {0x002A,0x04A0}, {0x0f12,0x05d0},  
	{0x0f12,0x0001}, {0x0f12,0x0400}, {0x0f12,0x0001}, {0x0f12,0x0583}, {0x0f12,0x0001},},	/*CAM_WB_MODE_CLOUDY*/
	{{0},},	/*CAM_WB_MODE_SHADE*/
	{{0},},	/*CAM_WB_MODE_OFF*/
	{{0},},	/*CAM_WB_MODE_OFF*/
};

static uint16_t s5k5ca_wb_size[] = {3,0,10,10,0,10,10,0,0,0};
#if upgrate_setting
static uint16_t s5k5ca_best_shot_size[] = {70,20,10,44,6,42,16,10,10};
#else
static uint16_t s5k5ca_best_shot_size[] = {61,44,10,60,44,40,16,3,10};
#endif
static struct msm_camera_i2c_reg_conf s5k5ca_best_shot[][70] = {
{// ----------------Normal-70
#if upgrate_setting
{ 0x0028, 0x7000},{ 0x002a, 0x246E},{ 0x0f12, 0x0001},{ 0x002A, 0x0842},{ 0x0F12, 0x7850},
{ 0x0F12, 0x2878},{ 0x002A, 0x0912},{ 0x0F12, 0x643C},{ 0x0F12, 0x2864},{ 0x002A, 0x09E2},
{ 0x0F12, 0x3C2A},{ 0x0F12, 0x283C},{ 0x002A, 0x0AB2},{ 0x0F12, 0x2228},{ 0x0F12, 0x2822},
{ 0x002A, 0x0B82},{ 0x0F12, 0x191C},{ 0x0F12, 0x2819},{ 0x0028, 0x7000},{ 0x002A, 0x020C},
{ 0x0F12, 0x0000},{ 0x002A, 0x0210},{ 0x0F12, 0x0000},{ 0x0F12, 0x0000},{ 0x002A, 0x0838},
{ 0x0F12, 0x083C},{ 0x002A, 0x0530},{ 0x0F12, 0x3A98},{ 0x002A, 0x0534},{ 0x0F12, 0x7EF4},
{ 0x002A, 0x167C},{ 0x0F12, 0x9C40},{ 0x002A, 0x1680},{ 0x0F12, 0xF424},{ 0x0F12, 0x0000},
{ 0x002A, 0x0538},{ 0x0F12, 0x3A98},{ 0x0F12, 0x0000},{ 0x0F12, 0x7EF4},{ 0x0F12, 0x0000},
{ 0x002A, 0x1684},{ 0x0F12, 0x9C40},{ 0x0F12, 0x0000},{ 0x0F12, 0xF424},{ 0x0F12, 0x0000},
{ 0x002A, 0x0540},{ 0x0F12, 0x0170},{ 0x0F12, 0x0250},{ 0x002A, 0x168C},{ 0x0F12, 0x0380},
{ 0x0F12, 0x0800},{ 0x002A, 0x0544},{ 0x0F12, 0x0100},{ 0x002A, 0x0208},{ 0x0F12, 0x0001},
{ 0x002A, 0x023C},{ 0x0F12, 0x0000},{ 0x002A, 0x0240},{ 0x0F12, 0x0001},{ 0x002A, 0x0230},
{ 0x0F12, 0x0001},{ 0x002A, 0x023E},{ 0x0F12, 0x0001},{ 0x002A, 0x0220},{ 0x0F12, 0x0001},
{ 0x0028, 0xD000},{ 0x002A, 0xB0A0},{ 0x0F12, 0x0000},{ 0x002A, 0x0222},{ 0x0F12, 0x0001},
#else
//scene mode normal
{0xFCFC, 0xD000},{0x0028, 0x7000},{0x002A, 0x020C},{0x0F12, 0x0000},{0x002A, 0x0210},
{0x0F12, 0x0000},{0x0F12, 0x0000},{0xfcfc, 0xd000},{0x0028, 0x7000},{0x002A, 0x12B8},
{0x0F12, 0x0B00},{0x002A, 0x0530},{0x0F12, 0x3A98},{0x0F12, 0x0000},{0x0F12, 0x7EF4},
{0x0F12, 0x0000},{0x002A, 0x167C},{0x0F12, 0x9C40},{0x0F12, 0x0000},{0x0F12, 0xF424},
{0x0F12, 0x0000},{0x002A, 0x0538},{0x0F12, 0x3A98},{0x0F12, 0x0000},{0x0F12, 0x7EF4},
{0x0F12, 0x0000},{0x002A, 0x1684},{0x0F12, 0x9C40},{0x0F12, 0x0000},{0x0F12, 0xF424},
{0x0F12, 0x0000},{0x002A, 0x0540},{0x0F12, 0x0170},{0x0F12, 0x0250},{0x002A, 0x168C},
{0x0F12, 0x0380},{0x0F12, 0x0800},{0x002A, 0x0544},{0x0F12, 0x0100},{0x0F12, 0x0800},
{0x002A, 0x04B4},{0x0F12, 0x0000},{0x0F12, 0x0000},{0x0F12, 0x0001},{0x0028, 0x7000}, 
{0x002A, 0x023C},{0x0F12, 0x0000},{0x002A, 0x0240},{0x0F12, 0x0001},{0x002A, 0x0230}, 
{0x0F12, 0x0001},{0x002A, 0x023E},{0x0F12, 0x0001},{0x002A, 0x0220},{0x0F12, 0x0001},  
{0x0028, 0xD000},{0x002A, 0xB0A0},{0x0F12, 0x0000},{0x0028, 0x7000},{0x002A, 0x0222}, 
{0x0F12, 0x0001}, 
#endif
},

{//-------------------Landscape-20
#if upgrate_setting
{ 0x0028, 0x7000},{ 0x002A, 0x020C},{ 0x0F12, 0x0000},{ 0x002A, 0x0210},{ 0x0F12, 0x001E},
{ 0x002A, 0x0842},{ 0x0F12, 0x6444},{ 0x0F12, 0x465A},{ 0x002A, 0x0912},{ 0x0F12, 0x4B3A},
{ 0x0F12, 0x463F},{ 0x002A, 0x09E2},{ 0x0F12, 0x1A2D},{ 0x0F12, 0x4628},{ 0x002A, 0x0AB2},
{ 0x0F12, 0x1328},{ 0x0F12, 0x3213},{ 0x002A, 0x0B82},{ 0x0F12, 0x0819},{ 0x0F12, 0x3204},
#else
//land scape    
{0xFCFC,0xD000},{0x0028,0x7000},{0x002A,0x020C},{0x0F12,0x0000},{0x002A,0x0210},
{0x0F12,0x001E},{0x0F12,0x000A},{0xfcfc,0xd000},{0x0028,0x7000},{0x002A,0x12B8},
{0x0F12,0x0B00},{0x002A,0x0530},{0x0F12,0x3A98},{0x0F12,0x0000},{0x0F12,0x7EF4},
{0x0F12,0x0000},{0x002A,0x167C},{0x0F12,0x9C40},{0x0F12,0x0000},{0x0F12,0xF424},
{0x0F12,0x0000},{0x002A,0x0538},{0x0F12,0x3A98},{0x0F12,0x0000},{0x0F12,0x7EF4},
{0x0F12,0x0000},{0x002A,0x1684},{0x0F12,0x9C40},{0x0F12,0x0000},{0x0F12,0xF424},
{0x0F12,0x0000},{0x002A,0x0540},{0x0F12,0x0170},{0x0F12,0x0250},{0x002A,0x168C},
{0x0F12,0x0380},{0x0F12,0x0800},{0x002A,0x0544},{0x0F12,0x0100},{0x0F12,0x0800},
{0x002A,0x04B4},{0x0F12,0x0000},{0x0F12,0x0000},{0x0F12,0x0001},
#endif
},

{//---------------------Sunset -10
{ 0x0028, 0x7000},{ 0x002a, 0x246E},{ 0x0f12, 0x0000},{ 0x002a, 0x04A0},{ 0x0f12, 0x05E0},
{ 0x0f12, 0x0001},{ 0x0f12, 0x0400},{ 0x0f12, 0x0001},{ 0x0f12, 0x0520},{ 0x0f12, 0x0001},
},

{//----------------------Night-44
#if 0
{0x0028, 0x7000},{0x002A, 0x0530},{0x0F12, 0x3415},{0x002A, 0x0534},{0x0F12, 0x682A},
{0x002A, 0x167C},{0x0F12, 0x8235},{0x002A, 0x1680},{0x0F12, 0x1A80},{0x0F12, 0x0006},
{0x002A, 0x0538},{0x0F12, 0x3415},{0x002A, 0x053C},{0x0F12, 0x682A},{0x002A, 0x1684},
{0x0F12, 0x8235},{0x002A, 0x1688},{0x0F12, 0x1A80},{0x0F12, 0x0006},{0x002A, 0x0540},
{0x0F12, 0x0180},{0x0F12, 0x0250},{0x002A, 0x168C},{0x0F12, 0x0340},{0x0F12, 0x0820},
{0x002A, 0x0544},{0x0F12, 0x0100},{0x0028, 0x7000},{0x002A, 0x023C},{0x0F12, 0x0002}, 
{0x002A, 0x0240},{0x0F12, 0x0001},{0x002A, 0x0230},{0x0F12, 0x0001},{0x002A, 0x023E}, 
{0x0F12, 0x0001},{0x002A, 0x0220},{0x0F12, 0x0001},{0x0028, 0xD000},{0x002A, 0xB0A0}, 
{0x0F12, 0x0000},{0x0028, 0x7000},{0x002A, 0x0222},{0x0F12, 0x0001}, 
#else
{0xFCFC,0xD000},{0x0028 ,0x7000},{0x002A,0x020C},{0x0F12,0x0000},{0x002A,0x0210}, 
{0x0F12,0x0000},{0x0F12 ,0x0000},{0xFCFC,0xD000},{0x0028,0x7000},{0x002A,0x12B8}, 
{0x0F12,0x0B00},{0x0028 ,0x7000},{0x002A,0x0530},{0x0F12,0x3415},{0x002A,0x0534}, 
{0x0F12,0x682A},{0x002A ,0x167C},{0x0F12,0x8235},{0x002A,0x1680},{0x0F12,0x1A80}, 
{0x0F12,0x0006},{0x002A ,0x0538},{0x0F12,0x3415},{0x002A,0x053C},{0x0F12,0x682A}, 
{0x002A,0x1684},{0x0F12 ,0x8235},{0x002A,0x1688},{0x0F12,0x1A80},{0x0F12,0x0006}, 
{0x002A,0x0540},{0x0F12 ,0x0180},{0x0F12,0x0250},{0x002A,0x168C},{0x0F12,0x0340}, 
{0x0F12,0x0820},{0x002A ,0x0544},{0x0F12,0x0100},{0x0F12,0x0800},{0x002A,0x04B4}, 
{0x0F12,0x0000},{0x0F12 ,0x0000},{0x0F12,0x0001},{0x0028,0x7000},{0x002A,0x023C}, 
{0x0F12,0x0002},{0x002A ,0x0240},{0x0F12,0x0001},{0x002A,0x0230},{0x0F12,0x0001}, 
{0x002A,0x023E},{0x0F12 ,0x0001},{0x002A,0x0220},{0x0F12,0x0001},{0x0028,0xD000}, 
{0x002A,0xB0A0},{0x0F12 ,0x0000},{0x0028,0x7000},{0x002A,0x0222},{0x0F12,0x0001}, 


#endif
},

{//----------------------Portrait-6
#if upgrate_setting
{0x0028,0x7000},{0x002A,0x020C},{0x0F12,0x0000},{0x002A,0x0210},{0x0F12,0x0000},
{0x0F12,0xFFCC},
#else
//portrait      
{0xFCFC,0xD000},{0x0028,0x7000},{0x002A,0x020C},{0x0F12,0x0000},{0x002A,0x0210},
{0x0F12,0x0000},{0x0F12,0xFFF6},{0xfcfc,0xd000},{0x0028,0x7000},{0x002A,0x12B8},
{0x0F12,0x0B00},{0x002A,0x0530},{0x0F12,0x3A98},{0x0F12,0x0000},{0x0F12,0x7EF4},
{0x0F12,0x0000},{0x002A,0x167C},{0x0F12,0x9C40},{0x0F12,0x0000},{0x0F12,0xF424},
{0x0F12,0x0000},{0x002A,0x0538},{0x0F12,0x3A98},{0x0F12,0x0000},{0x0F12,0x7EF4},
{0x0F12,0x0000},{0x002A,0x1684},{0x0F12,0x9C40},{0x0F12,0x0000},{0x0F12,0xF424},
{0x0F12,0x0000},{0x002A,0x0540},{0x0F12,0x0170},{0x0F12,0x0250},{0x002A,0x168C},
{0x0F12,0x0380},{0x0F12,0x0800},{0x002A,0x0544},{0x0F12,0x0100},{0x0F12,0x0800},
{0x002A,0x04B4},{0x0F12,0x0000},{0x0F12,0x0000},{0x0F12,0x0001},
#endif
},

{//----------------------Sports-42
#if upgrate_setting
{0x0028, 0x7000},{0x002A, 0x0530},{0x0F12, 0x1A0A},{0x002A, 0x0534},{0x0F12, 0x4e20},
{0x002A, 0x167C},{0x0F12, 0x682A},{0x002A, 0x1680},{0x0F12, 0x8235},{0x0F12, 0x0000},
{0x002A, 0x0538},{0x0F12, 0x1A0A},{0x002A, 0x053C},{0x0F12, 0x4e20},{0x002A, 0x1684},
{0x0F12, 0x682A},{0x002A, 0x1688},{0x0F12, 0x8235},{0x0F12, 0x0000},{0x002A, 0x0540},
{0x0F12, 0x0300},{0x0F12, 0x0380},{0x002A, 0x168C},{0x0F12, 0x0480},{0x0F12, 0x0800},        
{0x002A, 0x0544},{0x0F12, 0x0100},{0x002A, 0x023C},{0x0F12, 0x0000},{0x002A, 0x0240},
{0x0F12, 0x0001},{0x002A, 0x0230},{0x0F12, 0x0001},{0x002A, 0x023E},{0x0F12, 0x0001},
{0x002A, 0x0220},{0x0F12, 0x0001},{0x0028, 0xD000},{0x002A, 0xB0A0},{0x0F12, 0x0000},  
{0x002A, 0x0222},{0x0F12, 0x0001},
#else
//sport         
{0xFCFC,0xD000},{0x0028,0x7000},{0x002A,0x020C},{0x0F12,0x0000},{0x002A,0x0210},
{0x0F12,0x0000},{0x0F12,0x0000},{0xfcfc,0xd000},{0x0028,0x7000},{0x002A,0x12B8},
{0x0F12,0x2000},{0x002A,0x0530},{0x0F12,0x36B0},{0x002A,0x0534},{0x0F12,0x36B0},
{0x002A,0x167C},{0x0F12,0x36B0},{0x002A,0x1680},{0x0F12,0x36B0},{0x002A,0x0538},
{0x0F12,0x36B0},{0x002A,0x053C},{0x0F12,0x36B0},{0x002A,0x1684},{0x0F12,0x36B0},
{0x002A,0x1688},{0x0F12,0x36B0},{0x002A,0x0540},{0x0F12,0x0200},{0x0F12,0x0200},
{0x002A,0x168C},{0x0F12,0x0200},{0x0F12,0x0200},{0x002A,0x0544},{0x0F12,0x0100},
{0x0F12,0x8000},{0x002A,0x04B4},{0x0F12,0x0001},{0x0F12,0x00C8},{0x0F12,0x0001},
#endif
},

{//-------------------Text->flower-16
{ 0x0028, 0x7000},{ 0x002A, 0x0842},{ 0x0F12, 0x5C44},{ 0x0F12, 0x4656},{ 0x002A, 0x0912},
{ 0x0F12, 0x433A},{ 0x0F12, 0x463B},{ 0x002A, 0x09E2},{ 0x0F12, 0x122D},{ 0x0F12, 0x4624},
{ 0x002A, 0x0AB2},{ 0x0F12, 0x0B28},{ 0x0F12, 0x320F},{ 0x002A, 0x0B82},{ 0x0F12, 0x0010},
{ 0x0F12, 0x3200},
},

{//-------------------Cloudy

//{0x0028,0x7000},{0x002A,0x04D2},{0x0F12,0x0677},{0x002A,0x04A0},{0x0F12,0x0510},
//{0x0F12,0x0001},{0x0F12,0x0400},{0x0F12,0x0001},{0x0F12,0x0740},{0x0F12,0x0001},
{0x0028,0x7000},{0x002A,0x020C},{0x0F12,0x004D},

},
{//-------------------Party       
#if 0
{0x0028,0x7000},{0x002A,0x04D2},{0x0F12,0x0677},{0x002A,0x04A0},{0x0F12,0x0545},
{0x0F12,0x0001},{0x0F12,0x0400},{0x0F12,0x0001},{0x0F12,0x0640},{0x0F12,0x0001},
{0x0028,0x7000},{0x002A,0x020C},{0x0F12,0x0000},
#else //use wb -cloudy setting
{0x0028,0x7000}, {0x002A,0x04D2}, {0x0F12,0x0677}, {0x002A,0x04A0}, {0x0f12,0x05C8},  
{0x0f12,0x0001}, {0x0f12,0x0400}, {0x0f12,0x0001}, {0x0f12,0x0583}, {0x0f12,0x0001},
#endif
},

};
#if 1
static uint16_t s5k5ca_special_effect_size[] = {5,5,5,5,5,5};
static struct msm_camera_i2c_reg_conf s5k5ca_special_effect[][5] = {
	{{0x0028,0x7000}, {0x002a,0x021E}, {0x0F12,0x0000}, {0x002a,0x021E}, {0x0F12,0x0000}},	// off
	{{0x0028,0x7000}, {0x002a,0x021E}, {0x0F12,0x0000}, {0x002a,0x021E}, {0x0F12,0x0001}},	// mono
	{{0x0028,0x7000}, {0x002a,0x021E}, {0x0F12,0x0000}, {0x002a,0x021E}, {0x0F12,0x0003}},	//negative
	{{0x0028,0x7000}, {0x002a,0x021E}, {0x0F12,0x0000}, {0x002a,0x021E}, {0x0F12,0x0004}},	//sepia
	{{0x0028,0x7000}, {0x002a,0x021E}, {0x0F12,0x0000}, {0x002a,0x021E}, {0x0F12,0x0005}},	//aqua
	{{0x0028,0x7000}, {0x002a,0x021E}, {0x0F12,0x0000}, {0x002a,0x021E}, {0x0F12,0x0006}},	//sketch
};
#endif
#if upgrate_setting
static uint16_t s5k5ca_iso_size[] = {5,5,5,5};
static struct msm_camera_i2c_reg_conf s5k5ca_iso[][5] = {
	
	{{0x0028 ,0x7000}, {0x002A ,0x04B4}, {0x0F12 ,0x0000}, {0x0F12 ,0x0000}, {0x0F12 ,0x0001},},	// off
	{{0x0028 ,0x7000}, {0x002A ,0x04B4}, {0x0F12 ,0x0001}, {0x0F12 ,0x0064}, {0x0F12 ,0x0001},}, // 100
	{{0x0028 ,0x7000}, {0x002A ,0x04B4}, {0x0F12 ,0x0001}, {0x0F12 ,0x00C8}, {0x0F12 ,0x0001},}, // 200
	{{0x0028 ,0x7000}, {0x002A ,0x04B4}, {0x0F12 ,0x0001}, {0x0F12 ,0x0190}, {0x0F12 ,0x0001},}, // 400
#else
static uint16_t s5k5ca_iso_size[] = {37,33,33,33,33,33,33,33,33,33,33};
static struct msm_camera_i2c_reg_conf s5k5ca_iso[][37] = {
{
//ISO auto
{0xfcfc,0xd000},{0x0028,0x7000},{0x002A,0x12B8},{0x0F12,0x0B00},{0x002A,0x0530}, 
{0x0F12,0x3A98},{0x0F12,0x0000},{0x0F12,0x7EF4},{0x0F12,0x0000},{0x002A,0x167C}, 
{0x0F12,0x9C40},{0x0F12,0x0000},{0x0F12,0xF424},{0x0F12,0x0000},{0x002A,0x0538}, 
{0x0F12,0x3A98},{0x0F12,0x0000},{0x0F12,0x7EF4},{0x0F12,0x0000},{0x002A,0x1684}, 
{0x0F12,0x9C40},{0x0F12,0x0000},{0x0F12,0xF424},{0x0F12,0x0000},{0x002A,0x0540},
{0x0F12,0x0170},{0x0F12,0x0250},{0x002A,0x168C},{0x0F12,0x0380},{0x0F12,0x0800},              
{0x002A,0x0544},{0x0F12,0x0100},{0x0F12,0x0800},{0x002A,0x04B4},{0x0F12,0x0000},
{0x0F12,0x0000},{0x0F12,0x0001}      
},	
{//iso 100
{0xfcfc,0xd000},{0x0028,0x7000},{0x002A,0x12B8},{0x0F12,0x1800},{0x002A,0x0530},   	                                                    
{0x0F12,0xC350},{0x002A,0x0534},{0x0F12,0xC350},{0x002A,0x167C},{0x0F12,0xC350},          
{0x002A,0x1680},{0x0F12,0xc350},{0x002A,0x0538},{0x0F12,0xC350},{0x002A,0x053C},                       
{0x0F12,0xC350},{0x002A,0x1684},{0x0F12,0xC350},{0x002A,0x1688},{0x0F12,0xC350},                       
{0x002A,0x0540},{0x0F12,0x0200},{0x0F12,0x0200},{0x002A,0x168C},{0x0F12,0x0200},                             
{0x0F12,0x0200},{0x002A,0x0544},{0x0F12,0x0100},{0x0F12,0x8000},{0x002A,0x04B4},     
{0x0F12,0x0001},{0x0F12,0x0096},{0x0F12,0x0001}
},
{//iso 200
{0xfcfc,0xd000},{0x0028,0x7000},{0x002A,0x12B8},{0x0F12,0x2000},{0x002A,0x0530},   	                                                    
{0x0F12,0xC350},{0x002A,0x0534},{0x0F12,0xC350},{0x002A,0x167C},{0x0F12,0xC350},                      
{0x002A,0x1680},{0x0F12,0xc350},{0x002A,0x0538},{0x0F12,0xC350},{0x002A,0x053C},                                               
{0x0F12,0xC350},{0x002A,0x1684},{0x0F12,0xC350},{0x002A,0x1688},{0x0F12,0xC350},                             
{0x002A,0x0540},{0x0F12,0x0200},{0x0F12,0x0200},{0x002A,0x168C},{0x0F12,0x0200},                             
{0x0F12,0x0200},{0x002A,0x0544},{0x0F12,0x0100},{0x0F12,0x8000},{0x002A,0x04B4},  
{0x0F12,0x0001},{0x0F12,0x00C8},{0x0F12,0x0001}         
},
{//iso400       
{0xfcfc,0xd000},{0x0028,0x7000},{0x002A,0x12B8},{0x0F12,0x3000},{0x002A,0x0530},
{0x0F12,0xC350},{0x002A,0x0534},{0x0F12,0xC350},{0x002A,0x167C},{0x0F12,0xC350},
{0x002A,0x1680},{0x0F12,0xc350},{0x002A,0x0538},{0x0F12,0xC350},{0x002A,0x053C},
{0x0F12,0xC350},{0x002A,0x1684},{0x0F12,0xC350},{0x002A,0x1688},{0x0F12,0xC350},
{0x002A,0x0540},{0x0F12,0x0200},{0x0F12,0x0200},{0x002A,0x168C},{0x0F12,0x0200},
{0x0F12,0x0200},{0x002A,0x0544},{0x0F12,0x0100},{0x0F12,0x8000},{0x002A,0x04B4},
{0x0F12,0x0001},{0x0F12,0x0190},{0x0F12,0x0001}
},
{//iso 800       
{0xfcfc,0xd000},{0x0028,0x7000},{0x002A,0x12B8},{0x0F12,0x4000},{0x002A,0x0530},
{0x0F12,0xC350},{0x002A,0x0534},{0x0F12,0xC350},{0x002A,0x167C},{0x0F12,0xC350},
{0x002A,0x1680},{0x0F12,0xc350},{0x002A,0x0538},{0x0F12,0xC350},{0x002A,0x053C},
{0x0F12,0xC350},{0x002A,0x1684},{0x0F12,0xC350},{0x002A,0x1688},{0x0F12,0xC350},
{0x002A,0x0540},{0x0F12,0x0200},{0x0F12,0x0200},{0x002A,0x168C},{0x0F12,0x0200},
{0x0F12,0x0200},{0x002A,0x0544},{0x0F12,0x0100},{0x0F12,0x8000},{0x002A,0x04B4},
{0x0F12,0x0001},{0x0F12,0x0320},{0x0F12,0x0001},

},
{//iso 1600       
{0xfcfc,0xd000},{0x0028,0x7000},{0x002A,0x12B8},{0x0F12,0x4000},{0x002A,0x0530},
{0x0F12,0xC350},{0x002A,0x0534},{0x0F12,0xC350},{0x002A,0x167C},{0x0F12,0xC350},
{0x002A,0x1680},{0x0F12,0xc350},{0x002A,0x0538},{0x0F12,0xC350},{0x002A,0x053C},
{0x0F12,0xC350},{0x002A,0x1684},{0x0F12,0xC350},{0x002A,0x1688},{0x0F12,0xC350},
{0x002A,0x0540},{0x0F12,0x0200},{0x0F12,0x0200},{0x002A,0x168C},{0x0F12,0x0200},
{0x0F12,0x0200},{0x002A,0x0544},{0x0F12,0x0100},{0x0F12,0x8000},{0x002A,0x04B4},
{0x0F12,0x0001},{0x0F12,0x0640},{0x0F12,0x0001},
},
{//iso 300      
{0xfcfc,0xd000},{0x0028,0x7000},{0x002A,0x12B8},{0x0F12,0x4000},{0x002A,0x0530},
{0x0F12,0xC350},{0x002A,0x0534},{0x0F12,0xC350},{0x002A,0x167C},{0x0F12,0xC350},
{0x002A,0x1680},{0x0F12,0xc350},{0x002A,0x0538},{0x0F12,0xC350},{0x002A,0x053C},
{0x0F12,0xC350},{0x002A,0x1684},{0x0F12,0xC350},{0x002A,0x1688},{0x0F12,0xC350},
{0x002A,0x0540},{0x0F12,0x0200},{0x0F12,0x0200},{0x002A,0x168C},{0x0F12,0x0200},
{0x0F12,0x0200},{0x002A,0x0544},{0x0F12,0x0100},{0x0F12,0x8000},{0x002A,0x04B4},
{0x0F12,0x0001},{0x0F12,0x012c},{0x0F12,0x0001},
},
{//iso 900       
{0xfcfc,0xd000},{0x0028,0x7000},{0x002A,0x12B8},{0x0F12,0x4000},{0x002A,0x0530},
{0x0F12,0xC350},{0x002A,0x0534},{0x0F12,0xC350},{0x002A,0x167C},{0x0F12,0xC350},
{0x002A,0x1680},{0x0F12,0xc350},{0x002A,0x0538},{0x0F12,0xC350},{0x002A,0x053C},
{0x0F12,0xC350},{0x002A,0x1684},{0x0F12,0xC350},{0x002A,0x1688},{0x0F12,0xC350},
{0x002A,0x0540},{0x0F12,0x0200},{0x0F12,0x0200},{0x002A,0x168C},{0x0F12,0x0200},
{0x0F12,0x0200},{0x002A,0x0544},{0x0F12,0x0100},{0x0F12,0x8000},{0x002A,0x04B4},
{0x0F12,0x0001},{0x0F12,0x0384},{0x0F12,0x0001},
},
{//iso500       
{0xfcfc,0xd000},{0x0028,0x7000},{0x002A,0x12B8},{0x0F12,0x3000},{0x002A,0x0530},
{0x0F12,0xC350},{0x002A,0x0534},{0x0F12,0xC350},{0x002A,0x167C},{0x0F12,0xC350},
{0x002A,0x1680},{0x0F12,0xc350},{0x002A,0x0538},{0x0F12,0xC350},{0x002A,0x053C},
{0x0F12,0xC350},{0x002A,0x1684},{0x0F12,0xC350},{0x002A,0x1688},{0x0F12,0xC350},
{0x002A,0x0540},{0x0F12,0x0200},{0x0F12,0x0200},{0x002A,0x168C},{0x0F12,0x0200},
{0x0F12,0x0200},{0x002A,0x0544},{0x0F12,0x0100},{0x0F12,0x8000},{0x002A,0x04B4},
{0x0F12,0x0001},{0x0F12,0x01F4},{0x0F12,0x0001},
},
{//iso600       
{0xfcfc,0xd000},{0x0028,0x7000},{0x002A,0x12B8},{0x0F12,0x3000},{0x002A,0x0530},
{0x0F12,0xC350},{0x002A,0x0534},{0x0F12,0xC350},{0x002A,0x167C},{0x0F12,0xC350},
{0x002A,0x1680},{0x0F12,0xc350},{0x002A,0x0538},{0x0F12,0xC350},{0x002A,0x053C},
{0x0F12,0xC350},{0x002A,0x1684},{0x0F12,0xC350},{0x002A,0x1688},{0x0F12,0xC350},
{0x002A,0x0540},{0x0F12,0x0200},{0x0F12,0x0200},{0x002A,0x168C},{0x0F12,0x0200},
{0x0F12,0x0200},{0x002A,0x0544},{0x0F12,0x0100},{0x0F12,0x8000},{0x002A,0x04B4},
{0x0F12,0x0001},{0x0F12,0x0258},{0x0F12,0x0001},
},
{//iso 700       
{0xfcfc,0xd000},{0x0028,0x7000},{0x002A,0x12B8},{0x0F12,0x4000},{0x002A,0x0530},
{0x0F12,0xC350},{0x002A,0x0534},{0x0F12,0xC350},{0x002A,0x167C},{0x0F12,0xC350},
{0x002A,0x1680},{0x0F12,0xc350},{0x002A,0x0538},{0x0F12,0xC350},{0x002A,0x053C},
{0x0F12,0xC350},{0x002A,0x1684},{0x0F12,0xC350},{0x002A,0x1688},{0x0F12,0xC350},
{0x002A,0x0540},{0x0F12,0x0200},{0x0F12,0x0200},{0x002A,0x168C},{0x0F12,0x0200},
{0x0F12,0x0200},{0x002A,0x0544},{0x0F12,0x0100},{0x0F12,0x8000},{0x002A,0x04B4},
{0x0F12,0x0001},{0x0F12,0x02BC},{0x0F12,0x0001},
},

#endif	
	
};
static struct msm_camera_i2c_reg_conf s5k5ca_preview_settings[] = {
	{0x0028, 0x7000 }, 
	{0x002A, 0x023C }, 
	{0x0F12, 0x0000 }, //REG_TC_GP_ActivePrevConfig
	{0x002A, 0x0240 }, 
	{0x0F12, 0x0001 },  //REG_TC_GP_PrevOpenAfterChange
	{0x002A, 0x0230 }, 
	{0x0F12, 0x0001 },  //REG_TC_GP_NewConfigSync
	{0x002A, 0x023E }, 
	{0x0F12, 0x0001 },  //REG_TC_GP_PrevConfigChanged
	{0x002A, 0x0220 }, 
	{0x0F12, 0x0001 },  //REG_TC_GP_EnablePreview
	{0x0028, 0xD000 }, 
	{0x002A, 0xB0A0 }, 
	{0x0F12, 0x0000 }, // Clear cont. clock befor config change
	{0x0028, 0x7000 }, 
	{0x002A, 0x0222 }, 
	{0x0F12, 0x0001 }, //REG_TC_GP_EnablePreviewChanged
	//increase preview brightness setting to 0x0053
	{0x0028, 0x7000 },
	{0x002A, 0x0F70	},
	{0x0F12, 0x0053	}, 
};
static struct msm_camera_i2c_reg_conf s5k5ca_capture_normal_mode_settings[] = {
	//$MIPI[Width:2048,Height:1536,Format:YUV422,Lane:1,ErrorCheck:0,PolarityData:0,PolarityClock:0,Buffer:2,DataRate:928] 
	{0x0028, 0x7000 },
	{0x002A, 0x0244 },
	{0x0F12, 0x0000 }, //REG_TC_GP_ActiveCapConfig
	{0x002A, 0x0230 },
	{0x0F12, 0x0001 }, //REG_TC_GP_NewConfigSync
	{0x002A, 0x0246 },
	{0x0F12, 0x0001 }, //REG_TC_GP_CapConfigChanged
	{0x002A, 0x0224 },
	{0x0F12, 0x0001 }, //REG_TC_GP_EnableCapture
	{0x0028, 0xD000 },
	{0x002A, 0xB0A0 },
	{0x0F12, 0x0000 }, // Clear cont. clock befor config change
	{0x0028, 0x7000 },
	{0x002A, 0x0226 },
	{0x0F12, 0x0001 },  //REG_TC_GP_EnableCaptureChanged
};
static struct msm_camera_i2c_reg_conf s5k5ca_capture_night_mode_settings[] = {
	//$MIPI[Width:2048,Height:1536,Format:YUV422,Lane:1,ErrorCheck:0,PolarityData:0,PolarityClock:0,Buffer:2,DataRate:928] 
	{0x0028, 0x7000 },
	{0x002A, 0x0244 },
	{0x0F12, 0x0001 }, //REG_TC_GP_ActiveCapConfig
	{0x002A, 0x0230 },
	{0x0F12, 0x0001 }, //REG_TC_GP_NewConfigSync
	{0x002A, 0x0246 },
	{0x0F12, 0x0001 }, //REG_TC_GP_CapConfigChanged
	{0x002A, 0x0224 },
	{0x0F12, 0x0001 }, //REG_TC_GP_EnableCapture
	{0x0028, 0xD000 },
	{0x002A, 0xB0A0 },
	{0x0F12, 0x0000 }, // Clear cont. clock befor config change
	{0x0028, 0x7000 },
	{0x002A, 0x0226 },
	{0x0F12, 0x0001 },  //REG_TC_GP_EnableCaptureChanged
};
static struct v4l2_subdev_info s5k5ca_subdev_info[] = {
	{
		.code   = V4L2_MBUS_FMT_YUYV8_2X8,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.fmt    = 1,
		.order  = 0,
	},
};

static const struct i2c_device_id s5k5ca_i2c_id[] = {
	{S5KCA_SENSOR_NAME, (kernel_ulong_t)&s5k5ca_s_ctrl},
	{ }
};

static int32_t msm_s5k5ca_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	CDBG("%s, E.", __func__);
	CDBG("%x, E.",client->addr);

	return msm_sensor_i2c_probe(client, id, &s5k5ca_s_ctrl);
}

static struct i2c_driver s5k5ca_i2c_driver = {
	.id_table = s5k5ca_i2c_id,
	.probe  = msm_s5k5ca_i2c_probe,
	.driver = {
		.name = S5KCA_SENSOR_NAME,
	},
};

static struct msm_camera_i2c_client s5k5ca_sensor_i2c_client = {
	.addr_type = MSM_CAMERA_I2C_WORD_ADDR,
};

static const struct of_device_id s5k5ca_dt_match[] = {
	{.compatible = "qcom,s5k5ca", .data = &s5k5ca_s_ctrl},
	{}
};

MODULE_DEVICE_TABLE(of, s5k5ca_dt_match);

static struct platform_driver s5k5ca_platform_driver = {
	.driver = {
		.name = "qcom,s5k5ca",
		.owner = THIS_MODULE,
		.of_match_table = s5k5ca_dt_match,
	},
};

static int32_t s5k5ca_platform_probe(struct platform_device *pdev)
{
	int32_t rc;
	const struct of_device_id *match;
	CDBG("%s, E.", __func__);
	match = of_match_device(s5k5ca_dt_match, &pdev->dev);
	rc = msm_sensor_platform_probe(pdev, match->data);
	return rc;
}

static int __init s5k5ca_init_module(void)
{
	int32_t rc;
	pr_err("peter: %s:%d\n", __func__, __LINE__);
	rc = platform_driver_probe(&s5k5ca_platform_driver,
		s5k5ca_platform_probe);
	if (!rc)
		return rc;
	pr_err("%s:%d rc %d\n", __func__, __LINE__, rc);
	return i2c_add_driver(&s5k5ca_i2c_driver);
}

static void __exit s5k5ca_exit_module(void)
{
	pr_info("%s:%d\n", __func__, __LINE__);
	if (s5k5ca_s_ctrl.pdev) {
		msm_sensor_free_sensor_data(&s5k5ca_s_ctrl);
		platform_driver_unregister(&s5k5ca_platform_driver);
	} else
		i2c_del_driver(&s5k5ca_i2c_driver);
	return;
}
#if 1
static int32_t s5k5ca_sensor_enable_i2c_mux(struct msm_camera_i2c_conf *i2c_conf)
{
	struct v4l2_subdev *i2c_mux_sd =
		dev_get_drvdata(&i2c_conf->mux_dev->dev);
	v4l2_subdev_call(i2c_mux_sd, core, ioctl,
		VIDIOC_MSM_I2C_MUX_INIT, NULL);
	v4l2_subdev_call(i2c_mux_sd, core, ioctl,
		VIDIOC_MSM_I2C_MUX_CFG, (void *)&i2c_conf->i2c_mux_mode);
	return 0;
}
#endif
static int32_t s5k5ca_sensor_disable_i2c_mux(struct msm_camera_i2c_conf *i2c_conf)
{
	struct v4l2_subdev *i2c_mux_sd =
		dev_get_drvdata(&i2c_conf->mux_dev->dev);
	v4l2_subdev_call(i2c_mux_sd, core, ioctl,
				VIDIOC_MSM_I2C_MUX_RELEASE, NULL);
	return 0;
}
int32_t s5k5ca_sensor_power_up(struct msm_sensor_ctrl_t *s_ctrl)
{
	int32_t rc = 0, index = 0;//i=0,
	struct msm_sensor_power_setting_array *power_setting_array = NULL;
	struct msm_sensor_power_setting *power_setting = NULL;
	struct msm_camera_sensor_board_info *data = s_ctrl->sensordata;
	struct gpio *gpio_req = data->gpio_conf->cam_gpio_req_tbl;

	power_setting_array = &s_ctrl->power_setting_array;
	power_setting = &power_setting_array->power_setting[index];

	CDBG("peter: %s:%d\n", __func__, __LINE__);
#if 0
for(i=0;i<data->gpio_conf->cam_gpio_req_tbl_size;i++)
CDBG("Peter: gpio:%d value:%d %s",gpio_req[i].gpio,gpio_get_value(gpio_req[i].gpio),gpio_req[i].label);
#endif
	rc = msm_camera_request_gpio_table(
		data->gpio_conf->cam_gpio_req_tbl,
		data->gpio_conf->cam_gpio_req_tbl_size, 1);
	if (rc < 0) {
		pr_err("%s: request gpio failed\n", __func__);
		return rc;
	}
	//RST enable
	gpio_direction_output(gpio_req[3].gpio,0);
	//PWDN enable
	gpio_direction_output(gpio_req[4].gpio,0);
	usleep(10000);

	// 1.8 vreg enable
	gpio_direction_output(gpio_req[0].gpio,1);
	usleep(10000);
	// 2.8 vreg enable
	gpio_direction_output(gpio_req[1].gpio,1);
	
       usleep(10000);

	//mclk enable
	if (power_setting->config_val)
	{
//		char *name=NULL;
//		name = kzalloc(sizeof(char)*strlen("cam_clk"),GFP_KERNEL);
//		memcpy(name,"cam_clk",sizeof(char)*strlen("cam_clk"));
//		s_ctrl->clk_info[power_setting->seq_val].clk_name = name;
		s_ctrl->clk_info[power_setting->seq_val].	delay= power_setting->delay;
		s_ctrl->clk_info[power_setting->seq_val].	clk_rate = power_setting->config_val;

	}
	CDBG("peter: %s:%d clk_rate:%ld clk_info_size:%d", __func__, __LINE__,s_ctrl->clk_info[power_setting->seq_val].clk_rate,s_ctrl->clk_info_size);
	rc = msm_cam_clk_enable(s_ctrl->dev,
		&s_ctrl->clk_info[0],
		(struct clk **)&power_setting->data[0],
		s_ctrl->clk_info_size,
		1);
	if (rc < 0) {
		pr_err("%s: clk enable failed\n",
			__func__);
		}
	
       usleep(10000);

	//PWDN enable
	gpio_direction_output(gpio_req[4].gpio,1);
	usleep(10000);
	//RST enable
	gpio_direction_output(gpio_req[3].gpio,1);

       usleep(10000);
	// iic
	if (data->i2c_conf && data->i2c_conf->use_i2c_mux)
		s5k5ca_sensor_enable_i2c_mux(data->i2c_conf);

	//read camera sensor id
	if (s_ctrl->func_tbl->sensor_match_id)
		rc = s_ctrl->func_tbl->sensor_match_id(s_ctrl);
	else
		rc = msm_sensor_match_id(s_ctrl);
	if (rc < 0) {
		pr_err("%s:%d match id failed rc %d\n", __func__, __LINE__, rc);
	}

       HW_VERSION_GPIO=gpio_req[5].gpio;
	
      HW_VERSION=gpio_get_value(HW_VERSION_GPIO);
      s_ctrl->sensordata->sensor_init_params->HW_VERSION=HW_VERSION;
	 pr_err("%s: HW_VERSION_GPIO=%d,HW_VERSION=%d\n", __func__,HW_VERSION_GPIO,HW_VERSION); 

	return rc;
}
int32_t s5k5ca_sensor_power_down(struct msm_sensor_ctrl_t *s_ctrl)
{
	int32_t rc = 0 ,index = 0;
	struct msm_sensor_power_setting_array *power_setting_array = NULL;
	struct msm_sensor_power_setting *power_setting = NULL;
	struct msm_camera_sensor_board_info *data = s_ctrl->sensordata;
	struct gpio *gpio_req = data->gpio_conf->cam_gpio_req_tbl;

	power_setting_array = &s_ctrl->power_setting_array;
	power_setting = &power_setting_array->power_setting[index];

	CDBG("%s:%d\n", __func__, __LINE__);

	//RST enable
	gpio_direction_output(gpio_req[4].gpio,0);
	//PWDN enable
	gpio_direction_output(gpio_req[5].gpio,0);

	// 1.8 vreg enable
	gpio_direction_output(gpio_req[1].gpio,0);
	// 2.8 vreg enable
	gpio_direction_output(gpio_req[2].gpio,0);

	msm_cam_clk_enable(s_ctrl->dev,
		&s_ctrl->clk_info[0],
		(struct clk **)&power_setting->data[0],
		s_ctrl->clk_info_size,
		0);

	if (data->i2c_conf && data->i2c_conf->use_i2c_mux)
		s5k5ca_sensor_disable_i2c_mux(data->i2c_conf);

	rc  = msm_camera_request_gpio_table(
		data->gpio_conf->cam_gpio_req_tbl,
		data->gpio_conf->cam_gpio_req_tbl_size, 0);
	if (rc < 0) {
		pr_err("%s: request gpio failed\n", __func__);
//		return rc;
	}

	return 0;
}
int32_t s5k5ca_shutter_speed_switch(struct msm_sensor_ctrl_t *s_ctrl,int sut_speed)
{
        long rc = 0;
	 uint16_t max_value=0,min_value=0;
	 pr_err("%s:%d s5k5ca_shutter_speed_switch:%d \n", __func__, __LINE__,sut_speed);
	switch(sut_speed)
	{
                  case 0:
		    pr_err("%s:%d sut_speed:%d do nothing \n", __func__, __LINE__,sut_speed);
		    		
		    break;

		    case 1:
		    max_value=0x1388;
		    min_value=0x0D05;			
		    break;
			
		    case 2:
		    max_value=0x09C4;
		    min_value=0x07D0;			
		    break;
			
		    case 3:
		    max_value=0x0682;
		    min_value=0x0594;			
		    break;
			
		    case 4:
		    max_value=0x0594;
		    min_value=0x029A;	
		    break;
			
               default:
			pr_err("%s:%d sut_speed paramter error:%d \n", __func__, __LINE__,sut_speed);
		    break;
	 }

        if(sut_speed!=0)
        {
              rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
				s_ctrl->sensor_i2c_client,
				0x0028,
				0x7000, MSM_CAMERA_I2C_WORD_DATA);
		rc |= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
				s_ctrl->sensor_i2c_client,
				0x002a,
				0x037A, MSM_CAMERA_I2C_WORD_DATA);
		rc |= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
				s_ctrl->sensor_i2c_client,
				0x0f12,
				max_value, MSM_CAMERA_I2C_WORD_DATA);
		rc |= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
				s_ctrl->sensor_i2c_client,
				0x0f12,
				min_value, MSM_CAMERA_I2C_WORD_DATA);
		
        }
	
		return rc;

}
int32_t s5k5ca_sensor_config(struct msm_sensor_ctrl_t *s_ctrl,
	void __user *argp)
{
	struct sensorb_cfg_data *cdata = (struct sensorb_cfg_data *)argp;
	long rc = 0;
	int32_t i = 0;
	uint16_t lchipid = 0,hchipid=0;
	int32_t gain=0, shutter =0;
	
	mutex_lock(s_ctrl->msm_sensor_mutex);
	CDBG("%s:%d %s cfgtype = %d\n", __func__, __LINE__,
		s_ctrl->sensordata->sensor_name, cdata->cfgtype);
	switch (cdata->cfgtype) {
	case CFG_GET_SENSOR_INFO:
		memcpy(cdata->cfg.sensor_info.sensor_name,
			s_ctrl->sensordata->sensor_name,
			sizeof(cdata->cfg.sensor_info.sensor_name));
		cdata->cfg.sensor_info.session_id =
			s_ctrl->sensordata->sensor_info->session_id;
		for (i = 0; i < SUB_MODULE_MAX; i++)
			cdata->cfg.sensor_info.subdev_id[i] =
				s_ctrl->sensordata->sensor_info->subdev_id[i];
		CDBG("%s:%d sensor name %s\n", __func__, __LINE__,
			cdata->cfg.sensor_info.sensor_name);
		CDBG("%s:%d session id %d\n", __func__, __LINE__,
			cdata->cfg.sensor_info.session_id);
		for (i = 0; i < SUB_MODULE_MAX; i++)
			CDBG("%s:%d subdev_id[%d] %d\n", __func__, __LINE__, i,
				cdata->cfg.sensor_info.subdev_id[i]);

		break;
	case CFG_SET_INIT_SETTING:
		/* Write Recommend settings */
		pr_err("%s, sensor write init setting!E", __func__);
	rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
			s_ctrl->sensor_i2c_client,
			0xfcfc,
			0xd000, MSM_CAMERA_I2C_WORD_DATA);
//Reset
	rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
			s_ctrl->sensor_i2c_client,
			0x0010,
			0x0001, MSM_CAMERA_I2C_WORD_DATA);
//Clear host interrupt so main will wait
	rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
			s_ctrl->sensor_i2c_client,
			0x1030,
			0x0000, MSM_CAMERA_I2C_WORD_DATA);
//ARM go
	rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
			s_ctrl->sensor_i2c_client,
			0x0014,
			0x0001, MSM_CAMERA_I2C_WORD_DATA);
	usleep(10000);
		sensor_state =0;
	#if 1
		rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write_conf_tbl(
			s_ctrl->sensor_i2c_client, s5k5ca_recommend_settings,
			ARRAY_SIZE(s5k5ca_recommend_settings),
			MSM_CAMERA_I2C_WORD_DATA);
		//usleep(140000);
		pr_err("%s, sensor write init setting!X", __func__);
	#else
	       pr_err("%s, sensor write init setting move to CFG_SET_START_STREAM!X", __func__);
	#endif	
		break;
	case CFG_SET_RESOLUTION:
		pr_err("%s, sensor_state:%d setting:%d CFG_SET_RESOLUTION!!", __func__,sensor_state,*((int*)(cdata->cfg.setting)));
//		if( sensor_state == 1 )
//			sensor_state =2;
//		else if( sensor_state == 2 )
//			sensor_state =1;
//		else 
//			sensor_state =0;
		if( *((int*)(cdata->cfg.setting)) == 1 )
		{
	pr_err("%s, CFG_SET_RESOLUTION-preview_settings   global_current_iso_state=%d !!", __func__,global_current_iso_state);	
				rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write_conf_tbl(
				s_ctrl->sensor_i2c_client, s5k5ca_preview_settings,
				ARRAY_SIZE(s5k5ca_preview_settings),
				MSM_CAMERA_I2C_WORD_DATA);
			
                            if(night_mode_flag)//If least status is night ,reset night mode setting
				{
			       	pr_err("%s:%d set night mode[%d] in preview setting \n", __func__, __LINE__,3);
					rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write_conf_tbl(
					s_ctrl->sensor_i2c_client, s5k5ca_best_shot[3],
					s5k5ca_best_shot_size[3],
					MSM_CAMERA_I2C_WORD_DATA);
				       //night_mode_flag=0;
				}
//			sensor_state = 2;
		}
		else if( *((int*)(cdata->cfg.setting)) == 0 )
		{
	
	pr_err("%s, CFG_SET_RESOLUTION-!!night_mode_capture_flag=%d", __func__,night_mode_capture_flag);

	                  //decrease capture brightness setting to 0x0048
                               rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
                               s_ctrl->sensor_i2c_client,
                               0x0028,
                               0x7000, MSM_CAMERA_I2C_WORD_DATA);
                               rc |= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
                               s_ctrl->sensor_i2c_client,
                               0x002a,
                               0x0F70, MSM_CAMERA_I2C_WORD_DATA);
                               rc |= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
                               s_ctrl->sensor_i2c_client,
                               0x0f12,
                               0x0048, MSM_CAMERA_I2C_WORD_DATA);
                               msleep(50);
			if(night_mode_capture_flag)
				{    
															 
                               rc= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write_conf_tbl(
                               s_ctrl->sensor_i2c_client, s5k5ca_capture_night_mode_settings,
                               ARRAY_SIZE(s5k5ca_capture_night_mode_settings),
                               MSM_CAMERA_I2C_WORD_DATA);		
				}
			else
				{			
															 
                               rc= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write_conf_tbl(
                               s_ctrl->sensor_i2c_client, s5k5ca_capture_normal_mode_settings,
                               ARRAY_SIZE(s5k5ca_capture_normal_mode_settings),
                               MSM_CAMERA_I2C_WORD_DATA);
				}
			
			if(current_scene_flag==0)//Normal 
			s5k5ca_shutter_speed_switch(s_ctrl,4);
			else//other mode if global_current_shutter_speed=0 ,do nothiing
			s5k5ca_shutter_speed_switch(s_ctrl,global_current_shutter_speed);	
			
//			sensor_state = 1;
		}
		break;
	case CFG_SET_STOP_STREAM:
		pr_err("%s, sensor stop stream!!", __func__);
	//Stream off command: 
		rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
				s_ctrl->sensor_i2c_client,
				0x0028,
				0x7000, MSM_CAMERA_I2C_WORD_DATA);
		rc |= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
				s_ctrl->sensor_i2c_client,
				0x002a,
				0x0220, MSM_CAMERA_I2C_WORD_DATA);
		rc |= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
				s_ctrl->sensor_i2c_client,
				0x0f12,
				0x0000, MSM_CAMERA_I2C_WORD_DATA);
		rc |= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
				s_ctrl->sensor_i2c_client,
				0x0F12,
				0x0001, MSM_CAMERA_I2C_WORD_DATA);
		if (rc < 0) {
			pr_err("%s: %s: rc:%ld read id failed\n", __func__,
				s_ctrl->sensordata->sensor_name,rc);
			//return rc;
		}
		//usleep(140000);
		break;
	case CFG_SET_START_STREAM:
		pr_err("%s, sensor_state:%d sensor start stream!!", __func__,sensor_state);
		{
#if 0
		rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write_conf_tbl(
			s_ctrl->sensor_i2c_client, s5k5ca_recommend_settings,
			ARRAY_SIZE(s5k5ca_recommend_settings),
			MSM_CAMERA_I2C_WORD_DATA);
		msleep(140);
		pr_err("%s, sensor write init setting!X", __func__);
#else
			//Stream on command:
			rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
					s_ctrl->sensor_i2c_client,
					0x0028,
					0x7000, MSM_CAMERA_I2C_WORD_DATA);
			rc |= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
					s_ctrl->sensor_i2c_client,
					0x002a,
					0x0220, MSM_CAMERA_I2C_WORD_DATA);
			rc |= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
					s_ctrl->sensor_i2c_client,
					0x0f12,
					0x0001, MSM_CAMERA_I2C_WORD_DATA);

			rc |= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
					s_ctrl->sensor_i2c_client,
					0x0F12,
					0x0001, MSM_CAMERA_I2C_WORD_DATA);
			if (rc < 0) {
				pr_err("%s: %s: rc:%ld read id failed\n", __func__,
					s_ctrl->sensordata->sensor_name,rc);
				//return rc;
			}
			//usleep(140000);
#endif
			sensor_state = 1;
		}
#if 0
		else if( sensor_state == 1 )
		{
			rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write_conf_tbl(
				s_ctrl->sensor_i2c_client, s5k5ca_preview_settings,
				ARRAY_SIZE(s5k5ca_preview_settings),
				MSM_CAMERA_I2C_WORD_DATA);
//			sensor_state = 2;
		}
		else if( sensor_state == 2 )
		{
			rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write_conf_tbl(
				s_ctrl->sensor_i2c_client, s5k5ca_capture_settings,
				ARRAY_SIZE(s5k5ca_capture_settings),
				MSM_CAMERA_I2C_WORD_DATA);
//			sensor_state = 1;
		}
#endif		
		break;
	case CFG_GET_SENSOR_INIT_PARAMS:
		cdata->cfg.sensor_init_params =*s_ctrl->sensordata->sensor_init_params;
//		cdata->cfg.sensor_init_params.HW_VERSION =HW_VERSION;
		CDBG("%s:%d init params mode %d pos %d mount %d  HW_VERSION %d   \n", __func__,
			__LINE__,
			cdata->cfg.sensor_init_params.modes_supported,
			cdata->cfg.sensor_init_params.position,
			cdata->cfg.sensor_init_params.sensor_mount_angle,
			cdata->cfg.sensor_init_params.HW_VERSION);
		break;
	case CFG_SET_SLAVE_INFO: {
		struct msm_camera_sensor_slave_info sensor_slave_info;
		struct msm_sensor_power_setting_array *power_setting_array;
		int slave_index = 0;
		if (copy_from_user(&sensor_slave_info,
		    (void *)cdata->cfg.setting,
		    sizeof(struct msm_camera_sensor_slave_info))) {
			pr_err("%s:%d failed\n", __func__, __LINE__);
			rc = -EFAULT;
			break;
		}
		/* Update sensor slave address */
		if (sensor_slave_info.slave_addr) {
			s_ctrl->sensor_i2c_client->cci_client->sid =
				sensor_slave_info.slave_addr >> 1;
		}

		/* Update sensor address type */
		s_ctrl->sensor_i2c_client->addr_type =
			sensor_slave_info.addr_type;

		/* Update power up / down sequence */
		s_ctrl->power_setting_array =
			sensor_slave_info.power_setting_array;
		power_setting_array = &s_ctrl->power_setting_array;
		power_setting_array->power_setting = kzalloc(
			power_setting_array->size *
			sizeof(struct msm_sensor_power_setting), GFP_KERNEL);
		if (!power_setting_array->power_setting) {
			pr_err("%s:%d failed\n", __func__, __LINE__);
			rc = -ENOMEM;
			break;
		}
		if (copy_from_user(power_setting_array->power_setting,
		    (void *)sensor_slave_info.power_setting_array.power_setting,
		    power_setting_array->size *
		    sizeof(struct msm_sensor_power_setting))) {
			kfree(power_setting_array->power_setting);
			pr_err("%s:%d failed\n", __func__, __LINE__);
			rc = -EFAULT;
			break;
		}
		s_ctrl->free_power_setting = true;
		CDBG("%s sensor id %x\n", __func__,
			sensor_slave_info.slave_addr);
		CDBG("%s sensor addr type %d\n", __func__,
			sensor_slave_info.addr_type);
		CDBG("%s sensor reg %x\n", __func__,
			sensor_slave_info.sensor_id_info.sensor_id_reg_addr);
		CDBG("%s sensor id %x\n", __func__,
			sensor_slave_info.sensor_id_info.sensor_id);
		for (slave_index = 0; slave_index <
			power_setting_array->size; slave_index++) {
			CDBG("%s i %d power setting %d %d %ld %d\n", __func__,
				slave_index,
				power_setting_array->power_setting[slave_index].
				seq_type,
				power_setting_array->power_setting[slave_index].
				seq_val,
				power_setting_array->power_setting[slave_index].
				config_val,
				power_setting_array->power_setting[slave_index].
				delay);
		}
		kfree(power_setting_array->power_setting);
		break;
	}
	case CFG_WRITE_I2C_ARRAY: {
		struct msm_camera_i2c_reg_setting conf_array;
		struct msm_camera_i2c_reg_array *reg_setting = NULL;

		if (copy_from_user(&conf_array,
			(void *)cdata->cfg.setting,
			sizeof(struct msm_camera_i2c_reg_setting))) {
			pr_err("%s:%d failed\n", __func__, __LINE__);
			rc = -EFAULT;
			break;
		}

		reg_setting = kzalloc(conf_array.size *
			(sizeof(struct msm_camera_i2c_reg_array)), GFP_KERNEL);
		if (!reg_setting) {
			pr_err("%s:%d failed\n", __func__, __LINE__);
			rc = -ENOMEM;
			break;
		}
		if (copy_from_user(reg_setting, (void *)conf_array.reg_setting,
			conf_array.size *
			sizeof(struct msm_camera_i2c_reg_array))) {
			pr_err("%s:%d failed\n", __func__, __LINE__);
			kfree(reg_setting);
			rc = -EFAULT;
			break;
		}

		conf_array.reg_setting = reg_setting;
		rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write_table(
			s_ctrl->sensor_i2c_client, &conf_array);
		kfree(reg_setting);
			//usleep(140000);
		break;
	}
	case CFG_WRITE_I2C_SEQ_ARRAY: {
		struct msm_camera_i2c_seq_reg_setting conf_array;
		struct msm_camera_i2c_seq_reg_array *reg_setting = NULL;

		if (copy_from_user(&conf_array,
			(void *)cdata->cfg.setting,
			sizeof(struct msm_camera_i2c_seq_reg_setting))) {
			pr_err("%s:%d failed\n", __func__, __LINE__);
			rc = -EFAULT;
			break;
		}

		reg_setting = kzalloc(conf_array.size *
			(sizeof(struct msm_camera_i2c_seq_reg_array)),
			GFP_KERNEL);
		if (!reg_setting) {
			pr_err("%s:%d failed\n", __func__, __LINE__);
			rc = -ENOMEM;
			break;
		}
		if (copy_from_user(reg_setting, (void *)conf_array.reg_setting,
			conf_array.size *
			sizeof(struct msm_camera_i2c_seq_reg_array))) {
			pr_err("%s:%d failed\n", __func__, __LINE__);
			kfree(reg_setting);
			rc = -EFAULT;
			break;
		}

		conf_array.reg_setting = reg_setting;
		rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->
			i2c_write_seq_table(s_ctrl->sensor_i2c_client,
			&conf_array);
		kfree(reg_setting);
		break;
	}

	case CFG_POWER_UP:
		if (s_ctrl->func_tbl->sensor_power_up)
			rc = s_ctrl->func_tbl->sensor_power_up(s_ctrl);
		else
			rc = -EFAULT;
		global_current_brightness_state =0;
		global_current_iso_state =0;
		global_current_shutter_speed=0;//  0 do nothing; 1[2~3 fps];2[4~5 fps] ;3[6~7 fps];4 is  initial setting[7~15 fps]
		reduce_party_cloudy_flag=0;
		night_mode_flag=0;
		night_mode_capture_flag=0;
		night_mode_preview_flag=0;
		current_scene_flag=0;
//pr_err("power up, hw_version =%d\n", s_ctrl->sensordata->sensor_init_params->HW_VERSION);
		break;

	case CFG_POWER_DOWN:
	
		if (s_ctrl->func_tbl->sensor_power_down)
			rc = s_ctrl->func_tbl->sensor_power_down(
				s_ctrl);
		else
			rc = -EFAULT;
		
		break;

	case CFG_SET_STOP_STREAM_SETTING: {
		struct msm_camera_i2c_reg_setting *stop_setting =
			&s_ctrl->stop_setting;
		struct msm_camera_i2c_reg_array *reg_setting = NULL;
		if (copy_from_user(stop_setting, (void *)cdata->cfg.setting,
		    sizeof(struct msm_camera_i2c_reg_setting))) {
			pr_err("%s:%d failed\n", __func__, __LINE__);
			rc = -EFAULT;
			break;
		}

		reg_setting = stop_setting->reg_setting;
		stop_setting->reg_setting = kzalloc(stop_setting->size *
			(sizeof(struct msm_camera_i2c_reg_array)), GFP_KERNEL);
		if (!stop_setting->reg_setting) {
			pr_err("%s:%d failed\n", __func__, __LINE__);
			rc = -ENOMEM;
			break;
		}
		if (copy_from_user(stop_setting->reg_setting,
		    (void *)reg_setting, stop_setting->size *
		    sizeof(struct msm_camera_i2c_reg_array))) {
			pr_err("%s:%d failed\n", __func__, __LINE__);
			kfree(stop_setting->reg_setting);
			stop_setting->reg_setting = NULL;
			stop_setting->size = 0;
			rc = -EFAULT;
			break;
		}
		break;
	}
	
	case CFG_SET_WHITE_BALANCE:
		{
			
			if(s5k5ca_wb_size[*((int*)(cdata->cfg.setting))]==0)
			*((int*)(cdata->cfg.setting))=0;
				
			pr_err("%s:%d value:%d CFG_SET_WHITEBALANCE\n", __func__, __LINE__,*((int*)(cdata->cfg.setting)));
			rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write_conf_tbl(
				s_ctrl->sensor_i2c_client, s5k5ca_wb_oem[*((int*)(cdata->cfg.setting))],
				s5k5ca_wb_size[*((int*)(cdata->cfg.setting))],
				MSM_CAMERA_I2C_WORD_DATA);
		}
		break;
       case CFG_SET_BESTSHOT_MODE:
              {/*
 s  CAM_SCENE_MODE_OFF,---------------------0
 s  CAM_SCENE_MODE_AUTO,
 s  CAM_SCENE_MODE_LANDSCAPE,
 s  CAM_SCENE_MODE_SNOW,
    CAM_SCENE_MODE_BEACH,
 s  CAM_SCENE_MODE_SUNSET,----------------5
 s  CAM_SCENE_MODE_NIGHT,
 s  CAM_SCENE_MODE_PORTRAIT,
    CAM_SCENE_MODE_BACKLIGHT,
 s  CAM_SCENE_MODE_SPORTS,
    CAM_SCENE_MODE_ANTISHAKE,-------------10
 s  CAM_SCENE_MODE_FLOWERS,
    CAM_SCENE_MODE_CANDLELIGHT,
    CAM_SCENE_MODE_FIREWORKS,
 s CAM_SCENE_MODE_PARTY,
    CAM_SCENE_MODE_NIGHT_PORTRAIT,-------15
    CAM_SCENE_MODE_THEATRE,
    CAM_SCENE_MODE_ACTION,
    CAM_SCENE_MODE_AR,
    CAM_SCENE_MODE_FACE_PRIORITY,
    CAM_SCENE_MODE_BARCODE,-------------20
    CAM_SCENE_MODE_HDR,
               //Arima feature with Morpho function++
    CAM_SCENE_MODE_SOFT_SNAP,
    CAM_SCENE_MODE_ANTI_MOTION_BLUR,
    CAM_SCENE_MODE_HAND_HELD_TWILIGHT,
    CAM_SCENE_MODE_HIGH_SENSITIVITY,------25
    CAM_SCENE_MODE_GOURMENT,
    CAM_SCENE_MODE_PET,
    CAM_SCENE_MODE_DOCUMENT,
              //Arima feature with Morpho function-	
    CAM_SCENE_MODE_MAX
*/
                     uint16_t bestshot=0;
	              uint16_t Ev_feature=0;
			uint16_t iso_feature=0;
			uint16_t iso_value=0;
			uint16_t brightness_value=0;
			night_mode_capture_flag=0;
			night_mode_flag=0;
			global_current_iso_state = 0;			
			current_scene_flag=(*((int*)(cdata->cfg.setting)));
//**************************initial normal mode***********************
                  //if(night_mode_preview_flag)
                  	{
                           pr_err("%s:%d initial normal mode=%d \n", __func__, __LINE__,bestshot);
                           rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write_conf_tbl(
                           s_ctrl->sensor_i2c_client, s5k5ca_best_shot[0],
                           s5k5ca_best_shot_size[0],
                           MSM_CAMERA_I2C_WORD_DATA);
			      night_mode_preview_flag=0;			   
                  	}


		pr_err("%s:%d CFG_SET_BESTSHOT =%d\n", __func__, __LINE__,*((int*)(cdata->cfg.setting)));	
//************************* reduce  party&cloudy++***************
                   pr_err("%s:%d [reduce_party_cloudy_flag]  flag=%d \n", __func__, __LINE__,reduce_party_cloudy_flag);
                    if(reduce_party_cloudy_flag)
                    	{          
                           rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
                           s_ctrl->sensor_i2c_client,
                           0x0028, 0x7000,
                           MSM_CAMERA_I2C_WORD_DATA);                        
                           rc|=s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
                           s_ctrl->sensor_i2c_client,
                           0x002a, 0x04D2,
                           MSM_CAMERA_I2C_WORD_DATA);                           
                           rc|=s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
                           s_ctrl->sensor_i2c_client,
                           0x0F12, 0x067F, 
                           MSM_CAMERA_I2C_WORD_DATA);
			#if 0			   
				//************Briightness*****************
				rc|=s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
                           s_ctrl->sensor_i2c_client,
                           0x0028, 0x7000,
                           MSM_CAMERA_I2C_WORD_DATA);  
				rc|=s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
                           s_ctrl->sensor_i2c_client,
                           0x002a, 0x020C,
                           MSM_CAMERA_I2C_WORD_DATA); 
			      rc|=s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
                           s_ctrl->sensor_i2c_client,
                           0x0F12, 0x0000,
                           MSM_CAMERA_I2C_WORD_DATA);  	
			#endif	  
                           reduce_party_cloudy_flag=0;
                    	}
//************************* reduce  party&cloudy--***************	
		       global_current_shutter_speed=0;
			if((*((int*)(cdata->cfg.setting))) == 2)//LANDSCAPE
				bestshot = 1;
			else if((*((int*)(cdata->cfg.setting))) ==3)//SNOW
				{
				bestshot =7;
				brightness_value=global_current_brightness_state+U_EV_2;
				Ev_feature=1;	
				//reduce_party_cloudy_flag=1;
				}
			else if((*((int*)(cdata->cfg.setting))) ==4)//BEACH
				{
				bestshot =0;
				brightness_value=global_current_brightness_state+U_EV_1;
				Ev_feature=1;	
				}
			else if((*((int*)(cdata->cfg.setting))) ==5)//SUNSET
				bestshot =2;
                     else if((*((int*)(cdata->cfg.setting))) ==6)//NIGHT
                     	{
				bestshot =3;
                            night_mode_flag=1;
				night_mode_capture_flag=1;			
				night_mode_preview_flag=1;
				global_current_shutter_speed=1;	
				brightness_value=global_current_brightness_state+U_EV_2;
				Ev_feature=1;
                     	}
			else if((*((int*)(cdata->cfg.setting))) ==7)//PORTRAIT
				{
				     bestshot =4;	
                                 brightness_value=global_current_brightness_state+U_EV_2;
				     Ev_feature=1;			 
				}
			else if((*((int*)(cdata->cfg.setting))) ==9)//SPORTS
				{
                                 bestshot =5;
                                 global_current_shutter_speed=4;	
				}
			else if((*((int*)(cdata->cfg.setting))) ==11)//FLOWERS
				bestshot =6;
			else if((*((int*)(cdata->cfg.setting))) ==13)//FIREWORKS
				{
                                 iso_value=6;
				     iso_feature=1;
				     global_current_iso_state = 6;
				     global_current_shutter_speed=1;	 	 
			       }
			else if((*((int*)(cdata->cfg.setting))) ==14)//PARTY
				{
				     bestshot =8;
				     brightness_value=global_current_brightness_state+U_EV_2;	
				     Ev_feature=1;
				     reduce_party_cloudy_flag=1;	 
				}
			else if((*((int*)(cdata->cfg.setting))) ==15)//NIGHT_PORTRAIT
				{
                                 iso_value=6;
				     iso_feature=1;	 
				     global_current_iso_state = 6;					 
				     global_current_shutter_speed=1;	
				     brightness_value=global_current_brightness_state+U_EV_2;
				     Ev_feature=1;	 
			       }
			else if((*((int*)(cdata->cfg.setting))) ==21)//HDR
				{break;}
			else if((*((int*)(cdata->cfg.setting))) ==22)//SOFT_SNAP
				{
				    bestshot =4;	
                                brightness_value=global_current_brightness_state+U_EV_2; 
				    Ev_feature=1;				
			        }
			else if((*((int*)(cdata->cfg.setting))) ==23)//ANTI_MOTION_BLUR
				{
                                 iso_value=8;
				     iso_feature=1;	
				     global_current_iso_state = iso_value;							 
				     global_current_shutter_speed=4;	 
			       }
			else if((*((int*)(cdata->cfg.setting))) ==24)//HAND_HELD_TWILIGHT
				{
				     iso_value=3;
				     iso_feature=1;
				     global_current_iso_state = iso_value;						 
				     global_current_shutter_speed=4;	 	 
				}
			else if((*((int*)(cdata->cfg.setting))) ==25)//HIGH_SENSITIVITY
				{   
				     iso_value=9;
				     iso_feature=1;
				     global_current_iso_state = iso_value;						 
				     global_current_shutter_speed=4;		 	 
			       }
			else if((*((int*)(cdata->cfg.setting))) ==26)//GOURMENT
				{
                                  brightness_value=global_current_brightness_state+U_EV_1;
				      Ev_feature=1;				  
				}
			else if((*((int*)(cdata->cfg.setting))) ==27)//PET
				{
                                  global_current_shutter_speed=4;	 
                                  break;
				}
			else if((*((int*)(cdata->cfg.setting))) ==28)//DOCUMENT
				{
                                brightness_value=global_current_brightness_state+U_EV_1; 
				    Ev_feature=1;				
			        }
			else if((*((int*)(cdata->cfg.setting))) ==30)
				{
				    global_current_shutter_speed=4;
                                
			        }
			else
				bestshot=0;
				
				
			pr_err("%s:%d SENSOR_SET_BESTSHOT=%d \n", __func__, __LINE__,bestshot);
			rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write_conf_tbl(
				s_ctrl->sensor_i2c_client, s5k5ca_best_shot[bestshot],
				s5k5ca_best_shot_size[bestshot],
				MSM_CAMERA_I2C_WORD_DATA);
				
//*************************Ev_setting ++*************************
		      if(Ev_feature)
                    	{
                         pr_err("%s:%d [Morpho_setting]  Ev_value=%d \n", __func__, __LINE__,brightness_value);
                         rc |=s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
                         s_ctrl->sensor_i2c_client,
                         0x0028, 0x7000,
                         MSM_CAMERA_I2C_WORD_DATA);                  
                         rc|=s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
                         s_ctrl->sensor_i2c_client,
                         0x002a, 0x020C,
                         MSM_CAMERA_I2C_WORD_DATA);             
                         rc|=s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
                         s_ctrl->sensor_i2c_client,
                         0x0F12, (brightness_value*10), 
                         MSM_CAMERA_I2C_WORD_DATA);
                    	}	
		      else
		      	{
                          pr_err("%s:%d [sensor_setting]  Ev_value=%d \n", __func__, __LINE__,global_current_brightness_state);
                          rc|=s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
                          s_ctrl->sensor_i2c_client,
                          0x0028, 0x7000,
                          MSM_CAMERA_I2C_WORD_DATA);               
                          rc|=s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
                          s_ctrl->sensor_i2c_client,
                          0x002a, 0x020C,
                          MSM_CAMERA_I2C_WORD_DATA);             
                          rc|=s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
                          s_ctrl->sensor_i2c_client,
                          0x0F12, (global_current_brightness_state*10), 
                          MSM_CAMERA_I2C_WORD_DATA);
		      	}
	//***********************Ev_setting--******************************

	//***********************iso_setting++*****************************
			 if(iso_feature)
			 {
                        pr_err("%s:%d [Morpho_iso_setting]  iso_value=%d \n", __func__, __LINE__,iso_value);		
                          rc|=s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write_conf_tbl(
                          s_ctrl->sensor_i2c_client,s5k5ca_iso[iso_value],
                          s5k5ca_iso_size[iso_value],
                          MSM_CAMERA_I2C_WORD_DATA);
			 }
			 else
			 {
                        pr_err("%s:%d [sensor_iso_setting]  iso_value=%d \n", __func__, __LINE__,global_current_iso_state);			
                          rc|=s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write_conf_tbl(
                          s_ctrl->sensor_i2c_client,s5k5ca_iso[global_current_iso_state],
                          s5k5ca_iso_size[global_current_iso_state],
                          MSM_CAMERA_I2C_WORD_DATA);
			 }
	 //***********************iso_setting--*******************************		 
		}
		break;
#if 1
      case CFG_SET_EFFECT:
              {
                     uint16_t effect;
//		pr_err("%s:%d CFG_SET_EFFECT =%d\n", __func__, __LINE__,*((int*)(cdata->cfg.setting)));			 
			if((*((int*)(cdata->cfg.setting))) == 1)
				effect = 1;
			else if((*((int*)(cdata->cfg.setting))) ==2)
				effect =2;
                     else if((*((int*)(cdata->cfg.setting))) ==4)
				effect =3;
			else if((*((int*)(cdata->cfg.setting))) ==8)
				effect =4;	
			else if((*((int*)(cdata->cfg.setting))) ==10)
				effect =5;
			else
				effect=0;
				
//			pr_err("%s:%d CFG_SET_EFFECT=%d \n", __func__, __LINE__,effect);
			
			rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write_conf_tbl(
				s_ctrl->sensor_i2c_client,s5k5ca_special_effect[effect],
				s5k5ca_special_effect_size[effect],
				MSM_CAMERA_I2C_WORD_DATA);
		}
		break;

	case CFG_SET_ISO:
              {
                     uint16_t iso;
			if((current_scene_flag!=0) && (current_scene_flag!=1))
				break;
//		pr_err("%s:%d CFG_SET_ISO =%d\n", __func__, __LINE__,*((int*)(cdata->cfg.setting)));			 
			if((*((int*)(cdata->cfg.setting))) == 2)
				iso=1;
			else if((*((int*)(cdata->cfg.setting))) ==3)
				iso=2;
                     else if((*((int*)(cdata->cfg.setting))) ==4)
				iso=3;
			else if((*((int*)(cdata->cfg.setting))) ==5)
				iso=4;		 
			else if((*((int*)(cdata->cfg.setting))) ==6)
				iso=5;		
			else
				iso=0;
				
//			if(global_current_iso_state==0)				
				global_current_iso_state=iso;
			
			pr_err("%s:%d CFG_SET_ISO=%d \n", __func__, __LINE__,iso);		
			rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write_conf_tbl(
				s_ctrl->sensor_i2c_client,s5k5ca_iso[iso],
				s5k5ca_iso_size[iso],
				MSM_CAMERA_I2C_WORD_DATA);			
			rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write_conf_tbl(
			s_ctrl->sensor_i2c_client, s5k5ca_preview_settings,
			ARRAY_SIZE(s5k5ca_preview_settings),
			MSM_CAMERA_I2C_WORD_DATA);
		}
		break;	
        case CFG_SET_BRIGHTNESS:
              {
                     uint16_t brightness;
				 
			
			brightness=*((int*)(cdata->cfg.setting));	
			global_current_brightness_state = brightness;
			pr_err("%s:%d CFG_SET_BRIGHTNESS=%d \n", __func__, __LINE__,brightness);
			rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
			s_ctrl->sensor_i2c_client,
			0x0028, 0x7000,
			MSM_CAMERA_I2C_WORD_DATA);

			rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
			s_ctrl->sensor_i2c_client,
			0x002a, 0x020C,
			MSM_CAMERA_I2C_WORD_DATA);
			
                     rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
			s_ctrl->sensor_i2c_client,
			0x0F12, (brightness*10), 
			MSM_CAMERA_I2C_WORD_DATA);
			
			
		}
		break;			
//Qualcomm patch--
		//++++  read the shutter value for Morpho using
		case CFG_GET_SHUTTER:
			rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
					s_ctrl->sensor_i2c_client,0x002C,0x7000,MSM_CAMERA_I2C_WORD_DATA);
			rc |= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
					s_ctrl->sensor_i2c_client,0x002E,0x1A44,MSM_CAMERA_I2C_WORD_DATA);
			rc |= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_read(
					s_ctrl->sensor_i2c_client,
					0x0F12,
					&lchipid, MSM_CAMERA_I2C_WORD_DATA);
			if (rc < 0) {
				pr_err("%s: %s: rc:%ld read 3 lchipid id failed\n", __func__,
					s_ctrl->sensordata->sensor_name,rc);
//				return rc;
			}
			rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
					s_ctrl->sensor_i2c_client,0x002C,0x7000,MSM_CAMERA_I2C_WORD_DATA);
			rc |= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
					s_ctrl->sensor_i2c_client,0x002E,0x1A46,MSM_CAMERA_I2C_WORD_DATA);
			rc |= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_read(
					s_ctrl->sensor_i2c_client,
					0x0F12,
					&hchipid, MSM_CAMERA_I2C_WORD_DATA);
			if (rc < 0) {
				pr_err("%s: %s: rc:%ld read 3 hchipid id failed\n", __func__,
					s_ctrl->sensordata->sensor_name,rc);
				//return rc;
			}
			shutter = ((hchipid<<4)|lchipid)/400;
			memcpy(cdata->cfg.setting, (void*)&shutter,sizeof(int32_t));
//			*((int*)(cdata->cfg.setting)) = shutter;
		break;
              //---- read the shutter value for Morpho using
		//++++ read gain value for Morpho using
		case CFG_GET_GAIN:
			rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
					s_ctrl->sensor_i2c_client,0x002C,0x7000,MSM_CAMERA_I2C_WORD_DATA);
			rc |= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
					s_ctrl->sensor_i2c_client,0x002E,0x23EC,MSM_CAMERA_I2C_WORD_DATA);
			rc |= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_read(
					s_ctrl->sensor_i2c_client,
					0x0F12,
					&lchipid, MSM_CAMERA_I2C_WORD_DATA);
			if (rc < 0) {
				pr_err("%s: %s: rc:%ld read 3 gain id failed\n", __func__,
					s_ctrl->sensordata->sensor_name,rc);
				//return rc;
			}
		  	 pr_err("lchipid =%d\n",lchipid);
			 gain = lchipid/2;
			 if(gain<1)
			 	gain =1;
			memcpy(cdata->cfg.setting, (void*)&gain,sizeof(int32_t));
//			memcpy((void*)(cdata), (void*)&data, sizeof(data));
//			rc=copy_to_user((cdata->cfg.setting),&gain,sizeof(gain));
//		if(rc){
//		  	 pr_err("rc:%ld copy to user fail\n",rc);
//			return -EFAULT;
//			}
			 rc =0;
		break;
		//---- read gain value for Morpho using
		case CFG_GET_ISO:
			rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
					s_ctrl->sensor_i2c_client,0xFCFC,0xD000,MSM_CAMERA_I2C_WORD_DATA);
			rc |= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
					s_ctrl->sensor_i2c_client,0x002C,0x7000,MSM_CAMERA_I2C_WORD_DATA);
			rc |= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
					s_ctrl->sensor_i2c_client,0x002E,0x23EC,MSM_CAMERA_I2C_WORD_DATA);
			rc |= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_read(
					s_ctrl->sensor_i2c_client,
					0x0F12,
					&lchipid, MSM_CAMERA_I2C_WORD_DATA);
			if (rc < 0) {
				pr_err("%s: %s: rc:%ld read 3 gain id failed\n", __func__,
					s_ctrl->sensordata->sensor_name,rc);
				//return rc;
			}
			memcpy(cdata->cfg.setting, (void*)&lchipid,sizeof(int32_t));
			
		break;
	  
	 
	 	case CFG_SET_AUTO_BESTSHOT_MODE:
              {
  /*			  	
    SCENE_AUTO,//MORPHO_SCENE_DETECTOR_SCENE_NONE = 0,
    SCENE_PORTRAIT,//MORPHO_SCENE_DETECTOR_SCENE_FACE = 1,
    SCENE_LANDSCAPE,//MORPHO_SCENE_DETECTOR_SCENE_LANDSCAPE = 2,
    SCENE_BACKLIGHT,//MORPHO_SCENE_DETECTOR_SCENE_BACKLIGHT = 3,
    SCENE_BACKLIGHT_PORTRAIT,//MORPHO_SCENE_DETECTOR_SCENE_BACKLIGHT_PORTRAIT = 4,
    SCENE_NIGHT,//MORPHO_SCENE_DETECTOR_SCENE_NIGHT = 5,
    SCENE_NIGHT_PORTRAIT,//MORPHO_SCENE_DETECTOR_SCENE_NIGHT_PORTRAIT = 6,
    SCENE_DOCUMENT,//MORPHO_SCENE_DETECTOR_SCENE_DOCUMENT = 7,
    SCENE_MACRO, //MORPHO_SCENE_DETECTOR_SCENE_MACRO = 8,
    SCENE_LOW_LIGHT,//MORPHO_SCENE_DETECTOR_SCENE_LOW_LIGHT = 9,
    SCENE_SPOTLIGHT,//MORPHO_SCENE_DETECTOR_SCENE_SPOTLIGHT = 10,
    SCENE_BABY,   //MORPHO_SCENE_DETECTOR_SCENE_INFANT = 11,*/ 
    uint16_t bv=0;
    uint16_t iso_value=global_current_iso_state;
   
	pr_err("%s:%d CFG_SET_AUTO_BESTSHOT_MODE [auto scene mode item ] =%d\n", __func__, __LINE__,(*((int*)(cdata->cfg.setting))));
         if((*((int*)(cdata->cfg.setting))) == 0)
	bv=global_current_brightness_state;	 	
  else if((*((int*)(cdata->cfg.setting))) ==1)
  	bv=global_current_brightness_state+U_EV_1;
  else if((*((int*)(cdata->cfg.setting))) ==2)
  	bv=global_current_brightness_state;
  else if((*((int*)(cdata->cfg.setting))) ==3)	
  	bv=global_current_brightness_state;
  else if((*((int*)(cdata->cfg.setting))) ==4)
  	bv=global_current_brightness_state+U_EV_1;
  else if((*((int*)(cdata->cfg.setting))) ==5)	
  	{
          bv=global_current_brightness_state+U_EV_2;    
	   iso_value=8;	  
  	}
  else if((*((int*)(cdata->cfg.setting))) ==6)
  	{
          bv=global_current_brightness_state+U_EV_2;
          iso_value=8;	
  	}
  else if((*((int*)(cdata->cfg.setting))) ==7)
  	bv=global_current_brightness_state+U_EV_1;
  else if((*((int*)(cdata->cfg.setting))) ==8)
  	bv=global_current_brightness_state;
  else if((*((int*)(cdata->cfg.setting))) ==9)
  	bv=global_current_brightness_state+U_EV_3;
  else if((*((int*)(cdata->cfg.setting))) ==10)
  	{
           bv=global_current_brightness_state-U_EV_1;
           //if(bv<0)
           //bv=0;   	
  	}
  else if((*((int*)(cdata->cfg.setting))) ==11)
  	bv=global_current_brightness_state+U_EV_1;
  else
  	pr_err("%s:%d There is mo this setting\n", __func__, __LINE__);
                if(bv==0)
                   bv=global_current_brightness_state;   	
				
		  if(global_current_brightness_state!=bv)
                    	{
                         pr_err("%s:%d [Auto scene ev ]  Ev_value=%d \n", __func__, __LINE__,bv);
                         rc |=s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
                         s_ctrl->sensor_i2c_client,
                         0x0028, 0x7000,
                         MSM_CAMERA_I2C_WORD_DATA);                  
                         rc|=s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
                         s_ctrl->sensor_i2c_client,
                         0x002a, 0x020C,
                         MSM_CAMERA_I2C_WORD_DATA);             
                         rc|=s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
                         s_ctrl->sensor_i2c_client,
                         0x0F12, (bv*10), 
                         MSM_CAMERA_I2C_WORD_DATA);
                    	}	
		  
	pr_err("%s:%d [Auto scene iso] , iso_value=%d \n", __func__, __LINE__,iso_value);		  
                   
                     rc|=s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write_conf_tbl(
                     s_ctrl->sensor_i2c_client,s5k5ca_iso[iso_value],
                     s5k5ca_iso_size[iso_value],
                     MSM_CAMERA_I2C_WORD_DATA);
                   
                   
		      	
              }
		break;
#endif		
//Qualcomm patch--
	default:
			pr_err("%s:%d value:%d to do the other config case\n", __func__, __LINE__,*((int*)(cdata->cfg.setting)));
		rc = 0;
		break;
	}

	mutex_unlock(s_ctrl->msm_sensor_mutex);

			pr_err("%s:%d rc:%ld X\n", __func__, __LINE__,rc);
	return rc;
}

int32_t s5k5ca_match_id(struct msm_sensor_ctrl_t *s_ctrl)
{
	int32_t rc = 0;
	uint16_t chipid = 0;

	CDBG("peter: %s, E. calling i2c_read:, i2c_addr:%x, id_reg_addr:%x", __func__, s_ctrl->sensordata->slave_info->sensor_slave_addr, s_ctrl->sensordata->slave_info->sensor_id_reg_addr);

	rc = s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
			s_ctrl->sensor_i2c_client,
			0xfcfc,
			0xd000, MSM_CAMERA_I2C_WORD_DATA);
	rc |= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
			s_ctrl->sensor_i2c_client,
			0x002c,
			0x0000, MSM_CAMERA_I2C_WORD_DATA);
	rc |= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_write(
			s_ctrl->sensor_i2c_client,
			0x002e,
			0x0040, MSM_CAMERA_I2C_WORD_DATA);

	rc |= s_ctrl->sensor_i2c_client->i2c_func_tbl->i2c_read(
			s_ctrl->sensor_i2c_client,
			0x0F12,
			&chipid, MSM_CAMERA_I2C_WORD_DATA);
	if (rc < 0) {
		pr_err("%s: %s: rc:%d read id failed\n", __func__,
			s_ctrl->sensordata->sensor_name,rc);
		return rc;
	}

	CDBG("%s: read id: %x expected id :\n", __func__, chipid);
	if (chipid != 0x05ca) {
		pr_err("msm_sensor_match_id chip id doesnot match\n");
		return -ENODEV;
	}

	return rc;
}


static struct msm_sensor_fn_t s5k5ca_sensor_func_tbl = {
	.sensor_config = s5k5ca_sensor_config,
	.sensor_power_up = s5k5ca_sensor_power_up,
	.sensor_power_down = s5k5ca_sensor_power_down,
	.sensor_match_id = s5k5ca_match_id,
};

static struct msm_sensor_ctrl_t s5k5ca_s_ctrl = {
	.sensor_i2c_client = &s5k5ca_sensor_i2c_client,
	.power_setting_array.power_setting = s5k5ca_power_setting,
	.power_setting_array.size = ARRAY_SIZE(s5k5ca_power_setting),
	.msm_sensor_mutex = &s5k5ca_mut,
	.sensor_v4l2_subdev_info = s5k5ca_subdev_info,
	.sensor_v4l2_subdev_info_size = ARRAY_SIZE(s5k5ca_subdev_info),
	.func_tbl = &s5k5ca_sensor_func_tbl,
};

module_init(s5k5ca_init_module);
module_exit(s5k5ca_exit_module);
MODULE_DESCRIPTION("s5k5ca 3MP YUV sensor driver");
MODULE_LICENSE("GPL v2");
