#include "messagebuild.h"

#include <iostream>

namespace GTU{

    namespace AUTONOMOUS_VEHICLE{

        ///Constructor that doesn't initialize message
        MessageBuilder::MessageBuilder() {
            protocol.len = NULL;
            protocol.sysid = NULL;
            protocol.compid = NULL;
            protocol.msgid = NULL;
            protocol.payload = NULL;
        }

        ///Constructor that initializes message
        MessageBuilder::MessageBuilder(uint16_t len, uint8_t sysid, uint8_t compid, uint16_t msgid, uint8_t *payload) {
            protocol.len = len;
            protocol.sysid = sysid;
            protocol.compid = compid;
            protocol.msgid = msgid;
            protocol.payload = new uint8_t[len];
            for(uint16_t i=0; i<len; ++i){
                protocol.payload[i] = payload[i];
            }
        }

        ///Destructor that frees allocated memory for "protocol.payload"
        MessageBuilder::~MessageBuilder(){
            if(protocol.len != NULL)
                delete protocol.payload;
        }

        ///Builds message by previous valued parameters by parameter-constructor
        std::string MessageBuilder::build_message() {
            if(protocol.len == NULL){
                throw new _exception;
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
        std::string MessageBuilder::build_message(uint16_t len, uint8_t sysid, uint8_t compid, uint16_t msgid, uint8_t *payload) {
            protocol.len = len;
            protocol.sysid = sysid;
            protocol.compid = compid;
            protocol.msgid = msgid;
            protocol.payload = new uint8_t[len];
            for(uint16_t i=0; i<len; ++i){
                protocol.payload[i] = payload[i];
            }
            try{
                return this->build_message();
            }
            catch (Exception err){
                std::cout << "ERROR ---> " << std::endl;
            }
            return "";
        }
    }
}