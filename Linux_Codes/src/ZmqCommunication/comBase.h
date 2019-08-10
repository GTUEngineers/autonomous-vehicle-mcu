#ifndef INC_COMBASE_H_
#define INC_COMBASE_H_

#include <iostream>
#include <memory>
#include <zmq.hpp>

namespace ZMQCommunication {
class ComBase;

enum PollEventType {
    NO = 0,
    POLLIN = ZMQ_POLLIN,
    POLLOUT = ZMQ_POLLOUT,
    POLLERR = ZMQ_POLLERR,
    POLLPRI = ZMQ_POLLPRI
};

struct PollItem {
    ComBase* base;
    PollEventType events;
    PollEventType revents;
};

class ComBase {
public:
    ComBase(int s_type, bool is_server = false);
    virtual ~ComBase() = 0;
    virtual void connect();
    virtual void connect(int port, const std::string& ip);

    void disconnect();
    std::string m_ip;
    int m_port;

protected:
    int poll(PollItem& data, int timeout);

    std::shared_ptr<zmq::context_t> m_context;
    std::shared_ptr<zmq::socket_t> m_socket;
    bool m_is_server;
};
}
#endif /* INC_COMBASE_H_ */
