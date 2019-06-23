/**
 *  \file   communication_test.cpp
 *  \brief  Communication Test
 *  \author Husnu.Akcak
 *  \date   23.02.2019
 * */

#include <iostream>
#include <ctime>     // to take current time
#include <unistd.h>  // for sleep function
#include <string>
#include <exception>

#include "../Client.h"
#include "../Server.h"

using std::cout;
using std::cin;
using std::endl;
using std::exception;
using std::string;
using namespace GTU::AUTONOMOUS_VEHICLE;

// take computer type as parameter and make test process by itself using "ctime".
void reconnect_test(char comType);

// waits for user input to send message from server to client and vice versa.
void input_test();

// prints error status.
void comm_status(ErrorStatus st);

int
main(int argc, char const *argv[]) {
    int choice;

    cout << "Please choose a test type.\n"
         << "1 : Input test\n"
         << "2 : Reconnect test\n";
    cin >> choice;

    if (choice == 1) {
        input_test();
    } else if (choice == 2) {
        char comType;
        do {
            cout << "Plese enter 's' for Server or 'c' for Client.\n";
            cin >> comType;
        } while (comType != 's' && comType != 'S' && comType != 'C' && comType != 'c');
        reconnect_test(comType);
    } else {
        cout << "Choice is not valid, driver program is being terminated.\n";
    }

    return 0;
}

/* if reconnecting and stopping lines ignore, function is working. */
void
reconnect_test(char comType) {
    Communication *server{nullptr}, *client{nullptr}; // server and client
    string serverM, clientM;   // server message and client messages
    ErrorStatus st;            // communication status

    time_t msg_time;    //  keeps msg time
    string s_msg_time;  //  keeps msg time as string
    struct tm *ti;      //  to take local time

    //start conversation according to comType(computer type)
    if (comType == 's' || comType == 'S') {
        //create server
        server = new Server(8080);
        cout << "----------------------------------\n";
        //[server] receive message
        st = (server->receive(clientM, 25));
        cout << "Message is receiving...\n";
        comm_status(st); // prints status
        cout << "[Client's msg] : " << clientM << endl;

        //[server] send message
        st = (server->send("{123456789}", 11));
        cout << "Message is sending...\n";
        comm_status(st); // prints status
        cout << "----------------------------------\n";

        // [WARNING]
        /*****************************************************************
        When the following delete and new operation is done, the conversation is
        corrupted.
        To disconnect and reconnect, I destruct the server and recosntruct it.
        Is it a wrong behavior?
        ******************************************************************/
        //delete server;        // [server]stop connection
        //server= new Server(); // [server]reconnecting

        //while status is success conversation is continue
        do {
            cout << "--------------------------------------------\n";
            //[server] receive message regularly, one msg per second
            st = (server->receive(clientM, 25));  //msg is received.
            cout << "Message is receiving...\n";
            comm_status(st); // status is printed
            cout << "[Client's msg] : " << clientM << endl;

            //[server] send a message per second.
            time(&msg_time);          // Applying time()
            ti = localtime(&msg_time); // Using localtime()
            s_msg_time = asctime(ti);  // time format
            st = (server->send(s_msg_time, s_msg_time.size())); //msg is sent.
            cout << "Message is sending...\n";
            comm_status(st); // status is printed

            sleep(1); // wait for 1 sec.
            cout << "--------------------------------------------\n";
        } while (st == ErrorStatus::Success);
        // delete server
        if (server != nullptr) {
            delete server;
            server = nullptr;
        }
    } else if (comType == 'c' || comType == 'C') {
        //create client
        client = new Client();
        cout << "----------------------------------\n";

        //[client] send message
        st = (client->send("{987654321}", 11));
        cout << "Message is sending...\n";
        comm_status(st); // print status

        //[client] receive message
        st = (client->receive(serverM, 25));
        cout << "Message is receiving...\n";
        comm_status(st); // print status
        cout << "[Server's msg] : " << serverM << endl;
        cout << "----------------------------------\n";

        // [WARNING]
        /*****************************************************************
        I afraid, I could not use use reconnecting mechanism(stop and setup),
        and for the following block(stop func. call and obj creation) I need
        some help. Also for server side I have the same problem.
        ******************************************************************/
        // client ->stop();     // [client]stop connection
        // client = new Client; // [client]reconnecting


        //while connnection status is success loop is continues.
        do {
            //[client] send message regularly, 1 message per second
            cout << "--------------------------------------------\n";
            time(&msg_time);          // Applying time()
            ti = localtime(&msg_time); // Using localtime()
            s_msg_time = asctime(ti);  // time format
            st = (client->send(s_msg_time, s_msg_time.size()));
            cout << "Message is sending...\n";
            comm_status(st); // prints status

            //[client] receive message regularly, 1 message per second
            st = (client->receive(serverM, 25));
            cout << "Message is receiving...\n";
            comm_status(st);    // prints status

            cout << "[Server's msg] : " << serverM << endl;

            sleep(1);   //wait for 1 sec
            cout << "--------------------------------------------\n";
        } while (st == ErrorStatus::Success);

        // delete client
        if (client != nullptr) {
            delete client;
            client = nullptr;
        }
    }

    return;
}

