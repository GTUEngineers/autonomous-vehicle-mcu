/**
 * \file        SteerController.h
 * \brief       Detaylı bilgiyi SteerController.c de bulunmaktadır.
 *
 * \author      ahmet.alperen.bulut
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

/*------------------------------< Prototypes >--------------------------------*/

void steer_init ( );
void steer_set_value (int val);
int steer_get_value ( );
void steer_test ( );

#if defined(__cplusplus)
}                /* Make sure we have C-declarations in C++ programs */
#endif

#endif /* CONTROLLERS_STEERCONTROLLER_H_ */
