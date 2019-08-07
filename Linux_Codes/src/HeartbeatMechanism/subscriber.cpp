/**
 * \file        subscriber.cpp
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Jul 16, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "subscriber.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

Subscriber::Subscriber(bool is_server) : ComBase(ZMQ_SUB, is_server)
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

bool Subscriber::recv(std::string &topic, zmq::message_t &msg, long timeout)
{
    bool retval = false;
    zmq::message_t topic_msg;
    PollItem poll_item = {this, PollEventType::POLLIN, PollEventType::NO};

    poll(poll_item, timeout);
    if (poll_item.revents & PollEventType::POLLIN)
    {
        if ((retval = this->m_socket->recv(&topic_msg)))
        {
            topic.assign((const char *)topic_msg.data(), topic_msg.size());
            retval = this->m_socket->recv(&msg);
        }
    }
    return retval;
}

int Subscriber::poll(PollItem &data, int timeout)
{
    int retval = 0;
    zmq::pollitem_t item = {*data.base->m_socket, 0, data.events, data.revents};

    retval = zmq::poll(&item, 1, timeout);

    if (item.revents & ZMQ_POLLIN)
    {
        data.revents = PollEventType::POLLIN;
    }
    else if (item.revents & ZMQ_POLLOUT)
    {
        data.revents = PollEventType::POLLOUT;
    }
    else if (item.revents & ZMQ_POLLERR)
    {
        data.revents = PollEventType::POLLERR;
    }
    else if (item.revents & ZMQ_POLLPRI)
    {
        data.revents = PollEventType::POLLPRI;
    }
    else
    {
        data.revents = PollEventType::NO;
    }

    return retval;
};
