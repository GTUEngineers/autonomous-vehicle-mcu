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
    int dir_val = 0;
    if(last_position > val)
        dir_val = 1;
    //sets steer_direction_pin according to dir_val
    switch(dir_val){
        case 1:
            HAL_GPIO_WritePin(GPIOF, steer_direction_pin, GPIO_PIN_SET);
            break;
        case 0:
            HAL_GPIO_WritePin(GPIOF, steer_direction_pin, GPIO_PIN_RESET);
            break;
        default:
            break;
    }
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
