/**
 * \file        CommunicationMechanism.cpp
 * \brief       A brief description one line.
 *
 * \author      Sevval MEHDER
 * \date        Aug 17, 2019
 */

/*------------------------------< Includes >----------------------------------*/
#include "process.pb.h"
#include <iostream>
#include "CommunicationMechanism.h"
#include "UARTCommunication.cpp"

/*------------------------------< Defines >-----------------------------------*/

/*------------------------------< Typedefs >----------------------------------*/

/*------------------------------< Namespaces >--------------------------------*/

CommunicationMechanism::CommunicationMechanism() : helperThread(&CommunicationMechanism::threadFunction, this)
{

	// Constructor code
}

void CommunicationMechanism::threadFunction()
{

	while (true)
		;
}

void CommunicationMechanism::waitUntilFinish()
{

	// Join the thread with the main thread
	this->helperThread.join();
}

/*--------------------------< Parse Functions >--------------------------*/
bool parse_startstop_req(std::string &req, uart::startstop_enum &status)
{

	uart::pub_sub pubsub;
	if (pubsub.ParseFromArray(req.data(), req.size()))
	{
		if (pubsub.has_startstop())
		{
			status = pubsub.startstop().cmd();
			return true;
		}
	}

	return false;
}

bool parse_throttle_req(std::string &req, int &throttle)
{

	uart::pub_sub pubsub;
	if (pubsub.ParseFromArray(req.data(), req.size()))
	{
		if (pubsub.has_throttle())
		{
			throttle = pubsub.throttle().throttlevalue();
			return true;
		}
	}

	return false;
}
bool parse_steer_req(std::string &req, uart::steering_enum &cmd, double &angle)
{

	uart::pub_sub pubsub;
	if (pubsub.ParseFromArray(req.data(), req.size()))
	{
		if (pubsub.has_steering())
		{
			cmd = pubsub.steering().cmd();
			angle = pubsub.steering().angle();
			return true;
		}
	}

	return false;
}

bool parse_break_req(std::string &req, bool &is_break)
{

	uart::pub_sub pubsub;
	if (pubsub.ParseFromArray(req.data(), req.size()))
	{
		if (pubsub.has_brake())
		{
			is_break = pubsub.brake().brakevalue();
			return true;
		}
	}

	return false;
}
bool parse_stateworking(std::string &req, uart::stateWorking_enum &cmd)
{

	uart::pub_sub pubsub;
	if (pubsub.ParseFromArray(req.data(), req.size()))
	{
		if (pubsub.has_statework())
		{
			cmd = pubsub.statework().cmd();
			return true;
		}
	}

	return false;
}
bool parse_hcsr4(std::string &req, double &distance)
{

	uart::pub_sub pubsub;
	if (pubsub.ParseFromArray(req.data(), req.size()))
	{
		if (pubsub.has_hcsr4_dis())
		{
			distance = pubsub.hcsr4_dis().distance();
			return true;
		}
	}

	return false;
}
bool parse_gps(std::string &req, float &latitude, float &longitude)
{

	uart::pub_sub pubsub;
	if (pubsub.ParseFromArray(req.data(), req.size()))
	{
		if (pubsub.has_location())
		{
			latitude = pubsub.location().latitude();
			longitude = pubsub.location().longitude();
			return true;
		}
	}

	return false;
}
