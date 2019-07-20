/**
 * \file        ThrottleController.c
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Jul 5, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "ThrottleController.h"
#include "main.h"
#include "cmsis_os.h"
#include "BrakeController.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Variables >---------------------------------*/
uint32_t throttle_current_value = 0;
/*------------------------------< Prototypes >--------------------------------*/

/*------------------------------< Functions >---------------------------------*/

uint32_t throttle_get_value ( )
{
    return throttle_current_value;
}

void throttle_set_value (uint32_t val)
{
    if (val < THROTTLE_VOLTAGE_MIN_VAL || val > THROTTLE_VOLTAGE_MAX_VAL)
    {
        return;
    }
    throttle_current_value = val;
    HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, val);
}

void throttle_set_lock (ThrottleLockPosition val)
{
    if (val == THROTTLE_LOCK)
    {
        HAL_GPIO_WritePin(THROTTLE_LOCK_PIN_GPIO_Port, THROTTLE_LOCK_PIN_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(THROTTLE_LOCK_PIN_GPIO_Port, THROTTLE_LOCK_PIN_Pin, GPIO_PIN_RESET);
    }
}

void throttle_test ( )
{
    brake_set_value(BRAKE_RELEASE);
    osDelay(2000);
    brake_set_value(BRAKE_STOP);
    throttle_set_lock(THROTTLE_RELEASE);
    throttle_set_value(SPEED_0);
    osDelay(2000);
    throttle_set_value(SPEED_5);
    osDelay(3000);
    throttle_set_value(SPEED_10);
    osDelay(3000);
    throttle_set_value(SPEED_15);
    osDelay(3000);
    throttle_set_value(SPEED_20);
    osDelay(2000);
    throttle_set_value(SPEED_25);
    osDelay(2000);
    throttle_set_value(SPEED_10);
    osDelay(3000);
    throttle_set_value(SPEED_5);
    osDelay(3500);
    throttle_set_value(SPEED_0);
    osDelay(3000);
    brake_set_value(BRAKE_LOCK);
    osDelay(3000);
    brake_set_value(BRAKE_RELEASE);
    osDelay(3000);
    throttle_set_lock(THROTTLE_LOCK);
    return;
}
