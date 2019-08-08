#ifndef CLIENT_H
#define CLIENT_H

#include "comBase.h"

namespace ZMQCommunication {

class Client : public ComBase {
public:
    Client();
    ~Client();
    bool reqrep(zmq::message_t& req, zmq::message_t& rep, long timeout = -1);
};
} // namespace ZMQCommunication

#endif
