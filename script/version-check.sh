#! /bin/bash
#===============================
#
# version-check
#
# 2022/04/14 Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
#===============================
TOP=`readlink -f "$0" | xargs dirname | xargs dirname`
TARGET_DEVICEs=$@

cd ${TOP}

for target_device in ${TARGET_DEVICEs}
do
	t_dir=`echo ${target_device} | xargs dirname`
	t_dev=`echo ${target_device} | xargs basename`
	file=`find device | grep ${t_dev}`
	if [ "x${file}" = "x" ]; then
		echo "${t_dev} : unknown driver"
	else
		(
			dir=`echo ${file} | xargs dirname`
			SHA256SUMs=`ls ${TOP}/${dir}/sha256sum/*`
			cd ${t_dir}
			ver=
			for sha256sum in ${SHA256SUMs}
			do
				grep ${t_dev} ${sha256sum} | sha256sum -c --status -
				if [ $? = 0 ]; then
					ver=`echo ${sha256sum} | xargs basename`
					break
				fi
			done
			if [ "x${ver}" = x ]; then
				echo "${t_dev} : custom driver"
			else
				echo "${t_dev} : ${ver}"
			fi
		)
	fi
done
