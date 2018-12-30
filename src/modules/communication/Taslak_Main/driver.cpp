#include "header/Server.h"
#include "header/Client.h"
#include <iostream>
using namespace GTU::AUTONOMOUS_VEHICLE;
main(int argc, char const *argv[])
{
    Communication * ser;
    std::string recM;
    if(argc == 1)
    {
        ser = new Client();
        while(recM != "end")
        {
            recM = "client";
            ser->send(recM, 8);
            ser->receive(recM, 8);
            std::cout << recM << std:: endl;
        }
    }
    else
    {
        ser = new Server();
        while(recM != "end")
        {
            ser->receive(recM, 8);
            std::cout << recM << std:: endl;
            recM = "server";
            ser->send(recM, 8);
        }
    }
    delete ser;
    ser = nullptr;
    return 0;
}
