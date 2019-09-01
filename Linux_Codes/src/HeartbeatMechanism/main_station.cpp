#include "heartbeatsMechanism.h"
#include <iostream>
#include <thread>
#include <unistd.h>
//This function will be called from a thread

int main()
{
    HeartbeatsMechanism heartbeat_station("127.0.0.1", 5557, 5556, false);
    heartbeat_station.waitUntilFinish();

    return 0;
}