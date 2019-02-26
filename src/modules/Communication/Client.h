/**
 *  \file   Client.h
 *  \brief  Client
 *  \author Muaz.Kurt
 *  \date   23.02.2019
 * */


#ifndef AUTONOMOUS_VEHICLE_GTU_ABSTRACT_CLIENT_H
#define AUTONOMOUS_VEHICLE_GTU_ABSTRACT_CLIENT_H

#include "AbstractCommunication.h"

namespace GTU {
    namespace AUTONOMOUS_VEHICLE {
        class Client : public AbstractCommunication {
        public:
            Client(const std::string &hostName = "localhost", int portNumber = 8080);

            ErrorStatus setup(const std::string &hostName = "localhost", int port = 8080);

            virtual ~Client() override;
        };

    } // AUTONOMOUS_VEHICLE
} // GTU

#endif // AUTONOMOUS_VEHICLE_GTU_ABSTRACT_CLIENT_H