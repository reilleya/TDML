#include "TDML.h"

using namespace std;

TDML::world world1;
TDML::menu menu1;
TDML::particlesystem PS1;
TDML::terrain terrain;

float angy = 0;
float angx = 0;

float camX = 0;
float camZ = 0;

bool centering = false;
//float playVelX=

void playUpdateFunc(TDML::menuobject* me)
{
	me->setPosX(me->getPosX()+1);
	me->setPosY(me->getPosY()+1);
}

void manUpdateFunc(TDML::menuobject* me)
{
	float oldx = me->getPosX();
	float oldy = me->getPosY();
	me->setPosX(TDML::Input.getMouseX());
	me->setPosY(TDML::Input.getMouseY());
	TDML::menuobject& play = menu1.getObjectRefByName("play");
	if(me->rectCollide(play.getPosX(), play.getPosY(), play.getWidth(), play.getHeight()))
	{
		me->setPosX(oldx);
		me->setPosY(oldy);
	}
	/*if(TDML::Input.getMouseKeyPressed(LEFTMOUSE) && me->pointCollide(TDML::Input.getMouseX(),TDML::Input.getMouseY()))
	{
		TDML::menuobject& play = menu1.getObjectRefByName("play");
		play.setUpdateFunction(playUpdateFunc);
	}*/
}

void exit()
{
	
}

void display ()
{
	world1.draw();
	//menu1.draw();
	//TDML::Draw2D.line(((float)TDML::Window.getWidth())/2,((float)TDML::Window.getHeight())/2, TDML::Input.getMouseX(), TDML::Input.getMouseY(), 25, 255,128,0,255);
}

void animate()
{
	TDML::Window.hideCursor();

	if(TDML::Input.getKeyPressed('q'))
	{
		TDML::stop();
	}
	if(TDML::Input.getKeyPressed('l'))
	{
		TDML::Window.showCursor();
	}
	if(TDML::Input.getKeyPressed('e'))
	{
		menu1.dispInfo(); TDML::Log.sendOutputBuffer();
	}

	if(TDML::Input.getKeyState('w'))
	{
		camZ+=world1.getAdjustedTime(0.5, 10);
	}

	if(TDML::Input.getKeyState('s'))
	{
		camZ-=world1.getAdjustedTime(0.5, 10);
	}

	if(TDML::Input.getKeyState('a'))
	{
		camX+=world1.getAdjustedTime(0.5, 10);
	}

	if(TDML::Input.getKeyState('d'))
	{
		camX-=world1.getAdjustedTime(0.5, 10);
	}

	TDML::object& tv = world1.getObjectRef("tv");
	tv.setPosition(tv.getX(), world1.getHeightMapAt(tv.getX(), tv.getZ()), tv.getZ());

	world1.setCamAngleY(world1.getCamAngleY()+(TDML::Input.getMouseX()-(TDML::Window.getWidth())/2));
	world1.setCamAngleX(world1.getCamAngleX()+(TDML::Input.getMouseY()-(TDML::Window.getHeight())/2));

	world1.setCamPosition(camX, world1.getHeightMapAt(camX, camZ)+5, camZ);

	TDML::Log.sendOutputBuffer();
	world1.update();
	menu1.update();
}

int main(int argc, char** argv)
{
	TDML::Log.setDebugMode(LOG_POPUPFILE);
	TDML::setupAll(&argc, argv, 1024, 768, "3D Model Loader - Shader Testbed", 0.5, 0.8, 1.0, display, animate, exit);
	TDML::Shaders.setUseShaders(true);
	TDML::Shaders.setUseLighting(false);
	TDML::Shaders.setUseTextures(true);
	TDML::enableCulling(false);
	world1 = TDML::loadWorld("world.wor");
	menu1 = TDML::loadMenu("test.mnu");
	PS1 = TDML::particlesystem("ps1", "part.png", //image
				TDML::vector3d(0,0,0), TDML::vector3d(-0.5,-0.5,-0.5), TDML::vector3d(0.5,0.5,0.5),//pos
				TDML::vector3d(0.0000,0.0005,0.0000), TDML::vector3d(-0.00015,-0.0005,-0.00015), TDML::vector3d(0.00015,0.0005,0.00015),//dir
				TDML::vector3d(0,0,0), TDML::vector3d(0,0,0), TDML::vector3d(0,0,0),//accel
				5000, -2500, 5000,//Life
				0.25, -0.1, 0.1, //Size
				1, 20); //Spawn Delay
	//world1.addParticleSystem(PS1);
	terrain = TDML::loadTerrain("islandheightsmall.hgt", "height.png", 2500, 2);
	world1.setTerrain(terrain);

	TDML::object& tv = world1.getObjectRef("tv");
	//tv.setVisible(false);
	TDML::menuobject& man = menu1.getObjectRefByName("man");
	man.setUpdateFunction(manUpdateFunc);
	world1.setCamPosition(0, 0, 10);
	//TDML::Shaders.setSunVector(TDML::vector3d(
	TDML::Input.setCenterCursor(true);
	TDML::Log.clearOutputBuffer();
	
	TDML::start();
	return 0;
}