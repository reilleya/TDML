#include "TDML.h"

using namespace std;

TDML::world world1;
TDML::menu menu1;
TDML::particlesystem PS1;
TDML::terrain terrain;

float angy = 0;
float angx = 0;

float camX = 0;
float velX = 0;
float camY = 0;
float velY = 0;
float camZ = 0;
float velZ = 0;


bool centering = false;
bool canJump = true;
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
	//TDML::Draw3D.ball(0, 0, -10, 0, 0, 0, 4, 4, 4, 255, 0, 0, 255, false);
	TDML::Draw3D.cube(world1, 0, -5, -10, 0, 0, 0, 4, 4, 4, 255, 255, 128, 255, true);
	menu1.draw();
	//TDML::Draw2D.line(((float)TDML::Window.getWidth())/2,((float)TDML::Window.getHeight())/2, TDML::Input.getMouseX(), TDML::Input.getMouseY(), 25, 255,128,0,255);
}

void animate()
{
	TDML::Window.hideCursor();

	if(TDML::Input.getKeyPressed('q'))
	{
		TDML::exit();
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
		velX-=0.25*TDML::Math.sin(world1.getCamAngleY());
		velZ-=0.25*TDML::Math.cos(world1.getCamAngleY());
	}

	if(TDML::Input.getKeyState('s'))
	{
		velX+=0.25*TDML::Math.sin(world1.getCamAngleY());
		velZ+=0.25*TDML::Math.cos(world1.getCamAngleY());
	}

	if(TDML::Input.getKeyState('a'))
	{
		velX-=0.25*TDML::Math.cos(world1.getCamAngleY());
		velZ+=0.25*TDML::Math.sin(world1.getCamAngleY());
	}

	if(TDML::Input.getKeyState('d'))
	{
		velX+=0.25*TDML::Math.cos(world1.getCamAngleY());
		velZ-=0.25*TDML::Math.sin(world1.getCamAngleY());
	}

	if(TDML::Input.getKeyState('n'))
	{
		TDML::Input.setCenterCursor(false);
	}
	else TDML::Input.setCenterCursor(true);

	if (TDML::Input.getKeyPressed('l'))
	{
		TDML::Log.output(world1.getInclinationAt(camX, camZ)); TDML::Log.output("\n");
	}

	if(TDML::Input.getKeyPressed(SPACE))
	{
		if(canJump)
		{
			TDML::Log.output("JUMP\n");
			velY = 0.75;
			canJump = false;
		}
	}

	TDML::object& tv = world1.getObjectRef("tv");
	tv.setYangle(tv.getYangle()+0.5);
	tv.setPosition(tv.getX(), world1.getHeightMapAt(tv.getX(), tv.getZ())+0.5, tv.getZ());

	TDML::object& thing = world1.getObjectRef("thing");
	thing.setZangle(thing.getZangle() + 0.25);
	thing.setPosition(thing.getX(), world1.getHeightMapAt(thing.getX(), thing.getZ()) + 0.5, thing.getZ());


	if(TDML::Input.getKeyState('y'))
	{
		tv.setDrawBB(true);
	}
	else
	{
		tv.setDrawBB(false);
	}

	if(!TDML::Input.getKeyState('n'))
	{
		world1.setCamAngleY(world1.getCamAngleY()-(TDML::Input.getMouseX()-(TDML::Window.getWidth())/2));
		world1.setCamAngleX(world1.getCamAngleX()-(TDML::Input.getMouseY()-(TDML::Window.getHeight())/2));
	}

	if(abs(velX)+abs(velZ)>0.5)
	{
		float velXpart = velX/(abs(velX)+abs(velZ));
		float velZpart = velZ/(abs(velX)+abs(velZ));
		velX = 0.5*velXpart;
		velZ = 0.5*velZpart;
	}

	velX*=0.90;
	velZ*=0.90;

	camX+=TDML::Clock.getAdjustedTime(velX, 10);
	camZ+=TDML::Clock.getAdjustedTime(velZ, 10);

	velY -= TDML::Clock.getAdjustedTime(0.025, 10);
	camY += TDML::Clock.getAdjustedTime(velY, 10);
	if(camY-1<world1.getHeightMapAt(camX, camZ))
	{
		canJump = true;
		velY = 0;
		camY = world1.getHeightMapAt(camX, camZ)+1;
	}

	world1.setCamPosition(camX, camY, camZ);

	TDML::Log.sendOutputBuffer();
	world1.update();
	menu1.update();
}

int main(int argc, char** argv)
{
	TDML::Log.setDebugMode(LOG_CONSOLEFILE);
	TDML::setupAll(&argc, argv, 1280, 720, "3D Model Loader - Shader Testbed", 0.5, 0.8, 1.0, display, animate, exit);
	TDML::Shaders.setUseLighting(false);
	TDML::Shaders.setSunVector(TDML::vector3d(0, 1, 0));
	TDML::Shaders.setUseTextures(true);
	TDML::enableCulling(true);
	world1 = TDML::loadWorld("world.wor");
	menu1 = TDML::loadMenu("test.mnu");
	PS1 = TDML::particlesystem("ps1", "newsmoke.png", //image
				TDML::vector3d(0,0,0), TDML::vector3d(-0.5,-0.5,-0.5), TDML::vector3d(0.5,0.5,0.5),//pos
				TDML::vector3d(0.0000,0.0005,0.0000), TDML::vector3d(-0.00015,-0.0005,-0.00015), TDML::vector3d(0.00015,0.0005,0.00015),//dir
				TDML::vector3d(0,0,0), TDML::vector3d(0,0,0), TDML::vector3d(0,0,0),//accel
				5000, -2500, 5000,//Life
				0.25, -0.15, 0.15, //Size
				1, 20); //Spawn Delay
	//world1.addParticleSystem(PS1);
	terrain = TDML::loadTerrain("bump.hgt", "height.png", "height.png", 2500, 0.5);
	world1.setTerrain(terrain);
	TDML::matrix3x3 tm = TDML::matrix3x3();
	tm.p11 = 1; tm.p12 = 4; tm.p13 = 2;
	tm.p21 = 6; tm.p22 = 2; tm.p23 = 5;
	tm.p31 = 2; tm.p32 = 4; tm.p33 = 2;
	tm.dispInfo();
	TDML::Log.output(tm.determinant()); TDML::Log.output("\n");
	tm.inverse().dispInfo();
	TDML::object& tv = world1.getObjectRef("tv");
	TDML::object& thing = world1.getObjectRef("thing");
	thing.setY(world1.getTerrainRef().getHeightMapAt(thing.getX(), thing.getZ()));
	//tv.set
	//tv.setWireframe(true);
	//tv.setVisible(false);
	TDML::menuobject& man = menu1.getObjectRefByName("man");
	man.setUpdateFunction(manUpdateFunc);
	world1.setCamPosition(0, 0, 10);
	//TDML::Shaders.setSunVector(TDML::vector3d(
	TDML::Input.setCenterCursor(true);
	TDML::Log.clearOutputBuffer();
	//TDML::Window.setFullscreen(true);
	TDML::start();
	return 0;
}