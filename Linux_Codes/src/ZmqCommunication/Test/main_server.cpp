#include "server.h"
#include <iostream>
#include <unistd.h>
#include <zmq.hpp>

int main(){
    communication::Server server("127.0.0.1", 5555);
    server.connect(5555, "127.0.0.1");
    int counter = 0;
    while (true) {
	    zmq::message_t request(5);
        //  Wait for next request from client
        if(server.recv(request))
            std::cout << "Received from client: " << counter << std::endl;
        //  Do some 'work'
        sleep(1);
        ++counter;
	    zmq::message_t reply (5);
        //  Send reply back to client
        server.send(reply);
    }
    return 0;
}
