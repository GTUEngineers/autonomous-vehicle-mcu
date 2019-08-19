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

/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/

class UARTCommunication
{
public:
	UARTCommunication(); /* Constructor */
	std::string receive();
	void transmit(std::string message);

private:
	bool isConnected;
	std::string lastMessage;
};

#endif /* UART_COMMUNICATION_H_ */