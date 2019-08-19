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
#include <string>
// C library headers
#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/

class UARTCommunication
{
public:
	UARTCommunication(); /* Constructor */
	std::string sread();
	void swrite(std::string message);
private:
	bool isConnected;
	int serial_port;

};


#endif /* UART_COMMUNICATION_H_ */