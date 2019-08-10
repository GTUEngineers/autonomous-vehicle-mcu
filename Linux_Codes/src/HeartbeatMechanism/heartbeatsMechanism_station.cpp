/**
 * \file        heartbeatsMechanism_station.cpp
 * \brief       A brief description one line.
 *
 * \author      fatih
 * \date        Aug 3, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "heartbeatsMechanism.h"
#include <iostream>
#include <unistd.h>

/*------------------------------< Defines >-----------------------------------*/
#define MAX_COUNT (3)
#define RECEIVE_TIMEOUT (2000)
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
        bool change_control{ false };
        bool is_rcv{ false };

        while (1) {
            change_control = is_rcv;

            is_rcv = subscriber.recv(topic, msg, RECEIVE_TIMEOUT);

            if (!is_rcv) {
                std::cerr << "Unable to connect." << std::endl;
            } else {
                if (!change_control && is_rcv)
                    std::cout << "Connected" << std::endl;
                std::string message = std::string((char*)msg.data(), msg.size());
                std::cout << "Topic:" << topic << " Message:" << message << std::endl;
            }
        }
    } catch (std::exception e) {
        std::cerr << e.what() << " there is a problem in heartbeatsMechanism_station.cpp void HeartbeatsMechanism::listen() function" << std::endl;
    }
}

void HeartbeatsMechanism::publish()
{
    publisher.connect();

    while (1) {
        zmq::message_t msg("taskan", 10);
        publisher.publish("arac/hb", msg);
        //  std::cout << "pubpub" << std::endl;
        sleep(2);
    }
}
