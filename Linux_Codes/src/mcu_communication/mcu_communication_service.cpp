/**
 * \file        mcu_communication_service.cpp
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Aug 17, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "CommunicationMechanism.h"
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
#define LOGGER_NAME ("mcu_communication_service")

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/
/* std::unique_ptr<UARTCommunication> uartcom;
std::shared_ptr<spdlog::logger> logger;
int i = 0;
int counter = 0;
bool uart_reqrep(uart_req& req, uart_rep& rep)
{
    uint8_t try_counter{ 0 };
    bool ret{ false };
    do {
        uartcom->transmit(req); //stateworking
        ret = uartcom->receive(rep);
        if (!ret) {
            i++;
        }
        ++try_counter;
        usleep(100);
    } while (!ret && try_counter < 3);
    if (!ret && try_counter >= 3) {
        return false;
    }
    return true;
}
int main(int argc, char** argv)
{

    logger = spdlog::get(LOGGER_NAME);
    if (logger == nullptr) {
        logger = spdlog::stdout_color_mt(LOGGER_NAME);
    }

    logger->set_level(spdlog::level::debug);
    if (argc <= 1) {
        logger->critical("UART PORT ERROR");
        exit(1);
    }
    uartcom.reset(new UARTCommunication(argv[1]));
    uart_req req;
    uart_req req1;
    req.req.msg[0] = 0;
    req1.req.msg[1] = 1;
    uart_rep rep;
    uart_rep rep1;

    while (true) {
        logger->warn("i{}", i);
        logger->warn("counter{}", counter);
        ++counter;
        if (!uart_reqrep(req, rep)) {
            logger->critical("BAM");
            break;
        }
        usleep(10);
        if (!uart_reqrep(req1, rep1)) {
            logger->critical("BAM");
            break;
        }
        usleep(10);
    }
    // CommunicationMechanism cm(argv[1]);
    // cm.waitUntilFinish();
    //sleep(1111);
}
*/
int main(int argc, char** argv)
{

    std::shared_ptr<spdlog::logger> logger;
    logger = spdlog::get(LOGGER_NAME);
    if (logger == nullptr) {
        logger = spdlog::stdout_color_mt(LOGGER_NAME);
    }

    logger->set_level(spdlog::level::debug);
    if (argc <= 1) {
        logger->critical("UART PORT ERROR");
        exit(1);
    }
    CommunicationMechanism cm(argv[1]);
    cm.waitUntilFinish();
    //sleep(1111);
}