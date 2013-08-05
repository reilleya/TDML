//particle_system.h
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#pragma once

#include "TDML.h"

namespace TDML
{
	class particle;
	class world;
	class particlesystem
	{
		private:
			std::string name;
			std::string fileName;
			std::vector<particle> particles;
			std::vector<int> recyclables;
			vector3d pos;
			vector3d posMin;
			vector3d posMax;
			vector3d dir;
			vector3d dirMin;
			vector3d dirMax;
			vector3d accel;
			vector3d accelMin;
			vector3d accelMax;
			float life;
			float lifeMin;
			float lifeMax;
			float size;
			float sizeMin;
			float sizeMax;
			int nparts;
			int nrecyclabes;
			float timeTo;
			float spawnDelay;
			GLuint texid;
			void createParticle();
			bool spawning;
			float spawnQuan;

		public:
			particlesystem();
			particlesystem(
				std::string Name, std::string FileName,
				vector3d Pos, vector3d PosMin, vector3d PosMax,
				vector3d Dir, vector3d DirMin, vector3d DirMax,
				vector3d Accel, vector3d AccelMin, vector3d AccelMax,
				float Life, float LifeMin, float LifeMax,
				float Size, float SizeMin, float SizeMax,
				float SpawnDelay, float SpawnQuan
				);
			void update(float timedelta);
			void display(world* World);
			std::string getName();
			void setName(std::string Name);
			void setPos(vector3d Pos);
			vector3d getPos();
			vector3d getPosVariation();
			vector3d getDir();
			vector3d getDirVariation();
			vector3d getAccel();
			vector3d getAccelVariation();
			void markRecyclable(int id);
			void setSpawning(bool creating);
			void dispInfo();
	};
}