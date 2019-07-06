/*
 * SteerController.c
 *
 *  Created on: 6 Tem 2019
 *      Author: tolga
 */

/*------------------------------< Includes >----------------------------------*/
#include "SteerController.h"
#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include "semphr.h"
#include "dwt_delay.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Variables >---------------------------------*/
//last position of the steering
int last_position;
SemaphoreHandle_t steer_mutex;
/*------------------------------< Prototypes >--------------------------------*/

/*------------------------------< Functions >---------------------------------*/


//steer_mutex = xSemaphoreCreateMutex();
//vSemaphoreDelete(steer_mutex);


//steer_mutex = xSemaphoreCreateMutex();

//vSemaphoreDelete(steer_mutex);


void set_value (int val)
{
	if(val > STEERING_MAX_RIGHT_VALUE || val < STEERING_MAX_LEFT_VALUE)
		return;

	xSemaphoreTake( steer_mutex, portMAX_DELAY );
    int dir_val = 0;
    if(last_position > val)
    if(get_encoder_value() > val)
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
    xSemaphoreGive( steer_mutex);
}

int get_value ( )
{
    return last_position;
}
float get_encoder_value ( )
{
    return 0.0;
}

void steer_task ( )
{
    while (0)
    	DWT_Init();
	//int count = get_encoder_value();
    while (1)
    {
    	xSemaphoreTake( steer_mutex, portMAX_DELAY );
		while(get_value() != get_encoder_value()){
			HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_RESET);
			HAL_Delay(1); //delayMicroseconds(150); // micros() for non-blocking code
			HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_SET);
			HAL_Delay(1); //delayMicroseconds(150); // micros() for non-blocking code
			if(HAL_GPIO_ReadPin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin) == 1)
				set_value(get_value() - 1);
			else
				set_value(get_value() + 1);
			pulse();
			xSemaphoreGive( steer_mutex);
			xSemaphoreTake( steer_mutex, portMAX_DELAY );
		}
		xSemaphoreGive( steer_mutex);
    };
}

void test ( )
{
	//RELOCATE this function call
	DWT_Init();
	// to most right by max pulse to right
	HAL_GPIO_WritePin(STEER_DIRECTION_PIN_CONF.GPIOx, STEER_DIRECTION_PIN_CONF.GPIO_Pin, GPIO_PIN_RESET);
	for(int i=0; i<STEERING_MAX_RIGHT_VALUE; ++i)
	{
		HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_RESET);
		HAL_Delay(1); //delayMicroseconds(150); // micros() for non-blocking code
		DWT_Delay(150);
		HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_SET);
		HAL_Delay(1); //delayMicroseconds(150); // micros() for non-blocking code
		DWT_Delay(150);
	}

	// wait 1 second
    HAL_Delay(1000);

    // to zero point by max pulse to left
	HAL_GPIO_WritePin(STEER_DIRECTION_PIN_CONF.GPIOx, STEER_DIRECTION_PIN_CONF.GPIO_Pin, GPIO_PIN_SET);
	for(int i=0; i<STEERING_MAX_RIGHT_VALUE; ++i)
	{
		HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_RESET);
		HAL_Delay(1); //delayMicroseconds(150); // micros() for non-blocking code
		DWT_Delay(150);
		HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_SET);
		HAL_Delay(1); //delayMicroseconds(150); // micros() for non-blocking code
		DWT_Delay(150);
	}

	// wait 1 second
    HAL_Delay(1000);

    // to most left by max pulse to left
	HAL_GPIO_WritePin(STEER_DIRECTION_PIN_CONF.GPIOx, STEER_DIRECTION_PIN_CONF.GPIO_Pin, GPIO_PIN_SET);
	for(int i=0; i<STEERING_MAX_RIGHT_VALUE; ++i)
	{
		HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_RESET);
		HAL_Delay(1); //delayMicroseconds(150); // micros() for non-blocking code
		DWT_Delay(150);
		HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_SET);
		HAL_Delay(1); //delayMicroseconds(150); // micros() for non-blocking code
		DWT_Delay(150);
	}

	// wait 1 second
	HAL_Delay(1000);
    // to zero point by max pulse to right
	HAL_GPIO_WritePin(STEER_DIRECTION_PIN_CONF.GPIOx, STEER_DIRECTION_PIN_CONF.GPIO_Pin, GPIO_PIN_RESET);
	for(int i=0; i<STEERING_MAX_RIGHT_VALUE; ++i)
	{
		HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_RESET);
		HAL_Delay(1); //delayMicroseconds(150); // micros() for non-blocking code
		DWT_Delay(150);
		HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_SET);
		HAL_Delay(1); //delayMicroseconds(150); // micros() for non-blocking code
		DWT_Delay(150);
	}

	// wait 1 second
	HAL_Delay(1000);
}

void pulse()
{
	HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_RESET);
	DWT_Delay(150);
	HAL_GPIO_WritePin(STEER_PULSE_PIN_CONF.GPIOx, STEER_PULSE_PIN_CONF.GPIO_Pin,GPIO_PIN_SET);
	DWT_Delay(150);
}
