/**
 *  \file   logger_test.cpp
 *  \brief  Test Logger
 *  \author Ahmet.Alperen.BULUT
 *  \date   23.02.2019
 * */
#include "ConsoleLog.h"
#include "Syslog.h"
int main()
{

    GTU::AUTONOMOUS_VEHICLE::Syslog::syslog_test();
    GTU::AUTONOMOUS_VEHICLE::ConsoleLog::console_log_test();

    return 0;
}