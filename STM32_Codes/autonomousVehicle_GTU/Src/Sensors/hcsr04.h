/**
 * \file        hcsr04.h
 * \brief       A brief description one line.
 *
 * \author      ali.sacid.karadogan
 * \date        Jul 14, 2019
 */

#ifndef SENSORS_HCSR04_H_
#define SENSORS_HCSR04_H_

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*------------------------------< Includes >----------------------------------*/
#include <stdint.h>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Prototypes >--------------------------------*/
uint32_t hcsr04_read ( );
void hcsr04 ( );

#if defined(__cplusplus)
}                /* Make sure we have C-declarations in C++ programs */
#endif

#endif /* SENSORS_HCSR04_H_ */
