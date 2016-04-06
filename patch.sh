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
	echo $(tput bold)$(tput setaf 1)"The number of patch is: ${#}"$(tput sgr0)
	c="0"
	for link in ${@}; do
		c=$[$c+1]
		echo
		echo $(tput bold)$(tput setaf 1)"Patch #${c}"$(tput sgr0)
		echo
		if [[ $link == *".patch" ]]; then
			nl=$link
		else
			nl=$link.patch
		fi
		curl $nl | git am
		if [ $? == "0" ]; then
			echo
			git log --oneline -n 1
			echo $(tput bold)$(tput setaf 2)"Patch (${c}/${#})"$(tput sgr0)
			echo
		else
			echo
			echo $(tput bold)$(tput setaf 1)"Something not worked good in patch #${#}"
			echo "Aborting 'git am' process"
			if [ ${#} -gt "1" ]; then
				echo
				echo "Passing to next patch"
			fi
			echo $(tput sgr0)
			git am --abort
		fi
	done
fi
