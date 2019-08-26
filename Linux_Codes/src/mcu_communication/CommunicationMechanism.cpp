/**
 * \file        CommunicationMechanism.cpp
 * \brief       A brief description one line.
 *
 * \author      Sevval MEHDER
 * \date        Aug 17, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "CommunicationMechanism.h"
#include "process.pb.h"
#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/syslog_sink.h>


/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

CommunicationMechanism::CommunicationMechanism()
    : zmq_listener_thread(&CommunicationMechanism::zmq_listener_task, this)
    , uart_periodic_req_thread(&CommunicationMechanism::uart_periodic_req_task, this)
    , publisher(false)
    , subscriber(false)
{
    m_logger = spdlog::stdout_color_mt("CommunicationMechanism");
    m_logger->set_level(spdlog::level::debug);
    // Constructor code
}

void CommunicationMechanism::zmq_listener_task()
{
    subscriber.subscribe("");

    std::string addr;
    addr.resize(50);
    // sprintf(&addr.front(), zmqbase::TCP_CONNECTION.c_str(), ipNum.c_str(), portNumSub);
    m_logger->info("Subscriber addr:{}", addr);
    std::string topic, msg;
    uart::pub_sub pubsub;
    while (true) {
        subscriber.recv(topic, msg);
        if (topic == "control/steering") {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::STEERING_MSG) {
            }
        } else if (topic == "control/throttle") {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::THROTTLE_MSG) {
            }
        } else if (topic == "control/brake") {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::BRAKE_MSG) {
            }
        } else if (topic == "control/startstop") {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::START_STOP_MSG) {
            }
        } else if (topic == "info/stateworking") {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::STATE_WORKING_MSG) {
            }
        } else if (topic == "info/hcsr04") {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::HCSR4_MSG) {
            }
        } else if (topic == "info/gps") {
            pubsub.ParseFromArray(msg.data(), msg.size());
            if (pubsub.msg_type() == uart::pub_sub_message::GPS_MSG) {
            }
        } else {
            m_logger->critical("Invalid Topic: {}", topic);
        }
    }
}

void CommunicationMechanism::uart_periodic_req_task()
{

    while (true)
        ;
}

void CommunicationMechanism::waitUntilFinish()
{

    // Join the thread with the main thread
    this->zmq_listener_thread.join();
    this->uart_periodic_req_thread.join();
}

/*--------------------------< Parse Functions >--------------------------*/
bool parse_startstop_req(std::string& req, uart::startstop_enum& status)
{

    uart::pub_sub pubsub;
    if (pubsub.ParseFromArray(req.data(), req.size())) {
        if (pubsub.has_startstop()) {
            status = pubsub.startstop().cmd();
            return true;
        }
    }

    return false;
}

bool parse_throttle_req(std::string& req, int& throttle)
{

    uart::pub_sub pubsub;
    if (pubsub.ParseFromArray(req.data(), req.size())) {
        if (pubsub.has_throttle()) {
            throttle = pubsub.throttle().throttlevalue();
            return true;
        }
    }

    return false;
}
bool parse_steer_req(std::string& req, uart::steering_enum& cmd, double& angle)
{

    uart::pub_sub pubsub;
    if (pubsub.ParseFromArray(req.data(), req.size())) {
        if (pubsub.has_steering()) {
            cmd = pubsub.steering().cmd();
            angle = pubsub.steering().angle();
            return true;
        }
    }

    return false;
}

bool parse_break_req(std::string& req, bool& is_break)
{

    uart::pub_sub pubsub;
    if (pubsub.ParseFromArray(req.data(), req.size())) {
        if (pubsub.has_brake()) {
            is_break = pubsub.brake().brakevalue();
            return true;
        }
    }

    return false;
}
bool parse_stateworking(std::string& req, uart::stateWorking_enum& cmd)
{

    uart::pub_sub pubsub;
    if (pubsub.ParseFromArray(req.data(), req.size())) {
        if (pubsub.has_statework()) {
            cmd = pubsub.statework().cmd();
            return true;
        }
    }

    return false;
}
bool parse_hcsr4(std::string& req, double& distance)
{

    uart::pub_sub pubsub;
    if (pubsub.ParseFromArray(req.data(), req.size())) {
        if (pubsub.has_hcsr4_dis()) {
            distance = pubsub.hcsr4_dis().distance();
            return true;
        }
    }

    return false;
}
bool parse_gps(std::string& req, float& latitude, float& longitude)
{

    uart::pub_sub pubsub;
    if (pubsub.ParseFromArray(req.data(), req.size())) {
        if (pubsub.has_location()) {
            latitude = pubsub.location().latitude();
            longitude = pubsub.location().longitude();
            return true;
        }
    }

    return false;
}

/*--------------------------< Create Msg Functions >--------------------------*/

std::string create_statework(uart::stateWorking_enum cmd)
{
    std::string ret_str;
    uart::pub_sub pubsub;
    std::unique_ptr<uart::StateWorking> stateworks(new uart::StateWorking);
    pubsub.set_msg_type(uart::pub_sub_message::STATE_WORKING_MSG);
    stateworks->set_cmd(cmd);
    pubsub.set_allocated_statework(stateworks.release());

    pubsub.SerializeToString(&ret_str);
    return ret_str;
}

std::string create_location(float latitude, float longitude)
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

std::string create_hcsr4_dis(double distance)
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

std::string create_startstop_msg(uart::startstop_enum cmd)
{
    std::string ret_str;
    uart::pub_sub pubsub;
    std::unique_ptr<uart::StartStop_req> startstop(new uart::StartStop_req);

    pubsub.set_msg_type(uart::pub_sub_message::START_STOP_MSG);
    startstop->set_cmd(cmd);
    pubsub.set_allocated_startstop(startstop.release());

    pubsub.SerializeToString(&ret_str);
    return ret_str;
}

std::string create_steering_msg(uart::steering_enum cmd, double angle)
{
    std::string ret_str;
    uart::pub_sub pubsub;
    std::unique_ptr<uart::Steering_req> steering(new uart::Steering_req);

    pubsub.set_msg_type(uart::pub_sub_message::STEERING_MSG);
    steering->set_cmd(cmd);
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