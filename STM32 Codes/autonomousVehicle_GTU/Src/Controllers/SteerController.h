/**
 * \file        SteerController.h
 * \brief       A brief description one line.
 *
 * \author      Ahmet.Alperen.BULUT
 * \date        Jun 21, 2019
 */

#ifndef CONTROLLERS_STEERCONTROLLER_H_
#define CONTROLLERS_STEERCONTROLLER_H_

/*------------------------------< Includes >----------------------------------*/

/*------------------------------< Defines >-----------------------------------*/
#define "stm32fxxx_hal_gpio.h"

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/

class SteerController
{
public:
    SteerController ( ) = default;

    void set_value (int val);
    int get_value ( );
    float get_encoder_value ( );

private:
    void steer_task ( );
    //last position of the steering
    int last_position;
    uint32_t steer_direction_pin;
    uint32_t steer_pulse_pin;
};

#endif /* CONTROLLERS_STEERCONTROLLER_H_ */
