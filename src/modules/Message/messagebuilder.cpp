#include "messagebuilder.h"

#include <iostream>

namespace GTU{

    namespace AUTONOMOUS_VEHICLE{

        ///Constructor that doesn't initialize message
        MessageBuilder::MessageBuilder() {
            protocol.len = 0;
            protocol.sysid = 0;
            protocol.compid = 0;
            protocol.msgid = 0;
            protocol.payload = NULL;
        }

        ///Constructor that initializes message's target sysid and compid
        MessageBuilder::MessageBuilder(uint8_t sysid, uint8_t compid) {
            protocol.len = 0;
            protocol.msgid = 0;
            protocol.payload = NULL;
            protocol.sysid = sysid;
            protocol.compid = compid;
        }

        ///Destructor that frees allocated memory for "protocol.payload"
        MessageBuilder::~MessageBuilder(){
            if(protocol.len != 0)
                delete protocol.payload;
        }

        ///Builds message by previous valued parameters by parameter-constructor
        std::string MessageBuilder::build_message() {
            if(protocol.len == 0){
                throw new std::exception;
            }
            else{
                message = (std::string)(protocol.len + "");
                message += (char)protocol.sysid
                        + (char)protocol.compid;
                message +=(std::string)(protocol.msgid + "");
    
                for(uint16_t i=0; i<protocol.len; ++i){
                    message += (char)protocol.payload[i];
                }
                std::cout << message << std::endl;
                return message;
            }
        }

        ///Builds message by given parameters
        std::string MessageBuilder::build_message(uint16_t len, uint16_t msgid, uint8_t *payload, uint8_t sysid, uint8_t compid) {
            protocol.len = len;
            protocol.sysid = sysid;
            protocol.compid = compid;
            protocol.msgid = msgid;
            if(protocol.payload == NULL)
                delete protocol.payload;
            protocol.payload = new uint8_t[len];
            for(uint16_t i=0; i<len; ++i){
                protocol.payload[i] = payload[i];
            }
            try{
                return this->build_message();
            }
            catch (std::exception err){
                std::cout << "ERROR ---> " << std::endl;
            }
            return "";
        }
    }
}
