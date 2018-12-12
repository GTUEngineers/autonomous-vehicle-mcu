namespace communication{
    
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
    
    class	Communication {
        public:
            virtual ErrorStatus setup() = 0;
            virtual ErrorStatus connect() = 0;
            virtual ErrorStatus send(char* message, int length) = 0;
            virtual ErrorStatus recieve(char* message) = 0;
            virtual ErrorStatus process(char* in_message, char* out_message) = 0;
            virtual ErrorStatus close() = 0;
    };

}
