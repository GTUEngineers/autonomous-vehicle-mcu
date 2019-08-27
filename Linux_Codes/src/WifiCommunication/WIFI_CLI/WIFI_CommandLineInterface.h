#ifndef WIFI_CLI_H_
#define WIFI_CLI_H_

#include "client.h"
#include "process.pb.h"
#include "station_car.pb.h"
#include "subscriber.h"
#include <iostream>
#include <memory>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/syslog_sink.h>
#include <spdlog/spdlog.h>
#include <unistd.h>

enum type {
    dflt,
    _start_stop
};

class Wifi_Cli {
public:
    Wifi_Cli(bool isServer = false);
    Wifi_Cli(std::string ipNum, int portNumPub, bool isServer);
    void main_menu();

private:
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
};

#endif