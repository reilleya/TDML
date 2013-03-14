//particle.h
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#pragma once

#include "TDML.h"

namespace TDML
{
	class world;

	class particle
	{
		private:
			vector3d pos;
			vector3d dir;
			vector3d accel;
			float life;
			GLuint vboid;
			bool alive;
			float zangle;
			float size;

		public:
			particle();
			particle(vector3d Pos, vector3d Dir, vector3d Accel, float Life, float Size);
			void display(GLuint texid, world* World);
			bool update(particlesystem* ps, float timedelta);
			vector3d getPos();
			vector3d getDir();
			vector3d getAccel();
			bool getAlive();
	};
}