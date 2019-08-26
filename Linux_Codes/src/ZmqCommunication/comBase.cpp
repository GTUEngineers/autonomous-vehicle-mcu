/**
 * \file        comBase.cpp
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Aug 10, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "comBase.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

namespace zmqbase {
const std::string TCP_CONNECTION = "tcp://%s:%d";
const std::string PROC_CONNECTION = "ipc:///tmp/%s";

ComBase::ComBase(int s_type, bool is_server)
    : m_context(new zmq::context_t())
    , m_socket(new zmq::socket_t(*m_context, s_type))
    , m_is_server(is_server)
{
    m_socket->setsockopt(ZMQ_LINGER, 0);
}

ComBase::~ComBase()
{
}

void ComBase::connect(const std::string& addr)
{
    if (m_is_server) {
        m_socket->bind(addr.c_str());
    } else {
        m_socket->connect(addr.c_str());
    }
}

void ComBase::disconnect()
{
    if (!m_is_server) {
        m_socket->disconnect(addr.c_str());
    }
}

int ComBase::poll(PollItem& data, int timeout)
{
    int retval{ 0 };
    zmq::pollitem_t item = { *data.base->m_socket.get(), 0, data.events, data.revents };

    retval = zmq::poll(&item, 1, timeout);

    if (item.revents & ZMQ_POLLIN) {
        data.revents = PollEventType::POLLIN;
    } else if (item.revents & ZMQ_POLLOUT) {
        data.revents = PollEventType::POLLOUT;
    } else if (item.revents & ZMQ_POLLERR) {
        data.revents = PollEventType::POLLERR;
    } else if (item.revents & ZMQ_POLLPRI) {
        data.revents = PollEventType::POLLPRI;
    } else {
        data.revents = PollEventType::NO;
    }

    return retval;
}
}
