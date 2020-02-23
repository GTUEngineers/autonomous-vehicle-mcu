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
#include <stdint.h>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/
#define UART_REQ_SIZE (3)
#define UART_REP_SIZE (3)

enum HEADERS {
	START_STOP_REQ = 0,
	STEERING_REQ = 1,
	THROTTLE_REQ = 2,
	BRAKE_REQ = 3,
	GENERIC_REP = 4,
	STATE_REQ = 5,
	STATE_REP = 6
};

struct UART_req {
	uint8_t msg[UART_REQ_SIZE];
}__attribute__((packed, aligned(1)));
struct UART_req_packed {
	uint8_t header;
	uint16_t data;
}__attribute__((packed, aligned(1)));
union UART_req_un {
	struct UART_req req;
	struct UART_req_packed req_packed;
};

struct UART_rep {
	uint8_t msg[UART_REP_SIZE];
}__attribute__((packed, aligned(1)));
struct UART_rep_packed {
	uint8_t header;
	uint16_t data;
}__attribute__((packed, aligned(1)));
union UART_rep_un {
	struct UART_rep rep;
	struct UART_rep_packed rep_packed;
};
enum STATE{
    STOPPED = 0,
    RUNNING = 1,
    STATE_ERROR = 2
};

/*------------------------------< Typedefs >----------------------------------*/
typedef union UART_req_un uart_req;
typedef union UART_rep_un uart_rep;
/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Prototypes >--------------------------------*/
void create_state_rep_msg(uart_rep* rep, enum STATE val);
void create_steer_rep_msg(uart_rep* rep, const uint16_t val);
void create_general_rep_msg(uart_rep* rep, const uint8_t val);
void parse_steer_msg(const uart_req* req, uint8_t* dir, int16_t* val);
void parse_throttle_msg(const uart_req* req, uint8_t* val);
void parse_brake_msg(const uart_req* req, uint8_t* val);
void parse_startstop_msg(const uart_req* msg, uint8_t* val);
#if defined(__cplusplus)
}                /* Make sure we have C-declarations in C++ programs */
#endif

#endif /* COMMUNICATIONS_UART_MESSAGE_H_ */
