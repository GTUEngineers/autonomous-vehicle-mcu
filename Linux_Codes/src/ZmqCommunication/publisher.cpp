/**
 * \file        publisher.cpp
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Aug 10, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "publisher.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/
using namespace zmqbase;

namespace pubsub {
Publisher::Publisher(bool is_server)
    : ComBase(ZMQ_PUB, is_server)
{
}

bool Publisher::publish(const std::string& topic, const std::string& msg)
{
    bool retval{ true };
    retval = this->m_socket->send(topic.c_str(), topic.size(), ZMQ_SNDMORE);
    if (!retval)
        return retval;
    retval = this->m_socket->send(msg.c_str(), msg.size());
    return retval;
}
}
