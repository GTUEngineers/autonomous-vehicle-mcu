/**
 * \file        UARTMessageBuilder.h
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Aug 17, 2019
 */

#ifndef UART_MESSAGEBUILDER_H_
#define UART_MESSAGEBUILDER_H_

/*------------------------------< Includes >----------------------------------*/
#include <memory>
#include <spdlog/spdlog.h>
#include <string>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/

class UARTMessageBuilder
{
public:
    UARTMessageBuilder(); /* Constructor */
    ~UARTMessageBuilder();
  
private:
    std::shared_ptr<spdlog::logger> m_logger;
};

#endif /* UART_MESSAGEBUILDER_H_ */