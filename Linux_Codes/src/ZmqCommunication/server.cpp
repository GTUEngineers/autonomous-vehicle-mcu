#include "server.h"

namespace ZMQCommunication {
Server::Server()
    : ComBase(ZMQ_REP, true)
{
}

Server::~Server() {}

bool Server::recv(zmq::message_t& msg, long timeout)
{
    bool retval = false;
    zmq::message_t topic_msg;
    PollItem poll_item = { this, PollEventType::POLLIN, PollEventType::NO };

    poll(poll_item, timeout);
    if (poll_item.revents & PollEventType::POLLIN) {

        retval = this->m_socket->recv(&msg);
    }
    return retval;
}

bool Server::send(const zmq::message_t& msg)
{
    return this->m_socket->send(*(zmq::message_t*)&msg);
}
}
