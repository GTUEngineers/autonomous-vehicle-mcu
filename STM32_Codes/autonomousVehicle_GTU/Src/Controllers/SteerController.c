/**
 * \file        SteerController.c
 * \brief       Direksiyonun hareket ettirebilmesi için bir adet step motor ve bu motoru sürebilmek için bir adet step motor sürücüsü
 *              aracın üzerine koyulmuş bulunmaktadır.
 *              Bu motor sürücü pwm ile çalışmaktadır. PWM i üretebilmek için bir thread le high low seklinde ilerlemek cok ilkelce olacağı için
 *              STM32 nin pwm üreticisini kullandık.
 *              Bu PWM i bi yerde durdurmak gerekiyor. Gerekli adım atıldığında durması gerek bunun içinde ikinci bir timer kullanıldı.
 *              Bu timerla aslında pwmin kaç adım attığı tutuluyor bu timerin süresi dolduğunda pwm durduruluyor.
 *
 *  Detaylı bilgi için Ahmet Alperen BULUT https://www.linkedin.com/in/ahmetalperenbulut
 * \author      ahmet.alperen.bulut
 * \date        6 Tem 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "SteerController.h"
#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include "main.h"
#include <stdlib.h>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Variables >---------------------------------*/
int32_t position;
/*------------------------------< Prototypes >--------------------------------*/

/*------------------------------< Functions >---------------------------------*/

void steer_init ( )
{
    position = 0;

    //call configure
}

void steer_set_value (int val)
{
    if (val < STEERING_MIN_VALUE || val > STEERING_MAX_VALUE || position == val)
    {
        return;
    }
    HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
    HAL_TIM_Base_Stop(&htim3);     //check it
    HAL_GPIO_WritePin(STEER_PWM_GPIO_Port, STEER_PWM_Pin, GPIO_PIN_RESET);
    TIM3->CNT = 0;
    if (position > val)
    {
        HAL_GPIO_WritePin(STEER_DIR_GPIO_Port, STEER_DIR_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(STEER_DIR_GPIO_Port, STEER_DIR_Pin, GPIO_PIN_RESET);
    }
    int i = 0;
    while (i < 750)//for delay
    {
        ++i;
    }
    uint32_t abs_val = abs(position - val);
    TIM3->CNT = 0;
    TIM3->ARR = 2 * abs_val - 1;
    position = val;

    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
    HAL_TIM_Base_Start_IT(&htim3);
    //enable pwm and timer
}

int steer_get_value ( )
{
    return position;
}

void steer_test ( )
{

    steer_set_value(3500);
    osDelay(3000);

    steer_set_value(5000);
    osDelay(3000);

    steer_set_value(6800);
    osDelay(3000);

    steer_set_value(-3500);
    osDelay(5000);

    steer_set_value(-6800);
    osDelay(3000);

    steer_set_value(0);
    osDelay(5000);
}
