/**
 * \file        comBase.h
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Jul 16, 2019
 */

#ifndef INC_COMBASE_H_
#define INC_COMBASE_H_

/*------------------------------< Includes >----------------------------------*/
#include <iostream>
#include <memory>
#include <zmq.hpp>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Class  >------------------------------------*/

class ComBase
{
public:
    ComBase(int s_type, bool is_server = false);
    virtual ~ComBase() = 0;
    virtual void connect();
    virtual void connect(int port, const std::string &ip);
    void disconnect();
    std::shared_ptr<zmq::context_t> m_context;
    std::shared_ptr<zmq::socket_t> m_socket;
    bool m_is_server;
    std::string m_ip;
    int m_port;
};

#endif /* INC_COMBASE_H_ */
