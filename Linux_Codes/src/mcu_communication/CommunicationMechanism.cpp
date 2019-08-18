/**
 * \file        CommunicationMechanism.cpp
 * \brief       A brief description one line.
 *
 * \author      Sevval MEHDER
 * \date        Aug 17, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include <iostream>
#include "CommunicationMechanism.h"


/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/


CommunicationMechanism::CommunicationMechanism() : helperThread(&CommunicationMechanism::threadFunction, this){
	
	// Constructor code
	
}

void CommunicationMechanism::threadFunction(){

	while(true);

}

void CommunicationMechanism::waitUntilFinish(){

	// Join the thread with the main thread
	this->helperThread.join();

}

