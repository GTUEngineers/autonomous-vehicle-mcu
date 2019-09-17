#!/bin/sh
usb=$(dmesg | tail -n 50 | grep 'cp210x' | grep 'attached' | tail -n 1 | awk '
BEGIN {
	FORMAT="%-10s\n"
}
{
	if (match(tolower($0),"tty[A-Za-z0-256]*") > 0){
		usb=(substr($0,RSTART,RLENGTH))
	}
printf FORMAT,usb
}')
/home/gtu-hazine/Desktop/AllRepos_15.09.2019/autonomous-vehicle/Linux_Codes/local_build/Output/MCU_Communication/MCU_Communication /dev/$usb
