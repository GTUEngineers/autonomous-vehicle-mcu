/**
 *  \file   Syslog.cpp
 *  \brief  Syslog wrapper class.
 *          Sends logs to syslog
 *  \author Ahmet.Alperen.BULUT
 *  \date   17.11.2018
 * */

#include <syslog.h>
#include <cstring>
#include <cstdarg>
#include "Syslog.h"

namespace GTU {
    namespace AUTONOMOUS_VEHICLE {

        Syslog::Syslog() {
            openlog(IDENTIFIER.c_str(), LOG_CONS | LOG_NDELAY, LOG_LOCAL0);
        }

        Syslog::~Syslog() {
            closelog();
        }

        bool Syslog::send_log(const std::string &module_name, const Level &level, const std::string &msg, ...) {
            if (msg.empty() || module_name.empty()) {
                return false;
            }

            char user_msg[MESSAGE_LENGTH];
            va_list arg;

            sprintf(user_msg, MSG_FORMAT.c_str(), module_name.c_str(), LEVEL_TEXT[static_cast<int>(level)].c_str());
            if (msg.size() > MESSAGE_LENGTH - strlen(user_msg)) {
                return false;
            }
            va_start(arg, msg);
            vsprintf(&user_msg[strlen(user_msg)], msg.c_str(), arg);
            va_end(arg);

            syslog(static_cast<int>(level), user_msg);

            return true;
        }

        Syslog &Syslog::get_instance() {
            static Syslog instance;
            return instance;
        }

        void Syslog::syslog_test() {
            Syslog &logger = Syslog::get_instance();
            logger.send_log("Module 1", Level::CRITICAL, "Critical message %s", "String formatting");
            logger.send_log("Module 2", Level::ERROR, "Error message %d", 4);
            logger.send_log("Module 3", Level::INFO, "Info message %f", 0.21);
        }

    }//AUTONOMOUS_VEHICLE
}//GTU