#include "TDML.h"

using namespace std;

TDML::world world1;

void exit()
{
	
}

void display ()
{
	world1.draw();
}


void animate()
{
	world1.setCamPosition(0, 0, 10);
	TDML::object& tv = world1.getObjectRef("tv");
	tv.setYangle(tv.getYangle()+world1.getAdjustedTime(0.05, 2));
	tv.setZangle(tv.getZangle()+world1.getAdjustedTime(0.025, 2));
	if(TDML::Input.getMouseKeyPressed(WHEELUP))
	{
		tv.setScale(tv.getScaleX()*1.25, tv.getScaleY()*1.25, tv.getScaleZ()*1.25);
	}
	if(TDML::Input.getMouseKeyPressed(WHEELDOWN))
	{
		tv.setScale(tv.getScaleX()*0.8, tv.getScaleY()*0.8, tv.getScaleZ()*0.8);
	}
	if(TDML::Input.getSpecialKeyState(UP))
	{
		TDML::Log.output("boooonananananana\n");
	}
	world1.update();
}

int main(int argc, char** argv)
{
	TDML::Log.setDebugMode(true);
	TDML::enableCulling(false);
	TDML::Log.output("Hello, Worlds!\n");
	TDML::Log.output(TDML::Version.getFullVersion());
	TDML::setupAll(&argc, argv, 500, 500, "3D Model Loader - Lighting Testbed", 0.5, 0.8, 1.0, display, animate, exit);
	world1 = TDML::loadWorld("world.wor");
	TDML::start();
	return 0;
}