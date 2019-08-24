#include <iostream>
#include "UARTMessageBuilder.h"

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

    type get_selection();
    double get_steering_angle();
    std::string get_steering_tendency();
    int get_throttle_value();
    bool get_brake_value();
    bool get_start_stop_value();
    type get_user_selection();

private:
    //selection type
    type user_selection;
    //steering informations
    double steering_angle;
    std::string steering_tendency;
    //throttle informations
    int throttle_value;
    //brake informations
    bool brake_value;
    //start_stop informations
    bool start_stop_value;
};