/**
 * \file        MainController.c
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Oct 5, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "helpers.h"
#include "BrakeController.h"
#include "ThrottleController.h"
#include "SteerController.h"
#include "Communications/Communication_Mechanism.h"
#include "Communications/UART_Communication.h"
#include "Communications/UART_Message.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Variables >---------------------------------*/
osThreadId mainControllerTaskHandle;
uint32_t mainControllerTaskBuffer[ 512 ];
osStaticThreadDef_t mainControllerTaskControlBlock;
/*------------------------------< Prototypes >--------------------------------*/
void main_controller_task (void const * argument);
/*------------------------------< Functions >---------------------------------*/

void main_controller_init ( )
{
    osThreadStaticDef(mainController, main_controller_task, osPriorityAboveNormal, 0, 512, mainControllerTaskBuffer, &mainControllerTaskControlBlock);
    mainControllerTaskHandle = osThreadCreate(osThread(mainController), NULL);
}

void main_controller_task (void const * argument)
{
    /* USER CODE BEGIN ControlTask */
    /* Infinite loop */
    uart_req req;
    uint8_t ret_val = 0;
    for (;;)
    {
        uart_rep rep = { 0 };

        if (communication_get_msg(&req) == OK)
        {
            switch (req.req_packed.header)
            {
                case START_STOP_REQ:
                {
                    uint8_t val = 0;

                    parse_startstop_msg(&req, &val);

                    if (val == 1)
                    {
                        if (HAL_GPIO_ReadPin(EMERGENCY_STOP_GPIO_Port, EMERGENCY_STOP_Pin)
                                == GPIO_PIN_SET)
                        {
                            start_system( );
                            ret_val = 1;
                        }

                    }
                    else if (val == 0)
                    {
                        emergency_stop( );
                    }

                    break;
                }
                case STEERING_REQ:
                {
                    if (is_started == 1)
                    {
                        uint8_t dir;
                        int16_t val;
                        parse_steer_msg(&req, &dir, &val);
                        if (dir == 0)
                        {
                            val = val * 7;
                        }
                        else
                        {
                            val = val * 7 * -1;
                        }
                        steer_set_value(val);
                        ret_val = 1;
                    }
                    else
                    {
                        ret_val = 0;
                    }
                    break;
                }
                case THROTTLE_REQ://Throttle
                {
                    if (is_started == 1)
                    {
                        uint8_t val;
                        parse_throttle_msg(&req, &val);
                        switch (val)
                        {
                            case 0:
                            {
                                throttle_set_value(SPEED_0);
                                break;
                            }
                            case 5:
                            {
                                throttle_set_value(SPEED_5);
                                break;
                            }
                            case 8:
                            {
                                throttle_set_value(SPEED_8);
                                break;
                            }
                            case 10:
                            {
                                throttle_set_value(SPEED_10);
                                break;
                            }
                            case 13:
                            {
                                throttle_set_value(SPEED_13);
                                break;
                            }
                            case 15:
                            {
                                throttle_set_value(SPEED_15);
                                break;
                            }
                            case 20:
                            {
                                throttle_set_value(SPEED_20);
                                break;
                            }
                            default:
                            {

                                throttle_set_value(SPEED_0);
                                break;
                            }

                        }
                        ret_val = 1;
                    }
                    else
                    {
                        ret_val = 0;
                    }
                    break;
                }
                case BRAKE_REQ:
                {
                    if (is_started == 1)
                    {
                        uint8_t val;
                        parse_brake_msg(&req, &val);
                        if (val == 0)
                        {
                            brake_set_value(BRAKE_RELEASE);
                        }
                        else if (val == 1)
                        {
                            throttle_set_lock(THROTTLE_LOCK);
                            brake_set_value(BRAKE_LOCK);
                        }
                        ret_val = 1;
                    }
                    else
                    {
                        ret_val = 0;
                    }
                    break;
                }
                case STATE_REQ:
                {
                    ret_val = is_started;
                    break;
                }
                default:
                {
                    //LOGGER
                    break;
                }
            }

        }
        else
        {
        }
        create_general_rep_msg(&rep, ret_val);
        communication_send_msg(&rep);

    }
    /* USER CODE END ControlTask */
}
