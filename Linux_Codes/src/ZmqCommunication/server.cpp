#include "server.h"

namespace communication
{
    Server::Server(const std::string &ip, int port)
    : ComBase(ZMQ_REP, true)
    {
        
    }

    Server::~Server(){}

    bool Server::recv(zmq::message_t &msg, long timeout)
    {
        bool returnVal = false;
        zmq::pollitem_t pItems[] = {{*m_socket, 0, ZMQ_POLLIN, 0}};
        zmq::poll(pItems, 1, timeout);
        if(pItems[0].revents & ZMQ_POLLIN)
        {
            returnVal = this->m_socket->recv((zmq::message_t *)&msg);
        }
        return returnVal;
    }

    bool Server::send(const zmq::message_t &msg)
    {
        return this->m_socket->send(*(zmq::message_t *)&msg);
    }
}
