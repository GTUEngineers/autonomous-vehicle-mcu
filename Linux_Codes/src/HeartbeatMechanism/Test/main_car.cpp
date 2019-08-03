#include <iostream>
#include <thread>
#include <unistd.h>
#include "heartbeatsMechanism.h"
//This function will be called from a thread

int main()
{
	HeartbeatsMechanism smy("127.0.0.1", 2563, 2564, true);
	sleep(1000);

	return 0;
}