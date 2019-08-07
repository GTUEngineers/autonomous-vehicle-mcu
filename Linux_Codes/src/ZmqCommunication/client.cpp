#include "client.h"
#include <unistd.h>
namespace ZMQCommunication
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
    
  
}
