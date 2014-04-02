#include "TDML.h"

using namespace std;

TDML::world world1;
TDML::particlesystem PS1;
TDML::terrain terrain;
TDML::frameanimation FA1;

float angy = 0;
float angx = 0;

float camX = 0;
float velX = 0;
float camY = 0;
float velY = 0;
float camZ = 0;
float velZ = 0;
float walkspeed = 0.020;

bool centering = false;
bool canJump = true;

bool treeloadedID = false;
int treeid;
int treevao;

bool tree2loadedID = false;
int tree2id;
int tree2vao;

void exit()
{

}

void display()
{
	world1.draw();
	//TDML::Draw3D.cube(world1, 0, -5, -10, 0, 0, 0, 4, 4, 4, 255, 255, 128, 255, true);
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
		world1.setCamAngleY(world1.getCamAngleY() - 0.25*(TDML::Input.getMouseX() - (TDML::Window.getWidth()) / 2));
		world1.setCamAngleX(world1.getCamAngleX() - 0.25*(TDML::Input.getMouseY() - (TDML::Window.getHeight()) / 2));
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

	if (camY - 2 < world1.getHeightMapAt(camX, camZ))
	{
		canJump = true;
		velY = 0;
		camY = world1.getHeightMapAt(camX, camZ) + 2;
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
	FA1 = TDML::frameanimation("BallTest/animation.fam");
	world1 = TDML::loadWorld("world.wor");
	terrain = TDML::loadTerrain("newmap.hgt", "height.png", 500, 0.2);
	world1.setTerrain(terrain);
	world1.setCamPosition(0, 0, 10);

	for (int t = 0; t < 500; t++)
	{
		TDML::object newtree = TDML::loadObject("Tree/wintertree.tdm");
		newtree.setMaterial(TDML::loadTexture("Tree/wintertree.mdf"));
		newtree.setX(TDML::Math.randomRangeFloat(-495, 495));
		newtree.setZ(TDML::Math.randomRangeFloat(-495, 495));
		newtree.setY(world1.getHeightMapAt(newtree.getX(), newtree.getZ())+0.5);
		//while (newtree.getY()<-230 || newtree.getY() > 150)
		//{
		//	newtree.setX(TDML::Math.randomRangeFloat(-2000, 2000));
		//	newtree.setZ(TDML::Math.randomRangeFloat(-2000, 2000));
		//	newtree.setY(World1.getHeightMapAt(newtree.getX(), newtree.getZ()));
		//}
		newtree.setAngle(0, TDML::Math.randomRangeFloat(0, 360), 0);
		int root = TDML::Math.randomRangeInt(2, 7);
		float factor = TDML::Math.randomRangeFloat(75, 125) / 100.0;
		newtree.setScale(root, root*factor, root);
		newtree.setType("tree");
		newtree.setFrameDelay(0);
		newtree.createBoundingBox();
		newtree.setFileName("Tree/wintertree.tdm");
		newtree.setWireframe(false);
		newtree.setVisible(true);
		newtree.setAdjustBB(false);
		if (!treeloadedID)
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
		world1.addObject(newtree);
		newtree.dispInfo();
	}

	for (int t = 0; t < 0; t++)
	{
		TDML::object newtree = TDML::loadObject("Pinetree/pinetree.tdm");
		newtree.setMaterial(TDML::loadTexture("Pinetree/pinetree.mdf"));
		newtree.setX(TDML::Math.randomRangeFloat(-495, 495));
		newtree.setZ(TDML::Math.randomRangeFloat(-495, 495));
		newtree.setY(world1.getHeightMapAt(newtree.getX(), newtree.getZ()) + 0.5);
		//while (newtree.getY()<-230 || newtree.getY() > 150)
		//{
		//	newtree.setX(TDML::Math.randomRangeFloat(-2000, 2000));
		//	newtree.setZ(TDML::Math.randomRangeFloat(-2000, 2000));
		//	newtree.setY(World1.getHeightMapAt(newtree.getX(), newtree.getZ()));
		//}
		newtree.setAngle(0, TDML::Math.randomRangeFloat(0, 360), 0);
		int root = TDML::Math.randomRangeInt(2, 7);
		float factor = TDML::Math.randomRangeFloat(75, 125) / 100.0;
		newtree.setScale(root, root*factor, root);
		newtree.setType("tree");
		newtree.setFrameDelay(0);
		newtree.setFileName("Pinetree/pinetree.tdm");
		newtree.setWireframe(false);
		newtree.setVisible(true);
		newtree.setAdjustBB(false);
		if (!tree2loadedID)
		{
			newtree.generateVBO();
			tree2id = newtree.getVBOId();
			tree2vao = newtree.getVAOId();
			tree2loadedID = true;
		}
		else
		{
			newtree.setVBOId(tree2id);
			newtree.setVAOId(tree2vao);
		}
		world1.addObject(newtree);
		newtree.dispInfo();
	}

	TDML::Input.setCenterCursor(true);
	TDML::Log.clearOutputBuffer();
	TDML::start();
	return 0;
}