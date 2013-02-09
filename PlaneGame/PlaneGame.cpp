#include "TDML.h"
#include <math.h>

using namespace std;

TDML::world World1;
TDML::terrain Terrain1;

float speed = 0.016;
int framed = 0;
float zoom = 1.75;
float zoomlevel = 0;

bool dead = false;

void spin(TDML::object* me)
{
	me->setAngle(0, World1.getCamAngleY()+180, 0);
}

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
	framed++;
	if(framed == 30)
	{
		if(plane.getFrame()<3)
		{
			plane.setFrame(plane.getFrame()+1);
		}
		else
		{
			plane.setFrame(0);
		}
		framed = 0;
	}
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
		if(TDML::Input.getMouseKeyPressed(WHEELDOWN))
		{
			zoomlevel += 0.1;
		}
		if(TDML::Input.getMouseKeyState(WHEELUP))
		{
			if(zoomlevel > 0) zoomlevel -= 0.1;
		}
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
		
		World1.setCamX(plane.getX()+zoom*(pow(2, zoomlevel))*TDML::Math.sin(plane.getYangle()));
		World1.setCamZ(plane.getZ()+zoom*(pow(2, zoomlevel))*TDML::Math.cos(plane.getYangle()));
		World1.setCamY(plane.getY());
		World1.setCamAngleY(plane.getYangle());
		//if(World1.getHeightMapAt(World1.getCamX(), World1.getCamZ())>World1.getCamY())
		//{
		//	World1.setCamY(World1.getHeightMapAt(World1.getCamX(), World1.getCamZ())+10);
		//}
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
	TDML::Log.setDebugMode(false);
	TDML::setupAll(&argc, argv, 1024, 600, "TDML::Airplane", 0.5, 0.8, 1.0, display, animate, exit);
	TDML::enableCulling(true);
	World1 = TDML::loadWorld("Resources/World1/world.wor");
	Terrain1 = TDML::loadTerrain("Resources/World1/Heightmaps/islandheightsmall.hgt", "Resources/Common/Textures/height.png", 2500, 2);
	World1.setTerrain(Terrain1);
	for(int t = 0; t < 3000; t++)
	{
		TDML::object newtree = TDML::loadObject("Resources/World1/Tree/model.tdm");
		newtree.setMaterial(TDML::loadTexture("Resources/World1/Tree/material.mdf"));
		newtree.setX(TDML::Math.randomRange(-2000, 2000));
		newtree.setZ(TDML::Math.randomRange(-2000, 2000));
		newtree.setY(World1.getHeightMapAt(newtree.getX(), newtree.getZ()));
		newtree.setAngle(0,0,0);
		newtree.setScale(10,10,10);
		newtree.setType("tree");
		newtree.setName("tree");
		newtree.setFileName("Resources/World1/Tree/model.tdm");
		newtree.setWireframe(false);
		newtree.setVisible(true);
		newtree.generateVBO();
		newtree.setUpdateFunction(spin);
		World1.addObject(newtree);
	}
	TDML::Window.centerWindow();
	TDML::start();
	return 0;
}