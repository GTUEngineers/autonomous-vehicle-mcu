/**
 *  \file   ConsoleLog.cpp
 *  \brief  Console Logger
 *  \author Ahmet.Alperen.BULUT
 *  \date   23.11.2018
 * */

#include <iostream>
#include <cstring>
#include <cstdarg>
#include <chrono>
#include "ConsoleLog.h"

namespace GTU {
    namespace AUTONOMOUS_VEHICLE {

        bool ConsoleLog::send_log(const std::string &module_name, const Level &level, const std::string &msg, ...) {
            if (msg.empty() || module_name.empty()) {
                return false;
            }
            const unsigned int TIME_MSG_LEN = 100;
            char user_msg[MESSAGE_LENGTH], time_msg[TIME_MSG_LEN];

            va_list arg;

            get_time(time_msg, TIME_MSG_LEN);

            sprintf(user_msg, MSG_FORMAT.c_str(), time_msg, module_name.c_str(),
                    LEVEL_TEXT[static_cast<int>(level)].c_str());

            if (msg.size() > MESSAGE_LENGTH - strlen(user_msg)) {
                return false;
            }

            va_start(arg, msg);
            vsprintf(&user_msg[strlen(user_msg)], msg.c_str(), arg);
            va_end(arg);

            std::cerr << user_msg << std::endl;

            return true;
        }

        void ConsoleLog::get_time(char *buffer, const unsigned int len) {
            std::time_t time = std::time(nullptr);
            std::strftime(buffer, len, "%d.%m.%Y %H:%M:%S", std::localtime(&time));
        }

        void ConsoleLog::console_log_test() {
            ConsoleLog logger;
            logger.send_log("Module 1", Level::CRITICAL, "Critical message %s", "String formatting");
            logger.send_log("Module 2", Level::ERROR, "Error message %d", 4);
            logger.send_log("Module 3", Level::INFO, "Info message %f", 0.21);
        }

    }//AUTONOMOUS_VEHICLE
}//GTU