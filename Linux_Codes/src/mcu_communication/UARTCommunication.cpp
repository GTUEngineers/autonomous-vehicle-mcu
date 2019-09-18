/**
 * \file        UARTCommunication.cpp
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Aug 17, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "UARTCommunication.h"
#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/syslog_sink.h>
// Linux headers
#include <cstring>
#include <errno.h> // Error integer and strerror() function
#include <fcntl.h> // Contains file controls like O_RDWR
#include <stdio.h>
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

UARTCommunication::UARTCommunication(const std::string& serial_port)
{
    m_serial_port = serial_port;
    m_logger = spdlog::get("UARTCommunication");
    if (m_logger == nullptr) {
        m_logger = spdlog::stdout_color_mt("UARTCommunication");
    }
    m_logger->set_level(spdlog::level::debug);
    m_logger->info("Serial Port:{}", serial_port);
    configure_termios();
}

UARTCommunication::~UARTCommunication()
{
    try {
        close_fd();
    } catch (...) {
    }
}

void UARTCommunication::set_serial_port(const std::string& serial_port)
{
    this->m_serial_port = serial_port;
}

bool UARTCommunication::configure_termios()
{

    // Create new termios struc, we call it 'tty' for convention
    struct termios tty;
    std::memset(&tty, 0, sizeof(tty));
    m_fd = open(m_serial_port.c_str(), O_RDWR);
    // Check for errors
    if (m_fd < 0) {
        m_logger->critical("Open: {}", strerror(errno));
        exit(1);
    }

    // Read in existing settings, and handle any error
    if (tcgetattr(m_fd, &tty) != 0) {
        m_logger->critical("tcgetattr: {}", strerror(errno));
        exit(1);
    }

    //Setting termios
    //-------------------------c_cflag---------------////
    tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
    tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
    tty.c_cflag |= CS8; // 8 bits per byte (most common)
    tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
    tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)
    //-------------------------c_lflag---------------////
    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO; // Disable echo
    tty.c_lflag &= ~ECHOE; // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo
    tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
    //-------------------------c_iflag---------------////

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL); // Disable any special
    //-------------------------c_oflag---------------/////
    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
        //-------------------------c_cc---------------////
    tty.c_cc[VTIME] = 5; // Wait for up to 1s (10 deciseconds),
    tty.c_cc[VMIN] = 0; // returning as soon as 2 byte data is received.
    // Set in/out baud rate to be 115200
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    // Flush port, then apply attributes
    tcflush(m_fd, TCIOFLUSH);
    // Save tty settings, also checking for error
    if (tcsetattr(m_fd, TCSANOW, &tty) != 0) {
        m_logger->critical("tcsetattr: {}", strerror(errno));
        exit(1);
    }
    return true;
}

void UARTCommunication::close_fd()
{
    if (m_fd != -1) {

        auto retVal = close(m_fd);
        if (retVal != 0) {
            m_logger->critical("close: {}", strerror(errno));
        }
        m_fd = -1;
    }
}

bool UARTCommunication::receive(uart_rep& message)
{
    ssize_t n = read(m_fd, &message.rep.msg, UART_REP_SIZE);
    m_logger->info("read: {} {}", message.rep_uint16.msg, n);

    // Error Handling
    if (n <= 0) {
        // Read was unsuccessful
        m_logger->critical("Receive: {}", strerror(errno));
        return false;
    }

    return true;
}

bool UARTCommunication::transmit(const uart_req& message)
{
    int writeResult = write(m_fd, message.req.msg, UART_REQ_SIZE);
    m_logger->debug("write: {}", writeResult);
    // Check status
    if (writeResult == -1) {
        m_logger->critical("Transmit: {}", strerror(errno));
        return false;
    }
    return true;
}