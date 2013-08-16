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

	menu::menu(std::string filename)
	{
		fileName = filename;
		objects.resize(0);
		nobjs = 0;
	}

	void menu::update()
	{
		for(int mobj = 0; mobj < nobjs; mobj++)
		{
			objects[mobj].update();
		}
	}

	void menu::dispInfo()
	{
		Log.output("Menu:\n");
		Log.output("\tFilename: "+fileName+"\n");
		Log.output("\tNumber of Objects: " ); Log.output((float)nobjs); Log.output("\n");
		Log.output("\tObject Information: \n");
		for(int mniter = 0; mniter<nobjs; mniter++)
		{
			objects[mniter].dispInfo();
		}
	}

	void menu::draw()
	{
		modelMatrix.loadIdentity();
		projMatrix.loadIdentity();
		Shaders.setProjMat(projMatrix.glForm());
		glDisable(GL_DEPTH_TEST);
		for(int i = 0; i < nobjs; i++)
		{
			modelMatrix.translate(((objects[i].getPosX()/(Window.getWidth()/2))-1.0), 1.0-(objects[i].getPosY()/(Window.getHeight()/2)), 0);
			modelMatrix.scale(objects[i].getWidth()/(Window.getWidth()/2.0), -objects[i].getHeight()/(Window.getHeight()/2.0), 0);
			Shaders.setModelMat(modelMatrix.glForm());
			objects[i].draw();
			modelMatrix.loadIdentity();
		}
		glEnable(GL_DEPTH_TEST);
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

	menuobject& menu::getObjectRefByName(std::string name)
	{
		int id = getObjectIDByName(name);
		return objects.at(id);
	}

	int menu::getObjectIDByName(std::string name)
	{
		for(int testid = 0; testid < nobjs; testid++)
		{
			if(objects[testid].getName()==name)
			{
				return testid;
			}
		}

		Message.errorMessage("Found no object with name "+name+" in menu loaded from file "+fileName, "Menu Error"); 

		return -1;
	}
}