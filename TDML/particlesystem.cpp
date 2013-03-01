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
	particlesystem::particlesystem()
	{
		
	}

	particlesystem::particlesystem(string FileName, vector3d Pos, vector3d PosVariation,vector3d Dir, vector3d DirVariation,vector3d Accel, vector3d AccelVariation,float Life, float LifeVariation, float SpawnDelay)
	{
		pos = Pos;
		posVariation = PosVariation;
		dir = Dir;
		dirVariation = DirVariation;
		accel = Accel;
		accelVariation = AccelVariation;
		life = Life;
		lifeVariation = LifeVariation;
		spawnDelay = SpawnDelay;
		timeTo = SpawnDelay;
		texid = loadTextureData(FileName);
		Log.output("Created particle system\n");
		nparts = 0;
	}

	void particlesystem::update(float timedelta)
	{
		if(timedelta>=0)
		{
			timeTo -= timedelta;
		}
		if(timeTo<=0)
		{
			nparts++;
			particles.resize(nparts);
			timeTo = spawnDelay;
		}
		for(int n = 0; n<nparts; n++)
		{
			particles[n].update(timedelta);
		}
	}

	void particlesystem::display(world& World)
	{
		for(int n = 0; n<nparts; n++)
		{
			particles[n].display(texid, World);
		}
	}
}