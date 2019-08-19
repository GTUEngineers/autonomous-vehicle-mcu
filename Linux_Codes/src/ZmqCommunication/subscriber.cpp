/**
 * \file        subscriber.cpp
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Aug 10, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "subscriber.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

using namespace zmqbase;
namespace pubsub
{
Subscriber::Subscriber(bool is_server)
    : ComBase(ZMQ_SUB, is_server)
{
}

void Subscriber::subscribe(const std::string &topic)
{
    m_socket->setsockopt(ZMQ_SUBSCRIBE, topic.c_str(), topic.size());
}

void Subscriber::unsubscribe(const std::string &topic)
{
    m_socket->setsockopt(ZMQ_UNSUBSCRIBE, topic.c_str(), topic.size());
}

bool Subscriber::recv(std::string &topic, std::string &msg, long timeout)
{
    bool retval{false};
    zmq::message_t data;
    PollItem poll_item = {this, PollEventType::POLLIN, PollEventType::NO};

    poll(poll_item, timeout);
    if (poll_item.revents & PollEventType::POLLIN)
    {
        if ((retval = this->m_socket->recv(&data)))
        {
            topic.assign((const char *)data.data(), data.size());
            retval = this->m_socket->recv(&data);
            msg.assign((const char *)data.data(), data.size());
        }
    }
    return retval;
}
} // namespace pubsub
