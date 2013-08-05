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
	void log::setDebugMode(int debug)
	{
		debugMode = debug;
		if(debugMode==4||debugMode==5||debugMode==6) FreeConsole();
	}

	bool log::getDebugMode()
	{
		return debugMode;
	}

	log::log() : outputfile("log.txt")
	{
		debugMode = 0;
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
		if(debugMode==0||debugMode==1||debugMode==2||debugMode==3)
		{
			outputWindow(Number);
		}
		if(debugMode==1||debugMode==2||debugMode==5||debugMode==6)
		{
			outputLog(Number);
		}
		if(debugMode==0||debugMode==1||debugMode==2||debugMode==3)
		{
			outputBuffer+=Number;
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