/**
 * \file        UARTMessageBuilder.cpp
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Aug 17, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "UARTMessageBuilder.h"
#include "process.pb.h"
#include <iostream>
#include <memory>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/syslog_sink.h>
#include <spdlog/spdlog.h>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Variables >----------------------------------*/
std::shared_ptr<spdlog::logger> m_logger;
/*------------------------------< Namespaces >--------------------------------*/
void reverse(uart_req& req);

void init_uartmessagebuilder_logger()
{
    m_logger = spdlog::stdout_color_mt("UARTCommunication");
}
void reverse(uart_req& req)
{
    uint8_t l = req.req.msg[1];
    req.req.msg[1] = req.req.msg[0];
    req.req.msg[0] = l;
}

uart_req create_steer_msg(const uart::steering_enum dir, const uint16_t& val)
{
    uart_req req;
    req.req_uint16.msg = val;
    reverse(req);
    uint8_t header = (uint8_t)dir;
    req.req.msg[0] = ((req.req.msg[0] & 0b00000011) | (header << 2) | 0b00010000);
    return req;
}

uart_req create_throttle_msg(const uint8_t& val)
{
    uart_req req;
    memcpy(&req.req.msg[1], &val, sizeof(uint8_t));
    req.req.msg[0] = 0b00100000;
    return req;
}

uart_req create_brake_msg(const uart::brake_enum val)
{
    uart_req req;
    req.req.msg[0] = 3 << 4;
    req.req.msg[1] = val;
    return req;
}

uart_req create_startstop_msg(const uart::startstop_enum val)
{
    uart_req req;
    req.req.msg[0] = 0;
    req.req.msg[1] = val;
    return req;
}

uart_req create_state_msg()
{
    uart_req req;
    req.req.msg[0] = 64;
    return req;
}

uart_req create_hcsr4_msg()
{
    uart_req req;
    req.req.msg[0] = 80;
    return req;
}
uart_req create_gps_msg()
{
    uart_req req;
    req.req.msg[0] = 96;
    return req;
}

uart::stateWorking_enum parse_state_msg(const uart_rep& msg)
{
    return (uart::stateWorking_enum)msg.rep.msg[1];
}

std::string parse_hcsr4_msg(const uart_rep& msg)
{
}

uart_rep parse_gps_msg(const uart_rep& msg)
{
    return msg;
}

void parse_general_rep_msg(const uart_rep& msg, uint8_t& val)
{
    val = (bool)msg.rep.msg[1];
}

void parse_startstop_rep_msg(const uart_rep& msg, uint8_t& val)
{
    val = (bool)msg.rep.msg[1];
}

void parse_steer_msg(const uart_req& req, uint8_t& dir, uint16_t& val)
{
#define DIR_MASK (0b000000100)
#define ANGLE_MASK (0b00000011111111)
    uint16_t temp = req.req.msg[0];
    dir = (temp & DIR_MASK) >> 2;
    uart_req reqm = req;
    reverse(reqm);
    val = reqm.req_uint16.msg & ANGLE_MASK;
#undef DIR_MASK
#undef ANGLE_MASK
}

void parse_throttle_msg(const uart_req& req, uint8_t& val)
{
    val = req.req.msg[1];
}

void parse_brake_msg(const uart_req& req, uint8_t& val)
{
#define BRAKE_MASK (0b00000001)
    val = (req.req.msg[1] & BRAKE_MASK);
#undef BRAKE_MASK
}