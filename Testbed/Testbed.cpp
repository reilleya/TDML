#include "TDML.h"

using namespace std;

TDML::world world1;
TDML::menu menu1;
TDML::particlesystem PS1;

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
	//world1.setCamAngleY(world1.getCamAngleY()-(TDML::Input.getMouseX()-(TDML::Window.getWidth()/2)));
	if(TDML::Input.getKeyPressed('q'))
	{
		TDML::stop();
	}
	if(TDML::Input.getKeyPressed('l'))
	{
		TDML::Shaders.setUseLighting(!TDML::Shaders.getUseLighting());
	}
	if(TDML::Input.getKeyPressed('e'))
	{
		TDML::Log.output("test\n");
	}
	if(TDML::Input.getMouseKeyPressed(WHEELUP))
	{
		world1.setCamPosition(0, 0, world1.getCamZ()-0.5);
	}
	if(TDML::Input.getMouseKeyPressed(WHEELDOWN))
	{
		world1.setCamPosition(0, 0, world1.getCamZ()+0.5);
	}
	TDML::object& tv = world1.getObjectRef("tv");
	//world1.setCamAngleZ(world1.getCamAngleZ()+world1.getAdjustedTime(0.5, 4));
	tv.setYangle(tv.getYangle()+world1.getAdjustedTime(0.05, 4));
	//tv.setScaleY(TDML::Math.larger(0.15, abs(TDML::Math.sin(world1.getTimer()/4.0))));
	
	//TDML::Input.centerCursor();
	world1.update();
}

int main(int argc, char** argv)
{
	TDML::Log.setDebugMode(LOG_CONSOLEPOPUP);
	TDML::Shaders.setUseShaders(true);
	TDML::Shaders.setUseLighting(false);
	TDML::enableCulling(false);
	TDML::setupAll(&argc, argv, 500, 500, "3D Model Loader - Shader Testbed", 0.5, 0.8, 1.0, display, animate, exit);
	world1 = TDML::loadWorld("world.wor");
	menu1 = TDML::loadMenu("test.mnu");
	PS1 = TDML::particlesystem("ps1", "part.png", //image
				TDML::vector3d(0,0,0), TDML::vector3d(0,0,0), TDML::vector3d(0,0,0),//pos
				TDML::vector3d(0,0.0000,0), TDML::vector3d(-0.0000,0,-0.0000), TDML::vector3d(0.0000,0.00005,0.0000),//dir
				TDML::vector3d(0,0,0), TDML::vector3d(0,0,0), TDML::vector3d(0,0,0),//accel
				1000, -100, 100,//Life
				0.25, -0.01, 0.01, //Size
				10, 1); //Spawn Delay
	world1.addParticleSystem(PS1);
	TDML::object& tv = world1.getObjectRef("tv");
	world1.setCamPosition(0, 0, 2);
	TDML::start();
	return 0;
}