#!/bin/bash
# Writen by Caio Oliveira aka Caio99BR <caiooliveirafarias0@gmail.com>
# How to Use:
# . patch link.to.commit
#
# This script can apply various commits at once.
# . patch link.to.first.commit ... link.to.commit.over.8000 this.cant.be.possible

if [ ${#} == "0" ]; then
	echo
	echo "    Put the link after '. patch.sh'"
	echo "    To use this script"
	echo
else
	echo $(tput bold)$(tput setaf 1)"Number of patch's: ${#}"$(tput sgr0)
	c="0"
	for link in ${@}; do
		c=$[$c+1]
		echo
		echo $(tput bold)$(tput setaf 1)"Patch #${c}"$(tput sgr0)
		if [[ $link == *".patch" ]]; then
			nl=$link
		else
			nl=$link.patch
		fi
		patch_filename="patch.sh-${c}.patch"
		echo "- Downloading..."
		curl -# -o $patch_filename $nl
		if [ -f $patch_filename ]
		then
			echo "- Patching..."
			git am $patch_filename
			if [ $? == "0" ]; then
				echo $(tput bold)$(tput setaf 2)"Patch (${c}/${#})"$(tput sgr0)
			else
				echo $(tput bold)$(tput setaf 1)"Something not worked good in patch #${c}"
				echo "Aborting 'git am' process"
				if ! [ "${c}" == "${#}" ]
				then
					if [ ${#} -gt "1" ]; then
						echo
						echo "Passing to next patch"
					fi
				fi
				echo $(tput sgr0)
				git am --abort
			fi
		else
			echo "Patch not downloaded, check internet or link"
			if ! [ "${c}" == "${#}" ]
			then
				if [ ${#} -gt "1" ]; then
					echo
					echo "Passing to next patch"
				fi
			fi
		fi
		rm -rf $patch_filename
	done
fi
