/**
 * \file        common.cpp
 * \brief       A brief description one line.
 *
 * \author      fatihyakar
 * \date        Aug 27, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "common.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

namespace Common{
    //**********WifiCommunication**********
    //For client
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
    //For server
    std::string create_startstop_rep(const ReturnCode& retcode)
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

    bool parse_startstop_req(std::string& req, wifi::startstop_enum& start_or_stop)
    {
        wifi::seq_req_rep reqrep;
        if (reqrep.ParseFromArray(req.data(), req.size())) {
            if (reqrep.has_startstop_msg()) {
                if (reqrep.startstop_msg().has_req()) {
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
    //******************************
}