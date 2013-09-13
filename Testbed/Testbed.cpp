#include "TDML.h"

using namespace std;

TDML::world world1;
TDML::menu menu1;
TDML::particlesystem PS1;

float angy = 0;
float angx = 0;
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
	menu1.draw();
	TDML::Draw2D.line(((float)TDML::Window.getWidth())/2,((float)TDML::Window.getHeight())/2, TDML::Input.getMouseX(), TDML::Input.getMouseY(), 25, 1,0,0,1);
}

void animate()
{
	angy+=5;
	angx+=2.5;
	//world1.setCamAngleY(world1.getCamAngleY()-(TDML::Input.getMouseX()-(TDML::Window.getWidth()/2)));
	if(TDML::Input.getKeyPressed('q'))
	{
		TDML::stop();
	}
	if(TDML::Input.getKeyPressed('l'))
	{
		
	}
	if(TDML::Input.getKeyPressed('e'))
	{
		menu1.dispInfo(); TDML::Log.sendOutputBuffer();
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
	//tv.setYangle(tv.getYangle()+world1.getAdjustedTime(0.05, 4));
	//tv.setScaleY(TDML::Math.larger(0.15, abs(TDML::Math.sin(world1.getTimer()/4.0))));
	//tv.setPosition(TDML::Math.orbit(0, 0, 0, 3, 720*((float)TDML::Input.getMouseX()/(float)TDML::Window.getWidth()), 720*((float)TDML::Input.getMouseY()/(float)TDML::Window.getHeight())));
	//tv.setAngle(TDML::Math.angleTo(0,0,0,tv.getX(), tv.getY(), tv.getZ()));
	//TDML::Input.centerCursor();
	//world1.setCamPosition(TDML::Math.orbit(0, 0, 0, 3, 720*((float)TDML::Input.getMouseX()/(float)TDML::Window.getWidth()), 0));//720*((float)TDML::Input.getMouseY()/(float)TDML::Window.getHeight())));
	//world1.setCamAngle(TDML::Math.angleTo(0,0,0,world1.getCamX(), world1.getCamY(), world1.getCamZ())); 
	//world1.setCamAngleZ(720*((float)TDML::Input.getMouseX()/(float)TDML::Window.getWidth()));
	tv.setZangle(TDML::Math.angleBetween(((float)TDML::Window.getWidth())/2,((float)TDML::Window.getHeight())/2, TDML::Input.getMouseX(), TDML::Input.getMouseY()));
	TDML::Log.sendOutputBuffer();
	world1.update();
	menu1.update();
}

int main(int argc, char** argv)
{
	TDML::Log.setDebugMode(LOG_POPUPFILE);
	TDML::setupAll(&argc, argv, 500, 500, "3D Model Loader - Shader Testbed", 0.5, 0.8, 1.0, display, animate, exit);
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
	TDML::object& tv = world1.getObjectRef("tv");
	//tv.setVisible(false);
	TDML::menuobject& man = menu1.getObjectRefByName("man");
	man.setUpdateFunction(manUpdateFunc);
	world1.setCamPosition(0, 0, 10);
	//TDML::Shaders.setSunVector(TDML::vector3d(
	TDML::Log.clearOutputBuffer();
	TDML::start();
	return 0;
}