/**
 * \file        BrakeController.cpp
 * \brief       A brief description one line.
 *
 * \author      Ahmet.Alperen.BULUT
 * \date        21 Haz 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "BrakeController.h"
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

