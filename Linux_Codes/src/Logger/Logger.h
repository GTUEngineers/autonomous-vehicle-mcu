/**
 *  \file   Logger.h
 *  \brief  Log interface
 *  \author Ahmet.Alperen.BULUT
 *  \date   17.11.2018
 * */

#ifndef AUTONOMOUS_VEHICLE_GTU_LOGGER_H
#define AUTONOMOUS_VEHICLE_GTU_LOGGER_H

#include <iostream>

namespace GTU {
    namespace AUTONOMOUS_VEHICLE {

        /**
         * Log Severity Level
         * Level :          Description
         * Emergency :      System is unusable
         * Alert :          Should be corrected immediately
         * Critical :       Critical conditions
         * Error :          Error conditions
         * Warning :        May indicate that an error will occur if action is not taken.
         * Notice :         Events that are unusual, but not error conditions.
         * Informational :  Normal operational messages that require no action.
         * Debug :          Information useful to developers for debugging the application.
         * */
        enum class Level {
            EMERGENCY,
            ALERT,
            CRITICAL,
            ERROR,
            WARNING,
            NOTICE,
            INFO,
            DEBUG
        };

        /**
         * Logger Interface
         * */
        class Logger {

        public:

            /**
             * \brief Sends the log
             * \param std::string&  Module Name
             * \param Level&        Log Severity Level
             * \param std::string&  Message
             * \param ...           Formatting
             * \return bool         if send is successful return true, otherwise return false
             * */
            virtual bool send_log(const std::string &, const Level &, const std::string &, ...) = 0;

            /**
             * \brief Level text for log
            * */
            const std::string LEVEL_TEXT[8]{
                    "EMERGENCY",
                    "ALERT",
                    "CRITICAL",
                    "ERROR",
                    "WARNING",
                    "NOTICE",
                    "INFO",
                    "DEBUG"
            };

        };

    }//AUTONOMOUS_VEHICLE
}//GTU

#endif //AUTONOMOUS_VEHICLE_GTU_LOGGER_H
