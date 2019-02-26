/**
 *  \file   messageBuilder_test.cpp
 *  \brief  Message Builder yest
 *  \author Ongun.Alp.Baba
 *  \date   23.02.2019
 * */


#include <iostream>
#include <cassert>
#include <cstring>
#include "messagebuilder.h"

using namespace GTU::AUTONOMOUS_VEHICLE::MESSAGE;

void test_1() {
    Protocol aProtocol, bProtocol;
    aProtocol.sys_id = 1;
    aProtocol.comp_id = 2;
    aProtocol.msg_id = 3;
    snprintf(&aProtocol.payload[0], 50, "Test Code %d ", 1);
    aProtocol.len = 50;

    parse_message(build_message(&aProtocol), &bProtocol);

    assert(bProtocol.len == aProtocol.len);
    assert(bProtocol.msg_id == aProtocol.msg_id);
    assert(bProtocol.comp_id == aProtocol.comp_id);
    assert(bProtocol.sys_id == aProtocol.sys_id);
    assert(strcmp(bProtocol.payload, aProtocol.payload) == 0);
}

int main() {
    test_1();
    return 0;
}