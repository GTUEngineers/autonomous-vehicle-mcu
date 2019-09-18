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
#define LOGGER_NAME ("WifiCommunication_Client")
/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

/*------------------------------< Prototypes >--------------------------------*/
static void connect_tcp_soc(std::unique_ptr<seqreqrep::Client> &cli);
static void connect_sub(pubsub::Subscriber &sub);

//Driver file for Client
int main()
{
    std::shared_ptr<spdlog::logger> m_logger{spdlog::stdout_color_mt(LOGGER_NAME)};
    m_logger->set_level(spdlog::level::debug);
    std::unique_ptr<seqreqrep::Client> client(new seqreqrep::Client);
    pubsub::Subscriber subscriber(true);

    connect_tcp_soc(client);
    //a counter to counts requests and responses

    // temp code to listen published data from server
    connect_sub(subscriber);

    // temp end
    while (true)
    {
        std::string request = Common::seqreqrep::create_startstop_req(wifi::startstop_enum::START);

        std::string reply;
        //if connection is not broken
        if (client->reqrep(request, reply, 10000))
        {
            ReturnCode retCode;
            Common::seqreqrep::parse_startstop_rep(reply, retCode);

            m_logger->debug("Server Rep: {}", retCode);
        }
        //if it is broken
        else
        {
            m_logger->critical("Connection was Broken");
            //resets client
            client.reset(new seqreqrep::Client);
            //reconnects
            connect_tcp_soc(client);
        }
    }

    return 0;
}

void connect_sub(pubsub::Subscriber &sub)
{
    std::string addr;

    addr.resize(50);
    sprintf(&addr.front(), zmqbase::PROC_CONNECTION.c_str(), MCU_SUB_PROC_CONN);
    sub.connect(addr);

    sub.subscribe("");
}

/*
 *connects to tcp://127.0.0.1:5555 socket
 */
void connect_tcp_soc(std::unique_ptr<seqreqrep::Client> &cli)
{
    std::string addr;
    addr.resize(50);
    sprintf(&addr.front(), zmqbase::TCP_CONNECTION.c_str(), IP, PORT);
    cli->connect(addr);
}
