/**
 * \file        ThrottleController.h
 * \brief       A brief description one line.
 *
 * \author      Ahmet.Alperen.BULUT
 * \date        Jun 21, 2019
 */

#ifndef CONTROLLERS_THROTTLECONTROLLER_H_
#define CONTROLLERS_THROTTLECONTROLLER_H_

/*------------------------------< Includes >----------------------------------*/

/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/

class ThrottleController
{
public:
    ThrottleController ( ) = default;

    void set_value (unsigned int val);
    unsigned int get_value ( );
    float get_rotatary_position_sensor_value ( );

private:
    void throttle_task ( );
    unsigned int last_position;
};

#endif /* CONTROLLERS_THROTTLECONTROLLER_H_ */
