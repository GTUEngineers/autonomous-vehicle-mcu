all: source/Client.cpp source/Server.cpp
	g++ -c source/Client.cpp -o binaries/Client.o
	g++ -c source/Server.cpp -o binaries/Server.o
	g++ -c source/AbstractCommunication.cpp -o binaries/AbstractCommunication.o

clear: 
	rm binaries/*.o