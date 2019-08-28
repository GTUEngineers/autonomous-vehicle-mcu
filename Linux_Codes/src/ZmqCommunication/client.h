/**
 * \file        client.h
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Aug 10, 2019
 */

#ifndef SRC_ZMQCOMMUNICATION_CLIENT_H_
#define SRC_ZMQCOMMUNICATION_CLIENT_H_

/*------------------------------< Includes >----------------------------------*/
#include "comBase.h"

/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/

//namespace that is used for all ZMQCommunication parts
namespace seqreqrep {

//Client class that is client part of the sequential request-reply mechanism.
class Client : public zmqbase::ComBase {
public:
    //Constructor of the class.
    Client();
    //Destructor of the class.
    ~Client();
    //Send a request and wait for a reply from the Server.
    //Returns true if it is successful, false otherwise.
    bool reqrep(std::string& req, std::string& rep, long timeout = -1);
};
} // namespace seqreqrep

#endif /* SRC_ZMQCOMMUNICATION_CLIENT_H_ */
