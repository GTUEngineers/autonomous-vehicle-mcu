/**
 *  \file   messageBuilder.cpp
 *  \brief  Message Builder
 *  \author Ongun.Alp.Baba
 *  \date   23.02.2019
 * */

#include <iostream>
#include <sstream>
#include <cstdio>
#include "messagebuilder.h"

namespace GTU {

    namespace AUTONOMOUS_VEHICLE {

        namespace MESSAGE {

            const std::string msg_format = "%d,%c,%c,%d,%500c";

            ///Builds message by given parameters
            std::string build_message(const Protocol *protocol) {
                if (protocol == nullptr) {
                    return "";
                }
                std::stringstream buffer;

                buffer << (u_int16_t) protocol->len << "," << (char) protocol->sys_id << ","
                       << (char) protocol->comp_id << "," << (int16_t) protocol->msg_id << "," << protocol->payload;

                return buffer.str();
            }

            bool parse_message(const std::string &msg, Protocol *protocol) {
                sscanf(msg.c_str(), msg_format.c_str(), &protocol->len, &protocol->sys_id, &protocol->comp_id,
                       &protocol->msg_id, protocol->payload);
                return true;
            }
        }
    }
}
