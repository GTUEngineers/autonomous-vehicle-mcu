#ifndef CLIENT_H
#define CLIENT_H

#include "comBase.h"


namespace communication
{
    enum PollEventType
    {
        NO = 0,
        POLLIN = ZMQ_POLLIN,
        POLLOUT = ZMQ_POLLOUT,
        POLLERR = ZMQ_POLLERR,
        POLLPRI = ZMQ_POLLPRI
    };

    struct PollItem
    {
        ComBase *base;
        PollEventType events;
        PollEventType revents;
    };
    class Client: public ComBase
    {
    public:
        Client(const std::string &ip, int port);
        ~Client();
        bool reqrep(zmq::message_t &req, zmq::message_t &rep, long timeout = -1);
    private:
        int poll(PollItem &data, int timeout);
    };
}


#endif
