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
	class particle
	{
		private:
			vector3d pos;
			vector3d dir;
			vector3d accel;
			float life;
			GLuint vboid;

		public:
			particle(vector3d pos, vector3d dir, vector3d accel, float life);
			void display();
			void update();
			vector3d getPos();
			vector3d getDir();
			vector3d getAccel();
	};
}