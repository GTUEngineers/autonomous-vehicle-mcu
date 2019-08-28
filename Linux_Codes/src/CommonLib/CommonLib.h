/**
 * \file        common.h
 * \brief       A brief description one line.
 *
 * \author      fatihyakar
 * \date        Aug 27, 2019
 */

#ifndef COMMON_H_
#define COMMON_H_

/*------------------------------< Includes >----------------------------------*/
#include "process.pb.h"
#include "station_car.pb.h"
#include <iostream>
#include <stdlib.h>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/
namespace Common {
namespace seqreqrep {
    std::string create_startstop_req(wifi::startstop_enum start_or_stop);
    bool parse_startstop_rep(std::string& rep, ReturnCode& retCode);
    std::string create_startstop_rep(const ReturnCode& retcode);
    bool parse_startstop_req(std::string& req, wifi::startstop_enum& start_or_stop);
}
namespace pubsub {
    bool parse_startstop(std::string& rep, uart::startstop_enum& start_or_stop);

    std::string create_startstop(uart::startstop_enum start_or_stop);
}
}

#endif /* COMMON_H_ */