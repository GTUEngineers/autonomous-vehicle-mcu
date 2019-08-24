/**
 * \file        server.h
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Aug 10, 2019
 */

#ifndef SRC_ZMQCOMMUNICATION_SERVER_H_
#define SRC_ZMQCOMMUNICATION_SERVER_H_

/*------------------------------< Includes >----------------------------------*/
#include "comBase.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/

//namespace that is used for all ZMQCommunication parts
namespace seqreqrep {

//Server class that is server part of the sequential request-reply mechanism.
class Server : public zmqbase::ComBase {
public:
    //Constructor of the class.
    Server();
    ////Destructor of the class.
    ~Server();
    //Tries to receive a message from given socket.
    //Returns true if it is successful, false otherwise.
    bool recv(std::string& msg, long timeout = -1);
    //Tries to send a message to given socket.
    //Returns true if it is successful, false otherwise.
    bool send(const std::string& msg);
}; //end class
} //namespace ZMQCommunication

#endif /* SRC_ZMQCOMMUNICATION_SERVER_H_ */
