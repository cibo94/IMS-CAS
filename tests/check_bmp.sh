#!/usr/bin/env bash

ret=0
for line in `$1`
	do
		if [[ -e ${line} ]]
			then
				echo "${line} does exists"
			else
				echo "${line} does not exists"
				ret = $((ret + 1))
			fi
	done
exit ${ret}

