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
#define RECEIVE_TIMEOUT (3000)
/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

HeartbeatsMechanism::HeartbeatsMechanism(std::string ipNum, int portNumSub, int portNumPub,
    bool isServer)
    : m_tcp_subscriber(isServer)
    , m_tcp_publisher(isServer)
    , m_proc_publisher(isServer)
{

    m_logger = spdlog::stdout_color_mt("HeartbeatsMechanism_STATION");
    m_logger->set_level(spdlog::level::debug);
    std::string addr;
    addr.resize(50);
    sprintf(&addr.front(), zmqbase::TCP_CONNECTION.c_str(), ipNum.c_str(), portNumSub);
    m_logger->info("Subscriber addr:{}", addr);
    m_tcp_subscriber.connect(addr);
    addr.clear();
    addr.resize(50);
    sprintf(&addr.front(), zmqbase::TCP_CONNECTION.c_str(), ipNum.c_str(), portNumPub);
    m_tcp_publisher.connect(addr);
    m_logger->info("Publisher addr:{}", addr);
    m_subscriber_thread = std::thread(&HeartbeatsMechanism::listen, this);
    m_publisher_thread = std::thread(&HeartbeatsMechanism::publish, this);
}

void HeartbeatsMechanism::waitUntilFinish()
{
    m_subscriber_thread.join();
    m_publisher_thread.join();
}

void HeartbeatsMechanism::listen()
{
    try {
        std::string topic, msg;
        bool change_control{ false }, is_rcv{ false };
        m_tcp_subscriber.subscribe(CAR_HB_TOPIC);

        while (1) {
            change_control = is_rcv;

            is_rcv = m_tcp_subscriber.recv(topic, msg, RECEIVE_TIMEOUT);

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
    while (1) {
        std::string msg("1");
        m_tcp_publisher.publish(STATION_HB_TOPIC, msg);
        //sleep(0.5);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}
