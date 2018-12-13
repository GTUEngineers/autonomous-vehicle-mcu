#ifndef AUTONOMOUS_VEHICLE_GTU_COMMUNICATION_H
#define AUTONOMOUS_VEHICLE_GTU_COMMUNICATION_H

namespace GTU {
    namespace AUTONOMOUS_VEHICLE {

        enum class ErrorStatus {
            Success,
            SocketCreationFailed,
            AddressInUse,
            NotValidSocketDescriptor,
            ConnectionRejected,
            BufferSpaceNotAvailable,
            OperationTimedOut,
            SocketWasClosed
            //
        };
        
        
        //  Communication Interface
        class	Communication {
            public:
                virtual ErrorStatus setup() = 0;
                virtual ErrorStatus connect() = 0;
                virtual ErrorStatus send(const char* message, const int length) = 0;
                virtual ErrorStatus receive(char* message, const int length) = 0;
                virtual ErrorStatus process(const char* in_message, char* out_message) = 0;
                virtual ErrorStatus close() = 0;
        };
        
    }    
}


#endif //AUTONOMOUS_VEHICLE_GTU_COMMUNICATION_H
