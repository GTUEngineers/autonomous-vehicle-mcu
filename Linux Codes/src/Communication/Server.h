/**
 *  \file   Server.h
 *  \brief  Server
 *  \author Muaz.Kurt
 *  \date   23.02.2019
 * */


#ifndef AUTONOMOUS_VEHICLE_GTU_ABSTRACT_SERVER_H
#define AUTONOMOUS_VEHICLE_GTU_ABSTRACT_SERVER_H

#include "AbstractCommunication.h"

namespace GTU {
    namespace AUTONOMOUS_VEHICLE {
        class Server : public AbstractCommunication {
        public:
            /*******************************************************
             * Creates a socket and binds it to given port number. *
             * As default, it will be 8080.                        *
             *******************************************************/
            Server(int portNumber = 8080);

            virtual ~Server() override;

            ErrorStatus setup(int portNumber);

        private:
            int socketDescriptor;
        };

    } // AUTONOMOUS_VEHICLE
} // GTU

#endif // AUTONOMOUS_VEHICLE_GTU_ABSTRACT_SERVER_H