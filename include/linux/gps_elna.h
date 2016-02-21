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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

//ALERT:please relocate gps_elna.h under .\kernel\include\linux


#define GPS_ELNA_DEVICE_NAME   "gps_elna"
#define GPS_ELNA_MAGIC         0xA1

/*
 * GPS eLNA power control via ioctl
 * GPS_ELNA_SET_PWR(0): power off
 * GPS_ELNA_SET_PWR(1): power on
 */
#define GPS_ELNA_SET_PWR	_IOW(GPS_ELNA_MAGIC, 0x01, unsigned int)





