/**
 * \file        publisher.h
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Jul 16, 2019
 */

#ifndef INC_PUBLISHER_H_
#define INC_PUBLISHER_H_

/*------------------------------< Includes >----------------------------------*/
#include "comBase.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/
class Publisher: ComBase
{
public:
    Publisher (bool is_server);
    virtual void connect (int port = 5623, const std::string &ip = "127.0.0.1");
    virtual void disconnect ( );
    bool publish (const std::string &topic, zmq::message_t &msg);
};

#endif /* INC_PUBLISHER_H_ */
