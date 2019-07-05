/**
 * \file        ThrottleController.c
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Jul 5, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "ThrottleController.h"
#include "autonomousVehicle_conf.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Variables >---------------------------------*/
float throttle_current_value = 0.0;
/*------------------------------< Prototypes >--------------------------------*/

/*------------------------------< Functions >---------------------------------*/

float throttle_get_value ( )
{
    return throttle_current_value;
}

void throttle_set_value (float val)
{
    if (val < THROTTLE_VOLTAGE_MIN_VAL || val > THROTTLE_VOLTAGE_MAX_VAL)
    {
        return;
    }
    throttle_current_value = val;
    //TODO set dac

}
