#include "client.h"
#include <iostream>
#include <zmq.hpp>
#include <unistd.h>

int main(){
    communication::Client client("127.0.0.1", 5555);
    client.connect(5555, "127.0.0.1");
    int counter = 0;
    while (true)
    {
	    zmq::message_t request (5);
        std::cout << "Sending Hello: " << counter << std::endl;
	    zmq::message_t reply (5);
        if(client.reqrep(request, reply, 2))
            std::cout << "Received from server: " << counter << std::endl;
        sleep(1);
        ++counter;
    }
    client.disconnect();
    return 0;
}
