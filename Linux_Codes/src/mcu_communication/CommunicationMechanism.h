/**
 * \file        CommunicationMechanism.h
 * \brief       A brief description one line.
 *
 * \author      Sevval MEHDER
 * \date        Aug 17, 2019
 * \author      Tolga REİS
 * \update      Aug 29, 2019
 */

#ifndef COM_MECHANISM_H
#define COM_MECHANISM_H

/*------------------------------< Includes >----------------------------------*/
#include "UARTCommunication.h"
#include "publisher.h"
#include "subscriber.h"
#include <mutex>
#include <spdlog/spdlog.h>
#include <thread>

/*------------------------------< Defines >-----------------------------------*/
#define STEERING_CONTROL_TOPIC ("control/steering")
#define BRAKE_CONTROL_TOPIC ("control/brake")
#define THROTTLE_CONTROL_TOPIC ("control/throttle")
#define STARTSTOP_CONTROL_TOPIC ("control/startstop")
/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/

class CommunicationMechanism {
public:
    CommunicationMechanism(); /* Constructor */
    ~CommunicationMechanism();
    void waitUntilFinish();

private:
    void zmq_listener_task();
    void uart_periodic_req_task();
    bool uart_reqrep(uart_req& req, uart_rep& rep);
    void reinit_uart();
    std::unique_ptr<UARTCommunication> uartcom;
    std::mutex m_uartmutex;
    std::thread zmq_listener_thread;
    std::thread uart_periodic_req_thread;
    std::shared_ptr<spdlog::logger> m_logger;
    pubsub::Publisher publisher;
    pubsub::Subscriber subscriber;
    //	UARTCommunication communication;
};

#endif /* COM_MECHANISM_H */
