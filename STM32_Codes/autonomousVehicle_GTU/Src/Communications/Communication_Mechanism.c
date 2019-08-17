/**
 * \file        Communication_Mechanism.c
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Aug 17, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "Communication_Mechanism.h"
#include "UART_Communication.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Variables >---------------------------------*/
static StaticSemaphore_t xSemaphoreBuffer;
static SemaphoreHandle_t xSemaphore;

osThreadId communicationTransmitTaskHandle;
uint32_t communicationTransmitTaskBuffer[256];
osStaticThreadDef_t communicationTransmitTaskControlBlock;

osThreadId communicationReceiveTaskHandle;
uint32_t communicationReceiveTaskBuffer[512];
osStaticThreadDef_t communicationReceiveTaskControlBlock;
/*------------------------------< Prototypes >--------------------------------*/
static void communication_receive_task (void const * argument);
static void communication_transmit_task (void const * argument);
/*------------------------------< Functions >---------------------------------*/

void communication_init ( )
{
    xSemaphore = xSemaphoreCreateCountingStatic(1, 0, &xSemaphoreBuffer);

    osThreadStaticDef(CommunicationReceiveTask, communication_receive_task, osPriorityNormal, 0,
            512, communicationReceiveTaskBuffer, &communicationReceiveTaskControlBlock);
    communicationReceiveTaskHandle = osThreadCreate(osThread(CommunicationReceiveTask), NULL);

    osThreadStaticDef(CommunicationTransmitTask, communication_transmit_task, osPriorityNormal, 0,
            256, communicationTransmitTaskBuffer, &communicationTransmitTaskControlBlock);
    communicationTransmitTaskHandle = osThreadCreate(osThread(CommunicationTransmitTask), NULL);
}

void communication_receive_task (void const * argument)
{
    while (1)
    {
        //uart_receive()
        //and add queue
    }
}

uint8_t communication_get_msg (uint8_t* msg)
{
}

uint8_t communication_get_queue_length ( )
{
}

void communication_send_msg (uint8_t* msg)
{
}
