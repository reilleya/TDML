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
			std::vector<particle> particles;
			vector3d pos;
			vector3d posVariation;
			vector3d dir;
			vector3d dirVariation;
			vector3d accel;
			vector3d accelVariation;
			float life;
			float lifeVariation;
			int nparts;
			float timeTo;
			float spawnDelay;
			GLuint texid;

		public:
			particlesystem();
			particlesystem(
				std::string FileName,
				vector3d Pos, vector3d PosVariation,
				vector3d Dir, vector3d DirVariation,
				vector3d Accel, vector3d AccelVariation,
				float Life, float LifeVariation, 
				float SpawnDelay
				);
			void update(float timedelta);
			void display(world& World);
			vector3d getPos();
			vector3d getPosVariation();
			vector3d getDir();
			vector3d getDirVariation();
			vector3d getAccel();
			vector3d getAccelVariation();
	};
}