/**
 * \file        heartbeatMechanism_station.cpp
 * \brief       A brief description one line.
 *
 * \author      fatihyakar,sumeyyetaskan
 * \date        Aug 10, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "heartbeatsMechanism.h"
#include <iostream>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/syslog_sink.h>
#include <unistd.h>
/*------------------------------< Defines >-----------------------------------*/
#define MAX_COUNT (3)
#define RECEIVE_TIMEOUT (2000)
/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

HeartbeatsMechanism::HeartbeatsMechanism(std::string ipNum, int portNumSub, int portNumPub,
    bool isServer)
    : m_subscriber(isServer)
    , m_publisher(isServer)
{
    m_subscriber.m_ip = ipNum;
    m_subscriber.m_port = portNumSub;
    m_publisher.m_ip = ipNum;
    m_publisher.m_port = portNumPub;
    m_logger = spdlog::stdout_color_mt("HeartbeatsMechanism_STATION");
    m_logger->set_level(spdlog::level::debug);
    m_subscriber_thread = std::thread(&HeartbeatsMechanism::listen, this);
    m_publisher_thread = std::thread(&HeartbeatsMechanism::publish, this);
}

void HeartbeatsMechanism::listen()
{
    try {
        std::string topic;
        zmq::message_t msg;
        bool change_control{ false }, is_rcv{ false };

        m_subscriber.connect();
        m_subscriber.subscribe(CAR_HB_TOPIC);

        while (1) {
            change_control = is_rcv;

            is_rcv = m_subscriber.recv(topic, msg, RECEIVE_TIMEOUT);

            if (!is_rcv) {
                m_logger->critical("Unable to connect.");
            } else {
                if (!change_control && is_rcv) {
                    m_logger->info("Connected");
                }
                std::string message = std::string((char*)msg.data(), msg.size());
                m_logger->debug("Topic:{} Message:{}", topic, message);
            }
        }
    } catch (std::exception e) {
        m_logger->critical("{} there is a problem in heartbeatsMechanism_station.cpp void HeartbeatsMechanism::listen() function", e.what());
    }
}

void HeartbeatsMechanism::publish()
{
    m_publisher.connect();

    while (1) {
        zmq::message_t msg("1", 1);
        m_publisher.publish(STATION_HB_TOPIC, msg);
        sleep(2);
    }
}
