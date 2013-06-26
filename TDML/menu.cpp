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
		//BEGIN:THIS SECTION IS BAAAAD
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, Window.getWidth(), 0, Window.getHeight());
		glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		//END:THIS SECTION IS BAAAAD
		for(int i = 0; i < nobjs; i++)
		{
			//Log.output(i); Log.output("\n");
			modelMatrix.translate(objects[i].getPosX(), (-objects[i].getPosY())+Window.getHeight(), 0);
			//glTranslatef((GLfloat)objects[i].getPosX(), (GLfloat)(-objects[i].getPosY())+Window.getHeight(), 0);
			modelMatrix.scale(objects[i].getWidth(), -objects[i].getHeight(), 0);
			//glScalef((GLfloat)objects[i].getWidth(), (GLfloat)-objects[i].getHeight(), 0);
			Shaders.setModelMat(modelMatrix.glForm());
			Shaders.setMenuObject(true);
			objects[i].draw();
			modelMatrix.loadIdentity();
		}
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(Config.getFOV(), (float)Window.getWidth()/(float)Window.getHeight(), 1.0f, 10000.0f);
		glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
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