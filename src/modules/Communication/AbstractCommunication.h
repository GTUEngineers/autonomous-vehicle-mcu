/**
 *  \file   AbstractCommunication.h
 *  \brief  Abstract Communication
 *  \author Muaz.Kurt
 *  \date   23.02.2019
 * */


#ifndef AUTONOMOUS_VEHICLE_GTU_ABSTRACT_COMMUNICATION_H
#define AUTONOMOUS_VEHICLE_GTU_ABSTRACT_COMMUNICATION_H

#include "Communication.h"
#include <unistd.h>
#include <netdb.h>
#include <iostream>

namespace GTU {
    namespace AUTONOMOUS_VEHICLE {
        class AbstractCommunication : public Communication {
        public:
            ErrorStatus stop();

            ErrorStatus receive(std::string &message, int length);

            ErrorStatus send(const std::string &message, int length);

        protected:
            inline int setConnection(int input) {
                return (this->communication = input);
            }

            inline int getConnection() {
                return this->communication;
            }

        private:
            int communication;
        };
    } // AUTONOMOUS_VEHICLE
} // GTU

#endif // AUTONOMOUS_VEHICLE_GTU_ABSTRACT_COMMUNICATION_H
