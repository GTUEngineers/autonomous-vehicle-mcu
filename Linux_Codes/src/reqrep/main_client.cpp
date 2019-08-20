/**
 * \file        client.cpp
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Aug 10, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "client.h"
#include "station_car.pb.h"
#include <iostream>
#include <memory>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/syslog_sink.h>
#include <spdlog/spdlog.h>
#include <unistd.h>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

std::string create_cmd_req(cmd_enum cmd)
{
    std::string ret_str;
    seq_req_rep reqrep;
    std::unique_ptr<Commands> commands(new Commands);
    std::unique_ptr<Command_req> cmd_req(new Command_req);

    cmd_req->set_cmd(cmd);

    commands->set_allocated_req(cmd_req.release());
    reqrep.set_allocated_cmd_msg(commands.release());

    reqrep.SerializeToString(&ret_str);
    return ret_str;
}

std::string create_statework(stateWorking_enum cmd)
{
    std::string ret_str;
    pub_sub pubsub;
    std::unique_ptr<StateWorking> stateworks(new StateWorking);

    stateworks->set_cmd(cmd);

    pubsub.set_allocated_statework(stateworks.release());

    pubsub.SerializeToString(&ret_str);
    return ret_str;
}

std::string create_location(float latitude, float longitude)
{
    std::string ret_str;
    pub_sub pubsub;
    std::unique_ptr<GPS> gps(new GPS);

    gps->set_latitude(latitude);
    gps->set_longitude(longitude);

    pubsub.set_allocated_location(gps.release());

    pubsub.SerializeToString(&ret_str);
    return ret_str;
}

std::string create_hcsr4_dis(double distance)
{
    std::string ret_str;
    pub_sub pubsub;
    std::unique_ptr<HCSR4> hcsr4(new HCSR4);

    hcsr4->set_distance(distance);

    pubsub.set_allocated_hcsr4_dis(hcsr4.release());

    pubsub.SerializeToString(&ret_str);
    return ret_str;
}

bool parse_cmd_rep(std::string &rep, ReturnCode &retCode)
{
    seq_req_rep reqrep;
    if (reqrep.ParseFromArray(rep.data(), rep.size()))
    {
        if (reqrep.has_cmd_msg())
        {
            if (reqrep.cmd_msg().has_rep())
            {
                retCode = reqrep.cmd_msg().rep().retval();
                return true;
            }
        }
    }
    return false;
}

//Driver file for Client
int main()
{
    std::shared_ptr<spdlog::logger> m_logger{spdlog::stdout_color_mt("REQREP_Client")};

    m_logger->set_level(spdlog::level::debug);
    std::unique_ptr<seqreqrep::Client> client(new seqreqrep::Client);
    //connects to tcp://127.0.0.1:5555 socket

    std::string addr;
    addr.resize(50);
    sprintf(&addr.front(), zmqbase::TCP_CONNECTION.c_str(), "127.0.0.1", 5555);

    client->connect(addr);
    //a counter to counts requests and responses

    while (true)
    {
        std::string req = create_cmd_req(cmd_enum::START);
        zmq::message_t request(req.c_str(), req.size());

        zmq::message_t reply;
        //if connection is not broken
        if (client->reqrep(request, reply, 3))
        {
            ReturnCode retCode;
            std::string rep((char *)reply.data(), reply.size());
            parse_cmd_rep(rep, retCode);

            m_logger->debug("Server Rep: {}", retCode);
        }
        //if it is broken
        else
        {
            m_logger->critical("Connection was Broken");
            //resets client
            client.reset(new seqreqrep::Client);
            //reconnects
            client->connect(addr);
        }
        sleep(1);
    }

    return 0;
}
