/**
 * \file        CommunicationMechanism.cpp
 * \brief       A brief description one line.
 *
 * \author      Sevval MEHDER
 * \date        Aug 17, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "CommunicationMechanism.h"
#include "CommonLib.h"
#include "process.pb.h"
#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/syslog_sink.h>


/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

/*------------------------------< Functions >--------------------------------*/

CommunicationMechanism::CommunicationMechanism()
    : zmq_listener_thread(&CommunicationMechanism::zmq_listener_task, this)
    , uart_periodic_req_thread(&CommunicationMechanism::uart_periodic_req_task, this)
    , publisher(true)
    , subscriber(true)
{
    m_logger = spdlog::stdout_color_mt("CommunicationMechanism");
    m_logger->set_level(spdlog::level::debug);

    // Constructor code
}

void CommunicationMechanism::zmq_listener_task()
{
    std::string addr;
    addr.resize(50);

    sprintf(&addr.front(), zmqbase::PROC_CONNECTION.c_str(), "mcu_communication_sub");
    m_logger->info("Subscriber addr:{}", addr);
    subscriber.connect(addr);

    subscriber.subscribe("");

    std::string topic, msg;
    uart::pub_sub pubsub;
    while (true) {
        subscriber.recv(topic, msg);
        if (topic == "control/steering") {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::STEERING_MSG) {
            }
        } else if (topic == "control/throttle") {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::THROTTLE_MSG) {
            }
        } else if (topic == "control/brake") {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::BRAKE_MSG) {
            }
        } else if (topic == "control/startstop") {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::START_STOP_MSG) {
            }
        } else if (topic == "info/stateworking") {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::STATE_WORKING_MSG) {
            }
        } else if (topic == "info/hcsr04") {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::HCSR4_MSG) {
            }
        } else if (topic == "info/gps") {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::GPS_MSG) {
            }
        } else {
            m_logger->critical("Invalid Topic: {}", topic);
        }
    }
}

void CommunicationMechanism::uart_periodic_req_task()
{
    std::string addr;
    addr.clear();
    addr.resize(50);
    sprintf(&addr.front(), zmqbase::PROC_CONNECTION.c_str(), "mcu_communication_pub");

    publisher.connect(addr);
    m_logger->info("Publisher addr:{}", addr);
    while (true)
        ;
}

void CommunicationMechanism::waitUntilFinish()
{

    // Join the thread with the main thread
    this->zmq_listener_thread.join();
    this->uart_periodic_req_thread.join();
}