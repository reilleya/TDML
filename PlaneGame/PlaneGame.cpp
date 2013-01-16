#include "TDML.h"
#include <math.h>

using namespace std;

TDML::world World1;
TDML::terrain testterrain1;

float rad = 0.01745;
float speed = 0.008;

void exit()
{
	TDML::Log.output("Exiting!\n");
}

void display ()
{
	World1.draw();
}

void animate()
{
	World1.update();
	//World1.getHeightMapAt(World1.getObjAttribute("plane","x"),World1.getObjAttribute("plane","z"));
	//TDML::Log.output(World1.getHeightMapAt(World1.getObjAttribute("plane","x"),World1.getObjAttribute("plane","z"))); TDML::Log.output(":"); TDML::Log.output(World1.getObjAttribute("plane", "y"));TDML::Log.output("\n");
	if(TDML::Input.getSpecialKeyState(LEFT)) 
	{
		World1.setObjAttribute("plane", "zangle", World1.getObjAttribute("plane","zangle")+0.025*World1.getTimeDelta());
	}
	if(TDML::Input.getSpecialKeyState(RIGHT))
	{
		World1.setObjAttribute("plane", "zangle", World1.getObjAttribute("plane","zangle")-0.025*World1.getTimeDelta());
	}
	if(TDML::Input.getSpecialKeyState(UP))
	{
		World1.setObjAttribute("plane", "xangle", World1.getObjAttribute("plane","xangle")+0.02*World1.getTimeDelta());
	}
	if(TDML::Input.getSpecialKeyState(DOWN))
	{
		World1.setObjAttribute("plane", "xangle", World1.getObjAttribute("plane","xangle")-0.02*World1.getTimeDelta());
	}

	World1.setObjAttribute("plane", "yangle", World1.getObjAttribute("plane","yangle")+(World1.getObjAttribute("plane","zangle")/5000)*World1.getTimeDelta());

	/*if(World1.getObjAttribute("plane","yangle") > 360) World1.setObjAttribute("plane", "yangle", World1.getObjAttribute("plane","yangle")-360);
	if(World1.getObjAttribute("plane","yangle") < 0) World1.setObjAttribute("plane", "yangle", 360+World1.getObjAttribute("plane","yangle"));
	if(World1.getObjAttribute("plane","xangle") > 360) World1.setObjAttribute("plane", "xangle", World1.getObjAttribute("plane","xangle")-360);
	if(World1.getObjAttribute("plane","xangle") < 0) World1.setObjAttribute("plane", "xangle", 360+World1.getObjAttribute("plane","xangle"));
	if(World1.getObjAttribute("plane","zangle") > 360) World1.setObjAttribute("plane", "zangle", World1.getObjAttribute("plane","zangle")-360);
	if(World1.getObjAttribute("plane","zangle") < 0) World1.setObjAttribute("plane", "zangle", 360+World1.getObjAttribute("plane","zangle"));
	*/
	World1.setObjAttribute("plane", "x", World1.getObjAttribute("plane","x")-World1.getTimeDelta()*speed*(sinf(rad*World1.getObjAttribute("plane","yangle"))*cosf(rad*World1.getObjAttribute("plane","xangle"))));
	World1.setObjAttribute("plane", "z", World1.getObjAttribute("plane","z")-World1.getTimeDelta()*speed*(cosf(rad*World1.getObjAttribute("plane","yangle"))*cosf(rad*World1.getObjAttribute("plane","xangle"))));
	World1.setObjAttribute("plane", "y", World1.getObjAttribute("plane","y")+World1.getTimeDelta()*speed*(sinf(rad*World1.getObjAttribute("plane","xangle"))));
	World1.setObjAttribute("plane", "y", World1.getObjAttribute("plane","y")-(World1.getTimeDelta()/1000));

	World1.setCamX((World1.getObjAttribute("plane", "x"))+3*sinf(0.01745*World1.getObjAttribute("plane","yangle")));
	World1.setCamZ(World1.getObjAttribute("plane","z")+3*cosf(0.01745*World1.getObjAttribute("plane","yangle")));
	World1.setCamY(World1.getObjAttribute("plane","y"));
	World1.setCamAngleY(World1.getObjAttribute("plane","yangle"));
}

int main(int argc, char** argv)
{
	TDML::Log.setDebugMode(true);
	TDML::setupAll(&argc, argv, 1024, 600, "TDML::Airplane", 0.5, 0.8, 1.0, display, animate, exit);
	TDML::enableCulling(true);
	TDML::Log.outputWindow("Loading, please wait.");
	TDML::Log.output("Loading World\n");
	World1 = TDML::loadWorld("Resources/World1/world.wor");
	testterrain1 = TDML::loadTerrain("Resources/World1/Heightmaps/test.hgt", "Resources/Common/Textures/height.png", 2500, 2);
	World1.setTerrain(testterrain1);
	TDML::Log.output("Done.\n");
	TDML::Window.centerWindow();
	TDML::start();
	return 0;
}