/**
 * \file        Communication_Mechanism.h
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Aug 17, 2019
 */

#ifndef COMMUNICATIONS_COMMUNICATION_MECHANISM_H_
#define COMMUNICATIONS_COMMUNICATION_MECHANISM_H_

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*------------------------------< Includes >----------------------------------*/
#include "UART_Message.h"
#include "autonomousVehicle_conf.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Prototypes >--------------------------------*/

void communication_init ( );
Return_Status communication_get_msg (uart_message* msg);
uint8_t communication_get_queue_length ( );
Return_Status communication_send_msg (uart_message* msg);

#if defined(__cplusplus)
}                /* Make sure we have C-declarations in C++ programs */
#endif

#endif /* COMMUNICATIONS_COMMUNICATION_MECHANISM_H_ */
