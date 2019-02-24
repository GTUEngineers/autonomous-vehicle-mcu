#ifndef ABSTRACT_COMMUNICATION
    #define ABSTRACT_COMMUNICATION

    #include "Communication.h" 
    #include <unistd.h>
    #include <netdb.h>
    #include <iostream>
    namespace GTU
    {
        namespace AUTONOMOUS_VEHICLE
        {
            class AbstractCommunication : public Communication
            {
            public:
                ErrorStatus stop();
                ErrorStatus receive(std::string & message, int length);
                ErrorStatus send(const std::string & message, int length);
            protected:
                inline int setConnection(int input) 
                {
                    return (this->communication = input);
                }
                inline int getConnection() 
                {
                    return this->communication;
                }
            private:
                int communication;
            };            
        } // AUTONOMOUS_VEHICLE
    } // GTU

#endif
