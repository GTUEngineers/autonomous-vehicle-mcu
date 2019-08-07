#include "comBase.h"

namespace communication{
ComBase::ComBase(int s_type, bool is_server) : m_context(new zmq::context_t()),
                                               m_socket(new zmq::socket_t(*m_context, s_type)),
                                               m_is_server(is_server)
{
}

ComBase::~ComBase()
{
}

void ComBase::connect(int port, const std::string &ip)
{
    std::string addr;
    m_ip = ip;
    m_port = port;
    if (m_is_server)
    {
        addr = "tcp://*:" + std::to_string(port);
        m_socket->bind(addr.c_str());
    }
    else
    {
        addr = "tcp://" + ip + ":" + std::to_string(port);
        m_socket->connect(addr.c_str());
    }
}

void ComBase::connect()
{
    std::string addr;
    if (m_is_server)
    {
        addr = "tcp://*:" + std::to_string(m_port);
        m_socket->bind(addr.c_str());
    }
    else
    {
        addr = "tcp://" + m_ip + ":" + std::to_string(m_port);
        m_socket->connect(addr.c_str());
    }
}

void ComBase::disconnect()
{
    if (!m_is_server)
    {
        std::string addr = "tcp://" + m_ip + ":" + std::to_string(m_port);
        m_socket->disconnect(addr.c_str());
    }
}
}
