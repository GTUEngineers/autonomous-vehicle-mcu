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

	uart::pub_sub reqrep;
	if (reqrep.ParseFromArray(req.data(), req.size()))
	{
		if (reqrep.has_startstop())
		{
			status = reqrep.startstop().cmd();
			return true;
		}
	}

	return false;
}

bool parse_throttle_req(std::string &req, int &throttle)
{

	uart::pub_sub reqrep;
	if (reqrep.ParseFromArray(req.data(), req.size()))
	{
		if (reqrep.has_throttle())
		{
			throttle = reqrep.throttle().throttlevalue();
			return true;
		}
	}

	return false;
}
bool parse_steer_req(std::string &req, uart::steering_enum &cmd, double &angle)
{

	uart::pub_sub reqrep;
	if (reqrep.ParseFromArray(req.data(), req.size()))
	{
		if (reqrep.has_steering())
		{
			cmd = reqrep.steering().cmd();
			angle = reqrep.steering.angle();
			return true;
		}
	}

	return false;
}

bool parse_break_req(std::string &req, bool &is_break)
{

	uart::pub_sub reqrep;
	if (reqrep.ParseFromArray(req.data(), req.size()))
	{
		if (reqrep.has_brake())
		{
			is_break = reqrep.brake().brakevalue();
			return true;
		}
	}

	return false;
}
bool parse_stateworking(std::string &req, uart::stateWorking_enum &cmd)
{

	uart::pub_sub reqrep;
	if (reqrep.ParseFromArray(req.data(), req.size()))
	{
		if (reqrep.has_statework())
		{
			cmd = reqrep.statework().cmd();
			return true;
		}
	}

	return false;
}
bool parse_hcsr4(std::string &req, double &distance)
{

	uart::pub_sub reqrep;
	if (reqrep.ParseFromArray(req.data(), req.size()))
	{
		if (reqrep.has_hcsr4_dis())
		{
			distance = reqrep.hcsr4_dis().distance();
			return true;
		}
	}

	return false;
}
bool parse_gps(std::string &req, float &latitude, float &longitude)
{

	uart::pub_sub reqrep;
	if (reqrep.ParseFromArray(req.data(), req.size()))
	{
		if (reqrep.has_location())
		{
			latitude = reqrep.location().latitude();
			longitude = reqrep.location().longitude();
			return true;
		}
	}

	return false;
}
