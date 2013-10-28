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
		updateFuncSet = false;
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
		Log.output("\t\t\tTexture ID: "); Log.output((float)texid); Log.output("\n");
		Log.output("\t\t\tPosition: "); Log.output((float)posx); Log.output(", "); Log.output((float)posy); Log.output("\n");
		Log.output("\t\t\tDimensions: "); Log.output((float)width); Log.output(", "); Log.output((float)height); Log.output("\n");
	}

	void menuobject::draw()
	{
		bindBuffer(VBO, menuvboid);
		bindBuffer(TEX, texid);
		bindBuffer(VAO, menuvaoid);
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

	void menuobject::setPosX(float newPosX)
	{
		posx = newPosX;
	}
	 
	void menuobject::setPosY(float newPosY)
	{
		posy = newPosY;
	}

	void menuobject::setWidth(float newWidth)
	{
		width = newWidth;
	}
	 
	void menuobject::setHeight(float newHeight)
	{
		height = newHeight;
	}

	void menuobject::setUpdateFunction(void (*newupdatefunction)(menuobject* me))
	{
		updatefunction = *newupdatefunction;
		updateFuncSet = true;
	}

	bool menuobject::pointCollide(float x, float y)
	{
		return pointIn(posx, posy, width, height, x, y);
	}

	bool menuobject::rectCollide(float x, float y, float w, float h)
	{
		return pointIn(posx, posy, width, height, x, y) || pointIn(posx, posy, width, height, x+w, y) || pointIn(posx, posy, width, height, x, y+h) || pointIn(posx, posy, width, height, x+w, y+h) ||
			pointIn(x, y, w, h, posx, posy) || pointIn(x, y, w, h, posx+width, posy) || pointIn(x, y, w, h, posx, posy+height) || pointIn(x, y, w, h, posx+width, posy+height);
	}
}