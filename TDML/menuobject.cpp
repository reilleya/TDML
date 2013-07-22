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
		width = 0;
		height = 0;
		texname = ""; 
		texid = 0;
	}

	void menuobject::draw()
	{
		glBindBuffer(GL_ARRAY_BUFFER, menuvboid);
		glBindTexture(GL_TEXTURE_2D, texid);

		glEnableVertexAttribArray(0); // Position
		glEnableVertexAttribArray(2); // Texture Coords
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Position
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(12 * sizeof(GLfloat))); // Texture Coords

		//glVertexPointer(3, GL_FLOAT, 0, 0);
		//glTexCoordPointer(2, GL_FLOAT, 0, (GLvoid*)(12 * sizeof(GLfloat)));
		glDrawArrays(GL_QUADS, 0, 4);
	}

	void menuobject::loadTexture()
	{
		texid = loadTextureData(texname);
	}

	float menuobject::getPosX()
	{
		return posx;
	}
	
	float menuobject::getPosY()
	{
		return posy;
	}
	
	float menuobject::getWidth()
	{
		return width;
	}
	
	float menuobject::getHeight()
	{
		return height;
	}

	void menuobject::setTexture(string newTex)
	{
		texname = newTex;
	}

	void menuobject::setPosX(int newPosX)
	{
		posx = newPosX;
	}
	 
	void menuobject::setPosY(int newPosY)
	{
		posy = newPosY;
	}

	void menuobject::setWidth(int newWidth)
	{
		width = newWidth;
	}
	 
	void menuobject::setHeight(int newHeight)
	{
		height = newHeight;
	}
}