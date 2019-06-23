/**
 * \file        ThrottleController.cpp
 * \brief       A brief description one line.
 *
 * \author      Ahmet.Alperen.BULUT
 * \date        Jun 21, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "ThrottleController.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

void ThrottleController::set_value (unsigned int val)
{
    last_position = val;
}

unsigned int ThrottleController::get_value ( )
{
    return last_position;
}

float ThrottleController::get_rotatary_position_sensor_value ( )
{
    return 0.0;
}

void ThrottleController::throttle_task ( )
{
    while (false)
    {
    };
}

