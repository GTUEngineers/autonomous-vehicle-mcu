
/**
 * \file        heartbeatsMechanism.h
 * \brief       A brief description one line.
 *
 * \author      fatih
 * \date        Aug 3, 2019
 */

#ifndef INC_HEARTBEATSMECHANISIM_H_
#define INC_HEARTBEATSMECHANISIM_H_

/*------------------------------< Includes >----------------------------------*/
#include "comBase.h"
#include "publisher.h"
#include "subscriber.h"
#include <exception>
#include <thread>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

class HeartbeatsMechanism {
public:
    HeartbeatsMechanism(std::string ipNum, int portNumSub, int portNumPub, bool isServer);

private:
    void listen();
    void publish();

    ZMQCommunication::Subscriber subscriber;
    ZMQCommunication::Publisher publisher;
    std::thread subscriber_thread;
    std::thread publisher_thread;
};

#endif