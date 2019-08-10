#ifndef CLIENT_H
#define CLIENT_H

#include "comBase.h"

//namespace that is used for all ZMQCommunication parts 
namespace ZMQCommunication {

//Client class that is client part of the sequential request-reply mechanism.
class Client : public ComBase {
public:
    //Constructor of the class.
    Client();
    //Destructor of the class.
    ~Client();
    //Send a request and wait for a reply from the Server.
    //Returns true if it is successful, false otherwise.
    bool reqrep(zmq::message_t& req, zmq::message_t& rep, long timeout = -1);
};
} // namespace ZMQCommunication

#endif
