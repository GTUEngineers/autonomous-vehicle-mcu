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
#define LOGGER_NAME ("WifiCommunication_Server")
/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

/*------------------------------< Prototypes >--------------------------------*/
static void bind_req_rep_server(seqreqrep::Server &server);

static void bind_req_rep_pub(pubsub::Publisher &pub);

//Driver file for Server
int main()
{
    seqreqrep::Server server;
    pubsub::Publisher publisher(false); // publisher to mcu
    std::shared_ptr<spdlog::logger> m_logger{spdlog::stdout_color_mt(LOGGER_NAME)};
    m_logger->set_level(spdlog::level::debug);
    bind_req_rep_server(server);
    //a counter to counts requests and replies
    m_logger->debug("Server connected");
    bind_req_rep_pub(publisher);
    m_logger->debug("Publisher Connected");
    while (true)
    {
        std::string request;
        //Wait for next request from client
        //if receives a message
        if (server.recv(request))
        {
            wifi::startstop_enum start_or_stop;
            Common::seqreqrep::parse_startstop_req(request, start_or_stop);
            m_logger->debug("Clint Req: {}", start_or_stop);

            //  publish recieved message
            publisher.publish(STARTSTOP_CONTROL_TOPIC, Common::pubsub::create_startstop_msg((uart::startstop_enum)start_or_stop)); //Linux create startstop
            std::string reply = Common::seqreqrep::create_startstop_rep(ReturnCode::OK);

            server.send(reply);
        }
    }
    return 0;
}

/*
 *binds to localhost with port 5556
 */
void bind_req_rep_pub(pubsub::Publisher &pub)
{
    std::string addr;
    addr.resize(50);
    sprintf(&addr.front(), zmqbase::PROC_CONNECTION.c_str(), MCU_SUB_PROC_CONN);
    pub.connect(addr);
}
/*
 *binds to localhost with port 5555
 */
void bind_req_rep_server(seqreqrep::Server &server)
{
    std::string addr;
    addr.resize(50);
    sprintf(&addr.front(), zmqbase::TCP_CONNECTION.c_str(), "*", PORT);
    server.connect(addr);
}

void reply_req_rep_server(seqreqrep::Server &server)
{
}