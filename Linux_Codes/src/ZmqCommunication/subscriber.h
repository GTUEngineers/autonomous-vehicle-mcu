/**
 * \file        subscriber.h
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Aug 10, 2019
 */

#ifndef SRC_ZMQCOMMUNICATION_SUBSCRIBER_H_
#define SRC_ZMQCOMMUNICATION_SUBSCRIBER_H_

/*------------------------------< Includes >----------------------------------*/
#include "comBase.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/
namespace pubsub
{
class Subscriber : public zmqbase::ComBase
{
public:
    Subscriber(bool is_server);

    void subscribe(const std::string &topic);
    void unsubscribe(const std::string &topic);
    bool recv(std::string &topic, std::string &msg, long timeout = -1);
};
} // namespace pubsub

#endif /* SRC_ZMQCOMMUNICATION_SUBSCRIBER_H_ */
