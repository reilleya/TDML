//config.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	config::config()
	{
		multisample = false;
		fov = 45;
	}

	void config::save()
	{
		//put stuff in a config.cfg file somewhere
	}

	void config::reload()
	{
		//load stuff from config.cfg
	}

	void config::setAA(bool AA)
	{
		multisample = AA;
	}

	bool config::getAA()
	{
		return multisample;
	}

	void config::setFOV(float FOV)
	{
		if(FOV>5)
		{
			if(FOV<120)
			{
				fov = FOV;
			}
			else
			{
				fov = 120;
			}
		}
		else
		{
			fov = 5;
		}
	}

	float config::getFOV()
	{
		return fov;
	}
}