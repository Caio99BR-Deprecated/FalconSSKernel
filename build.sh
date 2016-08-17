#!/bin/bash
# Original Live Script by cybojenix <anthonydking@gmail.com>
# Menu by Caio99BR <caiooliveirafarias0@gmail.com>
# Colors by aidasaidas75 <aidaslukosius75@yahoo.com>
# Toolchains by skyinfo <sh.skyinfo@gmail.com>
# Commands for build Xperia E1 boot.img by mpersano <mpr@fzort.org>
# Rashed for the base of zip making
# And the internet for filling in else where

# Note!
# You need to download https://github.com/TeamVee/android_prebuilt_toolchains
# Clone in the same folder as the kernel to choose a toolchain and not specify a location

# Device Choice
device_choice() {
clear
# Devices available
#
# Xperia E1
device_variants_1="D2004 D2005 D2104 D2015 D2114" device_defconfig_1="stock_falconss_defconfig" device_name_1="Sony-XperiaE1"
# Menu
echo "${x} | ${color_green}Device choice${color_stock}"
echo
echo "1 | ${device_variants_1} | ${device_name_1}"
defconfig_updater ${device_name_1}
echo
echo "* | Any other key to Exit"
echo
read -p "  | Choice | " -n 1 -s x
case "${x}" in
	1) device_defconfig=${device_defconfig_1} device_name=${device_name_1};;
	a)
		if [ -f .config ]
		then
			echo "${x} | Working on ${device_name} defconfig!"
			make -j${build_cpu_usage}${kernel_build_output_enable} ARCH="${ARCH}" CROSS_COMPILE="${kernel_build_ccache}${CROSS_COMPILE}" savedefconfig
			mv defconfig arch/${ARCH}/configs/${device_defconfig}
		fi;;
	b)
		if [ -f .config ]
		then
			cp .config arch/${ARCH}/configs/${device_defconfig}
		fi;;
esac
if ! [ "${device_defconfig}" == "" ]
then
	echo "${x} | Working on ${device_name} defconfig!"
	make -j${build_cpu_usage}${kernel_build_output_enable} ARCH="${ARCH}" CROSS_COMPILE="${kernel_build_ccache}${CROSS_COMPILE}" ${device_defconfig}
	sleep 2
fi
}

# Toolchain Choice
toolchain_choice() {
echo "${x} | Toolchain choice"
echo
if [ -f ../android_prebuilt_toolchains/aptess.sh ]
then
	. ../android_prebuilt_toolchains/aptess.sh
else
	if [ -d ../android_prebuilt_toolchains ]
	then
		echo "  | You not have APTESS Script in Android Prebuilt Toolchain folder"
		echo "  | Check the folder"
		echo "  | We will use Manual Method now"
	else
		echo "  | You don't have TeamVee Prebuilt Toolchains"
	fi
	echo
	echo "  | Please specify a location"
	echo "  | and the prefix of the chosen toolchain at the end"
	echo "  | GCC 4.6 ex. ../arm-eabi-4.6/bin/arm-eabi-"
	echo
	echo "  | Stay blank if you want to exit"
	echo
	read -p "  | Place | " CROSS_COMPILE
	if ! [ "${CROSS_COMPILE}" == "" ]
	then
		ToolchainCompile="${CROSS_COMPILE}"
	fi
fi
}

# Kernel Build Process
kernel_build() {
if [ "${CROSS_COMPILE}" == "" ]
then
	wrong_choice
	unset CROSS_COMPILE ToolchainCompile
elif [ "${ToolchainCompile}" == "" ]
then
	wrong_choice
	unset CROSS_COMPILE ToolchainCompile
elif [ "${device_defconfig}" == "" ]
then
	wrong_choice
	unset device_name device_defconfig
elif [ "${device_name}" == "" ]
then
	wrong_choice
	unset device_name device_defconfig
elif [ ! -f .config ]
then
	wrong_choice
	unset device_name device_defconfig
else
	echo "${x} | Building ${builder} ${custom_kernel} ${custom_kernel_branch}"

	if [ ! $(which lz4c) ]
	then
		echo "We need LZ4 support on machine, lets install it"
		sudo apt-get install liblz4-tool -y
	fi

	if [ $(which ccache) ]
	then
		kernel_build_ccache="ccache "
		echo "  | ${color_blue}Using CCache to build${color_stock}"
	else
		echo "  | ${color_blue}CCache not enabled${color_stock}"
	fi

	echo "  | ${color_blue}Using ${build_cpu_usage} jobs at once${color_stock}"

	start_build_time=$(date +"%s")
	make -j${build_cpu_usage}${kernel_build_output_enable} ARCH="${ARCH}" CROSS_COMPILE="${kernel_build_ccache}${CROSS_COMPILE}"
	if ! [ "$?" == "0" ]
	then
		echo "  | ${color_red}Build Failed! Exiting...${color_stock}"
		break
	fi
	sleep 2
	build_time=$(($(date +"%s") - ${start_build_time}))
	build_time_minutes=$((${build_time} / 60))
fi
}

