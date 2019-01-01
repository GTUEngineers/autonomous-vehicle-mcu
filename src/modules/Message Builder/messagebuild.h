#ifndef MESSAGEBUILD_H
#define MESSAGEBUILD_H

#include <cstdint>
#include <string>

namespace GTU{

    namespace AUTONOMOUS_VEHICLE{

        enum Component{

        };

        ///A messages structure according to protocol
        struct Protocol{
            uint16_t len;               // Length of payload
            uint8_t sysid;              // ID of message sender system/(car)
            uint8_t compid;             // ID of the message sender component(car part)
            uint16_t msgid;             // first 16 bits of the ID of the message
            uint8_t *payload;           // A maximum of 500 payload bytes
        };


        class MessageBuilder {
        public:
            ///Constructor that doesn't initialize message
            MessageBuilder();

            ///Constructor that initializes message's target sysid and compid
            MessageBuilder(uint8_t sysid, uint8_t compid);

            ///Destructor that frees allocated memory for "protocol.payload"
            ~MessageBuilder();

            ///Builds message by previous valued parameters by parameter-constructor

            std::string build_message();
            ///Builds message by given parameters
            std::string build_message(uint16_t len, uint16_t msgid, uint8_t *payload, uint8_t sysid=protocol.sysid, uint8_t compid=protocol.compid);
        protected:
            Protokol protocol;

            std::string message;
        };
    }
}

#endif
