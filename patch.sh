#!/bin/bash
# Writen by Caio Oliveira aka Caio99BR <caiooliveirafarias0@gmail.com>

echo "  | Live Git Patcher"
echo "  |"
echo "  | Put the link after '. patch.sh'"
echo "  | To use this script"
echo "  |"
echo "  | Number of patch's: ${#}"
c="0"
for link in ${@}
do
	c=$[$c+1]
	echo "  |"
	echo "  | Patch #${c}"
	if [ "${link}" == *".patch" ]
	then
		nl="${link}"
	else
		nl="${link}.patch"
	fi
	path_patch="/tmp/patch.sh-${c}.patch"
	echo "  |"
	echo "  | Downloading"
	curl -# -o ${path_patch} ${nl}
	if [ -f "${path_patch}" ]
	then
		echo "  |"
		echo "  | Patching"
		git am -3 ${path_patch}
		if [ "${?}" == "0" ]
		then
			echo "  |"
			echo "  | Patch (${c}/${#})"
		else
			echo "  |"
			echo "  | Something not worked good in patch #${c}"
			echo "  | Aborting 'git am' process"
			git am --abort
			if ! [ "${c}" == "${#}" ]
			then
				if [ ${#} -gt "1" ]
				then
					echo "  |"
					echo "  | Passing to next patch"
				fi
			fi
		fi
	else
		echo "  |"
		echo "  | Patch not downloaded, check internet or link"
		if ! [ "${c}" == "${#}" ]
		then
			if [ ${#} -gt "1" ]
			then
				echo "  |"
				echo "  | Passing to next patch"
			fi
		fi
	fi
	rm -rf ${path_patch}
done
