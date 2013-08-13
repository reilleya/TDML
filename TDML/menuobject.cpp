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

	void menuobject::update()
	{
		if(updateFuncSet) updatefunction(this);
	}

	std::string menuobject::getName()
	{
		return name;
	}

	void menuobject::setName(std::string newName)
	{
		name = newName;
	}

	void menuobject::dispInfo()
	{
		Log.output("\t\tMenu Object:\n");
		Log.output("\t\t\tName: "+name+"\n");
		Log.output("\t\t\tImage Name: "+texname+"\n"); 
		Log.output("\t\t\tTexture ID: "); Log.output(texid); Log.output("\n");
		Log.output("\t\t\tPosition: "); Log.output(posx); Log.output(", "); Log.output(posy); Log.output("\n");
		Log.output("\t\t\tDimensions: "); Log.output(width); Log.output(", "); Log.output(height); Log.output("\n");
	}

	void menuobject::draw()
	{
		glBindBuffer(GL_ARRAY_BUFFER, menuvboid);
		glBindTexture(GL_TEXTURE_2D, texid);
		glBindVertexArray(menuvaoid);
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