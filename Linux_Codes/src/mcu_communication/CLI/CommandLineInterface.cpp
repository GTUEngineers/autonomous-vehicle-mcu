/**
 * \file        CommandLineInterface.cpp
 * \brief       A brief description one line.
 *
 * \author      Fatih Yakar, Tolga Reis
 * \date        Aug 17, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "CommandLineInterface.h"
#include "CommonLib.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/syslog_sink.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>

/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

/*------------------------------< Functions >--------------------------------*/

static bool flag = false;

Cli::Cli(bool isServer)
    : cli_msg("")
    , user_selection(type::dflt)
    , steering_angle(-1)
    , steering_dir(uart::steering_enum::LEFT)
    , throttle_value(-1)
    , start_stop_value(uart::startstop_enum::STOP)
    , cli_publisher(isServer)
{
    cli_logger = spdlog::stdout_color_mt("CommandLineInterface");
    cli_logger->set_level(spdlog::level::debug);

    std::string addr, ipNum;
    ipNum = "127.0.0.1";
    addr.resize(50);
    sprintf(&addr.front(), zmqbase::TCP_CONNECTION.c_str(), ipNum.c_str(), 5555);
    cli_publisher.connect(addr);
    cli_logger->info("Publisher addr:{}", addr);
}

Cli::Cli(std::string ipNum, int portNumPub, bool isServer = false)
    : cli_msg("")
    , user_selection(type::dflt)
    , steering_angle(-1)
    , steering_dir(uart::steering_enum::LEFT)
    , throttle_value(-1)
    , start_stop_value(uart::startstop_enum::STOP)
    , cli_publisher(isServer)
{
    cli_logger = spdlog::stdout_color_mt("CommandLineInterface");
    cli_logger->set_level(spdlog::level::debug);

    std::string addr;
    addr.resize(50);
    sprintf(&addr.front(), zmqbase::TCP_CONNECTION.c_str(), ipNum.c_str(), portNumPub);
    cli_publisher.connect(addr);
    cli_logger->info("Publisher addr:{}", addr);
}

void Cli::cli_start()
{
    std::cout << "" << std::endl;
    cli_logger->info("CLI started.");

    std::cout << "Select the message type(1-5):" << std::endl;
    std::cout << "(1)-Throttle" << std::endl;
    std::cout << "(2)-Break" << std::endl;
    std::cout << "(3)-Steer" << std::endl;
    std::cout << "(4)-Start_stop" << std::endl;
    std::cout << "(5)-Exit Menu" << std::endl;
    std::string msg_type;
    std::cin >> msg_type;

    if (msg_type == "1") {
        std::string input_throttle_val;
        user_selection = type::_throttle;
        std::cout << "Enter the throttle value(int)" << std::endl;
        std::cin >> input_throttle_val;
        throttle_value = (uint8_t)atoi(input_throttle_val.c_str());

        this->create_message();
        cli_publisher.publish(THROTTLE_CONTROL_TOPIC, cli_msg);
        cli_logger->info("Throttle message published.");
    } else if (msg_type == "2") {
        std::string input_brake_val;
        user_selection = type::_break;
        while (input_brake_val != "1" && input_brake_val != "0") {
            std::cout << "Enter the break value(0(LOCK) or 1(RELEASE))" << std::endl;
            std::cin >> input_brake_val;
            if (input_brake_val == "0") {
                brake_value = uart::brake_enum::LOCK;
            } else if (input_brake_val == "1") {
                brake_value = uart::brake_enum::RELEASE;
            }
        }
        this->create_message();
        cli_publisher.publish(BRAKE_CONTROL_TOPIC, cli_msg);
        cli_logger->info("Brake message published.");
    } else if (msg_type == "3") {
        std::string input_dir_val;
        int input_steering_angle;
        user_selection = type::_steer;
        while (input_dir_val != "left" && input_dir_val != "right") {
            std::cout << "Enter the steering tendency(\"left\" or \"right\")" << std::endl;
            std::cin >> input_dir_val;
            if (input_dir_val == "left") {
                steering_dir = uart::steering_enum::LEFT;
            } else if (input_dir_val == "right") {
                steering_dir = uart::steering_enum::RIGHT;
            }
        }
        while (input_steering_angle > 360 || input_steering_angle < 0) {
            std::cout << "Enter the steering angle(enter the range 0-360)" << std::endl;
            std::cin >> input_steering_angle;
            steering_angle = input_steering_angle;
        }
        this->create_message();
        cli_publisher.publish(STEERING_CONTROL_TOPIC, cli_msg);
        cli_logger->info("Steering message published.");
    } else if (msg_type == "4") {
        std::string input_startstop_val;
        user_selection = type::_start_stop;
        while (input_startstop_val != "0" && input_startstop_val != "1") {
            std::cout << "Enter the start_stop value(0(START) or 1(STOP))" << std::endl;
            std::cin >> input_startstop_val;
            if (input_startstop_val == "0") {
                start_stop_value = uart::startstop_enum::START;
            } else if (input_startstop_val == "1") {
                start_stop_value = uart::startstop_enum::STOP;
            }
        }
        this->create_message();
        cli_publisher.publish(STARTSTOP_CONTROL_TOPIC, cli_msg);
        cli_logger->info("Start_stop message published.");
    } else if (msg_type == "5") {
        cli_logger->info("Exited menu.");
        flag = true;
    } else {
        cli_logger->warn("Type error in cli_start();");
    }
}

