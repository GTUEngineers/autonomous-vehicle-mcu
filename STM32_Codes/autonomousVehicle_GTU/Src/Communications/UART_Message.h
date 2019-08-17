/**
 * \file        UART_Message.h
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Aug 17, 2019
 */

#ifndef COMMUNICATIONS_UART_MESSAGE_H_
#define COMMUNICATIONS_UART_MESSAGE_H_

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*------------------------------< Includes >----------------------------------*/

/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/
struct UART_generic_message
{
    uint8_t msg[9];
}__attribute__((packed, aligned(1)));

struct UART_gps_message
{
    uint8_t header;
    float latitude;
    float longitude;
}__attribute__((packed, aligned(1)));

union u_uart_message
{
    struct UART_generic_message generic_msg;
    struct UART_gps_message gps_msg;
};
typedef union u_uart_message uart_message;
/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Prototypes >--------------------------------*/

#if defined(__cplusplus)
}                /* Make sure we have C-declarations in C++ programs */
#endif

#endif /* COMMUNICATIONS_UART_MESSAGE_H_ */
