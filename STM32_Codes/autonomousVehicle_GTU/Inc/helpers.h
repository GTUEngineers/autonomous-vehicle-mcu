#ifndef HELPER_H_
#define HELPER_H_
#include "main.h"
#include "stm32f4xx_hal_gpio.h"
int _write (int file, char *ptr, int len);
void set_red_led (GPIO_PinState PinState);
void set_blue_led (GPIO_PinState PinState);
void set_green_led (GPIO_PinState PinState);
void set_orange_led (GPIO_PinState PinState);
void emergency_stop ( );
void start_system ( );
#endif
