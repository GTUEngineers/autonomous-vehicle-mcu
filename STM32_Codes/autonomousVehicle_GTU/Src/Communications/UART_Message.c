/**
 * \file        UART_Message.c
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Aug 17, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "UART_Message.h"
#include "string.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Variables >---------------------------------*/

/*------------------------------< Prototypes >--------------------------------*/

/*------------------------------< Functions >---------------------------------*/

void create_state_rep_msg (uart_rep* rep, enum STATE val)
{
#define STATE_MSG_MASK (0x0003)
	rep->rep_packed.header = STATE_REP;
	rep->rep_packed.data = val & STATE_MSG_MASK;
#undef STATE_MSG_MASK
}

void create_general_rep_msg (uart_rep* rep, const uint8_t val)
{
#define GENERAL_MSG_MASK (0x0001)
	rep->rep_packed.header = GENERIC_REP;
	rep->rep_packed.data = val & GENERAL_MSG_MASK;
#undef GENERAL_MSG_MASK
}

void parse_startstop_msg (const uart_req* req, uint8_t* val)
{
    *val = req->req_packed.data;
}

void parse_steer_msg (const uart_req* req, uint8_t* dir, int16_t* val)
{
	*val = req->req_packed.data & 0x0FFF;
	*dir = (uint8_t)(req->req_packed.data >> 12);
}

void parse_throttle_msg (const uart_req* req, uint8_t* val)
{
    *val = req->req_packed.data;
}

void parse_brake_msg (const uart_req* req, uint8_t* val)
{
    *val = req->req_packed.data;
}
