/**
 * \file        CommunicationMechanism.h
 * \brief       A brief description one line.
 *
 * \author      Sevval MEHDER
 * \date        Aug 17, 2019
 */

#ifndef COM_MECHANISM_H
#define COM_MECHANISM_H

/*------------------------------< Includes >----------------------------------*/
#include <thread>
#include "UARTCommunication.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/

class CommunicationMechanism
{
public:
	CommunicationMechanism(); /* Constructor */
	void waitUntilFinish();

private:
	std::thread helperThread;
	UARTCommunication communication;

	void threadFunction();
};

#endif /* COM_MECHANISM_H */
