#include "helpers.h"

#include "Controllers/BrakeController.h"
#include "Controllers/ThrottleController.h"

int _write (int file, char *ptr, int len)
{
    int DataIdx;

    for (DataIdx = 0; DataIdx < len; DataIdx++)
    {
        /*__io_putchar(*ptr++);*/
        ITM_SendChar(*ptr++);
    }
    return len;
}

void set_red_led (GPIO_PinState PinState)
{
    HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, PinState);
}

void set_blue_led (GPIO_PinState PinState)
{
    HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, PinState);
}

void set_green_led (GPIO_PinState PinState)
{
    HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, PinState);
}

void set_orange_led (GPIO_PinState PinState)
{
    HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, PinState);
}

void emergency_stop ( )
{
    throttle_set_value(SPEED_0);
    throttle_set_lock(THROTTLE_LOCK);
    brake_set_value(BRAKE_LOCK);
    is_started = 0;
    set_red_led(GPIO_PIN_SET);
    set_green_led(GPIO_PIN_RESET);
}

void start_system ( )
{
    if (HAL_GPIO_ReadPin(EMERGENCY_STOP_GPIO_Port, EMERGENCY_STOP_Pin) == GPIO_PIN_RESET)
    {
        brake_set_value(BRAKE_RELEASE);
        is_started = 1;
        set_red_led(GPIO_PIN_RESET);
        set_green_led(GPIO_PIN_SET);
    }
}
