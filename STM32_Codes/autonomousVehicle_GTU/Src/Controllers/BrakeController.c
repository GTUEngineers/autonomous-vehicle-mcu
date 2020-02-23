/**
 * \file        BrakeController.c
 * \brief       Aracın fren mekanizmasında bir adet dc motor bulunmaktadır.
 * Bu motora +12v uygulanırsa bir yöne dönüyor yani kitliyor olarak düşünebilirsiniz.
 * Eğer -12v uygulanırsa freni bırakıyor.
 * Bu işlemi gerçekleştirebilmek için Motordan 12v geliyor ve bir röleye gidiyor.
 * Rölede bir switch mekanizması yaptık. Rölenin girişleri aynı olursa frendeki motor hiç bir şekilde hareket etmeyecektir.
 * Eğer rölenin girişleri farklı olursa (1 0 veya 0 1) Motor hareket etmeye başlayacaktır.
 *
 *  Detaylı bilgi için Ahmet Alperen BULUT https://www.linkedin.com/in/ahmetalperenbulut
 * \author      ahmet.alperen.bulut
 * \date        Jul 5, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "BrakeController.h"
#include "cmsis_os.h"
#include "main.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Variables >---------------------------------*/
static StaticSemaphore_t xSemaphoreBuffer;
static SemaphoreHandle_t xSemaphore;

BrakePosition brake_current_position = BRAKE_STOP;
BrakePosition brake_next_position = BRAKE_STOP;

osThreadId brakeTaskHandle;
uint32_t brakeTaskBuffer[512];
osStaticThreadDef_t brakeTaskControlBlock;
/*------------------------------< Prototypes >--------------------------------*/
void brake_task (void const * argument);
void brake_lock ( );
void brake_release ( );
void brake_stop ( );
/*------------------------------< Functions >---------------------------------*/

void brake_init ( )
{
    brake_stop( );     // set GPIO pin initial value
    xSemaphore = xSemaphoreCreateCountingStatic(1, 0, &xSemaphoreBuffer);//Mutex gibi davranmasını sağlamak için kullanıldı.
// Initial valuesi 0 olarak başlayacak ve brake threadi bu locki almak için bekleyecek.
    // UARTTAN yada control mekanizmasından yeni bir fren pozisyonu geldiğinde semaphore 1 artıralacak ve brakethreadi semaphoreu alıp
    // yeni değeri için gerekli işlemi yapacak.
    osThreadStaticDef(BrakeTask, brake_task, osPriorityNormal, 0, 512, brakeTaskBuffer,
            &brakeTaskControlBlock);
    brakeTaskHandle = osThreadCreate(osThread(BrakeTask), NULL);
}

void brake_task (void const * argument)
{

    while (1)
    {
        if (osSemaphoreWait(xSemaphore, 2000) >= 0)
        {
            if(brake_next_position == brake_current_position)
                continue;
            switch (brake_next_position)
            {
                case BRAKE_STOP:
                    brake_stop( );
                    break;
                case BRAKE_RELEASE:
                    brake_release( );
                    osDelay(1150);     //Frenin bırakılabilmesi için beklenmesi gereken süre.
                    brake_stop( );
                    break;
                case BRAKE_HALF:
//TODO implement it
                    break;
                case BRAKE_LOCK:
                    brake_lock( );
                    osDelay(1600);//Frenin çekilebilmesi için beklenmesi gereken süre.
                    brake_stop( );
                    break;
                default:
                    //TODO add logger
                    break;
            }
            brake_current_position = brake_next_position;
        }
        else
        {
            //TODO logger
        }
    }
}

BrakePosition brake_get_value ( )
{
    return brake_current_position;
}

void brake_set_value (BrakePosition val)
{
    if (val == brake_next_position || val == brake_current_position)
    {
        return;
    }
    brake_next_position = val;
    osSemaphoreRelease(xSemaphore);
}

/**
 * Rölenin 1 - 0 yapıp fren motoru freni sıkmaya başlayacak.
 * */
void brake_lock ( )
{
    //Brake motor lock to brake
    HAL_GPIO_WritePin(BRAKE_RELAY_1_GPIO_Port, BRAKE_RELAY_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(BRAKE_RELAY_2_GPIO_Port, BRAKE_RELAY_2_Pin, GPIO_PIN_RESET);
}

/**
 * Rölenin 0 - 1 yapıp fren motoru freni bırakmaya başlayacak.
 * */
void brake_release ( )
{
    //Brake motor release to brake
    HAL_GPIO_WritePin(BRAKE_RELAY_1_GPIO_Port, BRAKE_RELAY_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(BRAKE_RELAY_2_GPIO_Port, BRAKE_RELAY_2_Pin, GPIO_PIN_SET);
}

/*
 * Fren çekilmeye başlandığında veya bırakılmaya başlandığında durdurmak için kullanılır.
 * */
void brake_stop ( )
{
    //Brake motor stop current position
    HAL_GPIO_WritePin(BRAKE_RELAY_1_GPIO_Port, BRAKE_RELAY_1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(BRAKE_RELAY_2_GPIO_Port, BRAKE_RELAY_2_Pin, GPIO_PIN_RESET);
}

float brake_get_rotary_position_sensor_value ( )
{
    return 0.0;     //TODO read rotary sensor value
}

void brake_test ( )
{
    // lock the brake 1 seconds
    brake_set_value(BRAKE_LOCK);
    osDelay(2000);
    //  wait for 5 seconds
    brake_set_value(BRAKE_STOP);
    osDelay(3000);
    // release the brake 1 seconds
    brake_set_value(BRAKE_RELEASE);
    osDelay(2000);
    //  wait for 5 seconds
    brake_set_value(BRAKE_STOP);
    osDelay(3000);
}
