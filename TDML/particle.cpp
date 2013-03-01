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
		dir = vector3d(0,0,0);
		accel = vector3d(0,0,0);
		life = 1000;
	}

	particle::particle(vector3d Pos, vector3d Dir, vector3d Accel, float Life)
	{
		pos = Pos;
		dir = Dir;
		accel = Accel;
		life = Life;
	}

	void particle::display(GLuint texid, world& World)
	{
		Log.output("dispin\n");
		glLoadIdentity();
		glRotatef(World.getCamAngleY(), 0, 1, 0);
		glRotatef(World.getCamAngleX(), 1, 0, 0);
		glRotatef(World.getCamAngleZ(), 0, 0, 1);
		glBindBuffer(GL_ARRAY_BUFFER, menuvboid);
		glBindTexture(GL_TEXTURE_2D, texid);
		glVertexPointer(3, GL_FLOAT, 0, 0);
		glTexCoordPointer(2, GL_FLOAT, 0, (GLvoid*)(12 * sizeof(GLfloat)));
		glDrawArrays(GL_QUADS, 0, 4);
		glLoadIdentity();
	}

	void particle::update(float timedelta)
	{
		pos += dir;
		dir += accel;
		life -= timedelta;
		if(life <= 0)
		{

		}
	}
}