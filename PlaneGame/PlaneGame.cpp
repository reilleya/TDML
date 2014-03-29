#include "TDML.h"
//#include <math.h>

using namespace std;

TDML::world World1;
TDML::menu MainMenu;
TDML::terrain Terrain1;
TDML::object test;
TDML::particlesystem crashSmoke;

float camy = 0;

float camyrot = 0;
float camxrot = 0;
bool previouslypressed = false;

float speed = 0.032;
int framed = 0;
float zoom = 1.75;
float zoomlevel = 0;

bool dead = false;

bool treeloadedID = false;
int treeid;
int treevao;
bool rockloadedID = false;
int rockid;
int rockvao;

string state = "menu";

void spin(TDML::object* me)
{
	me->setAngle(0, World1.getCamAngleY()+180, 0);
}

void load()
{
	World1 = TDML::loadWorld("Resources/World1/world.wor");
	Terrain1 = TDML::loadTerrain("Resources/World1/Heightmaps/Smooth.hgt", "Resources/Common/Textures/height.png", 2500, 2);
	World1.setTerrain(Terrain1);
	for(int t = 0; t < 000; t++)
	{
		TDML::object newtree = TDML::loadObject("Resources/World1/Tree/model.tdm");
		newtree.setMaterial(TDML::loadTexture("Resources/World1/Tree/material.mdf"));
		newtree.setX(TDML::Math.randomRangeFloat(-2000, 2000));
		newtree.setZ(TDML::Math.randomRangeFloat(-2000, 2000));
		newtree.setY(World1.getHeightMapAt(newtree.getX(), newtree.getZ()));
		while(newtree.getY()<-230 || newtree.getY() > 150)
		{
			newtree.setX(TDML::Math.randomRangeFloat(-2000, 2000));
			newtree.setZ(TDML::Math.randomRangeFloat(-2000, 2000));
			newtree.setY(World1.getHeightMapAt(newtree.getX(), newtree.getZ()));
		}
		newtree.setAngle(0,0,0);
		int root = TDML::Math.randomRangeInt(2, 7);
		float factor = TDML::Math.randomRangeFloat(75, 125) / 100.0;
		newtree.setScale(root,root*factor,root);
		newtree.setType("tree");
		newtree.setFrameDelay(0);
		newtree.setFileName("Resources/World1/Tree/model.tdm");
		newtree.setWireframe(false);
		newtree.setVisible(true);
		newtree.setAdjustBB(false);
		if(!treeloadedID)
		{
			newtree.generateVBO();
			treeid = newtree.getVBOId();
			treevao = newtree.getVAOId();
			treeloadedID = true;
		}
		else
		{
			newtree.setVBOId(treeid);
			newtree.setVAOId(treevao);
		}
		newtree.setUpdateFunction(spin);
		World1.addObject(newtree);
	}
	for(int t = 0; t < 00; t++)
	{
		TDML::object newrock = TDML::loadObject("Resources/World1/Rock/model.tdm");
		newrock.setMaterial(TDML::loadTexture("Resources/World1/Rock/material.mdf"));
		newrock.setX(TDML::Math.randomRangeFloat(-2000, 2000));
		newrock.setZ(TDML::Math.randomRangeFloat(-2000, 2000));
		newrock.setY(World1.getHeightMapAt(newrock.getX(), newrock.getZ())-2);
		while(newrock.getY()<-230 || newrock.getY() > 150)
		{
			newrock.setX(TDML::Math.randomRangeFloat(-2000, 2000));
			newrock.setZ(TDML::Math.randomRangeFloat(-2000, 2000));
			newrock.setY(World1.getHeightMapAt(newrock.getX(), newrock.getZ())-2);
		}
		newrock.setAngle(0,TDML::Math.randomRangeFloat(0, 360),0);
		int root = TDML::Math.randomRangeInt(2, 7);
		float factor = (float)TDML::Math.randomRangeFloat(75, 125) / 100.0;
		newrock.setScale(root,root*factor,root);
		newrock.setType("tree");
		newrock.setFrameDelay(0);
		newrock.setFileName("Resources/World1/Rock/model.tdm");
		newrock.setWireframe(false);
		newrock.setVisible(true);
		newrock.setAdjustBB(false);
		if(!rockloadedID)
		{
			newrock.generateVBO();
			rockid = newrock.getVBOId();
			rockvao = newrock.getVAOId();
			rockloadedID = true;
		}
		else
		{
			newrock.setVBOId(rockid);
			newrock.setVAOId(rockvao);
		}
		World1.addObject(newrock);
	}
	TDML::object& test = World1.getObjectRef("plane");
	test.dispInfo();
	TDML::Log.output("Done Loading!");
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
		MainMenu.draw();
	}
}

void respawn()
{
	TDML::object& plane = World1.getObjectRef("plane");
	dead = false;
	plane.setPosition(0, 200, 0);
	plane.setAngle(0,0,0);
	plane.setVisible(true);
	plane.dispInfo();
	crashSmoke.setSpawning(false);
	zoomlevel = 0;
}

