#include "client.h"
#include <iostream>
#include <memory>
#include <unistd.h>

int main()
{
    std::unique_ptr<ZMQCommunication::Client> client(new ZMQCommunication::Client);
    client->connect(5555, "127.0.0.1");
    int counter = 0;
    while (true) {
        zmq::message_t request("alperen", 7);
        std::cout << "Sending Hello: " << counter << std::endl;
        zmq::message_t reply;
        if (client->reqrep(request, reply, 3)) {
            std::cout << "Received from server: " << counter << std::endl;
        } else {
            client.reset(new ZMQCommunication::Client);

            client->connect(5555, "127.0.0.1");
        }
        sleep(1);
        ++counter;
    }

    return 0;
}
