/**
 * \file        hcsr04.c
 * \brief       A brief description one line.
 *
 * \author      ali.sacid.karadogan
 * \date        Jul 14, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "hcsr04.h"
#include "main.h"
#include "cmsis_os.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Variables >---------------------------------*/
uint32_t local_time, sensor_time;
uint16_t distance;
/*------------------------------< Prototypes >--------------------------------*/
void DWT_Init(void);
uint32_t DWT_Get(void);
uint8_t DWT_Compare(int32_t tp);
void DWT_Delay(uint32_t us) ;
/*------------------------------< Functions >---------------------------------*/

uint32_t hcsr04_read ( )
{
    /*local_time = 0;
    HAL_GPIO_WritePin(HCSR04_TRIG_GPIO_Port, HCSR04_TRIG_Pin, GPIO_PIN_RESET);     //Pull the trigger pin low
    DWT_Delay(2);     //Wait for 2us

    HAL_GPIO_WritePin(HCSR04_TRIG_GPIO_Port, HCSR04_TRIG_Pin, GPIO_PIN_SET);     //Pull the trigger pin high
    DWT_Delay(10);     //Wait for 10us
    HAL_GPIO_WritePin(HCSR04_TRIG_GPIO_Port, HCSR04_TRIG_Pin, GPIO_PIN_RESET);     //Pull the trigger pin low

    //Read the time for which the pin is high

    while (!(HAL_GPIO_ReadPin(HCSR04_ECHO_GPIO_Port, HCSR04_ECHO_Pin)))
        ;     //Wait for Echo pin to go high
    while (HAL_GPIO_ReadPin(HCSR04_ECHO_GPIO_Port, HCSR04_ECHO_Pin))
    {     //While the pin is high
        local_time++;     //Increase local time
        DWT_Delay(1);     //every 1us
    }
    return local_time * 2;*/
}

void hcsr04 ( )
{
    DWT_Init( );
    while (1)
    {
        sensor_time = hcsr04_read( );     //Get the high time of the Echo Pin
        distance = sensor_time * .0349/2;     //Measure distance with calculation of the formula
        if (distance >= 400)
        {
        	distance = 400;
        }

        osDelay(200);
    }
}


void DWT_Init(void)
{

      CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
      ITM->LAR = 0xc5acce55;
      DWT->CYCCNT = 0;
      DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

}

uint32_t DWT_Get(void)
{
  return DWT->CYCCNT;
}

__inline
uint8_t DWT_Compare(int32_t tp)
{
  return (((int32_t)DWT_Get() - tp) < 0);
}

void DWT_Delay(uint32_t us) // microseconds
{
  int32_t tp = DWT_Get() + us * (SystemCoreClock/1000000);
  while (DWT_Compare(tp));
}
