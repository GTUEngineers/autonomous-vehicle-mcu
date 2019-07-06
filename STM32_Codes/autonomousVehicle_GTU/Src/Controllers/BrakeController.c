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
BrakePosition brake_current_position = RELEASE;
/*------------------------------< Prototypes >--------------------------------*/

/*------------------------------< Functions >---------------------------------*/

BrakePosition brake_get_value ( )
{
    return brake_current_position;
}

void brake_set_value (BrakePosition val)
{
    brake_current_position = val;
    //TODO set GPIO @ahmet.alperen.bulut
}

float brake_get_rotary_position_sensor_value ( )
{
    return 0.0;     //TODO read rotary sensor value
}

void brake_test ( )
{

    // lock the brake 1.8 seconds
    HAL_GPIO_WritePin(BRAKE_RELAY_PIN_1_GPIO_Port, BRAKE_RELAY_PIN_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(BRAKE_RELAY_PIN_1_GPIO_Port, BRAKE_RELAY_PIN_2_Pin, GPIO_PIN_RESET);
    osDelay(1800);

    //  wait for 5 seconds
    HAL_GPIO_WritePin(BRAKE_RELAY_PIN_1_GPIO_Port, BRAKE_RELAY_PIN_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(BRAKE_RELAY_PIN_1_GPIO_Port, BRAKE_RELAY_PIN_2_Pin, GPIO_PIN_RESET);
    osDelay(5000);

    // release the brake 1.8 seconds
    HAL_GPIO_WritePin(BRAKE_RELAY_PIN_1_GPIO_Port, BRAKE_RELAY_PIN_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(BRAKE_RELAY_PIN_1_GPIO_Port, BRAKE_RELAY_PIN_2_Pin, GPIO_PIN_SET);
    osDelay(1800);

    //  wait for 5 seconds
    HAL_GPIO_WritePin(BRAKE_RELAY_PIN_1_GPIO_Port, BRAKE_RELAY_PIN_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(BRAKE_RELAY_PIN_1_GPIO_Port, BRAKE_RELAY_PIN_2_Pin, GPIO_PIN_RESET);
    osDelay(5000);
}
