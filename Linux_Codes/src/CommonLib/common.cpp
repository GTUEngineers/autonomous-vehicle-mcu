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
    //******************************
}