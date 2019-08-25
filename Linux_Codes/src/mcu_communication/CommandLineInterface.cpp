#include "CommandLineInterface.h"
#include <unistd.h>
static bool flag = false;

Cli::Cli()
    : cli_msg(""),
      user_selection(type::dflt),
      steering_angle(-1),
      steering_dir(uart::steering_enum::LEFT),
      throttle_value(-1),
      start_stop_value(uart::startstop_enum::STOP),
      cli_publisher(false)
{
}

void Cli::cli_start()
{
    std::cout << "\nSelect the message type(1-5):" << std::endl;
    std::cout << "(1)-Throttle" << std::endl;
    std::cout << "(2)-Break" << std::endl;
    std::cout << "(3)-Steer" << std::endl;
    std::cout << "(4)-Start_stop" << std::endl;
    std::cout << "(5)-Exit Menu" << std::endl;
    std::string msg_type;
    std::cin >> msg_type;

    if (msg_type == "1")
    {
        user_selection = type::_throttle;
        std::cout << "Enter the throttle value(int)" << std::endl;
        std::cin >> throttle_value;
        this->message_send();
    }
    else if (msg_type == "2")
    {
        std::string input_brake_val;
        user_selection = type::_break;
        while (input_brake_val != "1" && input_brake_val != "0")
        {
            std::cout << "Enter the break value(0(LOCK) or 1(RELEASE))" << std::endl;
            std::cin >> input_brake_val;
            if (input_brake_val == "0")
            {
                brake_value = uart::brake_enum::LOCK;
            }
            else if (input_brake_val == "1")
            {
                brake_value = uart::brake_enum::RELEASE;
            }
        }
        this->message_send();
    }
    else if (msg_type == "3")
    {
        user_selection = type::_steer;
        while (get_steering_dir() != uart::steering_enum::LEFT && get_steering_dir() != uart::steering_enum::RIGHT)
        {
            std::string input_dir_val;
            std::cout << "Enter the steering tendency(\"left\" or \"right\")" << std::endl;
            std::cin >> input_dir_val;
            if (input_dir_val == "left")
            {
                steering_dir = uart::steering_enum::LEFT;
            }
            else if (input_dir_val == "right")
            {
                steering_dir = uart::steering_enum::RIGHT;
            }
        }
        while (steering_angle > 360 || steering_angle < 0)
        {
            std::cout << "Enter the steering angle(enter the range 0.0-360.0)" << std::endl;
            std::cin >> steering_angle;
        }
        this->message_send();
    }
    else if (msg_type == "4")
    {
        uint8_t input_startstop_val;
        user_selection = type::_start_stop;
        while (input_startstop_val != 0 && input_startstop_val != 1)
        {
            std::cout << "Enter the start_stop value(0(START) or 1(STOP))" << std::endl;
            std::cin >> input_startstop_val;
            if (input_startstop_val == 0)
            {
                start_stop_value = uart::startstop_enum::START;
            }
            else if (input_startstop_val == 1)
            {
                start_stop_value = uart::startstop_enum::STOP;
            }
        }
        this->message_send();
    }
    else if (msg_type == "5")
    {
        flag = true;
    }
    else
    {
        std::cerr << "Type error" << std::endl;
    }
}

bool Cli::message_send()
{
    if (get_user_selection() == type::_throttle)
    {
        //int throttle_value; kullanarak mesaj oluştur ve gönder
    }
    else if (get_user_selection() == type::_break)
    {
        //bool break_value; kullanarak mesaj oluştur ve gönder
        create_brake_msg(get_brake_value());
    }
    else if (get_user_selection() == type::_steer)
    {
        //double steering_angle; , std::string steering_tendency; kullanarak mesaj oluştur ve gönder
        create_steer_msg(steering_dir, steering_angle);
    }
    else if (get_user_selection() == type::_start_stop)
    {
        //bool start_stop_value; kullanarak mesaj oluştur ve gönder
        create_startstop_msg(start_stop_value);
    }
    else
    {
        std::cerr << "Type error" << std::endl;
    }
}

void Cli::publish()
{
    while (true)
    {
        cli_publisher.publish(CLI_PUBLISH, cli_msg);
        sleep(1);
    }
}

std::string Cli::to_string(uart_req req)
{
    return "";
}

type Cli::get_user_selection() { return user_selection; }
uint16_t Cli::get_steering_angle() { return steering_angle; }
uart::steering_enum Cli::get_steering_dir() { return steering_dir; }
uint8_t Cli::get_throttle_value() { return throttle_value; }
uart::brake_enum Cli::get_brake_value() { return brake_value; }
uart::startstop_enum Cli::get_start_stop_value() { return start_stop_value; }

int main()
{
    Cli cli_process;
    while (!flag)
    {
        cli_process.cli_start();
        cli_process.publish();
    }
}