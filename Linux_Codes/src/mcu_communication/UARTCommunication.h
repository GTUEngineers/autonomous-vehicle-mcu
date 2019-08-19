/**
 * \file        UARTCommunication.h
 * \brief       A brief description one line.
 *
 * \author      Sevval MEHDER
 * \date        Aug 17, 2019
 */

#ifndef UART_COMMUNICATION_H_
#define UART_COMMUNICATION_H_

/*------------------------------< Includes >----------------------------------*/
#include <memory>
#include <spdlog/spdlog.h>
#include <string>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/

class UARTCommunication
{
public:
    UARTCommunication(const std::string &serial_port); /* Constructor */
    ~UARTCommunication();
    bool receive(std::string &message);
    bool transmit(const std::string &message);
    bool set_timeout(int timeout);
    void close_fd();
    void set_serial_port(const std::string &serial_port);

private:
    bool configure_termios();
    std::string m_serial_port;
    bool m_isConnected;
    int m_fd;

    std::shared_ptr<spdlog::logger> m_logger;
};

#endif /* UART_COMMUNICATION_H_ */