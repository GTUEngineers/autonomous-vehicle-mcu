/**
 * \file        SteerController.h
 * \brief       A brief description one line.
 *
 * \author      tolga
 * \date        6 Tem 2019
 */

#ifndef CONTROLLERS_STEERCONTROLLER_H_
#define CONTROLLERS_STEERCONTROLLER_H_

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*------------------------------< Includes >----------------------------------*/
#include "autonomousVehicle_conf.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/
pinSettings STEER_DIRECTION_PIN_CONF = { GPIOF, GPIO_PIN_6 };
pinSettings STEER_PULSE_PIN_CONF = { GPIOF, GPIO_PIN_7 };
/*------------------------------< Prototypes >--------------------------------*/

//initialization function of steering
void steer_construct ( );
//deletes mutex MIGHT BE RENAMED
void steer_deconstruct ( );
void set_value (int val);
int get_value ( );
float get_encoder_value ( );
void test ( );

#if defined(__cplusplus)
}                /* Make sure we have C-declarations in C++ programs */
#endif

#endif /* CONTROLLERS_STEERCONTROLLER_H_ */
