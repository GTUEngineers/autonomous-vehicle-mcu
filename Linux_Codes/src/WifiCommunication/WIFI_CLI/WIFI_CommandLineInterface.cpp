/**
 * \file        WIFI_CommandLineInterface.cpp
 * \brief       A brief description one line.
 *
 * \author      Fatih Selim Yakar
 * \date        Aug 28, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "WIFI_CommandLineInterface.h"
#include "comBase.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

/*------------------------------< Functions >--------------------------------*/

Wifi_Cli::Wifi_Cli()
    : cli_msg("")
    , user_selection(type::dflt)
    , start_stop_value(wifi::startstop_enum::STOP)
    , client(new seqreqrep::Client)
{
    cli_logger = spdlog::stdout_color_mt("WIFI_CommandLineInterface");
    cli_logger->set_level(spdlog::level::debug);

    std::string addr;
    addr.resize(50);
    sprintf(&addr.front(), zmqbase::TCP_CONNECTION.c_str(), "127.0.0.1", 5555);
    client->connect(addr);
    cli_logger->info("Client addr:{}", addr);
}

Wifi_Cli::Wifi_Cli(std::string ipNumb, int portNum)
    : cli_msg("")
    , user_selection(type::dflt)
    , start_stop_value(wifi::startstop_enum::STOP)
    , client(new seqreqrep::Client)
{
    cli_logger = spdlog::stdout_color_mt("WIFI_CommandLineInterface");
    cli_logger->set_level(spdlog::level::debug);

    std::string addr;
    addr.resize(50);
    sprintf(&addr.front(), zmqbase::TCP_CONNECTION.c_str(), ipNumb.c_str(), portNum);
    client->connect(addr);
    cli_logger->info("Client addr:{}", addr);
}

void Wifi_Cli::main_menu()
{
    std::string msg_type;
    while (msg_type != "1" && msg_type != "2") {
        std::cout << "\nSelect the message type:" << std::endl;
        std::cout << "(1)-Start_stop message." << std::endl;
        std::cout << "(2)-Quit menu." << std::endl;
        std::cin >> msg_type;
    }
    if (msg_type == "1") {
        user_selection = type::_start_stop;
    } else if (msg_type == "2") {
        cli_logger->info("Exited.");
        exit(0);
    }

    cli_logger->info("Message type selected.");
}

void Wifi_Cli::sub_menu()
{
    if (user_selection == type::_start_stop) {
        std::string input_startstop_val;
        while (input_startstop_val != "0" && input_startstop_val != "1") {
            std::cout << ">Enter the start_stop value(0(START) or 1(STOP))" << std::endl;
            std::cin >> input_startstop_val;
            if (input_startstop_val == "0") {
                start_stop_value = wifi::startstop_enum::START;
            } else if (input_startstop_val == "1") {
                start_stop_value = wifi::startstop_enum::STOP;
            }
        }
        cli_logger->info("start_stop value selected.");
    } else {
        cli_logger->warn("Invalid user selection.");
    }
}

bool Wifi_Cli::create_message()
{
    bool retVal;
    std::string request = Common::seqreqrep::create_startstop_req(start_stop_value);
    cli_logger->info("Message Created.");
    std::string reply;

    //if connection is not failed.
    if (client->reqrep(request, reply, 3)) {
        ReturnCode retCode;
        Common::seqreqrep::parse_startstop_rep(reply, retCode);

        cli_logger->debug("Server Rep: {}", retCode);
        retVal = true;
        cli_logger->info("Message Sent.");
    }
    //if it connection is failed.
    else {
        cli_logger->critical("Message did not send!");
        retVal = false;
    }
    return retVal;
}

void Wifi_Cli::cli_start()
{
    this->main_menu();
    this->sub_menu();
    this->create_message();
}

wifi::startstop_enum Wifi_Cli::get_start_stop_value() { return start_stop_value; }
type Wifi_Cli::get_user_selection() { return user_selection; }

int main()
{
    std::string ipAddr, temp;
    int portNum;
    std::cout << "Enter the ip address:" << std::endl;
    std::cin >> ipAddr;
    std::cout << "Enter the port number:" << std::endl;
    std::cin >> temp;
    portNum = atoi(temp.c_str());

    Wifi_Cli cli(ipAddr, portNum);
    while (true) {
        cli.cli_start();
    }
    return 0;
}
