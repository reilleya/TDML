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
}


void animate()
{
	world1.update();
	//world1.getParticleSystemRef("baofbndo");
	//world1.setCamAngleX(world1.getCamAngleX());
}

int main(int argc, char** argv)
{
	TDML::Log.setDebugMode(true);
	TDML::enableCulling(false);
	TDML::Log.output("Hello, Worlds!\n");
	TDML::Log.output(TDML::Version.getFullVersion());
	TDML::setupAll(&argc, argv, 500, 500, "3D Model Loader - Particle Testbed", 0.5, 0.8, 1.0, display, animate, exit);
	//world1 = TDML::loadWorld("world.wor");
	ps1 = TDML::particlesystem("ps1","part.png", //image
							   TDML::vector3d(0,0,0), TDML::vector3d(-0.5,-0.5,-0.5), TDML::vector3d(0.5,0.5,0.5),//pos
							   TDML::vector3d(0,0.0025,0), TDML::vector3d(-0.001,0,-0.001), TDML::vector3d(0.001,0.0005,0.001),//dir
							   TDML::vector3d(0,0,0), TDML::vector3d(0,0,0), TDML::vector3d(0,0,0),//accel
							   0.025, -0.005, 0.005,
							   1000, 0, 0,//Life
							   1, 15); //Spawn Delay
	world1.setCamPosition(0, 0, 8);
	world1.addParticleSystem(ps1);
	TDML::loadTexture("dofinadofin.mdf");
	TDML::start();
	return 0;
}