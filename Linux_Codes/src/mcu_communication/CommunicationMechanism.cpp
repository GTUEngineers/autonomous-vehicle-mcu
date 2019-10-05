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
#include <UARTCommunication.h>
#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/syslog_sink.h>
#include <unistd.h>
/*------------------------------< Defines >-----------------------------------*/
#define RETRY_UART (3)
#define LOGGER_NAME ("CommunicationMechanism")
/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

/*------------------------------< Functions >--------------------------------*/

CommunicationMechanism::CommunicationMechanism(std::string uart_port)
    : publisher(true)
    , subscriber(true)
    , uartcom{ nullptr }
{

    m_logger = spdlog::stdout_color_mt(LOGGER_NAME);
    m_logger->set_level(spdlog::level::debug);
    this->uart_port = uart_port;
    std::string addr;
    addr.clear();
    addr.resize(50);
    sprintf(&addr.front(), zmqbase::PROC_CONNECTION.c_str(), MCU_PUB_PROC_CONN);

    publisher.connect(addr);
    m_logger->info("Publisher addr:{}", addr);
    uartcom.reset(new UARTCommunication(uart_port)); //TODO Fix
    zmq_listener_thread = std::thread(&CommunicationMechanism::zmq_listener_task, this);
    //uart_periodic_req_thread = std::thread(&CommunicationMechanism::uart_periodic_req_task, this);

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
    while (true) {
        subscriber.recv(topic, msg);
        if (topic == STEERING_CONTROL_TOPIC) {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::STEERING_MSG) {
                uart_msg = uart_msg::create_steer_msg(pubsub.steering().dir(), pubsub.steering().angle());
                m_logger->debug("Steering:{},{}", pubsub.steering().angle(), pubsub.steering().dir());
            }
        } else if (topic == THROTTLE_CONTROL_TOPIC) {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::THROTTLE_MSG) {
                uart_msg = uart_msg::create_throttle_msg(pubsub.throttle().throttlevalue());
                m_logger->debug("Throttle:{}", pubsub.throttle().throttlevalue());
            }
        } else if (topic == BRAKE_CONTROL_TOPIC) {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::BRAKE_MSG) {
                uart_msg = uart_msg::create_brake_msg(pubsub.brake().brakevalue());
                m_logger->debug("Brake:{}", pubsub.brake().brakevalue());
            }
        } else if (topic == STARTSTOP_CONTROL_TOPIC) {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::START_STOP_MSG) {
                uart_msg = uart_msg::create_startstop_msg(pubsub.startstop().cmd());
                m_logger->critical("StartStop:{}", pubsub.startstop().cmd());
            }
        } else if (topic == STATEWORK_CONTROL_TOPIC) {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::STATE_WORKING_MSG) {
                uart_msg = uart_msg::create_state_msg();
            }
            m_logger->debug("Stateworking:{}", pubsub.statework().cmd());
        } /* else if (topic == "info/hcsr04") {
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
        else {
            m_logger->critical("Invalid Topic: {}", topic);
            continue;
        }
        if (!uart_reqrep(uart_msg, uart_rep)) {
            reinit_uart();
            subscriber.disconnect();
            subscriber.connect(addr);
            subscriber.subscribe("");
            m_logger->critical("UART ERROR");
        }
        if (topic == STATEWORK_CONTROL_TOPIC) {
            std::string msg;
            if (uart_rep.rep_uint16.msg == 0) {
                msg = Common::pubsub::create_statework_msg(uart::stateWorking_enum::INACTIVE);
            } else {
                msg = Common::pubsub::create_statework_msg(uart::stateWorking_enum::ACTIVE);
            }
            publisher.publish(STATEWORK_INFO_TOPIC, msg);
        }
        uart_rep.rep_uint16.msg = 0;
    }
}

bool CommunicationMechanism::uart_reqrep(uart_req& req, uart_rep& rep)
{
    std::unique_lock<std::mutex> lock(m_uartmutex);
    uint8_t try_counter{ 0 };
    bool ret{ false };
    do {
        uartcom->transmit(req); //stateworking
        ret = uartcom->receive(rep);
        ++try_counter;
        usleep(100);
    } while (!ret && try_counter < RETRY_UART);
    if (!ret && try_counter >= RETRY_UART) {
        return false;
    }
    return true;
}

void CommunicationMechanism::reinit_uart()
{
    std::unique_lock<std::mutex> lock(m_uartmutex);
    uartcom->close_fd();
    uartcom.reset(new UARTCommunication(this->uart_port));

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
    uart_req uart_msg = uart_msg::create_state_msg();
    uart_rep uart_rep;
    while (true) {
        if (uart_reqrep(uart_msg, uart_rep)) {
            std::string statework_msg = Common::pubsub::create_statework_msg(uart_msg::parse_state_msg(uart_rep));
            publisher.publish(STATEWORK_CONTROL_TOPIC, statework_msg);
        }
    }
}

void CommunicationMechanism::waitUntilFinish()
{

    // Join the thread with the main thread
    this->zmq_listener_thread.join();
    this->uart_periodic_req_thread.join();
}