void animate()
{
	if(state=="game")
	{
		World1.update();
		TDML::object& plane = World1.getObjectRef("plane");
		if(!dead)
		{
			if(World1.getHeightMapAt(plane.getX(),plane.getZ())>plane.getMinY() || plane.getMinY()<-250)
			{
				crashSmoke = TDML::particlesystem("ps1", "Resources/Common/Textures/part.png", //image
				TDML::vector3d(0,0,0), TDML::vector3d(-0.5,-0.5,-0.5), TDML::vector3d(0.5,0.5,0.5),//pos
				TDML::vector3d(0.0000,0.0005,0.0000), TDML::vector3d(-0.00015,-0.0005,-0.00015), TDML::vector3d(0.00015,0.0005,0.00015),//dir
				TDML::vector3d(0,0,0), TDML::vector3d(0,0,0), TDML::vector3d(0,0,0),//accel
				7500, -2500, 5000,//Life
				0.25, -0.1, 0.1, //Size
				1, 10); //Spawn Delay
				crashSmoke.setPos(TDML::vector3d(plane.getX(), plane.getY(), plane.getZ()));
				World1.addParticleSystem(crashSmoke);
				//plane.setVisible(false);
				dead = true;
			}
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
				plane.setZangle(plane.getZangle()+0.025*TDML::Clock.getTimeDelta());
			}
			if(TDML::Input.getSpecialKeyState(RIGHT))
			{
				plane.setZangle(plane.getZangle() - 0.025*TDML::Clock.getTimeDelta());
			}
			if(TDML::Input.getSpecialKeyState(UP))
			{
				plane.setXangle(plane.getXangle() + 0.02*TDML::Clock.getTimeDelta());
			}
			if(TDML::Input.getSpecialKeyState(DOWN))
			{
				plane.setXangle(plane.getXangle() - 0.02*TDML::Clock.getTimeDelta());
			}
			if(TDML::Input.getKeyState('q'))
			{
				dead = true;
			}
			if(TDML::Input.getKeyState('a'))
			{
				camy+=0.05;
			}
			//plane.setYangle(plane.getYangle()+((plane.getZangle()/5000)*World1.getTimeDelta()));
			TDML::vector3d forward = TDML::vector3d(0,0,1);
			TDML::Math.rotate(forward, plane.getXangle(), plane.getYangle(), plane.getZangle(), ZXY);
			plane.setX(plane.getX()-TDML::Clock.getAdjustedTime(forward.x, 14));
			plane.setY(plane.getY()-TDML::Clock.getAdjustedTime(forward.y, 14));
			plane.setZ(plane.getZ()-TDML::Clock.getAdjustedTime(forward.z, 14));
			/*plane.setYangle(plane.getYangle()+TDML::Math.sin(plane.getZangle()/5000));
			plane.setX(plane.getX()-World1.getTimeDelta()*speed*TDML::Math.sin(plane.getYangle())*TDML::Math.cos(plane.getXangle()));
			plane.setZ(plane.getZ()-World1.getTimeDelta()*speed*TDML::Math.cos(plane.getYangle())*TDML::Math.cos(plane.getXangle()));
			plane.setY(plane.getY()+World1.getTimeDelta()*speed*TDML::Math.sin(plane.getXangle()));
			plane.setY(plane.getY()-(World1.getTimeDelta()/1000));*/
		}
		else
		{
			TDML::Log.output("DEAD");
			if(zoomlevel<4) zoomlevel+=TDML::Clock.getAdjustedTime(0.0025, 6);
			if(TDML::Input.getMouseKeyPressed(LEFTMOUSE))
			{
				respawn();
			}
		}
		//World1.setCamX(plane.getX()+zoom*(pow(2, zoomlevel))*TDML::Math.sin(plane.getYangle()));
		//World1.setCamZ(plane.getZ()+zoom*(pow(2, zoomlevel))*TDML::Math.cos(plane.getYangle()));
		//World1.setCamY(plane.getY());
		TDML::vector3d forward = TDML::vector3d(0,0,1);
		TDML::Math.rotate(forward, plane.getXangle(), plane.getYangle(), plane.getZangle(), ZXY);
		World1.setCamX(plane.getX()+(forward.x*zoom*(pow(2, zoomlevel))));
		World1.setCamY(plane.getY()+(forward.y*zoom*(pow(2, zoomlevel))));
		World1.setCamZ(plane.getZ()+(forward.z*zoom*(pow(2, zoomlevel))));

		World1.setCamAngleX(plane.getXangle()+camxrot);
		World1.setCamAngleY(plane.getYangle()+camy+camyrot);
		World1.setCamAngleZ(plane.getZangle());
		if(TDML::Input.getMouseKeyState(RIGHTMOUSE))
		{
			TDML::Window.hideCursor();
			TDML::Input.setCenterCursor(true);
			if(previouslypressed)
			{
				camyrot = camyrot+(TDML::Input.getMouseX()-(TDML::Window.getWidth())/2);
				camxrot = camxrot+(TDML::Input.getMouseY()-(TDML::Window.getHeight())/2);
			}
			else
			{
				previouslypressed = true;
				TDML::Input.centerCursor();
			}
		}
		else 
		{
			TDML::Input.setCenterCursor(false);
			TDML::Window.showCursor();
			previouslypressed = false;
		}

		if(World1.getHeightMapAt(World1.getCamX(), World1.getCamZ())>World1.getCamY()-0)
		{
			World1.setCamY(World1.getHeightMapAt(World1.getCamX(), World1.getCamZ())+0);
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
	TDML::Log.setDebugMode(LOG_FILE);
	TDML::setObjectRotationOrder(ZXY);
	TDML::Shaders.setUseLighting(false);
	TDML::setupAll(&argc, argv, 1024, 600, "TDML::Airplane", 0.5, 0.8, 1.0, display, animate, exit);
	TDML::enableCulling(true);
	MainMenu = TDML::loadMenu("Resources/MainMenu/menu.mnu");
	//load();
	TDML::Log.output("Loaded menu\n");
	TDML::Window.centerWindow();
	TDML::start();
	return 0;
}