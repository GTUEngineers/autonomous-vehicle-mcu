/**
 * \file        heartbeatMechanism_car.cpp
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
#define RECEIVE_TIMEOUT (1000)
/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

HeartbeatsMechanism::HeartbeatsMechanism(std::string ipNum, int portNumSub, int portNumPub,
    bool isServer)
    : m_subscriber{ isServer }
    , m_publisher(isServer)
{

    m_logger = spdlog::stdout_color_mt("HeartbeatsMechanism_CAR");
    m_logger->set_level(spdlog::level::debug);

    std::string addr;
    addr.resize(50);
    sprintf(&addr.front(), zmqbase::TCP_CONNECTION.c_str(), ipNum.c_str(), portNumSub);
    m_logger->info("Subscriber addr:{}", addr);
    m_subscriber.connect(addr);
    addr.clear();
    addr.resize(50);
    sprintf(&addr.front(), zmqbase::TCP_CONNECTION.c_str(), ipNum.c_str(), portNumPub);
    m_publisher.connect(addr);
    m_logger->info("Publisher addr:{}", addr);
    m_subscriber_thread = std::thread(&HeartbeatsMechanism::listen, this);
    m_publisher_thread = std::thread(&HeartbeatsMechanism::publish, this);
}

void HeartbeatsMechanism::listen()
{
    try {

        m_subscriber.subscribe(STATION_HB_TOPIC);
        std::string topic, msg;
        int counter{ 0 };
        bool carstopped{ false }, is_rcv{ false };

        while (1) {
            is_rcv = m_subscriber.recv(topic, msg, RECEIVE_TIMEOUT);
            if (!is_rcv) {
                ++counter;
                if (counter == MAX_COUNT && !carstopped) {
                    m_logger->critical("Unable to connect"); //STOP CAR
                    carstopped = true; //stop
                }
            }

            else if (carstopped) {
                counter = 0;
                carstopped = false;
                m_logger->info("Reconnected"); //Start car

                std::string message((char*)msg.data(), msg.size());
                m_logger->debug("Topic:{} Message:{}", topic, message);
            } else {
                counter = 0;
                std::string message((char*)msg.data(), msg.size());
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
        m_publisher.publish(CAR_HB_TOPIC, msg);
        sleep(1);
    }
}
