#ifndef SERVER
    #define SERVER
    #include "AbstractCommunication.h"
    
    namespace GTU
    {
        namespace AUTONOMOUS_VEHICLE
        {
            class Server : public AbstractCommunication
            {
                public:
                    /**
                     * Creates a socket and binds it to given port number.
                     * As default, it will be 8080.
                     **/
                    Server(int portNumber = 8080);
                    ~Server();
                    ErrorStatus setup(int portNumber);
                private:
                    int socketDescriptor;
            };
            
        } // AUTONOMOUS_VEHICLE
    } // GTU
#endif
