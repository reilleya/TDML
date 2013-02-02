#include "TDML.h"

using namespace std;

TDML::world world1;
TDML::menu menu1;

void exit()
{
	
}

void display ()
{
	world1.draw();
	menu1.draw();
}


void animate()
{
	TDML::object& cube = world1.getObjectRef("tv");
	cube.setYangle(cube.getYangle()+0.05);
	if(TDML::Input.getMouseKeyPressed(LEFTMOUSE))
	{
		if(cube.getFrame()==2) cube.setFrame(0);
		else cube.setFrame(cube.getFrame()+1);
	}
	world1.update();
}

int main(int argc, char** argv)
{
	TDML::Log.setDebugMode(true);
	TDML::enableCulling(false);
	TDML::setupAll(&argc, argv, 500, 500, "3D Model Loader - Texture Testbed", 0.5, 0.8, 1.0, display, animate, exit);
	world1 = TDML::loadWorld("world.wor");
	menu1 = TDML::loadMenu("test2.mnu");
	world1.setCamPosition(0, 0, 15);
	TDML::start();
	return 0;
}