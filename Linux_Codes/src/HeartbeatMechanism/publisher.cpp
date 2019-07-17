/**
 * \file        publisher.cpp
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Jul 16, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "publisher.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

Publisher::Publisher (bool is_server) :
                ComBase(ZMQ_PUB, is_server)
{

}

void Publisher::connect (const std::string &ip, int port)
{
    std::string addr;
    m_ip = ip;
    m_port = port;
    if (m_is_server)
    {
        addr = "tcp://*:" + std::to_string(port);
        m_socket->bind(addr.c_str( ));
    }
    else
    {
        addr = "tcp://" + ip + ":" + std::to_string(port);
        m_socket->connect(addr.c_str( ));
    }
}
void Publisher::disconnect ( )
{
    if (!m_is_server)
    {
        std::string addr = "tcp://" + m_ip + ":" + std::to_string(m_port);
        m_socket->disconnect(addr.c_str( ));
    }
}
bool Publisher::publish (const std::string &topic, zmq::message_t &msg)
{
    bool retval = true;
    retval = this->m_socket->send(topic.c_str( ), topic.size( ), ZMQ_SNDMORE);
    if (!retval)
        return retval;
    retval = this->m_socket->send(*(zmq::message_t*) &msg);
    return retval;
}
