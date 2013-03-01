#include "TDML.h"

using namespace std;

TDML::world world1;
TDML::particlesystem ps1;

void exit()
{
	
}

void display ()
{
	world1.draw();
	ps1.display(world1);
}


void animate()
{
	world1.update();
	ps1.update(world1.getTimeDelta());
}

int main(int argc, char** argv)
{
	TDML::Log.setDebugMode(true);
	TDML::enableCulling(false);
	TDML::Log.output("Hello, World!\n");
	TDML::setupAll(&argc, argv, 500, 500, "3D Model Loader - Particle Testbed", 0.5, 0.8, 1.0, display, animate, exit);
	//world1 = TDML::loadWorld("world.wor");
	ps1 = TDML::particlesystem("part.png", //image
							   TDML::vector3d(0,0,0), TDML::vector3d(0,0,0), //pos
							   TDML::vector3d(0,0,0), TDML::vector3d(0,0,0), //dir
							   TDML::vector3d(0,0,0), TDML::vector3d(0,0,0), //accel
							   1000, 0, //Life
							   10); //Spawn Delay
	world1.setCamPosition(0, 0, 8);
	//world1.setCamAngleX(-30);
	TDML::start();
	return 0;
}