#ifndef SERVER_H
#define SERVER_H

#include "comBase.h"

namespace communication
{
    class Server: public ComBase
    {
    public:
        //constructor that takes a boolean paramater checks whether it is server or not
        Server(const std::string &ip, int port);
        ~Server();
        bool recv(zmq::message_t &msg, long timeout = -1);
        bool send(const zmq::message_t &msg);
    };

}

#endif
