#!/bin/bash

#if [ ! -f /etc/systemd/system/HeartbeatMechanism_car.service ] 
#then 
    sudo cp ../local_build/Output/HeartbeatMechanism/test/heartbeatMechanism_test_car /usr/bin
    sudo cp HeartbeatMechanism_car.service /etc/systemd/system
#fi

#if [ ! -f /etc/systemd/system/HeartbeatMechanism_test_station.service ] 
#then 
    sudo cp ../local_build/Output/HeartbeatMechanism/test/heartbeatMechanism_test_station /usr/bin
    sudo cp HeartbeatMechanism_station.service /etc/systemd/system
#fi

#if [ ! -f /etc/systemd/system/MCU_Communication.service ] 
#then
    sudo cp ../local_build/Output/MCU_Communication/MCU_Communication /usr/bin
    sudo cp MCU_Communication.service /etc/systemd/system
#fi

#if [ ! -f /etc/systemd/system/reqrep_client.service ] 
#then
    sudo cp ../local_build/Output/ReqRep/client_test /usr/bin
    sudo cp reqrep_client.service /etc/systemd/system
#fi

#if [ ! -f /etc/systemd/system/reqrep_server.service ] 
#then
    sudo cp ../local_build/Output/ReqRep/server_test /usr/bin
    sudo cp reqrep_server.service /etc/systemd/system
#fi

#if [ ! -f /etc/systemd/system/wifi_client.service ] 
#then
    sudo cp ../local_build/Output/WifiCommunication/client_test /usr/bin
    sudo cp wifi_client.service /etc/systemd/system
#fi

#if [ ! -f /etc/systemd/system/wifi_server.service ] 
#then
    sudo cp ../local_build/Output/WifiCommunication/server_test /usr/bin
    sudo cp wifi_server.service /etc/systemd/system
#fi

#if [ ! -f /etc/systemd/system/zmq_client.service ] 
#then
    sudo cp ../local_build/Output/ZmqCommunication/test/client_test /usr/bin
    sudo cp zmq_client.service /etc/systemd/system
#fi

#if [ ! -f /etc/systemd/system/zmq_server.service ] 
#then
    sudo cp ../local_build/Output/ZmqCommunication/test/server_test /usr/bin
    sudo cp zmq_server.service /etc/systemd/system
#fi

systemctl daemon-reload