/**
 * \file        client.cpp
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Aug 10, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "CommonLib.h"
#include "CommunicationMechanism.h"
#include "client.h"
#include "subscriber.h"
#include <iostream>
#include <memory>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/syslog_sink.h>
#include <spdlog/spdlog.h>
#include <unistd.h>
/*------------------------------< Defines >-----------------------------------*/
#define LOGGER_NAME "WifiCommunication_Client"
#define FAIL "Connection was Broken"
/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

/*------------------------------< Prototypes >--------------------------------*/
void connect_tcp_soc(std::string &addr, std::unique_ptr<seqreqrep::Client> &cli);
void connect_sub(std::string &add, pubsub::Subscriber &sub);

//Driver file for Client
int main()
{
    std::shared_ptr<spdlog::logger> m_logger{spdlog::stdout_color_mt(LOGGER_NAME)};
    m_logger->set_level(spdlog::level::debug);
    std::unique_ptr<seqreqrep::Client> client(new seqreqrep::Client);
    pubsub::Subscriber subscriber(true);
    std::string addr;
    connect_tcp_soc(addr, client);
    //a counter to counts requests and responses

    // temp code to listen published data from server
    connect_sub(addr, subscriber);

    // temp end
    while (true)
    {
        std::string request = Common::seqreqrep::create_startstop_req(wifi::startstop_enum::START);

        std::string reply;
        //if connection is not broken
        if (client->reqrep(request, reply, 3))
        {
            ReturnCode retCode;
            Common::seqreqrep::parse_startstop_rep(reply, retCode);

            m_logger->debug("Server Rep: {}", retCode);
        }
        //if it is broken
        else
        {
            m_logger->critical(FAIL);
            //resets client
            client.reset(new seqreqrep::Client);
            //reconnects
            client->connect(addr);
        }
    }

    return 0;
}

void connect_sub(std::string &add, pubsub::Subscriber &sub)
{
    add.clear();
    add.resize(50);
    sprintf(&add.front(), zmqbase::PROC_CONNECTION.c_str(), MCU_SUB_PROC_CONN);
    sub.connect(add);
    std::string top(STARTSTOP_CONTROL_TOPIC);
    sub.subscribe("");
}

/*
 *connects to tcp://127.0.0.1:5555 socket
 */
void connect_tcp_soc(std::string &addr, std::unique_ptr<seqreqrep::Client> &cli)
{
    addr.resize(50);
    sprintf(&addr.front(), zmqbase::TCP_CONNECTION.c_str(), IP, PORT);
    cli->connect(addr);
}