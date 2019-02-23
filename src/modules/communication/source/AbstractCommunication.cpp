#include "../header/AbstractCommunication.h"
using namespace GTU::AUTONOMOUS_VEHICLE;
ErrorStatus AbstractCommunication::stop()
{
    if(getConnection() != FALSE)
    {
        while(shutdown(getConnection(), SHUT_RD) == FALSE && errno == EINTR); 
        while(close(getConnection()) == FALSE && errno == EINTR);
        setConnection(FALSE);
        return ErrorStatus::Success;
    }
    return ErrorStatus::Success;
}

ErrorStatus AbstractCommunication::receive(std::string & message, int length)
{
    if(getConnection() == FALSE)
        return ErrorStatus::NoSuchConnection;
    char buffer[BUFFER_LENGTH];
    if(read(getConnection(), &buffer, length) == 0)
        return ErrorStatus::ReadError;
    message.assign(buffer, 0, length);
    return ErrorStatus::Success;
}

ErrorStatus AbstractCommunication::send(const std::string & message, int length)
{
    if(getConnection() == FALSE)
        return ErrorStatus::NoSuchConnection;
    if(write(getConnection(), message.c_str(), length) < 0)
        return ErrorStatus::WriteError;
    return ErrorStatus::Success;
}
