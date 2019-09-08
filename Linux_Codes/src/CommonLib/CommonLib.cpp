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
namespace lidar {
    std::string create_lidar_req(float x1, float y1, float x2, float y2)
    {
        std::string ret_str;
        LidarComm::req_rep reqrep;
        std::unique_ptr<LidarComm::RequestData> reqdata(new LidarComm::RequestData);
        std::unique_ptr<LidarComm::Pixel> pixel_upper_left(new LidarComm::Pixel);
        std::unique_ptr<LidarComm::Pixel> pixel_downer_right(new LidarComm::Pixel);

        pixel_upper_left->set_x(x1);
        pixel_upper_left->set_y(y1);
        reqdata->set_allocated_upper_left(pixel_upper_left.release());

        pixel_downer_right->set_x(x2);
        pixel_downer_right->set_y(y2);
        reqdata->set_allocated_downer_right(pixel_downer_right.release());

        reqrep.set_allocated_lidar_req(reqdata.release());

        reqrep.SerializeToString(&ret_str);

        return ret_str;
    }

    std::string create_lidar_rep(float x, float y, float z, float width, float height)
    {
        std::string ret_str;
        LidarComm::req_rep reqrep;
        std::unique_ptr<LidarComm::Cluster> repdata(new LidarComm::Cluster);
        std::unique_ptr<LidarComm::Position> cluster_position(new LidarComm::Position);
        std::unique_ptr<LidarComm::Size> cluster_size(new LidarComm::Size);

        cluster_size->set_width(width);
        cluster_size->set_height(height);
        cluster_position->set_x(x);
        cluster_position->set_y(y);
        cluster_position->set_z(z);

        repdata->set_allocated_center(cluster_position.release());
        repdata->set_allocated_size(cluster_size.release());

        reqrep.set_allocated_lidar_rep(repdata.release());

        reqrep.SerializeToString(&ret_str);

        return ret_str;
    }

    std::string create_clusters(std::vector<std::array<float, 5>>& clusterdata)
    {
        std::string ret_str;
        LidarComm::pub_sub pubsub;
        for (int i = 0; i < clusterdata.size(); ++i) {
            //std::unique_ptr<LidarComm::Cluster> subdata(new LidarComm::Cluster);
            std::unique_ptr<LidarComm::Position> cluster_position(new LidarComm::Position);
            std::unique_ptr<LidarComm::Size> cluster_size(new LidarComm::Size);

            cluster_position->set_x(clusterdata[i][0]);
            cluster_position->set_y(clusterdata[i][1]);
            cluster_position->set_z(clusterdata[i][2]);
            cluster_size->set_width(clusterdata[i][3]);
            cluster_size->set_height(clusterdata[i][4]);

            LidarComm::Cluster* subdata = pubsub.add_clusters();
            subdata->set_allocated_center(cluster_position.release());
            subdata->set_allocated_size(cluster_size.release());
        }

        pubsub.SerializeToString(&ret_str);

        return ret_str;
    }

    bool parse_lidar_req(std::string& req, float& x1, float& y1, float& x2, float& y2)
    {
        LidarComm::req_rep reqrep;
        if (reqrep.ParseFromArray(req.data(), req.size())) {
            if (reqrep.has_lidar_req()) {
                x1 = reqrep.lidar_req().upper_left().x();
                y1 = reqrep.lidar_req().upper_left().y();
                x2 = reqrep.lidar_req().downer_right().x();
                y2 = reqrep.lidar_req().downer_right().y();
                return true;
            }
        }
        return false;
    }

    bool parse_lidar_rep(std::string& rep, float& x, float& y, float& z, float& width, float& height)
    {
        LidarComm::req_rep reqrep;
        if (reqrep.ParseFromArray(rep.data(), rep.size())) {
            if (reqrep.has_lidar_rep()) {
                x = reqrep.lidar_rep().center().x();
                y = reqrep.lidar_rep().center().y();
                z = reqrep.lidar_rep().center().z();
                width = reqrep.lidar_rep().size().width();
                height = reqrep.lidar_rep().size().height();
                return true;
            }
        }
        return false;
    }

    bool parse_clusters(std::string& subdata, std::vector<std::vector<float>>& clusterdata)
    {
        LidarComm::pub_sub pubsub;
        if (pubsub.ParseFromArray(subdata.data(), subdata.size())) {
            for (int i = 0; i < pubsub.clusters_size(); ++i) {
                std::vector<float> temp;
                clusterdata.push_back(temp);
                temp.push_back(pubsub.clusters(i).center().x());
                temp.push_back(pubsub.clusters(i).center().y());
                temp.push_back(pubsub.clusters(i).center().z());
                temp.push_back(pubsub.clusters(i).size().width());
                temp.push_back(pubsub.clusters(i).size().height());
            }
            return true;
        }
        return false;
    }
} // namespace lidar
//******************************
} // namespace Common