/**
 * \file        ThrottleController.c
 * \brief       Aracın üzerinde hızlanma pedalını sürülebilmesi için bir adet rotary sensor kullanılmış.
 *              Bu sensör aslında ne kadar hızlanma pedalına basılırsa o kadar yüksek voltaj üretiyor.
 *              Voltaj değerlerini ölçtüğümüzde 0.4 volt ile 1.7 volt arası değerler üretmektedir.
 *              Bu sensörü taklit edebilmek için STM32 nin DAC modülünü kullandık.
 *              Aracın üzerinde yapılan ölçümlerinde autonomousVehicle_conf.h da değerler yazılmıştır.
 *              Fakat sürekli olarak aynı voltaj verildiğinde araç hızlanmaktadır.
 * Detaylı bilgi için Ahmet Alperen BULUT https://www.linkedin.com/in/ahmetalperenbulut
 * \author      ahmet.alperen.bulut
 * \date        Jul 5, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "ThrottleController.h"
#include "main.h"
#include "cmsis_os.h"
#include "BrakeController.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Variables >---------------------------------*/
static uint32_t throttle_current_value = 0;
/*------------------------------< Prototypes >--------------------------------*/

/*------------------------------< Functions >---------------------------------*/

uint32_t throttle_get_value ( )
{
    return throttle_current_value;
}

void throttle_set_value (uint32_t val)
{
    if (val < THROTTLE_VOLTAGE_MIN_VAL || val > THROTTLE_VOLTAGE_MAX_VAL || brake_get_value() == BRAKE_LOCK)
    {
        return;
    }
    throttle_set_lock(THROTTLE_RELEASE);
    throttle_current_value = val;
    HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, val);
}

/**
 * Aracın güvenliği için hızlanma pedalına ayrıca bir adet sensör yerleştirilmiş.
 * Bu sensörün amacı sofor gercekten gaza basıyor mu öğrenebilmek için bu sensör kullanılmış.
 *  Arac kendi kendine gitmesin diye kullanıldığını düşünüyorum.
 *  Sensörün çalışma mantığı hızlanma pedalına bastığında sofor devreyi kapatmış oluyor ve akım akmaya başlıyor.
 *  Bunu yapabilmek için sensoru devredışı bırakıp. Sensore giden kabloları bir röleye bağladık.
 *  Röle üzerinden bu sensörün işlevi gerçekleştiriliyor.
 * */
void throttle_set_lock (ThrottleLockPosition val)
{
    if (val == THROTTLE_LOCK)
    {
        HAL_GPIO_WritePin(THROTTLE_LOCK_GPIO_Port, THROTTLE_LOCK_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(THROTTLE_LOCK_GPIO_Port, THROTTLE_LOCK_Pin, GPIO_PIN_RESET);
    }
}

void throttle_test ( )
{
    brake_set_value(BRAKE_RELEASE);
    osDelay(2000);
    throttle_set_lock(THROTTLE_RELEASE);
    throttle_set_value(SPEED_0);
    osDelay(2000);
    throttle_set_value(SPEED_5);
    osDelay(3000);
    throttle_set_value(SPEED_8);
    osDelay(3000);
    throttle_set_value(SPEED_10);
    osDelay(3000);
    throttle_set_value(SPEED_13);
    osDelay(3000);
    throttle_set_value(SPEED_15);
    osDelay(3000);
    throttle_set_value(SPEED_20);
    osDelay(2000);
    throttle_set_value(SPEED_25);
    osDelay(2000);
    throttle_set_value(SPEED_10);
    osDelay(3000);
    throttle_set_value(SPEED_5);
    osDelay(3500);
    throttle_set_value(SPEED_0);
    osDelay(3000);
    brake_set_value(BRAKE_LOCK);
    osDelay(3000);
    brake_set_value(BRAKE_RELEASE);
    osDelay(3000);
    throttle_set_lock(THROTTLE_LOCK);
    return;
}
