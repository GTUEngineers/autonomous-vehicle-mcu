/**
 * \file        subscriber.h
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Jul 16, 2019
 */

#ifndef INC_SUBSCRIBER_H_
#define INC_SUBSCRIBER_H_

/*------------------------------< Includes >----------------------------------*/
#include "comBase.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/
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
/*------------------------------< Class  >------------------------------------*/

class Subscriber: public ComBase
{
public:
    Subscriber (bool is_server);
    
    void subscribe (const std::string &topic);
    void unsubscribe (const std::string &topic);
    bool recv (std::string &topic, zmq::message_t &msg, long timeout = -1);
private:

    int poll (PollItem &data, int timeout);
};

#endif /* INC_SUBSCRIBER_H_ */
