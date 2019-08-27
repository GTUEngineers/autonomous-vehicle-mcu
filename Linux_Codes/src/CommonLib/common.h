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
#include<stdlib.h>
#include<iostream>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/
namespace Common{
    std::string create_startstop_req(wifi::startstop_enum start_or_stop);
    bool parse_startstop_rep(std::string& rep, ReturnCode& retCode);
    bool parse_startstop_sub(std::string& rep, uart::startstop_enum& start_or_stop);    
}

#endif /* COMMON_H_ */