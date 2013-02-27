//particlesystem.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	particlesystem::particlesystem(vector3d Pos, vector3d PosVariation,vector3d Dir, vector3d DirVariation,vector3d Accel, vector3d AccelVariation,float Life, float LifeVariation)
	{
		pos = Pos;
		posVariation = PosVariation;
		dir = Dir;
		dirVariation = DirVariation;
		accel = Accel;
		accelVariation = AccelVariation;
		life = Life;
		lifeVariation = LifeVariation;
	}

	void particlesystem::update()
	{
		timeTo -= 0; //TIME SINCE LAST FRAME;
		if(timeTo<=0)
		{
			//creat a montage... of particles...
			timeTo = spawnDelay;
		}
		for(int n = 0; n<nparts; n++)
		{
			particles[n].update();
		}
	}

	void particlesystem::display()
	{
		for(int n = 0; n<nparts; n++)
		{
			particles[n].display();
		}
	}
}