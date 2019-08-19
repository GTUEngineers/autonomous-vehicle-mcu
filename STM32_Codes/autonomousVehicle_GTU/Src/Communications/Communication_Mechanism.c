/**
 * \file        Communication_Mechanism.c
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Aug 17, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "cmsis_os.h"
#include "Communication_Mechanism.h"
#include "UART_Communication.h"
#include "queue.h"

/*------------------------------< Defines >-----------------------------------*/
#define QUEUE_LENGTH    (10) // 10
#define ITEM_SIZE       (sizeof(uart_message)) //9 byte
#define QUEUE_SEND_TIMEOUT  (200)
#define REQ_SIZE            (2)
#define REP_SIZE            (9)
/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Variables >---------------------------------*/
static StaticQueue_t xStaticTransmitQueue;
uint8_t ucTransmitQueueStorageArea[QUEUE_LENGTH * ITEM_SIZE];
static StaticQueue_t xStaticReceiveQueue;
uint8_t ucReceiveQueueStorageArea[QUEUE_LENGTH * ITEM_SIZE];
QueueHandle_t xQueue_transmit, xQueue_receive;

osThreadId communicationTransmitTaskHandle;
uint32_t communicationTransmitTaskBuffer[256];
osStaticThreadDef_t communicationTransmitTaskControlBlock;

osThreadId communicationReceiveTaskHandle;
uint32_t communicationReceiveTaskBuffer[256];
osStaticThreadDef_t communicationReceiveTaskControlBlock;
/*------------------------------< Prototypes >--------------------------------*/
static void communication_receive_task (void const * argument);
static void communication_transmit_task (void const * argument);
/*------------------------------< Functions >---------------------------------*/

void communication_init ( )
{
    xQueue_transmit = xQueueCreateStatic(QUEUE_LENGTH, ITEM_SIZE, ucTransmitQueueStorageArea,
            &xStaticTransmitQueue);

    xQueue_receive = xQueueCreateStatic(QUEUE_LENGTH, ITEM_SIZE, ucReceiveQueueStorageArea,
            &xStaticReceiveQueue);

    osThreadStaticDef(CommunicationReceiveTask, communication_receive_task, osPriorityNormal, 0,
            256, communicationReceiveTaskBuffer, &communicationReceiveTaskControlBlock);
    communicationReceiveTaskHandle = osThreadCreate(osThread(CommunicationReceiveTask), NULL);

    osThreadStaticDef(CommunicationTransmitTask, communication_transmit_task, osPriorityNormal, 0,
            256, communicationTransmitTaskBuffer, &communicationTransmitTaskControlBlock);
    communicationTransmitTaskHandle = osThreadCreate(osThread(CommunicationTransmitTask), NULL);

}

void communication_receive_task (void const * argument)
{
    uart_message data;
    if (xQueue_receive == NULL)
    {
        //error
    }
    while (1)
    {
        if (uart_receive(data.generic_msg.msg, REQ_SIZE) == OK)
        {
            xQueueSend(xQueue_receive, &data, QUEUE_SEND_TIMEOUT);
        }
        else
        {
            //TODO error
        }
        osDelay(50);
    }
}

void communication_transmit_task (void const * argument)
{
    uart_message data;
    if (xQueue_transmit == NULL)
    {
        //TODO error
    }
    while (1)
    {
        if (xQueueReceive(xQueue_transmit, &(data), (TickType_t) portMAX_DELAY) == pdTRUE)
        {
            uart_transmit(data.generic_msg.msg, REP_SIZE);
        }
        osDelay(10);
    }
}

Return_Status communication_get_msg (uart_message* msg)
{
    if (xQueueReceive(xQueue_receive, msg, (TickType_t) portMAX_DELAY) == pdTRUE)
    {
        return OK;
    }

    return NOK;
}

uint8_t communication_get_queue_length ( )
{
    return uxQueueMessagesWaiting(xQueue_receive);
}

Return_Status communication_send_msg (uart_message* msg)
{
    if(xQueueSend(xQueue_transmit, msg, QUEUE_SEND_TIMEOUT) == pdTRUE)
    {
        return OK;
    }
    return NOK;
}
