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
#include "main.h"
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
    //TODO set dac

}
