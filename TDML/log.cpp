//log.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	void log::setDebugMode(bool debug)
	{
		debugMode = debug;
	}

	bool log::getDebugMode()
	{
		return debugMode;
	}

	log::log() : outputfile("log.txt")
	{
		debugMode = false;
		timestamp = true;
	}

	void log::output(std::string Message)
	{
		if(debugMode==true)
		{
			outputWindow(Message);
		}
		else
		{
			outputLog(Message);
		}
	}

	void log::outputWindow(std::string Message)
	{
		std::cout << Message;
	}

	void log::outputLog(std::string Message)
	{
		outputfile << Message;
	}

	void log::output(float Number)
	{
		if(debugMode==true)
		{
			outputWindow(Number);
		}
		else
		{
			outputLog(Number);
		}
	}

	void log::outputWindow(float Number)
	{
		std::cout << Number;
	}

	void log::outputLog(float Number)
	{
		outputfile << Number;
	}

	void log::cleanup()
	{
		outputfile.close();
	}
}