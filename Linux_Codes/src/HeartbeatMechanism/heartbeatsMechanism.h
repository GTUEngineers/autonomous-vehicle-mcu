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
#include "CommonLib.h"
#include <exception>
#include <spdlog/spdlog.h>
#include <thread>
/*------------------------------< Defines >-----------------------------------*/
#define CAR_HB_TOPIC ("car/hb")
#define STATION_HB_TOPIC ("station/hb")
/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/

class HeartbeatsMechanism
{
public:
    HeartbeatsMechanism(std::string ipNum, int portNumSub, int portNumPub, bool isServer);

private:
    void listen();
    void publish();

    pubsub::Subscriber m_tcp_subscriber;
    pubsub::Publisher m_tcp_publisher;
    pubsub::Publisher m_proc_publisher;
    std::thread m_subscriber_thread;
    std::thread m_publisher_thread;
    std::shared_ptr<spdlog::logger> m_logger;
};

#endif /* SRC_HEARTBEATMECHANISM_HEARTBEATMECHANISM_H_ */
