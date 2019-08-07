#ifndef INC_COMBASE_H_
#define INC_COMBASE_H_

#include <iostream>
#include <memory>
#include <zmq.hpp>

namespace communication{
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
}
#endif /* INC_COMBASE_H_ */
