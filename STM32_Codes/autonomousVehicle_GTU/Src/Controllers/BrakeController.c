/**
 * \file        BrakeController.c
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Jul 5, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "BrakeController.h"
#include "cmsis_os.h"
#include "main.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Variables >---------------------------------*/
static StaticSemaphore_t xSemaphoreBuffer;
static SemaphoreHandle_t xSemaphore;

BrakePosition brake_current_position = BRAKE_RELEASE;
BrakePosition brake_next_position = BRAKE_RELEASE;

osThreadId brakeTaskHandle;
uint32_t brakeTaskBuffer[512];
osStaticThreadDef_t brakeTaskControlBlock;
/*------------------------------< Prototypes >--------------------------------*/
void brake_task (void const * argument);
void brake_lock ( );
void brake_release ( );
void brake_stop ( );
/*------------------------------< Functions >---------------------------------*/

void brake_init ( )
{
    brake_stop( );     // set GPIO pin initial value
    xSemaphore = xSemaphoreCreateCountingStatic(1, 0, &xSemaphoreBuffer);

    osThreadStaticDef(BrakeTask, brake_task, osPriorityNormal, 0, 512, brakeTaskBuffer,
            &brakeTaskControlBlock);
    brakeTaskHandle = osThreadCreate(osThread(BrakeTask), NULL);
}

void brake_task (void const * argument)
{

    while (1)
    {
        if (osSemaphoreWait(xSemaphore, osWaitForever) >= 0)
        {
            switch (brake_next_position)
            {
                case BRAKE_STOP:
                    brake_stop( );
                    break;
                case BRAKE_RELEASE:
                    brake_release( );
                    osDelay(1550);     //TODO fix it
                    brake_stop( );
                    break;
                case BRAKE_HALF:

                    break;
                case BRAKE_LOCK:
                    brake_lock( );
                    osDelay(2050);
                    brake_stop( );
                    break;
                default:
                    //TODO add logger
                    break;
            }
            brake_current_position = brake_next_position;
        }
        else
        {
            //TODO logger
        }
    }
}

BrakePosition brake_get_value ( )
{
    return brake_current_position;
}

void brake_set_value (BrakePosition val)
{
    if (val == brake_next_position || val == brake_current_position)
    {
        return;
    }
    brake_next_position = val;
    osSemaphoreRelease(xSemaphore);

}

void brake_lock ( )
{
    //Brake motor lock to brake
    HAL_GPIO_WritePin(BRAKE_RELAY_PIN_1_GPIO_Port, BRAKE_RELAY_PIN_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(BRAKE_RELAY_PIN_1_GPIO_Port, BRAKE_RELAY_PIN_2_Pin, GPIO_PIN_RESET);
}

void brake_release ( )
{
    //Brake motor release to brake
    HAL_GPIO_WritePin(BRAKE_RELAY_PIN_1_GPIO_Port, BRAKE_RELAY_PIN_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(BRAKE_RELAY_PIN_1_GPIO_Port, BRAKE_RELAY_PIN_2_Pin, GPIO_PIN_SET);
}

void brake_stop ( )
{
    //Brake motor stop current position
    HAL_GPIO_WritePin(BRAKE_RELAY_PIN_1_GPIO_Port, BRAKE_RELAY_PIN_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(BRAKE_RELAY_PIN_1_GPIO_Port, BRAKE_RELAY_PIN_2_Pin, GPIO_PIN_RESET);
}

float brake_get_rotary_position_sensor_value ( )
{
    return 0.0;     //TODO read rotary sensor value
}

void brake_test ( )
{
    // lock the brake 1 seconds
    brake_set_value(BRAKE_LOCK);
    osDelay(1000);
    //  wait for 5 seconds
    brake_set_value(BRAKE_STOP);
    osDelay(3000);
    // release the brake 1 seconds
    brake_set_value(BRAKE_RELEASE);
    osDelay(1000);
    //  wait for 5 seconds
    brake_set_value(BRAKE_STOP);
    osDelay(3000);
}
