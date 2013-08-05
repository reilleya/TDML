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
	void particlesystem::createParticle()
	{
		int id = 0;
		if(nrecyclabes>0)
		{
			id = recyclables[recyclables.size()-1];
			recyclables.resize(recyclables.size()-1);
			nrecyclabes--;
		}
		else
		{
			nparts++;	
			particles.resize(nparts);
			id = nparts-1;
		}
		particles[id] = particle(
			vector3d(
				pos.x+Math.randomRange(posMin.x, posMax.x), 
				pos.y+Math.randomRange(posMin.y, posMax.y), 
				pos.z+Math.randomRange(posMin.z, posMax.z)),
			vector3d(
				dir.x+Math.randomRange(dirMin.x, dirMax.x), 
				dir.y+Math.randomRange(dirMin.y, dirMax.y), 
				dir.z+Math.randomRange(dirMin.z, dirMax.z)),
			vector3d(
				accel.x+Math.randomRange(accelMin.x, accelMax.x), 
				accel.y+Math.randomRange(accelMin.y, accelMax.y), 
				accel.z+Math.randomRange(accelMin.z, accelMax.z)),
				life + Math.randomRange(lifeMin, lifeMax),
				size + Math.randomRange(sizeMin, sizeMax)
			);
	}

	particlesystem::particlesystem()
	{
		
	}

	particlesystem::particlesystem(string Name, string FileName, 
		vector3d Pos, vector3d PosMin,  vector3d PosMax, 
		vector3d Dir, vector3d DirMin, vector3d DirMax, 
		vector3d Accel, vector3d AccelMin, vector3d AccelMax, 
		float Life, float LifeMin, float LifeMax, 
		float Size, float SizeMin, float SizeMax,
		float SpawnDelay, float SpawnQuan)
	{
		name = Name;
		pos = Pos;
		posMin = PosMin;
		posMax = PosMax;
		dir = Dir;
		dirMin = DirMin;
		dirMax = DirMax;
		accel = Accel;
		accelMin = AccelMin;
		accelMax = AccelMax;
		life = Life;
		lifeMin = LifeMin;
		lifeMax = LifeMax;
		size = Size;
		sizeMin = SizeMin;
		sizeMax = SizeMax;
		spawnDelay = SpawnDelay;
		timeTo = SpawnDelay;
		spawnQuan = SpawnQuan;
		texid = loadTextureData(FileName);
		fileName = FileName;
		Log.output("Created particle system\n");
		nparts = 0;
		nrecyclabes = 0;
		spawning = true;
	}

	void particlesystem::update(float timedelta)
	{
		if(timedelta>=0)
		{
			timeTo -= timedelta;
		}
		if(timeTo<=0)
		{
			if(spawning)
			{
				for(int i = 0; i < spawnQuan; i++)
				{
					createParticle();
				}
			}
			timeTo = spawnDelay;
		}
		for(int n = 0; n<nparts; n++)
		{
			if(particles[n].update(this, timedelta)==false)
			{
				/*if(nrecyclabes<(nparts*1.5))*/ markRecyclable(n);
				/*else
				{
					particles.erase(particles.begin()+n);
					nparts--;
				}*/
			}
		}
	}

	void particlesystem::display(world* World)
	{
		glDisable(GL_DEPTH_TEST);
		for(int n = 0; n<nparts; n++)
		{
			particles[n].display(texid, World);
		}
		glEnable(GL_DEPTH_TEST);
	}

	string particlesystem::getName()
	{
		return name;
	}

	void particlesystem::setName(string Name)
	{
		name = Name;
	}

	vector3d particlesystem::getPos()
	{
		return pos;
	}

	void particlesystem::setPos(vector3d Pos)
	{
		pos = Pos;
	}

	void particlesystem::markRecyclable(int id)
	{
		recyclables.resize(recyclables.size()+1);
		recyclables[recyclables.size()-1]=id;
		nrecyclabes++;
	}

	void particlesystem::setSpawning(bool creating)
	{
		spawning = creating;
	}

	void particlesystem::dispInfo()
	{
		Log.output("Particle System:\n");
		Log.output("\tName: "); Log.output(name); Log.output("\n");
		Log.output("\tImage: "); Log.output(fileName); Log.output("\n");
		Log.output("\tNumber of Particles: "); Log.output(particles.size()); Log.output("\n");
		Log.output("\tNumber of Particles (Recyclable): "); Log.output(recyclables.size()); Log.output("\n");
	}
}