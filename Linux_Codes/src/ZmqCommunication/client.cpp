#include "client.h"
#include <unistd.h>
namespace communication
{
    Client::Client(const std::string &ip, int port)
    : ComBase(ZMQ_REQ, false)
    {
    }
    Client::~Client(){}
    bool Client::reqrep(zmq::message_t &req, zmq::message_t &rep, long timeout)
    {
        bool returnVal = false;
        PollItem pollout = {this, PollEventType::POLLOUT, PollEventType::NO};
        poll(pollout, timeout);
        if(pollout.revents & PollEventType::POLLOUT)
        {
            if(m_socket->send(*(zmq::message_t *)&req))
            {
                sleep(1);
                PollItem pollin = {this, PollEventType::POLLIN, PollEventType::NO};
                poll(pollin, timeout);
                if(pollin.revents & PollEventType::POLLIN)
                {
                    returnVal = m_socket->recv((zmq::message_t *)&rep);
                }
            }
        }
        return returnVal;
    }
    int Client::poll(PollItem &data, int timeout)
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
    }
}
