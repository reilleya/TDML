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
	if(TDML::Input.getKeyPressed('l'))
	{
		TDML::Shaders.setUseLighting(!TDML::Shaders.getUseLighting());
	}
	TDML::object& tv = world1.getObjectRef("tv");
	tv.setYangle(tv.getYangle()+world1.getAdjustedTime(0.05, 4));
	world1.setCamPosition(0, 0, 10);
	world1.update();
}

int main(int argc, char** argv)
{
	TDML::Log.setDebugMode(true);
	TDML::Shaders.setUseShaders(true);
	TDML::Shaders.setUseLighting(true);
	TDML::enableCulling(false);
	TDML::setupAll(&argc, argv, 500, 500, "3D Model Loader - Shader Testbed", 0.5, 0.8, 1.0, display, animate, exit);
	world1 = TDML::loadWorld("world.wor");
	TDML::object& tv = world1.getObjectRef("tv");
	//tv.dispInfo();
	TDML::Shaders.dispInfo();
	TDML::start();
	return 0;
}