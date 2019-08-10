/**
 * \file        publisher.cpp
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Jul 16, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "publisher.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/
namespace ZMQCommunication {
Publisher::Publisher(bool is_server)
    : ComBase(ZMQ_PUB, is_server)
{
}

bool Publisher::publish(const std::string& topic, zmq::message_t& msg)
{
    bool retval = true;
    retval = this->m_socket->send(topic.c_str(), topic.size(), ZMQ_SNDMORE);
    if (!retval)
        return retval;
    retval = this->m_socket->send(*(zmq::message_t*)&msg);
    return retval;
}
}