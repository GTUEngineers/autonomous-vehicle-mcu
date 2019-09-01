/**
 * \file        UART_Message.c
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Aug 17, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "UART_Message.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Variables >---------------------------------*/

/*------------------------------< Prototypes >--------------------------------*/
void reverse (uart_message_req* req);
/*------------------------------< Functions >---------------------------------*/
void reverse (uart_message_req* req)
{
    uint8_t l = req->req.msg[1];
    req->req.msg[1] = req->req.msg[0];
    req->req.msg[0] = l;
}


void create_state_rep_msg(uart_message_rep* rep, enum STATE val)
{
#define STATE_MSG_MASK (0b00000011)
    rep->generic_msg.msg[1] = val & STATE_MSG_MASK;
#undef STATE_MSG_MASK
}

void create_steer_rep_msg(uart_message_rep* rep, const uint16_t val)
{
    memcpy(rep->generic_msg.msg, &val, sizeof(uint16_t));
    reverse(rep);
}

void create_general_rep_msg (uart_message_rep* rep, const uint8_t val)
{
#define GENERAL_MSG_MASK (0b00000001)
    rep->generic_msg.msg[1] = val & GENERAL_MSG_MASK;
#undef GENERAL_MSG_MASK
}

void parse_startstop_msg (const uart_message_req* req, uint8_t* val)
{
#define STARTSTOP_MASK (0b00000001)
    *val = (req->req.msg[1] & STARTSTOP_MASK);
#undef STARTSTOP_MASK
}

void parse_steer_msg (const uart_message_req* req, uint8_t* dir, uint16_t* val)
{
#define DIR_MASK (0b000000100)
#define ANGLE_MASK (0b00001111111111)
    uint8_t temp = req->req.msg[0];
    *dir = (temp & DIR_MASK) >> 2;
    uart_message_req reqm;
    reqm.req_uint16.msg = req->req_uint16.msg;
    reverse(&reqm);
    *val = reqm.req_uint16.msg & ANGLE_MASK;
#undef DIR_MASK
#undef ANGLE_MASK
}

void parse_throttle_msg (const uart_message_req* req, uint8_t* val)
{
#define THROTTLE_MASK (0b00011111)
    *val = (req->req.msg[1] & THROTTLE_MASK);
#undef THROTTLE_MASK
}

void parse_brake_msg (const uart_message_req* req, uint8_t* val)
{
#define BRAKE_MASK (0b00000001)
    *val = (req->req.msg[1] & BRAKE_MASK);
#undef BRAKE_MASK
}
