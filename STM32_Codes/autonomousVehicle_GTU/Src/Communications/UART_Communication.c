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
#define SEMAPHORE_TIMEOUT (3000)
/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Variables >---------------------------------*/
static StaticSemaphore_t xSemaphoreBuffer;
static SemaphoreHandle_t xSemaphore;
/*------------------------------< Prototypes >--------------------------------*/

/*------------------------------< Functions >---------------------------------*/

void uart_init ( )
{
    xSemaphore = xSemaphoreCreateCountingStatic(1, 1, &xSemaphoreBuffer);
}

void uart_transmit (uint8_t * msg, uint8_t msg_len)
{
    if (osSemaphoreWait(xSemaphore, SEMAPHORE_TIMEOUT) >= 0)
    {
        HAL_UART_Transmit(&huart2, (uint8_t *) msg, msg_len, UART_TRANSMIT_TIMEOUT);
    }
    osSemaphoreRelease(xSemaphore);
    return;
}

Return_Status uart_receive (uint8_t * msg, uint8_t msg_len)
{
    Return_Status ret_val = NOK;
    if (osSemaphoreWait(xSemaphore, SEMAPHORE_TIMEOUT) >= 0)
    {
        if (HAL_UART_Receive(&huart2, (uint8_t *) msg, msg_len, (TickType_t) UART_RECEIVE_TIMEOUT)
                == HAL_OK)
        {
            ret_val = OK;
        }
    }
    osSemaphoreRelease(xSemaphore);
    return ret_val;

}
