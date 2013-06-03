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
	if(TDML::Input.getKeyState('e'))
	{
		world1.dispModelMatInfo();
	}
	TDML::object& tv = world1.getObjectRef("tv");
	world1.setCamAngleZ(world1.getCamAngleZ()+world1.getAdjustedTime(0.05, 4));
	//tv.setYangle(tv.getYangle()+world1.getAdjustedTime(0.05, 4));
	tv.setScaleY(TDML::Math.larger(0.15, abs(TDML::Math.sin(world1.getTimer()/4.0))));
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
	//TDML::Shaders.dispInfo();
	//TDML::matrix4x4 m1 = TDML::matrix4x4();
	//m1.rotate(90,45,0,XYZ);
	//m1.translate(10,5,0);
	//m1.scale(1,5,1);
	//m1.dispInfo();
	//m1.rotate(90,0,0,XYZ);
	//m1.dispInfo();
	TDML::start();
	//system("pause");
	return 0;
}