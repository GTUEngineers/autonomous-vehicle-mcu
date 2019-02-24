#include <iostream>

#include "messagebuilder.h"

using GTU::AUTONOMOUS_VEHICLE::MessageBuilder;

void tester1()
{
    //Initializing necessary parameters
    uint16_t len = 10;
    uint8_t sysid = 1;
    uint8_t compid = 2;
    uint16_t msgid = 100;
    uint8_t payload[10] = {0,1,2,3,4,5,6,7,8,9};

    //Protocol filler constructor called
    MessageBuilder mes = MessageBuilder(sysid, compid);

    //Message built with filled protocol
    mes.build_message(len, msgid, payload);

    std::cout << "Message's bytes length should be 16 ->" << (std::string)(len + "\0");
}

int main()
{
    tester1();
    return 0;
}