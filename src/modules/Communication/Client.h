#ifndef CLIENT
    #define CLIENT
    #include "AbstractCommunication.h"

    namespace GTU
    {
        namespace AUTONOMOUS_VEHICLE
        {
            class Client : public AbstractCommunication
            {
            public:
                Client(const std::string & hostName = "localhost", int portNumber = 8080);
                ErrorStatus setup(const std::string & hostName = "localhost", int port = 8080);
                virtual ~Client() override;
            };

        } // AUTONOMOUS_VEHICLE
    } // GTU
#endif