// [WARNING]
/* In 'input_test' func, if client only send msg and server only receive msg,
    function works without any problem, but when two operation is available
    for two computer program stops working. In a word client can send msg,
    server can receive msg(In this function). But in normal the two operation
    must be available for both of them.
*/
void
input_test() {

    Communication *server = nullptr, *client = nullptr;// server and client
    string serverM, clientM;    // server message and client message
    ErrorStatus st;             // communication status.

    char choice; //s= server , c= client

    // choice
    cout << "SERVER :s\n" << "CLIENT :c\n";
    cin >> choice;

    if (choice == 'c' || choice == 'C') {
        client = new Client();
        do {
            // client message is from the user
            cout << "> ";
            getline(cin, clientM);
            st = client->send(clientM, 80); // msg is sent.
            cout << "Client's message is sending...\n";
            comm_status(st); // print operation status on the screen.

            //// [WARNING]
            //// I could not run 'receive' fucn for Client.
            // st= (client->receive(serverM, 2));
            // cout << serverM << endl;
            // cout << "Server's message is receiving...\n";
            // comm_status(st); // prints operation status to the screen

        } while (st == ErrorStatus::Success && clientM != "end");

        if (client != nullptr) {
            delete client;
            client = nullptr;
        }
    } else if (choice == 's' || choice == 'S') {
        server = new Server();
        do {
            st = (server->receive(clientM, 80)); // msg is being received
            cout << clientM << endl;
            cout << "Client's message is receiving...\n";
            comm_status(st); //prints op. status on the screen.

            //// [WARNING]
            //// I could not run 'send' function for server!
            //cout << "> ";
            //getline(cin, serverM);
            //st=(server->send(serverM, 2)); // msg is being sent.
            //cout << "Server's message is sending...\n";
            //comm_status(st); //prints op. status on the screen.

        } while (st == ErrorStatus::Success && clientM != "end");

        if (server != nullptr) {
            delete server;
            server = nullptr;
        }
    }
    return;
}

/* 'comm_status' prints status of communication. */
void
comm_status(ErrorStatus st) {
    switch (st) {
        case (ErrorStatus::BindError) :
            cout << "BindError\n";
            break;
        case (ErrorStatus::ListenError) :
            cout << "ListenError\n";
            break;
        case (ErrorStatus::AcceptError) :
            cout << "AcceptError\n";
            break;
        case (ErrorStatus::SocketCreationFailed) :
            cout << "SocketCreationFailed\n";
            break;
        case (ErrorStatus::AddressInUse) :
            cout << "AddressInUse\n";
            break;
        case (ErrorStatus::NotValidSocketDescriptor) :
            cout << "NotValidSocketDescriptor\n";
            break;
        case (ErrorStatus::ConnectionRejected) :
            cout << "ConnectionRejected\n";
            break;
        case (ErrorStatus::SocketWasClosed) :
            cout << "SocketWasClosed\n";
            break;
        case (ErrorStatus::NoSuchConnection) :
            cout << "NoSuchConnection\n";
            break;
        case (ErrorStatus::WriteError) :
            cout << "WriteError\n";
            break;
        case (ErrorStatus::ReadError) :
            cout << "ReadError\n";
            break;
        case (ErrorStatus::Success) :
            cout << "Success\n";
            break;
        default:
            cout << "(driver-comm_status func)Something wrong about ErrorStatus!\n";
    }
}
