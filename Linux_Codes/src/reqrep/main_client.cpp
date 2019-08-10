#include "client.h"
#include <iostream>
#include <memory>
#include <unistd.h>

//Driver file for Client
int main()
{

    std::unique_ptr<ZMQCommunication::Client> client(new ZMQCommunication::Client);
    //connects to tcp://127.0.0.1:5555 socket
    client->connect(5555, "127.0.0.1");
    //a counter to counts requests and responses
    int counter = 0;
    while (true) {
        zmq::message_t request("alperen", 7);
        std::cout << "Sending Hello: " << counter << std::endl;
        zmq::message_t reply;
        //if connection is not broken
        if (client->reqrep(request, reply, 3)) {
            std::cout << "Received from server: " << counter << std::endl;
        }
        //if it is broken
        else {
            //resets client
            client.reset(new ZMQCommunication::Client);
            //reconnects
            client->connect(5555, "127.0.0.1");
        }
        sleep(1);
        ++counter;
    }
    return 0;
}
