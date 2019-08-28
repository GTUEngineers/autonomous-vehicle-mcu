
/**
 * \file        WIFI_CommandLineInterface.H
 * \brief       A brief description one line.
 *
 * \author      Fatih Selim Yakar
 * \date        Aug 28, 2019
 */

#ifndef WIFI_CLI_H_
#define WIFI_CLI_H_

/*------------------------------< Includes >----------------------------------*/
#include "CommonLib.h"
#include "client.h"
#include "subscriber.h"
#include <iostream>
#include <memory>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/syslog_sink.h>
#include <spdlog/spdlog.h>
#include <unistd.h>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/
enum type {
    dflt,
    _start_stop
};
/*------------------------------< Class  >------------------------------------*/
class Wifi_Cli {
public:
    Wifi_Cli();
    Wifi_Cli(std::string ipNumb, int portNumPub);
    void cli_start();

private:
    void main_menu();
    void sub_menu();
    bool create_message();
    wifi::startstop_enum get_start_stop_value();
    type get_user_selection();

private:
    //message to send
    std::string cli_msg;
    //selection type
    type user_selection;
    //start_stop informations
    wifi::startstop_enum start_stop_value;
    //smart pointer type logger
    std::shared_ptr<spdlog::logger> cli_logger;
    //smart pointer type client
    std::unique_ptr<seqreqrep::Client> client;
};

#endif