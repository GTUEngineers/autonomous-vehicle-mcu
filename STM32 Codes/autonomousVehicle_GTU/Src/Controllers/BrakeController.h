/**
 * \file        BrakeController.h
 * \brief       Brake Controller
 *
 * \author      Ahmet.Alperen.BULUT
 * \date        21 Haz 2019
 */

#ifndef CONTROLLERS_BRAKECONTROLLER_H_
#define CONTROLLERS_BRAKECONTROLLER_H_

/*------------------------------< Includes >----------------------------------*/

/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/

enum class BRAKE_POSITION
{
    RELEASE = 0,
    HALF = 1,
    LOCK = 2
};

class BrakeController
{

public:
    BrakeController(const BrakeController&) = delete; //copy constructor
    BrakeController& operator=(const BrakeController &) = delete;//assignment operator
    BrakeController(BrakeController &&) = delete;//move operator
    BrakeController & operator=(BrakeController &&) = delete;//move assignment

    static BrakeController& get_instance ( );
    void set_value (BRAKE_POSITION val);
    BRAKE_POSITION get_value ( );
    float get_rotatary_position_sensor_value ( );
    static void test ( );
private:
    BrakeController ( ) = default;
    void brake_task ( );

    BRAKE_POSITION last_position;
};

#endif /* CONTROLLERS_BRAKECONTROLLER_H_ */