# Zip Packer Process
zip_packer() {
if ! [ "${device_defconfig}" == "" ]
then
	if [ -f arch/${ARCH}/boot/zImage ]
	then
		echo "${x} | Ziping ${builder} ${custom_kernel} ${custom_kernel_branch}"

		# Make base of zip
		original_dir=$(pwd)
		zip_out="/tmp/zip-creator_out"
		rm -rf ${zip_out}/
		mkdir -p ${zip_out}/META-INF/com/google/android/
		mkdir -p ${zip_out}/base-ramdisk/

		# Copy Update Binary
		cp zip-creator/base/update-binary ${zip_out}/META-INF/com/google/android/

		# Copy ramdisk and delete folder_holder files
		cd zip-creator/base/base-ramdisk/
		find . -depth | cpio -pmdv ${zip_out}/base-ramdisk/
		cd ${original_dir}/
		rm -rf $(find ${zip_out}/base-ramdisk/ -name folder_holder)

		# Make android ramdisk
		cd ${zip_out}/base-ramdisk/sbin/ramdisk/
		chmod +x ${original_dir}/zip-creator/base/ramdisk_permissions.sh
		${original_dir}/zip-creator/base/ramdisk_permissions.sh
		find . | cpio -o -H newc > ${zip_out}/base-ramdisk/sbin/ramdisk.cpio
		cd ${original_dir}/
		rm -rf ${zip_out}/base-ramdisk/sbin/ramdisk/

		# Make main ramdisk
		cd ${zip_out}/base-ramdisk/
		find . | cpio -o -H newc | gzip > ${zip_out}/ramdisk.cpio.gz
		cd ${original_dir}/
		rm -rf ${zip_out}/base-ramdisk/

		# Make new boot.img
		chmod +x ${original_dir}/zip-creator/base/mkqcdtbootimg
		${original_dir}/zip-creator/base/mkqcdtbootimg \
		--kernel arch/${ARCH}/boot/zImage \
		--ramdisk ${zip_out}/ramdisk.cpio.gz \
		--dt_dir arch/${ARCH}/boot \
		--cmdline "$(cat zip-creator/base/cmdline)" \
		--base 0x00000000 \
		--ramdisk_offset 0x02000000 \
		--tags_offset 0x01E00000 \
		--pagesize 2048 \
		-o ${zip_out}/boot.img
		rm -rf ${zip_out}/ramdisk.cpio.gz

		# Set device
		echo "${builder}" >> ${zip_out}/device.prop
		echo "${custom_kernel} ${custom_kernel_branch}" >> ${zip_out}/device.prop
		echo "${device_name}" >> ${zip_out}/device.prop
		echo "Release ${release}" >> ${zip_out}/device.prop

		# Stock need new firmware files
		mkdir -p ${zip_out}/wifi/
		cp drivers/staging/prima/firmware_bin/WCNSS_cfg.dat ${zip_out}/wifi/
		cp drivers/staging/prima/firmware_bin/WCNSS_qcom_cfg.ini ${zip_out}/wifi/

		# We need modules
		mkdir ${zip_out}/modules
		find . -name *.ko | xargs cp -a --target-directory=${zip_out}/modules/ &> /dev/null
		${CROSS_COMPILE}strip --strip-unneeded ${zip_out}/modules/*.ko

		# Pack zip
		cd ${zip_out}/
		zip -r ${zipfile} * -x .gitignore &> /dev/null
		cd ${original_dir}/

		# Copy the zip created
		cp ${zip_out}/${zipfile} zip-creator/
		rm -rf ${zip_out}/
	else
		wrong_choice
	fi
else
	wrong_choice
fi
}

# Updater of defconfigs
defconfig_updater() {
if [ -f .config ]
then
	if [[ "${device_defconfig}" == "${1}" || "${device_name}" == "${1}" ]]
	then
		echo "  | Update defconfig to:"
		echo "a | Default Linux Kernel format  | Small"
		echo "b | Usual copy of .config format | Complete"
		echo
	fi
fi
}

# Copy zip's via ADB
zip_copy_adb() {
if [ -f zip-creator/${zipfile} ]
then
	echo "${x} | Coping ${builder} ${custom_kernel} ${custom_kernel_branch}"
	echo
	adb shell rm -rf /data/media/0/${zipfile} &> /dev/null
	adb push zip-creator/${zipfile} /data/media/0/${zipfile} &> /dev/null
	if ! [ "$?" == "0" ]
	then
		echo "  | Copy failed!"
		if [ ! "$(which adb)" ]
		then
			echo "  | ADB not installed!"
		else
			echo "  | Check connection!"
		fi
		sleep 2
	fi
else
	wrong_choice
fi
}

# Wrong choice
wrong_choice() {
echo "${x} | This option is not available! | Something is wrong! | Check ${color_green}Choice Menu${color_stock}!"; sleep 2
}

if [ ! "${BASH_VERSION}" ]
then
	echo "  | Please do not use ${0} to run this script, just use '. build.sh'"
elif [ -e build.sh ]
then
	# Stock Color
	color_stock=$(tput sgr0)
	# Bold Colors
	color_red=$(tput bold)$(tput setaf 1)
	color_green=$(tput bold)$(tput setaf 2)
	color_yellow=$(tput bold)$(tput setaf 3)
	color_blue=$(tput bold)$(tput setaf 4)
	# Main Variables
	custom_kernel=FalconSSKernel
	builder=Caio99BR
	custom_kernel_branch=KK-Stock
	ARCH=arm

	while true
	do
		# Kernel OutPut
		if [ "${kernel_build_output}" == "(OFF)" ]
		then
			kernel_build_output_enable=" -s"
		else
			kernel_build_output="(${color_green}ON${color_stock})"
			unset kernel_build_output_enable
		fi
		# Build Time
		if ! [ "${build_time}" == "" ]
		then
			if [ "${build_time_minutes}" == "" ]
			then
				menu_build_time="(${color_green}$((${build_time} % 60))s${color_stock})"
			else
				menu_build_time="(${color_green}${build_time_minutes}m$((${build_time} % 60))s${color_stock})"
			fi
		fi
		build_cpu_usage=$(($(grep -c ^processor /proc/cpuinfo) + 1))
		# Variable's
		k_version=$(cat Makefile | grep VERSION | cut -c 11- | head -1)
		k_patch_level=$(cat Makefile | grep PATCHLEVEL | cut -c 14- | head -1)
		k_sub_level=$(cat Makefile | grep SUBLEVEL | cut -c 12- | head -1)
		kernel_base="${k_version}.${k_patch_level}.${k_sub_level}"
		release=$(date +%d""%m""%Y)
		build=R6-FinalOld
		export zipfile="${custom_kernel}-${custom_kernel_branch}-${device_name}-${release}-${build}.zip"
		# Check ZIP
		if [ -f zip-creator/${zipfile} ]
		then
			menu_zipfile="(${color_green}zip-creator/${zipfile}${color_stock})"
		else
			unset menu_zipfile
		fi
		# Menu
		clear
		echo "  | Simple Linux Kernel ${kernel_base} Build Script ($(date +%d"/"%m"/"%Y))"
		echo "  | ${builder} ${custom_kernel} ${custom_kernel_branch} Release $(date +%d"/"%m"/"%Y) Build #${build}"
		echo
		echo "  | ${color_red}Clean Menu${color_stock}"
		echo "1 | Clean Zip Folder"
		echo "2 | Clean Kernel"
		echo "  | ${color_green}Choice Menu${color_stock}"
		echo "3 | Set Device Defconfig ${color_green}${device_name}${color_stock}"
		echo "4 | Set Toolchain        ${color_green}${ToolchainCompile}${color_stock}"
		echo "5 | Toggle Build Output  ${kernel_build_output}"
		echo "  | ${color_yellow}Build Menu${color_stock}"
		echo "6 | Build Kernel         ${menu_build_time}"
		echo "7 | Build Zip Package    ${menu_zipfile}"
		echo "8 | Copy Zip to '/data/media/0' of Device"
		echo "e | Exit"
		echo
		read -n 1 -p "  | Choice | " -s x
		case ${x} in
			1) rm -rf zip-creator/*.zip;;
			2)
				echo "${x} | Cleaning Kernel"
				make -j${build_cpu_usage}${kernel_build_output_enable} ARCH="${ARCH}" CROSS_COMPILE="${kernel_build_ccache}${CROSS_COMPILE}" clean mrproper
				unset device_name device_defconfig build_time;;
			3) device_choice;;
			4) toolchain_choice;;
			5)
				if [ "${kernel_build_output}" == "(OFF)" ]
				then
					unset kernel_build_output
				else
					kernel_build_output="(OFF)"
				fi;;
			6) kernel_build;;
			7) zip_packer;;
			8) zip_copy_adb;;
			q|e) echo "${x} | Ok, Bye!"; break;;
			*) wrong_choice;;
		esac
	done
else
	echo
	echo "  | Ensure you run this file from the SAME folder as where it was,"
	echo "  | otherwise the script will have problems running the commands."
	echo "  | After you 'cd' to the correct folder, start the build script"
	echo "  | with the . build.sh command, NOT with any other command!"
	echo
fi
