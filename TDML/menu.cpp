//menu.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	menu::menu()
	{
		objects.resize(0);
		nobjs = 0;
	}

	void menu::dispInfo()
	{
		Log.output((float)nobjs); Log.output("\n");
	}

	void menu::draw()
	{
		modelMatrix.loadIdentity();
		projMatrix.loadIdentity();
		//projMatrix.ortho2D(0, 0, Window.getWidth(), Window.getHeight());
		Shaders.setProjMat(projMatrix.glForm());
		for(int i = 0; i < nobjs; i++)
		{
			//Log.output(i); Log.output("\n");
			modelMatrix.translate((objects[i].getPosX()/Window.getWidth())-1.0, 1.0-(objects[i].getPosY()/(Window.getHeight()/2)), 0);
			//glTranslatef((GLfloat)objects[i].getPosX(), (GLfloat)(-objects[i].getPosY())+Window.getHeight(), 0);
			modelMatrix.scale(objects[i].getWidth()/(Window.getWidth()/2.0), -objects[i].getHeight()/(Window.getHeight()/2.0), 0);
			//glScalef((GLfloat)objects[i].getWidth(), (GLfloat)-objects[i].getHeight(), 0);
			//modelMatrix.dispInfo();
			Shaders.setModelMat(modelMatrix.glForm());
			objects[i].draw();
			modelMatrix.loadIdentity();
		}
		projMatrix.loadIdentity();
		projMatrix.perspective(Config.getFOV(), (float)Window.getWidth()/(float)Window.getHeight(), 1.000f, 1000000.0f);
		Shaders.setProjMat(projMatrix.glForm());
	}

	void menu::loadTextures()
	{
		for(int obj = 0; obj < nobjs; obj++)
		{
			objects[obj].loadTexture();
		}
	}

	void menu::addObject(menuobject newobj)
	{
		nobjs++;
		objects.resize(nobjs);
		objects[nobjs-1] = newobj;
	}
}