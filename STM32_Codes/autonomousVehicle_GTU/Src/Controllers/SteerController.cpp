/**
 * \file        SteerController.cpp
 * \brief       A brief description one line.
 *
 * \author      Ahmet.Alperen.BULUT
 * \date        Jun 21, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "SteerController.h"
#include "autonomousVehicle_conf.h"
#include "cmsis_os.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

void SteerController::set_value (int val)
{
    int dir_val = 0;
    if(last_position > val)
        dir_val = 1;
    //sets STEER_DIRECTION_PIN_CONF according to dir_val
    switch(dir_val){
        case 1:
            HAL_GPIO_WritePin(GPIOF, STEER_DIRECTION_PIN_CONF.GPIO_Pin, GPIO_PIN_SET);
            break;
        case 0:
            HAL_GPIO_WritePin(GPIOF, STEER_DIRECTION_PIN_CONF.GPIO_Pin, GPIO_PIN_RESET);
            break;
        default:
            break;
    }
    last_position = val;
}

int SteerController::get_value ( )
{
    return last_position;
}

float SteerController::get_encoder_value ( )
{
    return 0.0;
}

void SteerController::steer_task ( )
{
    while (false)
    {
		while(get_value() != get_encoder_value()){
			HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_RESET);
			HAL_Delay(1); //delayMicroseconds(150); // micros() for non-blocking code
			HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_SET);
			HAL_Delay(1); //delayMicroseconds(150); // micros() for non-blocking code
			if(HAL_GPIO_ReadPin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin) == 1)
				set_value(get_value() - 1);
			else
				set_value(get_value() + 1);
		}
    };
}

void SteerController::test ( )
{
	// to most right by max pulse to right
	HAL_GPIO_WritePin(STEER_DIRECTION_PIN_CONF.GPIOx, STEER_DIRECTION_PIN_CONF.GPIO_Pin, GPIO_PIN_RESET);
	for(int i=0; i<STEERING_MAX_VALUE; ++i)
	{
		HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_RESET);
		HAL_Delay(1); //delayMicroseconds(150); // micros() for non-blocking code
		HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_SET);
		HAL_Delay(1); //delayMicroseconds(150); // micros() for non-blocking code
	}
			
	// wait 1 second
    HAL_Delay(1000);
	
    // to zero point by max pulse to left
	HAL_GPIO_WritePin(STEER_DIRECTION_PIN_CONF.GPIOx, STEER_DIRECTION_PIN_CONF.GPIO_Pin, GPIO_PIN_SET);
	for(int i=0; i<STEERING_MAX_VALUE; ++i)
	{
		HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_RESET);
		HAL_Delay(1); //delayMicroseconds(150); // micros() for non-blocking code
		HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_SET);
		HAL_Delay(1); //delayMicroseconds(150); // micros() for non-blocking code
	}
			
	// wait 1 second
    HAL_Delay(1000);
	
    // to most left by max pulse to left
	HAL_GPIO_WritePin(STEER_DIRECTION_PIN_CONF.GPIOx, STEER_DIRECTION_PIN_CONF.GPIO_Pin, GPIO_PIN_SET);
	for(int i=0; i<STEERING_MAX_VALUE; ++i)
	{
		HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_RESET);
		HAL_Delay(1); //delayMicroseconds(150); // micros() for non-blocking code
		HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_SET);
		HAL_Delay(1); //delayMicroseconds(150); // micros() for non-blocking code
	}

	// wait 1 second
	HAL_Delay(1000);

    // to zero point by max pulse to right
	HAL_GPIO_WritePin(STEER_DIRECTION_PIN_CONF.GPIOx, STEER_DIRECTION_PIN_CONF.GPIO_Pin, GPIO_PIN_RESET);
	for(int i=0; i<STEERING_MAX_VALUE; ++i)
	{
		HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_RESET);
		HAL_Delay(1); //delayMicroseconds(150); // micros() for non-blocking code
		HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_SET);
		HAL_Delay(1); //delayMicroseconds(150); // micros() for non-blocking code
	}
	
	// wait 1 second
	HAL_Delay(1000);
}
