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

/*------------------------------< Class  >------------------------------------*/
namespace ZMQCommunication{
class Subscriber : public ComBase
{
public:
    Subscriber(bool is_server);

    void subscribe(const std::string &topic);
    void unsubscribe(const std::string &topic);
    bool recv(std::string &topic, zmq::message_t &msg, long timeout = -1);

};
}

#endif /* INC_SUBSCRIBER_H_ */
