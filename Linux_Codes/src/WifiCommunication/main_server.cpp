/**
 * \file        server.cpp
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Aug 10, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "server.h"
#include "publisher.h"
#include "station_car.pb.h"
#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/syslog_sink.h>
#include <spdlog/spdlog.h>
#include <unistd.h>
#include <zmq.hpp>
#include "process.pb.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/
std::string create_startstop_rep(const ReturnCode &retcode)
{
    std::string ret_str;
    wifi::seq_req_rep reqrep;
    std::unique_ptr<wifi::StartStop> startstop(new wifi::StartStop);
    std::unique_ptr<wifi::StartStop_rep> startstop_rep(new wifi::StartStop_rep);

    startstop_rep->set_retval(retcode);

    startstop->set_allocated_rep(startstop_rep.release());
    reqrep.set_allocated_startstop_msg(startstop.release());

    reqrep.SerializeToString(&ret_str);
    return ret_str;
}

bool parse_startstop_req(std::string &req, wifi::startstop_enum &start_or_stop)
{
    wifi::seq_req_rep reqrep;
    if (reqrep.ParseFromArray(req.data(), req.size()))
    {
        if (reqrep.has_startstop_msg())
        {
            if (reqrep.startstop_msg().has_req())
            {
                start_or_stop = reqrep.startstop_msg().req().startstop();
                return true;
            }
        }
    }
    return false;
}

std::string create_startstop_pub(uart::startstop_enum start_or_stop)
{
    std::string ret_str;
    uart::pub_sub pubsub;

    std::unique_ptr<uart::StartStop_req> startstop_req(new uart::StartStop_req);

    startstop_req->set_cmd(start_or_stop);
    pubsub.set_msg_type(uart::pub_sub_message::START_STOP_MSG);
    pubsub.set_allocated_startstop(startstop_req.release());

    pubsub.SerializeToString(&ret_str);
    return ret_str;
}

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
            parse_startstop_req(request, start_or_stop);
            m_logger->debug("Clint Req: {}", start_or_stop);
            std::string reply = create_startstop_rep(ReturnCode::OK);

            //  Send reply back to client
            server.send(reply);

            std::string pub = create_startstop_pub((uart::startstop_enum)start_or_stop);
            //  publish recieved message
            m_logger->debug("Pub: {}", pub);
            publisher.publish("startstoptopic", pub);
        }
    }
    return 0;
}
