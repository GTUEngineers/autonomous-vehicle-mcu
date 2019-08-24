/**
 * \file        client.cpp
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Aug 10, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "client.h"
#include <unistd.h>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/
using namespace zmqbase;
namespace seqreqrep {

Client::Client()
    : ComBase(ZMQ_REQ, false)
{
}
Client::~Client()
{
}
bool Client::reqrep(std::string& req, std::string& rep, long timeout)
{
    //return value of function that is default false
    bool returnVal{ false };

    //sets pollout as a ZMQ_POLLOUT
    PollItem pollout = { this, PollEventType::POLLOUT, PollEventType::NO };
    poll(pollout, timeout);
    //if poll operation is ZMQ_POLLOUT
    if (pollout.revents & PollEventType::POLLOUT) {

        //sends message to given socket
        if (m_socket->send(req.c_str), req.size) {

            //sets pollin as a ZMQ_POLLIN
            PollItem pollin = { this, PollEventType::POLLIN, PollEventType::NO };
            poll(pollin, timeout);

            //if poll operation is ZMQ_POLLIN
            if (pollin.revents & PollEventType::POLLIN) {
                zmq::message_t rep_zmq;
                //receives a message from given socket and assigns result as returnVal
                returnVal = m_socket->recv(&rep_zmq);
                rep.assign((const char*)rep_zmq.data(), rep_zmq.size());
            }
        }
    }
    return returnVal;
}
} // namespace seqreqrep
