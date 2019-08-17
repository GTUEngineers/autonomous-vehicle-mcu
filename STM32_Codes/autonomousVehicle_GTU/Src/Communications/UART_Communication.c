/**
 * \file        UART_Communication.c
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Aug 17, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "UART_Communication.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Variables >---------------------------------*/

/*------------------------------< Prototypes >--------------------------------*/

/*------------------------------< Functions >---------------------------------*/

void uart_init ( )
{
}

void uart_transmit (uint8_t * msg, uint8_t msg_len)
{
    HAL_UART_Transmit(&huart2, (uint8_t *) message, UART_TRANSMIT_TIMEOUT);
}

void uart_receive (uint8_t * msg)
{
    HAL_UART_Receive(&huart2, (uint8_t *) message, msg_len, UART_RECEIVE_TIMEOUT);
}
