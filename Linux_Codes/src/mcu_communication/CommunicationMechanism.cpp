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
#include "UARTMessageBuilder.h"
#include "process.pb.h"
#include <UARTCommunication.h>
#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/syslog_sink.h>

/*------------------------------< Defines >-----------------------------------*/
#define RETRY_UART (2)
#define NAME "CommunicationMechanism"
/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

/*------------------------------< Functions >--------------------------------*/

CommunicationMechanism::CommunicationMechanism()
    : zmq_listener_thread(&CommunicationMechanism::zmq_listener_task, this), uart_periodic_req_thread(&CommunicationMechanism::uart_periodic_req_task, this), publisher(true), subscriber(true), uartcom{nullptr}
{
    m_logger = spdlog::stdout_color_mt(NAME);
    m_logger->set_level(spdlog::level::debug);
    uartcom.reset(new UARTCommunication(UART_PORT)); //TODO Fix

    // Constructor code
}

void CommunicationMechanism::zmq_listener_task()
{
    std::string addr;
    addr.resize(50);

    sprintf(&addr.front(), zmqbase::PROC_CONNECTION.c_str(), MCU_SUB_PROC_CONN);
    m_logger->info("Subscriber addr:{}", addr);
    subscriber.connect(addr);

    subscriber.subscribe("");

    std::string topic, msg;
    uart::pub_sub pubsub;
    uart_rep uart_rep;
    uart_req uart_msg;
    while (true)
    {
        subscriber.recv(topic, msg);
        if (topic == "control/steering")
        {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::STEERING_MSG)
            {
                uart_msg = uart_msg::create_steer_msg(pubsub.steering().dir(), pubsub.steering().angle());
            }
        }
        else if (topic == "control/throttle")
        {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::THROTTLE_MSG)
            {
                uart_msg = uart_msg::create_throttle_msg(pubsub.throttle().throttlevalue());
            }
        }
        else if (topic == "control/brake")
        {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::BRAKE_MSG)
            {
                uart_msg = uart_msg::create_brake_msg(pubsub.brake().brakevalue());
            }
        }
        else if (topic == "control/startstop")
        {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::START_STOP_MSG)
            {
                uart_msg = uart_msg::create_startstop_msg(pubsub.startstop().cmd());
            }
        } /* else if (topic == "info/stateworking") {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::STATE_WORKING_MSG) {
                uart_msg = uart_msg::create_state_msg();
            }
        } else if (topic == "info/hcsr04") {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::HCSR4_MSG) {
                uart_msg = uart_msg::create_hcsr4_msg();
            }
        } else if (topic == "info/gps") {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::GPS_MSG) {
                uart_msg = uart_msg::create_gps_msg();
            }
        } */
        else
        {
            m_logger->critical("Invalid Topic: {}", topic);
        }
        if (!uart_reqrep(uart_msg, uart_rep))
        {
            reinit_uart();
            m_logger->critical("UART ERROR");
        }
    }
}

bool CommunicationMechanism::uart_reqrep(uart_req &req, uart_rep &rep)
{
    std::unique_lock<std::mutex> lock(m_uartmutex);
    uint8_t try_counter{0};
    bool ret{false};
    do
    {
        uartcom->transmit(req); //stateworking
        ret = uartcom->receive(rep);
        ++try_counter;
    } while (!ret && try_counter < RETRY_UART);
    if (!ret && try_counter > RETRY_UART)
    {
        return false;
    }
    return true;
}

void CommunicationMechanism::reinit_uart()
{
    uartcom->close_fd();
    uartcom.reset(new UARTCommunication(UART_PORT));

    return;
}

void CommunicationMechanism::uart_periodic_req_task()
{
    std::string addr;
    addr.clear();
    addr.resize(50);
    sprintf(&addr.front(), zmqbase::PROC_CONNECTION.c_str(), MCU_PUB_PROC_CONN);

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