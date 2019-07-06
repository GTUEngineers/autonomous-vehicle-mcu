/**
 * \file        SteerController.c
 * \brief       A brief description one line.
 *
 * \author      tolga
 * \date        6 Tem 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "SteerController.h"
#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include "semphr.h"
#include "dwt_delay.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Variables >---------------------------------*/
//last position of the steering
int last_position;
SemaphoreHandle_t steer_mutex;
/*------------------------------< Prototypes >--------------------------------*/
void pulse ( );
void steer_task ( );
/*------------------------------< Functions >---------------------------------*/

void steer_construct ( )
{
    steer_mutex = xSemaphoreCreateMutex();
}

void steer_deconstruct ( )
{
    vSemaphoreDelete(steer_mutex);
}
//steer_mutex = xSemaphoreCreateMutex();
//vSemaphoreDelete(steer_mutex);

void set_value (int val)
{
    if (val > STEERING_MAX_VALUE || val < -STEERING_MAX_VALUE)
        return;

    xSemaphoreTake(steer_mutex, portMAX_DELAY);
    int dir_val = 0;
    if (get_encoder_value( ) > val)
        dir_val = 1;
    //sets STEER_DIRECTION_PIN_CONF according to dir_val
    switch (dir_val)
    {
        case 1:
            HAL_GPIO_WritePin(GPIOF, STEER_DIRECTION_PIN_CONF.GPIO_Pin, GPIO_PIN_SET);
            break;
        case 0:
            HAL_GPIO_WritePin(GPIOF, STEER_DIRECTION_PIN_CONF.GPIO_Pin, GPIO_PIN_RESET);
            break;
        default:
            break;
    }
    last_position = val;
    xSemaphoreGive(steer_mutex);
}

int get_value ( )
{
    return last_position;
}
float get_encoder_value ( )
{
    return 0.0;
}

void steer_task ( )
{
    DWT_Init( );
    //int count = get_encoder_value();
    while (1)
    {
        xSemaphoreTake(steer_mutex, portMAX_DELAY);
        while (get_value( ) != get_encoder_value( ))
        {
            pulse( );
            xSemaphoreGive(steer_mutex);
            xSemaphoreTake(steer_mutex, portMAX_DELAY);
        }
        xSemaphoreGive(steer_mutex);
    };
}

void test ( )
{
    //RELOCATE this function call
    DWT_Init( );
    // to most right by max pulse to right
    HAL_GPIO_WritePin(STEER_DIRECTION_PIN_CONF.GPIOx, STEER_DIRECTION_PIN_CONF.GPIO_Pin,
            GPIO_PIN_RESET);
    for (int i = 0; i < STEERING_MAX_VALUE; ++i)
    {
        pulse( );
    }

    // wait 1 second
    osDelay(1000);

    // to zero point by max pulse to left
    HAL_GPIO_WritePin(STEER_DIRECTION_PIN_CONF.GPIOx, STEER_DIRECTION_PIN_CONF.GPIO_Pin,
            GPIO_PIN_SET);
    for (int i = 0; i < STEERING_MAX_VALUE; ++i)
    {
        pulse( );
    }

    // wait 1 second
    osDelay(1000);

    // to most left by max pulse to left
    HAL_GPIO_WritePin(STEER_DIRECTION_PIN_CONF.GPIOx, STEER_DIRECTION_PIN_CONF.GPIO_Pin,
            GPIO_PIN_SET);
    for (int i = 0; i < STEERING_MAX_VALUE; ++i)
    {
        pulse( );
    }

    // wait 1 second
    osDelay(1000);
    // to zero point by max pulse to right
    HAL_GPIO_WritePin(STEER_DIRECTION_PIN_CONF.GPIOx, STEER_DIRECTION_PIN_CONF.GPIO_Pin,
            GPIO_PIN_RESET);
    for (int i = 0; i < STEERING_MAX_VALUE; ++i)
    {
        pulse( );
    }

    // wait 1 second
    osDelay(1000);
}

void pulse ( )
{
    HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin, GPIO_PIN_RESET);
    DWT_Delay(150);
    HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin, GPIO_PIN_SET);
    DWT_Delay(150);
}
