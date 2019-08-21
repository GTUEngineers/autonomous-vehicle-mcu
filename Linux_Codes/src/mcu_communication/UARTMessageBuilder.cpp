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
    memcpy(&req.req_uint16, &val, sizeof(uint16_t));
    reverse(req);
    uint8_t header = 0b00010000 | ((uint8_t)dir << 2);
    req.req.msg[0] = (req.req.msg[0] & 0b00000011) | header;
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
}
std::string parse_hcsr4_msg(const uart_rep& msg)
{
}
gps parse_gps_msg(const uart_rep& msg)
{
}
bool parse_general_rep_msg(const uart_rep& msg)
{
    return (bool)msg.rep_uint16.msg;
}
