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
    //0001 0011 0000 0010
    init_uartmessagebuilder_logger();
    uint16_t temp;
    logger->info("{}", create_gps_msg().req_uint16.msg);

    sleep(1);
}