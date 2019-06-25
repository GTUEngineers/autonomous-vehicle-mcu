/**
 * \file        autonomousVehicle_conf.h
 * \brief       A brief description one line.
 *
 * \author      Ahmet.Alperen.BULUT
 * \date        23 Haz 2019
 */

#ifndef AUTONOMOUSVEHICLE_CONF_H_
#define AUTONOMOUSVEHICLE_CONF_H_

/*------------------------------< Includes >----------------------------------*/
#include "stm32f4xx_hal.h"
/*------------------------------< Defines >-----------------------------------*/

#define THROTTLE_MIN_VOLTAGE (0.4)
#define THROTTLE_MAX_VOLTAGE (1.8)

/*------------------------------< Typedefs >----------------------------------*/
struct s_PinSettings
{
    GPIO_TypeDef* GPIOx;
    uint16_t GPIO_Pin;
};

typedef struct s_PinSettings pinSettings;

/*------------------------------< Variables >----------------------------------*/

const pinSettings BRAKE_RELAY_PIN_1_CONF = {GPIOF, GPIO_PIN_4};
const pinSettings BRAKE_RELAY_PIN_2_CONF = {GPIOF, GPIO_PIN_4};

const pinSettings STEER_DIRECTION_PIN_CONF = {GPIOF, GPIO_PIN_6};
const pinSettings STEER_PULSE_PIN_CONF = {GPIOF, GPIO_PIN_7};

#endif /* AUTONOMOUSVEHICLE_CONF_H_ */
