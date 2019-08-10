/**
 * \file        comBase.cpp
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Jul 16, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "heartbeatsMechanism.h"
#include <iostream>
#include <unistd.h>

/*------------------------------< Defines >-----------------------------------*/
#define MAX_COUNT (3)
#define RECEIVE_TIMEOUT (1000)
/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/
HeartbeatsMechanism::HeartbeatsMechanism(std::string ipNum, int portNumSub, int portNumPub, bool isServer)
    : subscriber{ isServer }
    , publisher(isServer)
{
    subscriber.m_ip = ipNum;
    subscriber.m_port = portNumSub;
    publisher.m_ip = ipNum;
    publisher.m_port = portNumPub;
    subscriber_thread = std::thread(&HeartbeatsMechanism::listen, this);
    publisher_thread = std::thread(&HeartbeatsMechanism::publish, this);
}

void HeartbeatsMechanism::listen()
{
    try {
        subscriber.connect();
        subscriber.subscribe("arac/hb");
        std::string topic;
        zmq::message_t msg(10);
        int counter{ 0 };
        bool carstopped{ false };
        bool is_rcv{ false };

        while (1) {
            is_rcv = subscriber.recv(topic, msg, RECEIVE_TIMEOUT);
            if (!is_rcv) {
                ++counter;
                if (counter == MAX_COUNT && !carstopped) {
                    std::cout << "Unable to connect" << std::endl; // MCU YU DURDURUR
                    carstopped = true;
                }
            }

            else if (carstopped) {
                counter = 0;
                carstopped = false;
                std::cout << "Reconnected" << std::endl; // MCU YU BASLAT
                std::string message = std::string((char*)msg.data(), msg.size());
                std::cout << "Topic:" << topic << " Message:" << message << std::endl;
            } else {
                counter = 0;
                std::string message = std::string((char*)msg.data(), msg.size());
                std::cout << "Topic:" << topic << " Message:" << message << std::endl;
            }
        }
    } catch (std::exception e) {
        std::cerr << e.what() << "there is a problem in heartbeatsMechanism_car.cpp void HeartbeatsMechanism::listen() function" << std::endl;
    }
}

void HeartbeatsMechanism::publish()
{
    publisher.connect();

    while (1) {
        zmq::message_t msg("taskan", 10);
        publisher.publish("arac/hb", msg);
        //  std::cout << "pubpub" << std::endl;
        sleep(1);
    }
}
