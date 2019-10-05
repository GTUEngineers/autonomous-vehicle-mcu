#!/bin/bash

sudo systemctl restart MCU_Communication.service
sudo systemctl restart lidar_communication.service
sudo systemctl restart wifi_server.service
sudo systemctl restart HeartbeatMechanism_car.service
sudo systemctl restart lane_detection.service 
sudo systemctl restart light_sign_detection.service 
sudo systemctl restart linux_control.service 


