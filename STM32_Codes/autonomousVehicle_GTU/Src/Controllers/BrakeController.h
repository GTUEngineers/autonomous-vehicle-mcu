/**
 * \file        BrakeController.h
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Jul 5, 2019
 */

#ifndef CONTROLLERS_BRAKECONTROLLER_H_
#define CONTROLLERS_BRAKECONTROLLER_H_

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*------------------------------< Includes >----------------------------------*/
#include "autonomousVehicle_conf.h"
/*------------------------------< Defines >-----------------------------------*/
//Connect BRAKE_RELAY_PIN_1_Pin to Relay in 1
//Connect BRAKE_RELAY_PIN_2_Pin to Relay in 2
/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Prototypes >--------------------------------*/

void brake_init ( );
BrakePosition brake_get_value ( );
void brake_set_value (BrakePosition val);
float brake_get_rotary_position_sensor_value ( );
void brake_test ( );

#if defined(__cplusplus)
}                /* Make sure we have C-declarations in C++ programs */
#endif

#endif /* CONTROLLERS_BRAKECONTROLLER_H_ */
