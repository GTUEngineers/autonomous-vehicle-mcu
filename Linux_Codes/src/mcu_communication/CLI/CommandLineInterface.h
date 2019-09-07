
/**
 * \file        CommunicationMechanism.h
 * \brief       A brief description one line.
 *
 * \author      Fatih Yakar, Tolga Reis
 * \date        Aug 17, 2019
 */

#ifndef CLI_H_
#define CLI_H_

/*------------------------------< Includes >----------------------------------*/
#include "CommunicationMechanism.h"
#include "process.pb.h"
#include "publisher.h"
#include <iostream>
#include <spdlog/spdlog.h>
#include <thread>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/

enum type {
    dflt,
    _throttle,
    _break,
    _steer,
    _start_stop
};

class Cli {
public:
    Cli(bool isServer = false);
    //Cli(std::string ipNum, int portNumPub, bool isServer);
    void cli_start();

private:
    bool create_message();

    uint16_t get_steering_angle();
    uart::steering_enum get_steering_dir();
    uint8_t get_throttle_value();
    uart::brake_enum get_brake_value();
    uart::startstop_enum get_start_stop_value();
    type get_user_selection();

private:
    //message to send
    std::string cli_msg;
    //selection type
    type user_selection;
    //steering informations
    uint16_t steering_angle;
    uart::steering_enum steering_dir;
    //throttle informations
    uint8_t throttle_value;
    //brake informations
    uart::brake_enum brake_value;
    //start_stop informations
    uart::startstop_enum start_stop_value;
    //publisher for command line interface
    pubsub::Publisher cli_publisher;
    //smart pointer type logger
    std::shared_ptr<spdlog::logger> cli_logger;
};

#endif