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
std::shared_ptr<UARTCommunication> uartcom;
bool uart_reqrep(uart_req& req, uart_rep& rep)
{

    int try_counter{ 0 };
    bool ret{ false };
    do {
        uartcom->transmit(req); //stateworking
        ret = uartcom->receive(rep);
        ++try_counter;
        sleep(1);
    } while (!ret && try_counter < 2);
    std::cerr << try_counter << std::endl;
    if (!ret && try_counter >= 2) {
        std::cerr << "girtdi1";
        return false;
    }
    return true;
}

void reinit_uart()
{
    uartcom->close_fd();
    uartcom.reset(new UARTCommunication("/dev/ttyUSB0"));
    std::cerr << "ALPEREN";
    return;
}
int main()
{
    uartcom.reset(new UARTCommunication("/dev/ttyUSB0"));
    std::shared_ptr<spdlog::logger> logger;
    logger = spdlog::get("mcu_communication_service");
    if (logger == nullptr) {
        logger = spdlog::stdout_color_mt("mcu_communication_service");
    }

    logger->set_level(spdlog::level::debug);
    uart_msg::init_uartmessagebuilder_logger();
    uart_req alp1;
    alp1.req_uint16.msg = 2231;

    uart_rep alp;

    bool ret;
    uint64_t try_counter{ 0 };

    do {
        if (!uart_reqrep(alp1, alp))
            reinit_uart();
        ++try_counter;
        logger->info("{}", try_counter);
    } while (!ret && try_counter < 4);
    //0001 0011 0000 0010

    sleep(1);
}