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
	//menu1.draw();
}

void animate()
{
	//world1.setCamAngleY(world1.getCamAngleY()-(TDML::Input.getMouseX()-(TDML::Window.getWidth()/2)));
	if(TDML::Input.getKeyPressed('q'))
	{
		TDML::stop();
	}
	if(TDML::Input.getKeyPressed('l'))
	{
		TDML::Shaders.setUseLighting(!TDML::Shaders.getUseLighting());
	}
	if(TDML::Input.getKeyState('e'))
	{
		world1.dispModelMatInfo();
	}
	TDML::object& tv = world1.getObjectRef("tv");
	//world1.setCamAngleZ(world1.getCamAngleZ()+world1.getAdjustedTime(0.5, 4));
	tv.setYangle(tv.getYangle()+world1.getAdjustedTime(0.05, 4));
	//tv.setScaleY(TDML::Math.larger(0.15, abs(TDML::Math.sin(world1.getTimer()/4.0))));
	world1.setCamPosition(0, 0, 4);
	//TDML::Input.centerCursor();
	world1.update();
}

int main(int argc, char** argv)
{
	TDML::Log.setDebugMode(true);
	TDML::Shaders.setUseShaders(true);
	TDML::Shaders.setUseLighting(false);
	TDML::enableCulling(false);
	TDML::setupAll(&argc, argv, 500, 500, "3D Model Loader - Shader Testbed", 0.5, 0.8, 1.0, display, animate, exit);
	world1 = TDML::loadWorld("world.wor");
	menu1 = TDML::loadMenu("test2.mnu");
	TDML::object& tv = world1.getObjectRef("tv");
	TDML::start();
	return 0;
}