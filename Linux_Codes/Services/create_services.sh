#!/bin/bash

#copies heartbeatMechanism_test_car binary to /usr/bin
#copies HeartbeatMechanism_car.service to /etc/systemd/system
sudo cp ../local_build/Output/HeartbeatMechanism/test/heartbeatMechanism_test_car /usr/bin
sudo cp HeartbeatMechanism_car.service /etc/systemd/system
 
#copies heartbeatMechanism_test_statioc binary to /usr/bin
#copies HeartbeatMechanism_server.service to /etc/systemd/system 
sudo cp ../local_build/Output/HeartbeatMechanism/test/heartbeatMechanism_test_station /usr/bin
sudo cp HeartbeatMechanism_station.service /etc/systemd/system

#copies MCU_Communication binary to /usr/bin
#copies MCU_Communication.service to /etc/systemd/system
sudo cp ../local_build/Output/MCU_Communication/MCU_Communication /usr/bin
sudo cp MCU_Communication.service /etc/systemd/system

#copies client_test binary to /usr/bin
#copies reqrep_client.service to /etc/systemd/system
sudo cp ../local_build/Output/ReqRep/client_test /usr/bin
sudo cp reqrep_client.service /etc/systemd/system

#copies server_test binary to /usr/bin
#copies reqrep_server.service to /etc/systemd/system
sudo cp ../local_build/Output/ReqRep/server_test /usr/bin
sudo cp reqrep_server.service /etc/systemd/system

#copies client_test binary to /usr/bin
#copies wifi_client.service to /etc/systemd/system
sudo cp ../local_build/Output/WifiCommunication/client_test /usr/bin
sudo cp wifi_client.service /etc/systemd/system

#copies server_test binary to /usr/bin
#copies wifi_server.service to /etc/systemd/system
sudo cp ../local_build/Output/WifiCommunication/server_test /usr/bin
sudo cp wifi_server.service /etc/systemd/system

#copies client_test binary to /usr/bin
#copies zmq_client.service to /etc/systemd/system
sudo cp ../local_build/Output/ZmqCommunication/test/client_test /usr/bin
sudo cp zmq_client.service /etc/systemd/system

#copies server_test binary to /usr/bin
#copies zmq_server.service to /etc/systemd/system
sudo cp ../local_build/Output/ZmqCommunication/test/server_test /usr/bin
sudo cp zmq_server.service /etc/systemd/system

systemctl daemon-reload