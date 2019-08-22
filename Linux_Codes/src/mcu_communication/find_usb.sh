#!/bin/sh
dmesg | tail -n 50 | grep 'cp210x' | grep 'attached' | tail -n 1 | awk '
BEGIN {
	FORMAT="%-15s\n"
}
{
	if (match(tolower($0),"tty[A-Za-z0-256]*") > 0){
		usb=(substr($0,RSTART,RLENGTH))
	}else {
		usb="-"
	}
	
printf FORMAT,usb
}'
