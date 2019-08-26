/**
 * \file        client.cpp
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Aug 10, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "client.h"
#include "process.pb.h"
#include "station_car.pb.h"
#include "subscriber.h"
#include <iostream>
#include <memory>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/syslog_sink.h>
#include <spdlog/spdlog.h>
#include <unistd.h>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

std::string create_startstop_req(wifi::startstop_enum start_or_stop)
{
    std::string ret_str;
    wifi::seq_req_rep reqrep;
    std::unique_ptr<wifi::StartStop> startstop(new wifi::StartStop);
    std::unique_ptr<wifi::StartStop_req> startstop_req(new wifi::StartStop_req);

    startstop_req->set_startstop(start_or_stop);

    startstop->set_allocated_req(startstop_req.release());
    reqrep.set_allocated_startstop_msg(startstop.release());

    reqrep.SerializeToString(&ret_str);
    return ret_str;
}

bool parse_startstop_rep(std::string& rep, ReturnCode& retCode)
{
    wifi::seq_req_rep reqrep;
    if (reqrep.ParseFromArray(rep.data(), rep.size())) {
        if (reqrep.has_startstop_msg()) {
            if (reqrep.startstop_msg().has_rep()) {
                retCode = reqrep.startstop_msg().rep().retval();
                return true;
            }
        }
    }
    return false;
}

// temp function to listen published data from server
bool parse_startstop_sub(std::string& rep, uart::startstop_enum& start_or_stop)
{
    uart::pub_sub pubsub;
    if (pubsub.ParseFromArray(rep.data(), rep.size())) {
        if (pubsub.has_startstop()) {
            start_or_stop = pubsub.startstop().cmd();
            return true;
        }
    }
    return false;
}
// temp end

//Driver file for Client
int main()
{
    std::shared_ptr<spdlog::logger> m_logger{ spdlog::stdout_color_mt("WifiCommunication_Client") };

    m_logger->set_level(spdlog::level::debug);
    std::unique_ptr<seqreqrep::Client> client(new seqreqrep::Client);
    //connects to tcp://127.0.0.1:5555 socket

    std::string addr;
    addr.resize(50);
    sprintf(&addr.front(), zmqbase::TCP_CONNECTION.c_str(), "127.0.0.1", 5555);

    client->connect(addr);
    //a counter to counts requests and responses

    // temp code to listen published data from server
    pubsub::Subscriber subscriber(true);
    addr.clear();
    addr.resize(50);
    sprintf(&addr.front(), zmqbase::PROC_CONNECTION.c_str(), "mcu_communication_su");
    subscriber.connect(addr);
    std::string top("startstoptopic");
    subscriber.subscribe("");
    // temp end
    while (true) {
        std::string request = create_startstop_req(wifi::startstop_enum::START);

        std::string reply;
        //if connection is not broken
        if (client->reqrep(request, reply, 3)) {
            ReturnCode retCode;
            parse_startstop_rep(reply, retCode);

            m_logger->debug("Server Rep: {}", retCode);
        }
        //if it is broken
        else {
            m_logger->critical("Connection was Broken");
            //resets client
            client.reset(new seqreqrep::Client);
            //reconnects
            client->connect(addr);
        }
    }

    return 0;
}
