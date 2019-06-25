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
#include "stm32f4xx_hal.h"

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/

class SteerController
{
public:
    SteerController ( ) = default;

    void set_value (int val);
    int get_value ( );
    float get_encoder_value ( );
	void test();

private:
    void steer_task ( );
    //last position of the steering
    int last_position;
};

#endif /* CONTROLLERS_STEERCONTROLLER_H_ */
