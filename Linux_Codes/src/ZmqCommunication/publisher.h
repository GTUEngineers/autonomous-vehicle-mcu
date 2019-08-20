/**
 * \file        publisher.h
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Aug 10, 2019
 */

#ifndef SRC_ZMQCOMMUNICATION_PUBLISHER_H_
#define SRC_ZMQCOMMUNICATION_PUBLISHER_H_

/*------------------------------< Includes >----------------------------------*/
#include "comBase.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/

namespace pubsub {
class Publisher : public zmqbase::ComBase {
public:
    Publisher(bool is_server);

    bool publish(const std::string& topic, const std::string& msg);
};
}
#endif /* SRC_ZMQCOMMUNICATION_PUBLISHER_H_ */
