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
		dir = vector3d(0.005,0.005,-0.005);
		accel = vector3d(0,0,0);
		life = 1000;
		alive = true;
		zangle = Math.randomRange(0, 360);
	}

	particle::particle(vector3d Pos, vector3d Dir, vector3d Accel, float Life, float Size)
	{
		pos = Pos;
		dir = Dir;
		accel = Accel;
		life = Life;
		size = Size;
		alive = true;
		zangle = Math.randomRange(0, 360);
	}

	void particle::display(GLuint texid, world* World)
	{
		if(alive)
		{
			modelMatrix.loadIdentity();
			//pos.dispInfo();
			modelMatrix.translate(pos.x-(size/2), pos.y-(size/2), pos.z-(size/2));
				//glTranslatef(pos.x-(size/2), pos.y-(size/2), pos.z-(size/2));
			modelMatrix.scale(size, size, size); 
				//glScalef(size, size, size);
			modelMatrix.rotate(World->getCamAngleX(), World->getCamAngleY(), World->getCamAngleZ(), crotorder);
				//glRotatef(World->getCamAngleY(), 0, 1, 0);
				//glRotatef(World->getCamAngleX(), 1, 0, 0);
				//glRotatef(World->getCamAngleZ(), 0, 0, 1);
			//modelMatrix.rotate(0, 0, zangle, crotorder);
				//glRotatef(zangle, 0, 0, 1);
			//glRotatef(World->getCamAngleZ(), 0, 0, 1);
			glBindBuffer(GL_ARRAY_BUFFER, menuvboid);
			glBindTexture(GL_TEXTURE_2D, texid);
			glBindVertexArray(menuvaoid);
			glDrawArrays(GL_QUADS, 0, 4);
			//glRotatef(-zangle, 0, 0, 1);
			modelMatrix.rotate(-World->getCamAngleX(), -World->getCamAngleY(), -World->getCamAngleZ(), crotorder);
				//glRotatef(-World->getCamAngleZ(), 0, 0, 1);
				//glRotatef(-World->getCamAngleX(), 1, 0, 0);
				//glRotatef(-World->getCamAngleY(), 0, 1, 0);
			modelMatrix.scale((1/size), (1/size), (1/size)); 
				//glScalef((1/size), (1/size), (1/size));
			modelMatrix.translate(-(pos.x-(size/2)), -(pos.y-(size/2)), -(pos.z-(size/2)));
				//glTranslatef(-(pos.x-(size/2)), -(pos.y-(size/2)), -(pos.z-(size/2)));
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