#include "TDML.h"

using namespace std;

TDML::world world1;
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
float walkspeed = 0.025;

bool centering = false;
bool canJump = true;

void exit()
{

}

void display()
{
	world1.draw();
	TDML::Draw3D.cube(world1, 0, -5, -10, 0, 0, 0, 4, 4, 4, 255, 255, 128, 255, true);
}

void animate()
{
	TDML::Window.hideCursor();

	if (TDML::Input.getKeyPressed('q'))
	{
		TDML::exit();
	}

	if (TDML::Input.getKeyState('w'))
	{
		velX -= walkspeed*TDML::Math.sin(world1.getCamAngleY());
		velZ -= walkspeed*TDML::Math.cos(world1.getCamAngleY());
	}

	if (TDML::Input.getKeyState('s'))
	{
		velX += walkspeed*TDML::Math.sin(world1.getCamAngleY());
		velZ += walkspeed*TDML::Math.cos(world1.getCamAngleY());
	}

	if (TDML::Input.getKeyState('a'))
	{
		velX -= walkspeed*TDML::Math.cos(world1.getCamAngleY());
		velZ += walkspeed*TDML::Math.sin(world1.getCamAngleY());
	}

	if (TDML::Input.getKeyState('d'))
	{
		velX += walkspeed*TDML::Math.cos(world1.getCamAngleY());
		velZ -= walkspeed*TDML::Math.sin(world1.getCamAngleY());
	}

	if (TDML::Input.getKeyPressed('t'))
	{
		TDML::Log.output(TDML::Clock.getFramerate()); TDML::Log.output("\n");
	}

	if (TDML::Input.getKeyState('n'))
	{
		TDML::Input.setCenterCursor(false);
	}
	else
	{
		TDML::Input.setCenterCursor(true);
		world1.setCamAngleY(world1.getCamAngleY() - (TDML::Input.getMouseX() - (TDML::Window.getWidth()) / 2));
		world1.setCamAngleX(world1.getCamAngleX() - (TDML::Input.getMouseY() - (TDML::Window.getHeight()) / 2));
	}

	if (TDML::Input.getKeyPressed(SPACE))
	{
		if (canJump)
		{
			TDML::Log.output("JUMP\n");
			velY = 0.75;
			canJump = false;
		}
	}

	//if (abs(velX) + abs(velZ)>15)
	//{
	//	float velXpart = velX / (abs(velX) + abs(velZ));
	//	float velZpart = velZ / (abs(velX) + abs(velZ));
	//	velX = 0.5*velXpart;
	//	velZ = 0.5*velZpart;
	//}

	velX *= 0.95;
	velZ *= 0.95;
	//TDML::Log.output(velX); TDML::Log.output("\n");
	//TDML::Log.output(velZ); TDML::Log.output("\n");

	camX += TDML::Clock.getAdjustedTime(velX, 10);
	camZ += TDML::Clock.getAdjustedTime(velZ, 10);

	velY -= TDML::Clock.getAdjustedTime(0.025, 10);
	camY += TDML::Clock.getAdjustedTime(velY, 10);

	if (camY - 1<world1.getHeightMapAt(camX, camZ))
	{
		canJump = true;
		velY = 0;
		camY = world1.getHeightMapAt(camX, camZ) + 1;
	}

	world1.setCamPosition(camX, camY, camZ);

	TDML::Log.sendOutputBuffer();
	world1.update();
}

int main(int argc, char** argv)
{
	TDML::Log.setDebugMode(LOG_CONSOLEFILE);
	TDML::setupAll(&argc, argv, 1280, 720, "A Goddamn Bear", 0.5, 0.8, 1.0, display, animate, exit);
	TDML::Shaders.setUseTextures(true);
	TDML::enableCulling(true);
	world1 = TDML::loadWorld("world.wor");
	terrain = TDML::loadTerrain("bump.hgt", "height.png", 2500, 0.5);
	world1.setTerrain(terrain);
	world1.setCamPosition(0, 0, 10);
	TDML::Input.setCenterCursor(true);
	TDML::Log.clearOutputBuffer();
	TDML::start();
	return 0;
}