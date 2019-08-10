/**
 *  \file   ConsoleLog.h
 *  \brief  Console Logger
 *  \author Ahmet.Alperen.BULUT
 *  \date   23.11.2018
 * */

#ifndef AUTONOMOUS_VEHICLE_GTU_CONSOLELOG_H
#define AUTONOMOUS_VEHICLE_GTU_CONSOLELOG_H

#include "Logger.h"

namespace GTU {
    namespace AUTONOMOUS_VEHICLE {

        /**
         * \brief It's derived from Logger class (pure abstract class)
         * */
        class ConsoleLog : public Logger {

        public:

            ConsoleLog() = default;

            ~ConsoleLog() = default;

            /**
             * \brief Sends the log
             * \param std::string&  Module Name
             * \param Level&        Log Severity Level
             * \param std::string&  Message
             * \param ...           Formatting
             * \return bool         if send is successful return true, otherwise return false
             * */
            bool send_log(const std::string &, const Level &, const std::string &, ...) override;

            /**
             * \brief Test function of console log
             * */
            static void console_log_test();

            /**
             * \brief Message Length
             * */
            const unsigned int MESSAGE_LENGTH{1024};

        private:
            /**
             * \brief Gets current time
             * \param char*             Current time is written to the buffer
             * \param unsigned int      Buffer length
             * */
            void get_time(char *buffer, const unsigned int len);

            /**
             * \brief Time Module_Name Level: Message
             * */
            const std::string MSG_FORMAT{"%s %s %s: "};

        };

    }//AUTONOMOUS_VEHICLE
}//GTU

#endif //AUTONOMOUS_VEHICLE_GTU_CONSOLELOG_H
