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

void ComBase::connect(int port, const std::string& ip)
{
    std::string addr;
    m_ip = ip;
    m_port = port;
    if (m_is_server) {
        addr = "tcp://*:" + std::to_string(port);
        m_socket->bind(addr.c_str());
    } else {
        addr = "tcp://" + ip + ":" + std::to_string(port);
        m_socket->connect(addr.c_str());
    }
}

void ComBase::connect()
{
    std::string addr;
    if (m_is_server) {
        addr = "tcp://*:" + std::to_string(m_port);
        m_socket->bind(addr.c_str());
    } else {
        addr = "tcp://" + m_ip + ":" + std::to_string(m_port);
        m_socket->connect(addr.c_str());
    }
}

void ComBase::disconnect()
{
    if (!m_is_server) {
        std::string addr = "tcp://" + m_ip + ":" + std::to_string(m_port);
        m_socket->disconnect(addr.c_str());
    }
}

int ComBase::poll(PollItem& data, int timeout)
{
    int retval = 0;
    zmq::pollitem_t item = { *data.base->m_socket, 0, data.events, data.revents };

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
