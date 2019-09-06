/**
 * \file        common.h
 * \brief       A brief description one line.
 *
 * \author      Fatih Selim YAKAR, Tolga REİS
 * \date        Aug 29, 2019
 */

#ifndef COMMON_H_
#define COMMON_H_

/*------------------------------< Includes >----------------------------------*/
#include "lidar_comm.pb.h"
#include "process.pb.h"
#include "station_car.pb.h"
#include <array>
#include <iostream>
#include <stdlib.h>
#include <vector>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/
namespace Common {
namespace seqreqrep {
    std::string create_startstop_req(wifi::startstop_enum start_or_stop);
    bool parse_startstop_rep(std::string& rep, ReturnCode& retCode);
    std::string create_startstop_rep(const ReturnCode& retcode);
    bool parse_startstop_req(std::string& req, wifi::startstop_enum& start_or_stop);
} // namespace seqreqrep

namespace pubsub {
    bool parse_startstop(std::string& rep, uart::startstop_enum& start_or_stop);
    bool parse_gps(std::string& rep_or_req, float& latitude, float& longitude);
    bool parse_hcsr4(std::string& rep_or_req, double& distance);
    bool parse_stateworking(std::string& rep_or_req, uart::stateWorking_enum& active_or_inactive);
    bool parse_break(std::string& rep_or_req, bool& is_break);
    bool parse_steering(std::string& rep_or_req, uart::steering_enum& left_or_right, double& angle);
    bool parse_throttle(std::string& rep_or_req, int& throttle);

    std::string create_startstop_msg(uart::startstop_enum start_or_stop);
    std::string create_brake_msg(uart::brake_enum brakeValue);
    std::string create_throttle_msg(uint32_t throttleValue);
    std::string create_steering_msg(uart::steering_enum left_or_right, double angle);
    std::string create_hcsr4_dis_msg(double distance);
    std::string create_location_msg(float latitude, float longitude);
    std::string create_statework_msg(uart::stateWorking_enum active_or_inactive);
} // namespace pubsub

namespace lidar {
    std::string create_lidar_req(float x1, float y1, float x2, float y2);
    std::string create_lidar_rep(float x, float y, float z, float width, float height);
    std::string create_clusters(std::vector<std::array<float, 5>>& clusterdata);
    bool parse_lidar_req(std::string& req, float& x1, float& y1, float& x2, float& y2);
    bool parse_lidar_rep(std::string& rep, float& x, float& y, float& z, float& width, float& height);
    bool parse_clusters(std::string& subdata, std::vector<std::vector<float>>& clusterdata);
} // namespace lidar
} // namespace Common

#endif /* COMMON_H_ */