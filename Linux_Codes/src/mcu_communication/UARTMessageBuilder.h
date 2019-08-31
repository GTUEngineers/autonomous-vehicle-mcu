/**
 * \file        UARTMessageBuilder.h
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Aug 17, 2019
 */

#ifndef UART_MESSAGEBUILDER_H_
#define UART_MESSAGEBUILDER_H_

/*------------------------------< Includes >----------------------------------*/
#include "process.pb.h"
#include <string>
/*------------------------------< Defines >-----------------------------------*/
#define UART_REQ_SIZE (2)
#define UART_REP_SIZE (9)

struct UART_req {
    uint8_t msg[2];
} __attribute__((packed, aligned(1)));
struct UART_req_uint16 {
    uint16_t msg;
} __attribute__((packed, aligned(1)));

union UART_req_un {
    struct UART_req req;
    struct UART_req_uint16 req_uint16;
};
struct UART_rep {
    uint8_t msg[9];
} __attribute__((packed, aligned(1)));
struct UART_rep_uint16 {
    uint16_t msg;
} __attribute__((packed, aligned(1)));
union UART_rep_un {
    struct UART_rep rep;
    struct UART_rep_uint16 rep_uint16;
};
struct GPS {
    float latitude;
    float longitude;
} __attribute__((packed, aligned(1)));
/*------------------------------< Typedefs >----------------------------------*/
typedef union UART_req_un uart_req;
typedef union UART_rep_un uart_rep;
typedef struct GPS gps;

/*------------------------------< Class  >------------------------------------*/
namespace uart_msg {
void init_uartmessagebuilder_logger();
uart_req create_steer_msg(const uart::steering_enum dir, const uint16_t& val);
uart_req create_throttle_msg(const uint8_t& val);
uart_req create_brake_msg(const uart::brake_enum val);
uart_req create_startstop_msg(const uart::startstop_enum val);
uart_req create_state_msg();
uart_req create_hcsr4_msg();
uart_req create_gps_msg();
bool parse_general_rep_msg(const uart_rep& msg);
uint16_t parse_steering_msg(const uart_rep& msg);
uart::stateWorking_enum parse_state_msg(const uart_rep& msg);
std::string parse_hcsr4_msg(const uart_rep& msg);
gps parse_gps_msg(const uart_rep& msg);
}
#endif /* UART_MESSAGEBUILDER_H_ */