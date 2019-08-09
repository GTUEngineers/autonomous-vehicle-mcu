#ifndef SERVER_H
#define SERVER_H

#include "comBase.h"

//namespace that is used for all ZMQCommunication parts
namespace ZMQCommunication {

//Server class that is server part of the sequential request-reply mechanism.
class Server : public ComBase {
public:
    //Constructor of the class.
    Server();
    ////Destructor of the class.
    ~Server();
    //Tries to receive a message from given socket.
    //Returns true if it is successful, false otherwise.
    bool recv(zmq::message_t& msg, long timeout = -1);
    //Tries to send a message to given socket.
    //Returns true if it is successful, false otherwise.
    bool send(const zmq::message_t& msg);
}; //end class
} //namespace ZMQCommunication

#endif
