/**
 * \file        heartbeatMechanism.h
 * \brief       A brief description one line.
 *
 * \author      fatihyakar
 * \date        Aug 10, 2019
 */

#ifndef SRC_HEARTBEATMECHANISM_HEARTBEATMECHANISM_H_
#define SRC_HEARTBEATMECHANISM_HEARTBEATMECHANISM_H_

/*------------------------------< Includes >----------------------------------*/
#include "comBase.h"
#include "publisher.h"
#include "subscriber.h"
#include <exception>
#include <thread>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/

class HeartbeatsMechanism {
public:
    HeartbeatsMechanism(std::string ipNum, int portNumSub, int portNumPub, bool isServer);

private:
    void listen();
    void publish();

    pubsub::Subscriber subscriber;
    pubsub::Publisher publisher;
    std::thread subscriber_thread;
    std::thread publisher_thread;
};

#endif /* SRC_HEARTBEATMECHANISM_HEARTBEATMECHANISM_H_ */
