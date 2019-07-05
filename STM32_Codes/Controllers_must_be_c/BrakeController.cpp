/**
 * \file        BrakeController.cpp
 * \brief       A brief description one line.
 *
 * \author      Ahmet.Alperen.BULUT
 * \date        21 Haz 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "BrakeController.h"
#include "autonomousVehicle_conf.h"
#include "cmsis_os.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

void BrakeController::set_value (BRAKE_POSITION val)
{
    last_position = val;
}

BRAKE_POSITION BrakeController::get_value ( )
{
    return last_position;
}

float BrakeController::get_rotatary_position_sensor_value ( )
{
    return 0.0;
}

void BrakeController::brake_task ( )
{
    while (false)
    {
    };
}

void BrakeController::test ( )
{
    // lock the brake 1 seconds
    HAL_GPIO_WritePin(BRAKE_RELAY_PIN_1_CONF.GPIOx, BRAKE_RELAY_PIN_1_CONF.GPIO_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(BRAKE_RELAY_PIN_2_CONF.GPIOx, BRAKE_RELAY_PIN_2_CONF.GPIO_Pin,
            GPIO_PIN_RESET);
    HAL_Delay(1000);
    //  wait for 2 seconds
    HAL_GPIO_WritePin(BRAKE_RELAY_PIN_1_CONF.GPIOx, BRAKE_RELAY_PIN_1_CONF.GPIO_Pin,
            GPIO_PIN_RESET);
    HAL_GPIO_WritePin(BRAKE_RELAY_PIN_2_CONF.GPIOx, BRAKE_RELAY_PIN_2_CONF.GPIO_Pin,
            GPIO_PIN_RESET);
    HAL_Delay(2000);
    // release the brake 1 seconds
    HAL_GPIO_WritePin(BRAKE_RELAY_PIN_1_CONF.GPIOx, BRAKE_RELAY_PIN_1_CONF.GPIO_Pin,
            GPIO_PIN_RESET);
    HAL_GPIO_WritePin(BRAKE_RELAY_PIN_2_CONF.GPIOx, BRAKE_RELAY_PIN_2_CONF.GPIO_Pin, GPIO_PIN_SET);
    HAL_Delay(1000);

}
