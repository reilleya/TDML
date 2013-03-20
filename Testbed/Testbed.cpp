#include "TDML.h"

using namespace std;

TDML::world world1;
float xpos = 0;
float zpos = 0;


void exit()
{
	
}

void display ()
{
	world1.draw();
}


void animate()
{
	world1.setCamPosition(xpos, world1.getHeightMapAt(xpos,zpos)+1, zpos);

	if(TDML::Input.getKeyState('w'))
	{
		zpos-=world1.getAdjustedTime(0.1, 5);

	}
	if(TDML::Input.getKeyState('s'))
	{
		zpos+=world1.getAdjustedTime(0.1, 5);
	}
	if(TDML::Input.getKeyState('a'))
	{
		xpos-=world1.getAdjustedTime(0.1, 5);
	}
	if(TDML::Input.getKeyState('d'))
	{
		xpos+=world1.getAdjustedTime(0.1, 5);
	}


	if(TDML::Input.getKeyState('b'))
	{
		TDML::stop();
	}
	TDML::Log.output(TDML::Input.getMouseX()-((float)TDML::Window.getWidth()/2)); TDML::Log.output("\n");
	//TDML::Log.output(TDML::Input.getMouseY()-((float)TDML::Window.getHeight()/2)); TDML::Log.output("\n");
	world1.setCamAngleY(world1.getCamAngleY()-(TDML::Input.getMouseX()-((float)TDML::Window.getWidth()/2)));
	world1.setCamAngleX(world1.getCamAngleX()+(TDML::Input.getMouseY()-((float)TDML::Window.getHeight()/2)));
	//if(!TDML::Input.getKeyState('r'))TDML::Input.centerCursor();
	world1.update();
	//world1.setCamAngleY((((float)TDML::Input.getMouseX()/(float)TDML::Window.getWidth())-0.5)*180.0);
	//world1.setCamAngleX((((float)TDML::Input.getMouseY()/(float)TDML::Window.getHeight())-0.5)*180.0);
}

int main(int argc, char** argv)
{
	TDML::Log.setDebugMode(true);
	TDML::enableCulling(false);
	TDML::Log.output("Hello, Worlds!\n");
	TDML::Log.output(TDML::Version.getFullVersion());
	TDML::setupAll(&argc, argv, 500, 500, "3D Model Loader - Particle Testbed", 0.5, 0.8, 1.0, display, animate, exit);
	world1.setCamPosition(0,0,0);
	world1.setTerrain(TDML::loadTerrain("terrible.hgt", "height1.png", 500, 0.25));
	TDML::start();
	return 0;
}