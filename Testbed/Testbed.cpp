#include "TDML.h"

using namespace std;

TDML::world world1;
//TDML::menu menu1;

void exit()
{
	
}

void display ()
{
	world1.draw();
	//menu1.draw();
}


void animate()
{
	TDML::object& cube = world1.getObjectRef("tv");
	//cube.setWireframe(true);
	cube.setXangle(cube.getXangle()+0.2);
	cube.setYangle(cube.getYangle()+0.1);
	cube.setZangle(cube.getZangle()-0.3);
	if(TDML::Input.getMouseKeyPressed(LEFTMOUSE))
	{
		if(cube.getFrame()==2) cube.setFrame(0);
		else cube.setFrame(cube.getFrame()+1);
	}
	if(TDML::Input.getMouseKeyState(LEFTMOUSE))
	{
		cube.setScale(1.5, 1.5, 1.5);
	}
	else
	{
		cube.setScale(1, 1, 1);
	}
	world1.update();
	//TDML::Log.output(cube.getYangle()); TDML::Log.output("\n");
}

int main(int argc, char** argv)
{
	TDML::Log.setDebugMode(true);
	TDML::Log.output("Hello, World!\n");
	TDML::setupAll(&argc, argv, 500, 500, "3D Model Loader - Matrix Testbed", 0.5, 0.8, 1.0, display, animate, exit);
	world1 = TDML::loadWorld("world.wor");
	world1.setCamPosition(0, 5, 8);
	world1.setCamAngleX(-30);
	TDML::start();
	return 0;
}