#include "TDML.h"

using namespace std;

TDML::world world1;

void exit()
{
	
}

void display ()
{
	world1.draw();
}


void animate()
{
	TDML::object& tv = world1.getObjectRef("tv");
	tv.setYangle(tv.getYangle()+world1.getAdjustedTime(0.05, 4));
	world1.setCamPosition(0, 0, 10);
	world1.update();
}

int main(int argc, char** argv)
{
	TDML::Log.setDebugMode(true);
	TDML::Shaders.setUseShaders(true);
	TDML::Shaders.setUseLighting(true);
	TDML::enableCulling(false);
	TDML::Log.output("Hello, Worlds!\n");
	TDML::Log.output(TDML::Version.getFullVersion());
	TDML::setupAll(&argc, argv, 500, 500, "3D Model Loader - Shader Testbed", 0.5, 0.8, 1.0, display, animate, exit);
	world1 = TDML::loadWorld("world.wor");
	TDML::Message.popupMessage("THIS IS A LONG MESSAGE! THIS IS A LONG MESSAGE! THIS IS A LONG MESSAGE! THIS IS A LONG MESSAGE! THIS IS A LONG MESSAGE! THIS IS A LONG MESSAGE! THIS IS A LONG MESSAGE! THIS IS A LONG MESSAGE! THIS IS A LONG MESSAGE! ", "THIS ISN'T");
	TDML::start();
	return 0;
}