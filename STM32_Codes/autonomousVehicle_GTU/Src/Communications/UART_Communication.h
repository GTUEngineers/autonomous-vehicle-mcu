/**
 * \file        UART_Communication.h
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Aug 17, 2019
 */

#ifndef COMMUNICATIONS_UART_COMMUNICATION_H_
#define COMMUNICATIONS_UART_COMMUNICATION_H_

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*------------------------------< Includes >----------------------------------*/

/*------------------------------< Defines >-----------------------------------*/
#define UART_TRANSMIT_TIMEOUT (2)
#define UART_RECEIVE_TIMEOUT (2)
/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Prototypes >--------------------------------*/
void uart_init ( );
void uart_transmit (uint8_t * msg, uint8_t msg_len);
void uart_receive (uint8_t * msg);

#if defined(__cplusplus)
}                /* Make sure we have C-declarations in C++ programs */
#endif

#endif /* COMMUNICATIONS_UART_COMMUNICATION_H_ */
