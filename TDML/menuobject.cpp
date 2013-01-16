//menuobject.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	menuobject::menuobject()
	{
		posx = 0;
		posy = 0;
		width = 256;
		height = 64;
		texname = "play_button.png"; 
		texid = 0;
	}

	void menuobject::draw()
	{
		glBindBuffer(GL_ARRAY_BUFFER, menuvboid);
		glBindTexture(GL_TEXTURE_2D, texid);
		glVertexPointer(3, GL_FLOAT, 0, 0);
		glTexCoordPointer(2, GL_FLOAT, 0, (GLvoid*)(12 * sizeof(GLfloat)));
		glDrawArrays(GL_QUADS, 0, 4);
	}

	void menuobject::loadTexture()
	{
		texid = loadTextureData(texname);
	}

	int menuobject::getPosX()
	{
		return posx;
	}
	
	int menuobject::getPosY()
	{
		return posy;
	}
	
	int menuobject::getWidth()
	{
		return width;
	}
	
	int menuobject::getHeight()
	{
		return height;
	}
}