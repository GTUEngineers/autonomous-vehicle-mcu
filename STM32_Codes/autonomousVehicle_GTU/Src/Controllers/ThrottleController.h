/**
 * \file        ThrottleController.h
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Jul 5, 2019
 */

#ifndef CONTROLLERS_THROTTLECONTROLLER_H_
#define CONTROLLERS_THROTTLECONTROLLER_H_

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*------------------------------< Includes >----------------------------------*/
#include <stdint.h>
#include "autonomousVehicle_conf.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Prototypes >--------------------------------*/

uint32_t throttle_get_value ( );
void throttle_set_value (uint32_t val);

void throttle_set_lock (ThrottleLockPosition val);
void throttle_test ( );

#if defined(__cplusplus)
}                /* Make sure we have C-declarations in C++ programs */
#endif

#endif /* CONTROLLERS_THROTTLECONTROLLER_H_ */
