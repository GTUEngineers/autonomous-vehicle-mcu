#include "../header/AbstractCommunication.h"
using namespace GTU::AUTONOMOUS_VEHICLE;
ErrorStatus AbstractCommunication::stop()
{
    if(getConnection() != -1)
    {
        while(shutdown(getConnection(), SHUT_RD) == -1 && errno == EINTR); 
        while(close(getConnection()) == -1 && errno == EINTR);
        setConnection(-1);
        return ErrorStatus::Success;
    }
    return ErrorStatus::Success;
}

ErrorStatus AbstractCommunication::receive(std::string & message, int length)
{
    if(getConnection() == -1)
        return ErrorStatus::NoSuchConnection;
    char buffer[255];
    if(read(getConnection(), &buffer, length) == 0)
        return ErrorStatus::ReadError;
    message.assign(buffer, 0, length);
    return ErrorStatus::Success;
}

ErrorStatus AbstractCommunication::send(const std::string & message, int length)
{
    if(getConnection() == -1)
        return ErrorStatus::NoSuchConnection;
    if(write(getConnection(), message.c_str(), length) < 0)
        return ErrorStatus::WriteError;
    return ErrorStatus::Success;
}