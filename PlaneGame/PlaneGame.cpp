#include "TDML.h"
#include <math.h>

using namespace std;

TDML::world World1;
TDML::terrain Terrain1;

float speed = 0.008;

bool dead = false;

void exit()
{
	TDML::Log.output("Exiting!\n");
}

void display ()
{
	World1.draw();
}

void respawn()
{
	TDML::object& plane = World1.getObjectRef("plane");
	dead = false;
	plane.setPosition(0, 100, 0);
	plane.setAngle(0,0,0);
	plane.setVisible(true);
	plane.dispInfo();
}

void animate()
{
	World1.update();
	TDML::object& plane = World1.getObjectRef("plane");
	if(World1.getHeightMapAt(plane.getX(),plane.getZ())>plane.getMinY())
	{
		TDML::Log.output("Underground!\n");
		plane.setVisible(false);
		dead = true;
	}

	/*if(World1.getObjAttribute("plane","yangle") > 360) World1.setObjAttribute("plane", "yangle", World1.getObjAttribute("plane","yangle")-360);
	if(World1.getObjAttribute("plane","yangle") < 0) World1.setObjAttribute("plane", "yangle", 360+World1.getObjAttribute("plane","yangle"));
	if(World1.getObjAttribute("plane","xangle") > 360) World1.setObjAttribute("plane", "xangle", World1.getObjAttribute("plane","xangle")-360);
	if(World1.getObjAttribute("plane","xangle") < 0) World1.setObjAttribute("plane", "xangle", 360+World1.getObjAttribute("plane","xangle"));
	if(World1.getObjAttribute("plane","zangle") > 360) World1.setObjAttribute("plane", "zangle", World1.getObjAttribute("plane","zangle")-360);
	if(World1.getObjAttribute("plane","zangle") < 0) World1.setObjAttribute("plane", "zangle", 360+World1.getObjAttribute("plane","zangle"));
	*/

	/*if(plane.getZangle()>90)
	{
		plane.setZangle(-90);
	}
	if(plane.getZangle()<-90)
	{
		plane.setZangle(90);
	}*/
	if(!dead)
	{
		if(TDML::Input.getSpecialKeyState(LEFT)) 
		{
			plane.setZangle(plane.getZangle()+0.025*World1.getTimeDelta());
		}
		if(TDML::Input.getSpecialKeyState(RIGHT))
		{
			plane.setZangle(plane.getZangle()-0.025*World1.getTimeDelta());
		}
		if(TDML::Input.getSpecialKeyState(UP))
		{
			plane.setXangle(plane.getXangle()+0.02*World1.getTimeDelta());
		}
		if(TDML::Input.getSpecialKeyState(DOWN))
		{
			plane.setXangle(plane.getXangle()-0.02*World1.getTimeDelta());
		}

		plane.setYangle(plane.getYangle()+((plane.getZangle()/5000)*World1.getTimeDelta()));
		plane.setX(plane.getX()-World1.getTimeDelta()*speed*TDML::Math.sin(plane.getYangle())*TDML::Math.cos(plane.getXangle()));
		plane.setZ(plane.getZ()-World1.getTimeDelta()*speed*TDML::Math.cos(plane.getYangle())*TDML::Math.cos(plane.getXangle()));
		plane.setY(plane.getY()+World1.getTimeDelta()*speed*TDML::Math.sin(plane.getXangle()));
		plane.setY(plane.getY()-(World1.getTimeDelta()/1000));
		
		World1.setCamX(plane.getX()+3*TDML::Math.sin(plane.getYangle()));
		World1.setCamZ(plane.getZ()+3*TDML::Math.cos(plane.getYangle()));
		World1.setCamY(plane.getY());
		World1.setCamAngleY(plane.getYangle());
		if(World1.getHeightMapAt(World1.getCamX(), World1.getCamZ())>World1.getCamY())
		{
			World1.setCamY(World1.getHeightMapAt(World1.getCamX(), World1.getCamZ()));
		}
	}
	else
	{
		if(TDML::Input.getMouseKeyPressed(LEFTMOUSE))
		{
			respawn();
		}
	}
	
}

int main(int argc, char** argv)
{
	TDML::Log.setDebugMode(true);
	TDML::setupAll(&argc, argv, 1024, 600, "TDML::Airplane", 0.5, 0.8, 1.0, display, animate, exit);
	TDML::enableCulling(true);
	TDML::Log.outputWindow("Loading, please wait.");
	TDML::Log.output("Loading World\n");
	World1 = TDML::loadWorld("Resources/World1/world.wor");
	Terrain1 = TDML::loadTerrain("Resources/World1/Heightmaps/test.hgt", "Resources/Common/Textures/height.png", 2500, 3);
	World1.setTerrain(Terrain1);
	TDML::Log.output("Done.\n");
	TDML::Window.centerWindow();
	TDML::start();
	return 0;
}