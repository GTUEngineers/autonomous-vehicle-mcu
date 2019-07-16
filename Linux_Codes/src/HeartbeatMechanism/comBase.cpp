/**
 * \file        comBase.cpp
 * \brief       A brief description one line.
 *
 * \author      alperenbulut
 * \date        Jul 16, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "comBase.h"
/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

ComBase::ComBase (int s_type, bool is_server) :
                m_context(new zmq::context_t( )),
                m_socket(new zmq::socket_t(*m_context, s_type)),
                m_is_server(is_server)
{
}

ComBase::~ComBase ( )
{
}

