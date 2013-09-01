//particle.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	particle::particle()
	{
		pos = vector3d(0,0,0);
		dir = vector3d((float)0.005,(float)0.005,(float)-0.005);
		accel = vector3d(0,0,0);
		life = 1000;
		alive = true;
		zangle = Math.randomRangeFloat(0, 360);
	}

	particle::particle(vector3d Pos, vector3d Dir, vector3d Accel, float Life, float Size)
	{
		pos = Pos;
		dir = Dir;
		accel = Accel;
		life = Life;
		size = Size;
		alive = true;
		zangle = Math.randomRangeFloat(0, 360);
	}

	void particle::display(GLuint texid, world* World)
	{
		if(alive)
		{
			modelMatrix.translate(pos.x-(size/2), pos.y-(size/2), pos.z-(size/2));
			modelMatrix.scale(size, size, size); 
			modelMatrix.rotate(-World->getCamAngleX(), -World->getCamAngleY(), -World->getCamAngleZ(), invertRotationOrder(crotorder));
			modelMatrix.rotate(0, 0, zangle, crotorder);
			Shaders.setModelMat(modelMatrix.glForm());
			glBindBuffer(GL_ARRAY_BUFFER, menuvboid);
			glBindTexture(GL_TEXTURE_2D, texid);
			glBindVertexArray(menuvaoid);
			glDrawArrays(GL_QUADS, 0, 4);
			glBindVertexArray(0);
		}
	}

	bool particle::update(particlesystem* ps, float timedelta)
	{
		if(alive)
		{
			pos += (dir*timedelta);
			dir += (accel*timedelta);
			life -= timedelta;
			if(life <= 0)
			{
				alive = false;
			}
			return true;
		}
		else
		{
			return false;
		}
	}
}