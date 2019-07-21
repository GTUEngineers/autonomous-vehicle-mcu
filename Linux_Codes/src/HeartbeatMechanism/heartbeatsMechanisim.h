
/**
 * \file        subscriber.h
 * \brief       A brief description one line.
 *
 * \author      sumeyye
 * \date        Jul 20, 2019
 */

#ifndef INC_HEARTBEATSMECHANISIM_H_
#define INC_HEARTBEATSMECHANISIM_H_


/*------------------------------< Includes >----------------------------------*/
#include "comBase.h"
#include "subscriber.h"
#include "publisher.h"
#include <thread>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/


class HeartbeatsMechanisim{
    public:
    HeartbeatsMechanisim ();
    private:
    void listen();
    void publish();

    Subscriber subscriber; 
    Publisher publisher;
    std::thread subscriber_thread;
    std::thread publisher_thread;

};



#endif