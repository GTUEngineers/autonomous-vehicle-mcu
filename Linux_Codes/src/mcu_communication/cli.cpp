#include "cli.h"

static bool flag = false;

Cli::Cli()
{
    user_selection = type::dflt;
    steering_angle = -1;
    steering_tendency = "none";
    throttle_value = -1;
    start_stop_value = "none";
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
        std::string tmp;
        std::cin >> tmp;
        throttle_value = atoi(tmp.c_str());
        this->message_send();
    }
    else if (msg_type == "2")
    {
        std::string tmp;
        user_selection = type::_break;
        while (tmp != "1" && tmp != "0")
        {
            std::cout << "Enter the break value(0 or 1)" << std::endl;
            std::cin >> tmp;
            brake_value = atoi(tmp.c_str());
        }
        this->message_send();
    }
    else if (msg_type == "3")
    {
        user_selection = type::_steer;
        while (steering_tendency != "left" && steering_tendency != "right")
        {
            std::cout << "Enter the steering tendency(\"left\" or \"right\")" << std::endl;
            std::cin >> steering_tendency;
        }
        while (steering_angle > 360 || steering_angle < 0)
        {
            std::cout << "Enter the steering angle(enter the range 0.0-360.0)" << std::endl;
            std::string tmp;
            std::cin >> tmp;
            steering_angle = atof(tmp.c_str());
        }
        this->message_send();
    }
    else if (msg_type == "4")
    {
        std::string tmp;
        user_selection = type::_start_stop;
        while (tmp != "0" && tmp != "1")
        {
            std::cout << "Enter the start_stop value(0 or 1)" << std::endl;
            std::cin >> tmp;
            start_stop_value = atoi(tmp.c_str());
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
    }
    else if (get_user_selection() == type::_steer)
    {
        //double steering_angle; , std::string steering_tendency; kullanarak mesaj oluştur ve gönder
    }
    else if (get_user_selection() == type::_start_stop)
    {
        //bool start_stop_value; kullanarak mesaj oluştur ve gönder
    }
    else
    {
        std::cerr << "Type error" << std::endl;
    }
}

type Cli::get_user_selection() { return user_selection; }
double Cli::get_steering_angle() { return steering_angle; }
std::string Cli::get_steering_tendency() { return steering_tendency; }
int Cli::get_throttle_value() { return throttle_value; }
bool Cli::get_brake_value() { return brake_value; }
bool Cli::get_start_stop_value() { return start_stop_value; }

int main()
{
    while (!flag)
    {
        Cli deneme;
        deneme.cli_start();
    }
}