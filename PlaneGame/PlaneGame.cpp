#include "TDML.h"
#include <math.h>

using namespace std;

TDML::world World1;
TDML::menu MainMenu;
TDML::terrain Terrain1;

float speed = 0.032;
int framed = 0;
float zoom = 1.75;
float zoomlevel = 0;

bool dead = false;

bool treeloadedID = false;
int treeid;
bool rockloadedID = false;
int rockid;

string state = "game";

void spin(TDML::object* me)
{
	me->setAngle(0, World1.getCamAngleY()+180, 0);
}

void load()
{
	World1 = TDML::loadWorld("Resources/World1/world.wor");
	Terrain1 = TDML::loadTerrain("Resources/World1/Heightmaps/islandheightsmall.hgt", "Resources/Common/Textures/height.png", 2500, 2);
	World1.setTerrain(Terrain1);
	for(int t = 0; t < 5000; t++)
	{
		TDML::object newtree = TDML::loadObject("Resources/World1/Tree/model.tdm");
		newtree.setMaterial(TDML::loadTexture("Resources/World1/Tree/material.mdf"));
		newtree.setX(TDML::Math.randomRange(-2000, 2000));
		newtree.setZ(TDML::Math.randomRange(-2000, 2000));
		newtree.setY(World1.getHeightMapAt(newtree.getX(), newtree.getZ()));
		while(newtree.getY()<-230 || newtree.getY() > 150)
		{
			newtree.setX(TDML::Math.randomRange(-2000, 2000));
			newtree.setZ(TDML::Math.randomRange(-2000, 2000));
			newtree.setY(World1.getHeightMapAt(newtree.getX(), newtree.getZ()));
		}
		newtree.setAngle(0,0,0);
		int root = TDML::Math.randomRange(2, 7);
		float factor = (float)TDML::Math.randomRange(75, 125) / 100.0;
		newtree.setScale(root,root*factor,root);
		newtree.setType("tree");
		newtree.setFrameDelay(0);
		newtree.setFileName("Resources/World1/Tree/model.tdm");
		newtree.setWireframe(false);
		newtree.setVisible(true);
		if(!treeloadedID)
		{
			newtree.generateVBO();
			treeid = newtree.getVBOId();
			treeloadedID = true;
		}
		else
		{
			newtree.setVBOId(treeid);
		}
		newtree.setUpdateFunction(spin);
		World1.addObject(newtree);
	}
	for(int t = 0; t < 500; t++)
	{
		TDML::object newrock = TDML::loadObject("Resources/World1/Rock/model.tdm");
		newrock.setMaterial(TDML::loadTexture("Resources/World1/Rock/material.mdf"));
		newrock.setX(TDML::Math.randomRange(-2000, 2000));
		newrock.setZ(TDML::Math.randomRange(-2000, 2000));
		newrock.setY(World1.getHeightMapAt(newrock.getX(), newrock.getZ())-2);
		while(newrock.getY()<-230 || newrock.getY() > 150)
		{
			newrock.setX(TDML::Math.randomRange(-2000, 2000));
			newrock.setZ(TDML::Math.randomRange(-2000, 2000));
			newrock.setY(World1.getHeightMapAt(newrock.getX(), newrock.getZ())-2);
		}
		newrock.setAngle(0,TDML::Math.randomRange(0, 360),0);
		int root = TDML::Math.randomRange(2, 7);
		float factor = (float)TDML::Math.randomRange(75, 125) / 100.0;
		newrock.setScale(root,root*factor,root);
		newrock.setType("tree");
		newrock.setFrameDelay(0);
		newrock.setFileName("Resources/World1/Rock/model.tdm");
		newrock.setWireframe(false);
		newrock.setVisible(true);
		if(!rockloadedID)
		{
			newrock.generateVBO();
			rockid = newrock.getVBOId();
			rockloadedID = true;
		}
		else
		{
			newrock.setVBOId(rockid);
		}
		//newrock.setUpdateFunction(spin);
		World1.addObject(newrock);
	}
}

void exit()
{
	TDML::Log.output("Exiting!\n");
}

void display ()
{
	if(state=="game")
	{
		World1.draw();
	}
	else
	{
		TDML::Log.output("Darwing\n");
		MainMenu.draw();
	}
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
	if(state=="game")
	{
		World1.update();
		TDML::object& plane = World1.getObjectRef("plane");

		if(World1.getHeightMapAt(plane.getX(),plane.getZ())>plane.getMinY())
		{
			TDML::Log.output("Underground!\n");
			plane.setVisible(false);
			dead = true;
		}

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
			if(World1.getHeightMapAt(World1.getCamX(), World1.getCamZ())>World1.getCamY()-0)
			{
				World1.setCamY(World1.getHeightMapAt(World1.getCamX(), World1.getCamZ())+0);
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
	else
	{
		if(TDML::Input.getMouseKeyPressed(LEFTMOUSE))
		{
			state="game";
			load();
		}
	}
}

int main(int argc, char** argv)
{
	//TDML::Log.setDebugMode(true);
	TDML::setupAll(&argc, argv, 1024, 600, "TDML::Airplane", 0.5, 0.8, 1.0, display, animate, exit);
	TDML::enableCulling(true);
	//MainMenu = TDML::loadMenu("Resources/MainMenu/menu.mnu");
	load();
	//TDML::Log.output("Loaded menu\n");
	TDML::Window.centerWindow();
	TDML::start();
	return 0;
}