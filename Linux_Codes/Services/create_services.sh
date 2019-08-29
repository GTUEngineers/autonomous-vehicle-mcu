#!/bin/bash
# Check for the file that gets created when the script successfully finishes.
if [ ! -f /etc/systemd/system/MCU_Communication.service ] 
then 
    sudo cp MCU_Communication.service /etc/systemd/system
    chmod +x /etc/systemd/system/MCU_Communication.service
fi

if [ ! -f /etc/systemd/system/HeartbeatMechanism_car.service ] 
then 
    sudo cp HeartbeatMechanism_car.service /etc/systemd/system
fi