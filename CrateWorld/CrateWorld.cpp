#include "TDML.h"

using namespace std;

TDML::world World;

float velx = 0;
float vely = 0;
float velz = 0;

float killpoint = -100;

bool jumped = false;

bool menushow = true;
bool menutoggle = false;

void exit()
{
	TDML::Log.output("Done. Exiting.");
}

void display ()
{
	World.draw();
	//if(menushow) mainmenu.draw();
}

void animate()
{
	TDML::object& character = World.getObjectRef("Character");
	World.update();
	//World.setCamPosition(10, 10, 5);
	//World.setCamAngle(0, 90, 30);

	if(vely < 0.05) vely+=World.getAdjustedTime((float)0.00025, 2);
	character.setY(character.getY()-World.getAdjustedTime(vely,2));
	if(World.getBBCollideType("Character", "crate"))
	{

		character.setY(character.getY()+World.getAdjustedTime(vely,2));
		vely=0;
		jumped = false;
	}
	if(TDML::Input.getKeyState(SPACE))
	{
		if(!jumped)
		{
			vely = (float)-0.04;
			jumped = true;
		}
	}
	if(TDML::Input.getKeyState('a'))
	{
		character.setYangle(character.getYangle()+World.getAdjustedTime((float)0.1, 1));
	}
	if(TDML::Input.getKeyState('d'))
	{
		character.setYangle(character.getYangle()-World.getAdjustedTime((float)0.1, 1));
	}
	if(TDML::Input.getKeyState('w'))
	{
		character.setX(character.getX()-World.getAdjustedTime(TDML::Math.sin(character.getYangle()), 200));
		character.setZ(character.getZ()-World.getAdjustedTime(TDML::Math.cos(character.getYangle()), 200));
		if(World.getBBCollideType("Character", "crate"))
		{
			character.setX(character.getX()+World.getAdjustedTime(TDML::Math.sin(character.getYangle()), 200));
			character.setZ(character.getZ()+World.getAdjustedTime(TDML::Math.cos(character.getYangle()), 200));
		}
	}
	if(TDML::Input.getKeyState('s'))
	{
		character.setX(character.getX()+World.getAdjustedTime(TDML::Math.sin(character.getYangle()), 200));
		character.setZ(character.getZ()+World.getAdjustedTime(TDML::Math.cos(character.getYangle()), 200));
		if(World.getBBCollideType("Character", "crate"))
		{
			character.setX(character.getX()-World.getAdjustedTime(TDML::Math.sin(character.getYangle()), 200));
			character.setZ(character.getZ()-World.getAdjustedTime(TDML::Math.cos(character.getYangle()), 200));
		}
	}
	if(TDML::Input.getKeyState('b'))
	{
		TDML::stop();
	}
	if(TDML::Input.getKeyState('f'))
	{
		TDML::object& one = World.getObjectRef("Wall1");
		TDML::object& two = World.getObjectRef("Ground1");
		one.setWireframe(!one.getWireframe());
		two.setWireframe(!two.getWireframe());
	}
	if(character.getY()<killpoint)
	{
		character.setX(0);
		character.setY(10);
		character.setZ(0);
	}
	//World.setCamAngleX(World.getCamAngleX()+((TDML::Input.getMouseY()-300)/2));
	//World.setCamAngleY(World.getCamAngleY()+(TDML::Input.getMouseX()-400)/2);
	World.setCamPosition(character.getX(), character.getY()+1, character.getZ());
	World.setCamAngle(0, character.getYangle(), 0);
	//TDML::Input.centerCursor();
}

int main(int argc, char** argv)
{
	TDML::Log.setDebugMode(true);
	TDML::setupAll(&argc, argv, 800, 600, "TDML::Platformer", 0.0, 1.0, 1.0, display, animate, exit);
	World = TDML::loadWorld("Resources/LevelOne/output.wor");
	//mainmenu.testlod();
	TDML::enableCulling(true);
	TDML::Window.centerWindow();
	TDML::start();
	return 0;
}