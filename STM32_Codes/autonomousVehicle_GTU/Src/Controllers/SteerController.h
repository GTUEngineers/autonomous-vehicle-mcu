/*
 * SteerController.h
 *
 *  Created on: 6 Tem 2019
 *      Author: tolga
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
pinSettings STEER_DIRECTION_PIN_CONF = {GPIOF, GPIO_PIN_6};
pinSettings STEER_PULSE_PIN_CONF = {GPIOF, GPIO_PIN_7};
/*------------------------------< Prototypes >--------------------------------*/


void set_value (int val);
int get_value ( );
float get_encoder_value ( );
void test();
void pulse();
void steer_task ( );


#if defined(__cplusplus)
}                /* Make sure we have C-declarations in C++ programs */
#endif


#endif /* CONTROLLERS_STEERCONTROLLER_H_ */
