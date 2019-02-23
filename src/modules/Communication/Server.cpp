#include "Server.h"

using namespace GTU::AUTONOMOUS_VEHICLE;

Server::Server(int portNumber)
{
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    this->setup(portNumber);
}

ErrorStatus Server::setup(int portNumber)
{
    if(getConnection() != FALSE)
        stop();
    struct sockaddr_in  serverAddress;
    serverAddress                   = {0};
    serverAddress.sin_family        = AF_INET;
    serverAddress.sin_addr.s_addr   = htonl(INADDR_ANY);
    serverAddress.sin_port          = htons(portNumber);

    if(bind(socketDescriptor, (struct sockaddr *) &serverAddress, sizeof(sockaddr_in)))
    {
        return ErrorStatus::BindError;
    }
    if(listen(socketDescriptor, 1))
    {
        return ErrorStatus::ListenError;
    }
    socklen_t socketLength = sizeof(struct sockaddr_in);
    if (setConnection(accept(socketDescriptor, (struct sockaddr *) &serverAddress, &socketLength))) {
        return ErrorStatus::AcceptError;
    }
    return ErrorStatus::Success;
}

Server::~Server()
{
    this->stop();
    shutdown(socketDescriptor, SHUT_RDWR);
    close(socketDescriptor);
}
