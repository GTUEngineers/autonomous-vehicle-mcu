#include "heartbeatsMechanism.h"
#include <iostream>
#include <thread>
#include <unistd.h>
//This function will be called from a thread

int main()
{
    HeartbeatsMechanism heartbeat_car("*", 5556, 5557, true);
    heartbeat_car.waitUntilFinish();

    return 0;
}