#include "server.h"
#include <iostream>
#include <unistd.h>
#include <zmq.hpp>

//Driver file for Server
int main()
{
    ZMQCommunication::Server server;
    //binds to localhost with port 5555
    server.connect(5555, "127.0.0.1");
    //a counter to counts requests and replies
    int counter = 0;
    while (true) {
        zmq::message_t request;
        //Wait for next request from client
        //if receives a message
        if (server.recv(request))
            //prints
            std::cout << "Received from client: " << counter << std::endl;
        ++counter;
        zmq::message_t reply("alper", 5);
        //  Send reply back to client
        server.send(reply);
    }
    return 0;
}
