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

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

//Driver file for Server
int main()
{
    seqreqrep::Server server;
    std::shared_ptr<spdlog::logger> m_logger{spdlog::stdout_color_mt("WifiCommunication_Server")};

    m_logger->set_level(spdlog::level::debug);
    //binds to localhost with port 5555
    std::string addr;
    addr.resize(50);
    sprintf(&addr.front(), zmqbase::TCP_CONNECTION.c_str(), "*", 5555);
    server.connect(addr);
    //a counter to counts requests and replies
    m_logger->debug("Server connected");
    // publisher to mcu
    pubsub::Publisher publisher(false);
    //binds to localhost with port 5556
    addr.clear();
    addr.resize(50);
    sprintf(&addr.front(), zmqbase::PROC_CONNECTION.c_str(), "mcu_communication_su");
    publisher.connect(addr);
    m_logger->debug("Publisher Connected");
    while (true)
    {

        std::string request;
        //Wait for next request from client
        //if receives a message
        if (server.recv(request))
        {
            //prints
            wifi::startstop_enum start_or_stop;
            Common::seqreqrep::parse_startstop_req(request, start_or_stop);
            m_logger->debug("Clint Req: {}", start_or_stop);
            std::string reply = Common::seqreqrep::create_startstop_rep(ReturnCode::OK);

            //  Send reply back to client
            server.send(reply);

            std::string pub = Common::pubsub::create_startstop_msg((uart::startstop_enum)start_or_stop);
            //  publish recieved message
            m_logger->debug("Pub: {}", pub);
            publisher.publish("a/a", pub);
        }
    }
    return 0;
}
