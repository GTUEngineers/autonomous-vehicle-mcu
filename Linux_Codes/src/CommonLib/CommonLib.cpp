/**
 * \file        common.cpp
 * \brief       A brief description one line.
 *
 * \author      fatihyakar
 * \date        Aug 27, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "CommonLib.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

namespace Common {

namespace seqreqrep { //**********WifiCommunication**********
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

    // For server
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
} // namespace seqreqrep
namespace pubsub {

    /*--------------------------< Parse Functions >--------------------------*/
    bool parse_startstop(std::string& rep_or_req, uart::startstop_enum& start_or_stop)
    {
        uart::pub_sub pubsub;
        if (pubsub.ParseFromArray(rep_or_req.data(), rep_or_req.size())) {
            if (pubsub.has_startstop()) {
                start_or_stop = pubsub.startstop().cmd();
                return true;
            }
        }
        return false;
    }

    bool parse_throttle(std::string& rep_or_req, int& throttle)
    {

        uart::pub_sub pubsub;
        if (pubsub.ParseFromArray(rep_or_req.data(), rep_or_req.size())) {
            if (pubsub.has_throttle()) {
                throttle = pubsub.throttle().throttlevalue();
                return true;
            }
        }

        return false;
    }
    bool parse_steering(std::string& rep_or_req, uart::steering_enum& left_or_right, double& angle)
    {

        uart::pub_sub pubsub;
        if (pubsub.ParseFromArray(rep_or_req.data(), rep_or_req.size())) {
            if (pubsub.has_steering()) {
                left_or_right = pubsub.steering().dir();
                angle = pubsub.steering().angle();
                return true;
            }
        }

        return false;
    }

    bool parse_break(std::string& rep_or_req, bool& is_break)
    {

        uart::pub_sub pubsub;
        if (pubsub.ParseFromArray(rep_or_req.data(), rep_or_req.size())) {
            if (pubsub.has_brake()) {
                is_break = pubsub.brake().brakevalue();
                return true;
            }
        }

        return false;
    }
    bool parse_stateworking(std::string& rep_or_req, uart::stateWorking_enum& active_or_inactive)
    {

        uart::pub_sub pubsub;
        if (pubsub.ParseFromArray(rep_or_req.data(), rep_or_req.size())) {
            if (pubsub.has_statework()) {
                active_or_inactive = pubsub.statework().cmd();
                return true;
            }
        }

        return false;
    }
    bool parse_hcsr4(std::string& rep_or_req, double& distance)
    {

        uart::pub_sub pubsub;
        if (pubsub.ParseFromArray(rep_or_req.data(), rep_or_req.size())) {
            if (pubsub.has_hcsr4_dis()) {
                distance = pubsub.hcsr4_dis().distance();
                return true;
            }
        }

        return false;
    }
    bool parse_gps(std::string& rep_or_req, float& latitude, float& longitude)
    {

        uart::pub_sub pubsub;
        if (pubsub.ParseFromArray(rep_or_req.data(), rep_or_req.size())) {
            if (pubsub.has_location()) {
                latitude = pubsub.location().latitude();
                longitude = pubsub.location().longitude();
                return true;
            }
        }

        return false;
    }
    /*--------------------------< Create Msg Functions >--------------------------*/

    std::string create_statework_msg(uart::stateWorking_enum active_or_inactive)
    {
        std::string ret_str;
        uart::pub_sub pubsub;
        std::unique_ptr<uart::StateWorking> stateworks(new uart::StateWorking);
        pubsub.set_msg_type(uart::pub_sub_message::STATE_WORKING_MSG);
        stateworks->set_cmd(active_or_inactive);
        pubsub.set_allocated_statework(stateworks.release());

        pubsub.SerializeToString(&ret_str);
        return ret_str;
    }

    std::string create_location_msg(float latitude, float longitude)
    {
        std::string ret_str;
        uart::pub_sub pubsub;
        std::unique_ptr<uart::GPS> gps(new uart::GPS);

        pubsub.set_msg_type(uart::pub_sub_message::GPS_MSG);
        gps->set_latitude(latitude);
        gps->set_longitude(longitude);
        pubsub.set_allocated_location(gps.release());

        pubsub.SerializeToString(&ret_str);
        return ret_str;
    }

    std::string create_hcsr4_dis_msg(double distance)
    {
        std::string ret_str;
        uart::pub_sub pubsub;
        std::unique_ptr<uart::HCSR4> hcsr4(new uart::HCSR4);

        pubsub.set_msg_type(uart::pub_sub_message::HCSR4_MSG);
        hcsr4->set_distance(distance);
        pubsub.set_allocated_hcsr4_dis(hcsr4.release());

        pubsub.SerializeToString(&ret_str);
        return ret_str;
    }

    std::string create_startstop_msg(uart::startstop_enum start_or_stop)
    {
        std::string ret_str;
        uart::pub_sub pubsub;
        std::unique_ptr<uart::StartStop_req> startstop(new uart::StartStop_req);

        pubsub.set_msg_type(uart::pub_sub_message::START_STOP_MSG);
        startstop->set_cmd(start_or_stop);
        pubsub.set_allocated_startstop(startstop.release());

        pubsub.SerializeToString(&ret_str);
        return ret_str;
    }

    std::string create_steering_msg(uart::steering_enum left_or_right, double angle)
    {
        std::string ret_str;
        uart::pub_sub pubsub;
        std::unique_ptr<uart::Steering_req> steering(new uart::Steering_req);

        pubsub.set_msg_type(uart::pub_sub_message::STEERING_MSG);
        steering->set_dir(left_or_right);
        steering->set_angle(angle);
        pubsub.set_allocated_steering(steering.release());

        pubsub.SerializeToString(&ret_str);
        return ret_str;
    }

    std::string create_throttle_msg(uint32_t throttleValue)
    {
        std::string ret_str;
        uart::pub_sub pubsub;
        std::unique_ptr<uart::Throttle_req> throttle(new uart::Throttle_req);

        pubsub.set_msg_type(uart::pub_sub_message::THROTTLE_MSG);
        throttle->set_throttlevalue(throttleValue);
        pubsub.set_allocated_throttle(throttle.release());

        pubsub.SerializeToString(&ret_str);
        return ret_str;
    }

    std::string create_brake_msg(uart::brake_enum brakeValue)
    {
        std::string ret_str;
        uart::pub_sub pubsub;
        std::unique_ptr<uart::Brake_req> brake(new uart::Brake_req);

        pubsub.set_msg_type(uart::pub_sub_message::BRAKE_MSG);
        brake->set_brakevalue(brakeValue);
        pubsub.set_allocated_brake(brake.release());

        pubsub.SerializeToString(&ret_str);
        return ret_str;
    }
} // namespace pubsub
//******************************
} // namespace Common