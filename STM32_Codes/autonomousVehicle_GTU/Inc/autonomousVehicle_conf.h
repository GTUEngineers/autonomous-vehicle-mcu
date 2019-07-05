/**
 * \file        autonomousVehicle_conf.h
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Jul 5, 2019
 */

#ifndef AUTONOMOUSVEHICLE_CONF_H_
#define AUTONOMOUSVEHICLE_CONF_H_

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*------------------------------< Includes >----------------------------------*/

/*------------------------------< Defines >-----------------------------------*/
//Throttle Voltage Values
#define SPEED_0                     (0.4)
#define SPEED_5                     (0.8)
#define SPEED_10                    (1.0)
#define SPEED_15                    (1.2)
#define SPEED_20                    (1.4)
#define SPEED_25                    (1.8)
#define THROTTLE_VOLTAGE_MIN_VAL    SPEED_0
#define THROTTLE_VOLTAGE_MAX_VAL    SPEED_25
//TODO fix values @ahmet.alperen.bulut

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Prototypes >--------------------------------*/

#if defined(__cplusplus)
}                /* Make sure we have C-declarations in C++ programs */
#endif

#endif /* AUTONOMOUSVEHICLE_CONF_H_ */
