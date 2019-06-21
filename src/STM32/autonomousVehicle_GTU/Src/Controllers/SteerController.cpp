/**
 * \file        SteerController.cpp
 * \brief       A brief description one line.
 *
 * \author      Ahmet.Alperen.BULUT
 * \date        Jun 21, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "SteerController.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

void SteerController::set_value (int val)
{
    last_position = val;
}

int SteerController::get_value ( )
{
    return last_position;
}

float SteerController::get_encoder_value ( )
{
    return 0.0;
}

void SteerController::steer_task ( )
{
    while (false)
    {
    };
}
