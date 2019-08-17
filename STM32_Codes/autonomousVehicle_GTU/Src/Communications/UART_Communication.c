/**
 * \file        UART_Communication.c
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Aug 17, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "cmsis_os.h"
#include "UART_Communication.h"
#include "main.h"

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
    HAL_UART_Transmit(&huart2, (uint8_t *) msg, msg_len, UART_TRANSMIT_TIMEOUT);
}

Return_Status uart_receive (uint8_t * msg, uint8_t msg_len)
{
    if (HAL_UART_Receive(&huart2, (uint8_t *) msg, msg_len, (TickType_t) portMAX_DELAY) == HAL_OK)
    {
        return OK;
    }

    return NOK;

}
