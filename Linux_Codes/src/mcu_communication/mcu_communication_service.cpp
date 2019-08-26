/**
 * \file        mcu_communication_service.cpp
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Aug 17, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "UARTCommunication.h"
#include "UARTMessageBuilder.h"
#include "process.pb.h"
#include <cstring>
#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/syslog_sink.h>
#include <spdlog/spdlog.h>
#include <string>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

int main()
{
    std::shared_ptr<spdlog::logger> logger{ spdlog::stdout_color_mt("mcu_communication_service") };
    logger->set_level(spdlog::level::debug);
    /* UARTCommunication a("/dev/ttyUSB0");
    a.transmit("aa");
    std::string alp;
    a.receive(alp);
*/
    float a = 0.52;
    uart_rep rep;
    memcpy(&rep.rep.msg[1], &a, sizeof(float));
    logger->info("{}", rep.gps.latitude);
}