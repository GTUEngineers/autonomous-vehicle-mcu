/**
 * \file        UART_Message.c
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Aug 17, 2019
 */

/*------------------------------< Includes >----------------------------------*/

/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Variables >---------------------------------*/

/*------------------------------< Prototypes >--------------------------------*/

/*------------------------------< Functions >---------------------------------*/

void parse_startstop_rep_msg(const uart_rep* msg, uint8_t* val)
{
    val = (bool)msg.rep.msg[1];
}

void parse_steer_msg(const uart_req* req, uint8_t* dir, uint16_t* val)
{
#define DIR_MASK (0b000000100)
#define ANGLE_MASK (0b00000011111111)
    uint16_t temp = req.req.msg[0];
    dir = (temp & DIR_MASK) >> 2;
    uart_req reqm = req;
    reverse(reqm);
    val = reqm.req_uint16.msg & ANGLE_MASK;
#undef DIR_MASK
#undef ANGLE_MASK
}

void parse_throttle_msg(const uart_req* req, uint8_t* val)
{
    val = req.req.msg[1];
}

void parse_brake_msg(const uart_req* req, uint8_t* val)
{
#define BRAKE_MASK (0b00000001)
    val = (req.req.msg[1] & BRAKE_MASK);
#undef BRAKE_MASK
}
