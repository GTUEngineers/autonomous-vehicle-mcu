/**
 * \file        comBase.cpp
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Jul 16, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "heartbeatsMechanisim.h"
#include <unistd.h>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

 HeartbeatsMechanisim::HeartbeatsMechanisim 
():subscriber{true},publisher{false}{

subscriber_thread = std::thread(&HeartbeatsMechanisim::listen,this);
publisher_thread = std::thread(&HeartbeatsMechanisim::publish,this);

    
}

  
     void HeartbeatsMechanisim::listen (){
         subscriber.connect();
         subscriber.subscribe("arac");
std::string topic ;
zmq::message_t msg(10);
         while (1)
         {
             subscriber.recv(topic,msg);
            std::cout <<topic<<" "<<msg.str()<< std::endl;
         }   
         
     }

     void HeartbeatsMechanisim::publish() {
         publisher.connect();
    
          while (1)
          {
           zmq::message_t msg("taskan",10);   
    publisher.publish("arac", msg);
          std::cout << "pubpub" << std::endl;
          sleep (1);
          }
      }
