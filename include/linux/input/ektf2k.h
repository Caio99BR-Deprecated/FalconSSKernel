#ifndef _LINUX_ELAN_KTF2K_H
#define _LINUX_ELAN_KTF2K_H

#define ELAN_X_MAX	1280
#define ELAN_Y_MAX	2112

#define ELAN_KTF2K_NAME	"elan-ktf2k-touch"

struct elan_ktf2k_i2c_platform_data {	
	uint16_t version;
	int abs_x_min;
	int abs_x_max;
	int abs_y_min;
	int abs_y_max;
	int intr_gpio;
	int reset_gpio;
	int hw_det_gpio;
	u32 hw_det_gpio_flags;
	u32 reset_gpio_flags;
	u32 intr_gpio_flags;
	bool i2c_pull_up;
	int mode_check_gpio;
	int (*power)(int on);
};

#endif /* _LINUX_ELAN_KTF2K_H */
