/**
 *  \file   Syslog.h
 *  \brief  Syslog wrapper
 *  \author Ahmet.Alperen.BULUT
 *  \date   17.11.2018
 * */


#ifndef AUTONOMOUS_VEHICLE_GTU_SYSLOG_H
#define AUTONOMOUS_VEHICLE_GTU_SYSLOG_H

#include <string>
#include <iostream>
#include "Logger.h"

namespace GTU {
    namespace AUTONOMOUS_VEHICLE {

        /**
         * \brief Syslog is a singleton class.
         *        It's derived from Logger class (pure abstract class)
         * */
        class Syslog : public Logger {

        public:

            /**
             * \brief Destructor of syslog
             * */
            virtual ~Syslog();

            /**
             * \brief Returns Syslog Reference
             * */
            static Syslog &get_instance();

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
             * \brief Test function of syslog
             * */
            static void syslog_test();

            /**
             * \brief Syslog identifier
             * */
            const std::string IDENTIFIER{"AUTONOMOUS-VEHICLE"};

            /**
             * \brief Message Length
             * */
            const unsigned int MESSAGE_LENGTH{1024};

        private:

            Syslog();

            Syslog(const Syslog &) = delete;

            Syslog(Syslog &&) = delete;

            Syslog &operator=(const Syslog &) = delete;

            /**
             * \brief Module_Name.Level Message
             * */
            const std::string MSG_FORMAT{"%s.%s: "};

        };

    }//AUTONOMOUS_VEHICLE
}//GTU

#endif //AUTONOMOUS_VEHICLE_GTU_SYSLOG_H
