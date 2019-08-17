/**
 * \file        Communication_Mechanism.h
 * \brief       A brief description one line.
 *
 * \author      ahmet.alperen.bulut
 * \date        Aug 17, 2019
 */

#ifndef COMMUNICATIONS_COMMUNICATION_MECHANISM_H_
#define COMMUNICATIONS_COMMUNICATION_MECHANISM_H_


#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*------------------------------< Includes >----------------------------------*/

/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Constants >---------------------------------*/

/*------------------------------< Prototypes >--------------------------------*/

    void communication_init();
    uint8_t communication_get_msg(uint8_t* msg);
    uint8_t communication_get_queue_length();
    void communication_send_msg(uint8_t* msg);


#if defined(__cplusplus)
}                /* Make sure we have C-declarations in C++ programs */
#endif


#endif /* COMMUNICATIONS_COMMUNICATION_MECHANISM_H_ */