bool Cli::create_message()
{
    cli_logger->info("message created.");

    bool retVal = true;
    if (get_user_selection() == type::_throttle) {
        cli_msg = Common::pubsub::create_throttle_msg(get_throttle_value());
        std::string message((char*)cli_msg.data(), cli_msg.size());
        cli_logger->debug("Type:{} Topic:{} Message:{}", "Throttle", THROTTLE_CONTROL_TOPIC, message);
    } else if (get_user_selection() == type::_break) {
        cli_msg = Common::pubsub::create_brake_msg(get_brake_value());
        std::string message((char*)cli_msg.data(), cli_msg.size());
        cli_logger->debug("Type:{} Topic:{} Message:{}", "Break", BRAKE_CONTROL_TOPIC, message);
    } else if (get_user_selection() == type::_steer) {
        cli_msg = Common::pubsub::create_steering_msg(steering_dir, steering_angle);
        std::string message((char*)cli_msg.data(), cli_msg.size());
        cli_logger->debug("Type:{} Topic:{} Message:{}", "Steer", STEERING_CONTROL_TOPIC, message);
    } else if (get_user_selection() == type::_start_stop) {
        cli_msg = Common::pubsub::create_startstop_msg(start_stop_value);
        std::string message((char*)cli_msg.data(), cli_msg.size());
        cli_logger->debug("Type:{} Topic:{} Message:{}", "Start_stop", STARTSTOP_CONTROL_TOPIC, message);
    } else {
        cli_logger->warn("Type error in create_message();");
        retVal = false;
    }

    return retVal;
}

type Cli::get_user_selection() { return user_selection; }
uint16_t Cli::get_steering_angle() { return steering_angle; }
uart::steering_enum Cli::get_steering_dir() { return steering_dir; }
uint8_t Cli::get_throttle_value() { return throttle_value; }
uart::brake_enum Cli::get_brake_value() { return brake_value; }
uart::startstop_enum Cli::get_start_stop_value() { return start_stop_value; }

int main()
{
    std::string ipAddr, temp;
    int portNum;
    std::cout << "Enter the ip address:" << std::endl;
    std::cin >> ipAddr;
    std::cout << "Enter the port number:" << std::endl;
    std::cin >> temp;
    portNum = atoi(temp.c_str());

    Cli cli_process(ipAddr, portNum);
    //Cli cli_process;
    while (!flag) {
        cli_process.cli_start();
    }
}