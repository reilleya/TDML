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
		objects.resize(1);
		nobjs = 1;
	}

	void menu::draw()
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, Window.getWidth(), 0, Window.getHeight());
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		for(int i = 0; i < nobjs; i++)
		{
			glTranslatef(objects[i].getPosX(), (-objects[i].getPosY())+Window.getHeight(), 0);
			glScalef(objects[i].getWidth(), -objects[i].getHeight(), 0);
			objects[i].draw();
		}
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (float)Window.getWidth()/(float)Window.getHeight(), 1.0f, 10000.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void menu::testlod()
	{
		objects[0].loadTexture();
	}
}