#include "heartbeatsMechanism.h"
#include <iostream>
#include <thread>
#include <unistd.h>
//This function will be called from a thread

int main()
{
    HeartbeatsMechanism smy("*", 5556, 5557, true);
    sleep(1000);

    return 0;
}