/**
 *  \file   messageBuilder.h
 *  \brief  Message Builder
 *  \author Ongun.Alp.Baba
 *  \date   23.02.2019
 * */


#ifndef AUTONOMOUS_VEHICLE_GTU_ABSTRACT_MESSAGE_H
#define AUTONOMOUS_VEHICLE_GTU_ABSTRACT_MESSAGE_H

#include <cstdint>
#include <string>

namespace GTU {

    namespace AUTONOMOUS_VEHICLE {

        namespace MESSAGE {

            const u_int16_t PAYLOAD_MAX_SIZE = 500;

            enum Components {

            };

            enum Systems {

            };
            ///A messages structure according to protocol
            struct Protocol {
                uint16_t len;               // Length of payload
                uint8_t sys_id;              // ID of message sender system(car)
                uint8_t comp_id;             // ID of the message sender component(car part)
                uint16_t msg_id;             // first 16 bits of the ID of the message
                char payload[PAYLOAD_MAX_SIZE];           // A maximum of 500 payload bytes
            };


            std::string build_message(const Protocol *protocol);

            bool parse_message(const std::string &msg, Protocol *protocol);
        }
    }
}

#endif // AUTONOMOUS_VEHICLE_GTU_ABSTRACT_MESSAGE_H
