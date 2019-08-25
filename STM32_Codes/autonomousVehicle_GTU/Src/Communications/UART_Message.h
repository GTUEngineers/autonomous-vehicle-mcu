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

struct UART_message_req
{
    uint8_t msg[2];
}__attribute__((packed, aligned(1)));

struct UART_message_req_uint16
{
    uint16_t msg;
}__attribute__((packed, aligned(1)));

union u_UART_message_req
{
    struct UART_message_req req;
    struct UART_message_req_uint16 req_uint16;
};

struct UART_generic_message_rep
{
    uint8_t msg[9];
}__attribute__((packed, aligned(1)));

struct UART_gps_message_rep
{
    uint8_t header;
    float latitude;
    float longitude;
}__attribute__((packed, aligned(1)));

union u_uart_message_rep
{
    struct UART_generic_message_rep generic_msg;
    struct UART_gps_message_rep gps_msg;
};

typedef union u_uart_message_rep uart_message_rep;
typedef union u_UART_message_req uart_message_req;
/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Prototypes >--------------------------------*/
void parse_steer_msg(const uart_message_req* req, uint8_t* dir, uint16_t* val);
void parse_throttle_msg(const uart_message_req* req, uint8_t* val);
void parse_brake_msg(const uart_message_req* req, uint8_t* val);
void parse_startstop_rep_msg(const uart_message_req* msg, uint8_t* val);
#if defined(__cplusplus)
}                /* Make sure we have C-declarations in C++ programs */
#endif

#endif /* COMMUNICATIONS_UART_MESSAGE_H_ */
