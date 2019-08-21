/**
 * \file        UARTMessageBuilder.cpp
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Aug 17, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "UARTMessageBuilder.h"
#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/syslog_sink.h>

/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

UARTMessageBuilder::UARTMessageBuilder()
{
    m_logger = spdlog::stdout_color_mt("UARTMessageBuilder");
    m_logger->set_level(spdlog::level::debug);
    m_logger->info("Serial Port:{}", serial_port);

}

UARTMessageBuilder::~UARTMessageBuilder()
{
    try {

    } catch (...) {
    }
}
