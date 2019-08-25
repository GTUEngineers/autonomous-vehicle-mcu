#ifndef CLI_H_
#define CLI_H_

#include <iostream>
#include "UARTMessageBuilder.h"
#include "process.pb.h"
#include "publisher.h"
#include <thread>

#define CLI_PUBLISH ("cli")

enum type
{
    dflt,
    _throttle,
    _break,
    _steer,
    _start_stop
};

class Cli
{
public:
    Cli();
    void cli_start();
    bool message_send();

    uint16_t get_steering_angle();
    uart::steering_enum get_steering_dir();
    uint8_t get_throttle_value();
    uart::brake_enum get_brake_value();
    uart::startstop_enum get_start_stop_value();
    type get_user_selection();
    void publish();

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
    //converts UART_req_un to string
    std::string to_string(uart_req req);
};

#endif