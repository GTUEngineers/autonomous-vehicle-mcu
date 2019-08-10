/**
 * \file        client.cpp
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Aug 10, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "client.h"
#include "station_car.pb.h"
#include <iostream>
#include <memory>
#include <unistd.h>
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

//Driver file for Client
int main()
{

    std::unique_ptr<seqreqrep::Client> client(new seqreqrep::Client);
    //connects to tcp://127.0.0.1:5555 socket
    client->connect(5555, "127.0.0.1");
    //a counter to counts requests and responses
    int counter = 0;
    while (true) {

        std::string adinisenkoy;
        seq_req_rep reqrep;
        std::unique_ptr<Commands> commands(new Commands);
        std::unique_ptr<Command_req> cmd_req(new Command_req);
        cmd_req->set_cmd(cmd_enum::STOP);
        commands->set_allocated_req(cmd_req.release());
        reqrep.set_allocated_cmd_msg(commands.release());
        reqrep.SerializeToString(&adinisenkoy);

        zmq::message_t request(adinisenkoy.c_str(), adinisenkoy.size());
        std::cout << "Sending Hello: " << counter << std::endl;
        zmq::message_t reply;
        //if connection is not broken
        if (client->reqrep(request, reply, 3)) {
            std::cout << "Received from server: " << counter << std::endl;
        }
        //if it is broken
        else {
            //resets client
            client.reset(new seqreqrep::Client);
            //reconnects
            client->connect(5555, "127.0.0.1");
        }
        sleep(1);
        ++counter;
    }
    return 0;
}
