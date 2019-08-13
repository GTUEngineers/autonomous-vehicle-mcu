/**
 * \file        server.cpp
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Aug 10, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "server.h"
#include "station_car.pb.h"
#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/syslog_sink.h>
#include <spdlog/spdlog.h>
#include <unistd.h>
#include <zmq.hpp>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/
bool parse_cmd_req(std::string& req, cmd_enum& cmd)
{
    seq_req_rep reqrep;
    if (reqrep.ParseFromArray(req.data(), req.size())) {
        if (reqrep.has_cmd_msg()) {
            if (reqrep.cmd_msg().has_req()) {
                cmd = reqrep.cmd_msg().req().cmd();
                return true;
            }
        }
    }
    return false;
}

std::string create_cmd_rep(const ReturnCode& retcode)
{
    std::string ret_str;
    seq_req_rep reqrep;
    std::unique_ptr<Commands> commands(new Commands);
    std::unique_ptr<Command_rep> cmd_rep(new Command_rep);

    cmd_rep->set_retval(retcode);

    commands->set_allocated_rep(cmd_rep.release());
    reqrep.set_allocated_cmd_msg(commands.release());

    reqrep.SerializeToString(&ret_str);
    return ret_str;
}
//Driver file for Server
int main()
{
    seqreqrep::Server server;
    std::shared_ptr<spdlog::logger> m_logger{ spdlog::stdout_color_mt("REQREP_Server") };

    m_logger->set_level(spdlog::level::debug);
    //binds to localhost with port 5555
    std::string addr;
    addr.resize(50);
    sprintf(&addr.front(), zmqbase::TCP_CONNECTION.c_str(), "127.0.0.1", 5555);
    server.connect(addr);
    //a counter to counts requests and replies

    while (true) {
        zmq::message_t request;
        //Wait for next request from client
        //if receives a message
        if (server.recv(request)) {
            //prints
            cmd_enum cmd;
            std::string retstr((char*)request.data(), request.size());
            parse_cmd_req(retstr, cmd);
            m_logger->debug("Clint Req: {}", cmd);
            std::string rep = create_cmd_rep(ReturnCode::OK);

            zmq::message_t reply((char*)rep.data(), rep.size());
            //  Send reply back to client
            server.send(reply);
        }
    }
    return 0;
}
