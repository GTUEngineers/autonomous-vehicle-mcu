/**
 * \file        server.cpp
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Aug 10, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "CommonLib.h"
#include "CommunicationMechanism.h"
#include "publisher.h"
#include "server.h"
#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/syslog_sink.h>
#include <spdlog/spdlog.h>
#include <unistd.h>
#include <zmq.hpp>
/*------------------------------< Defines >-----------------------------------*/
#define LOGGER_NAME "WifiCommunication_Server"
/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

/*------------------------------< Prototypes >--------------------------------*/
void bind_req_rep_server(std::string &add, seqreqrep::Server &server);
void reply_req_rep_server(seqreqrep::Server &server);
void bind_req_rep_pub(std::string &add, pubsub::Publisher &pub);

//Driver file for Server
int main()
{
    seqreqrep::Server server;
    pubsub::Publisher publisher(false); // publisher to mcu
    std::shared_ptr<spdlog::logger> m_logger{spdlog::stdout_color_mt(LOGGER_NAME)};
    std::string addr;
    m_logger->set_level(spdlog::level::debug);
    bind_req_rep_server(addr, server);
    //a counter to counts requests and replies
    m_logger->debug("Server connected");
    bind_req_rep_pub(addr, publisher);
    m_logger->debug("Publisher Connected";
    while (true)
    {
        std::string request;
        //Wait for next request from client
        //if receives a message
        if (server.recv(request))
        {
            wifi::startstop_enum start_or_stop;
            Common::seqreqrep::parse_startstop_req(req, start_or_stop);
            log->debug("Clint Req: {}", start_or_stop);
            reply_req_rep_server(server);
            //std::string pub = Common::pubsub::create_startstop_msg((uart::startstop_enum)start_or_stop);
            //  publish recieved message
            m_logger->debug("Pub: {}", STARTSTOP_CONTROL_TOPIC);
            publisher.publish("a/a", STARTSTOP_CONTROL_TOPIC);
        }
    }
    return 0;
}

/*
 *binds to localhost with port 5556
 */
void bind_req_rep_pub(std::string &add, pubsub::Publisher &pub)
{
    add.resize(50);
    sprintf(&add.front(), zmqbase::PROC_CONNECTION.c_str(), MCU_SUB_PROC_CONN);
    pub.connect(add);
}
/*
 *binds to localhost with port 5555
 */
void bind_req_rep_server(std::string &add, seqreqrep::Server &server)
{
    add.resize(50);
    sprintf(&add.front(), zmqbase::TCP_CONNECTION.c_str(), "*", PORT);
    server.connect(add);
    add.clear();
}

void reply_req_rep_server(seqreqrep::Server &server)
{
    std::string reply = Common::seqreqrep::create_startstop_rep(ReturnCode::OK);
    server.send(reply);
}