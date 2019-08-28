/**
 * \file        server.cpp
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Aug 10, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "server.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

using namespace zmqbase;

namespace seqreqrep {

Server::Server()
    : ComBase(ZMQ_REP, true)
{
}

Server::~Server() {}

bool Server::recv(std::string& msg, long timeout)
{
    //return value of the function default false
    bool retval{ false };
    zmq::message_t msg_zmq;
    //sets poll_item as ZMQ_POLLIN
    PollItem poll_item = { this, PollEventType::POLLIN, PollEventType::NO };
    poll(poll_item, timeout);
    //if poll operation is ZMQ_POLLIN
    if (poll_item.revents & PollEventType::POLLIN) {
        //changes return value to true if it receives a message
        retval = this->m_socket->recv(&msg_zmq);
        msg.assign((const char*)msg_zmq.data(), msg_zmq.size());
    }
    return retval;
}

bool Server::send(const std::string& msg)
{
    //sends given message to given socket
    return this->m_socket->send(msg.c_str(), msg.size());
}
}
