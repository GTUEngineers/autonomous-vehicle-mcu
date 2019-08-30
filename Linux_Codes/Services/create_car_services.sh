#!/bin/bash

#if [ ! -f /etc/systemd/system/MCU_Communication.service ] 
#then
    sudo cp ../local_build/Output/MCU_Communication/MCU_Communication /usr/bin
    sudo cp MCU_Communication.service /etc/systemd/system
#fi

#if [ ! -f /etc/systemd/system/HeartbeatMechanism_car.service ] 
#then 
    sudo cp ../local_build/Output/HeartbeatMechanism/test/heartbeatMechanism_test_car /usr/bin
    sudo cp HeartbeatMechanism_car.service /etc/systemd/system
#fi

#if [ ! -f /etc/systemd/system/communication_test.service ] 
#then
    sudo cp ../local_build/Output/Communication/test/communication_test /usr/bin
    sudo cp communication_test.service /etc/systemd/system
#fi

systemctl daemon-reload