/**
 *  \file   Communication.h
 *  \brief  Communication interface
 *  \author Emre.ARTIS
 *  \date   13.12.2018
 * */
#ifndef AUTONOMOUS_VEHICLE_GTU_COMMUNICATION_H
#define AUTONOMOUS_VEHICLE_GTU_COMMUNICATION_H

    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <exception>
    #include <string>

    #define BUFFER_LENGTH   1024
    #define FALSE           -1
    namespace GTU {
        namespace AUTONOMOUS_VEHICLE {

            enum class ErrorStatus {
                Success,
                BindError,
                ListenError,
                AcceptError,
                ReadError,
                NoSuchConnection,
                SocketCreationFailed,
                AddressInUse,
                NotValidSocketDescriptor,
                ConnectionRejected,
                SocketWasClosed,
                WriteError
            };

            //  Communication Interface
            class   Communication {
                public:
                    virtual ErrorStatus send(const std::string & message, int length) = 0;
                    virtual ErrorStatus receive(std::string & message, int length) = 0;
                    virtual ErrorStatus stop() = 0;
                    virtual ~Communication() { /*intentionally empty*/ }
            };
        }
    }
#endif