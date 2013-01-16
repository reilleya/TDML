#include "TDML.h"

using namespace std;

TDML::world TestWorld1;

float speed = 0;
float deltaz=100;
float deltay=0;
float rad2degree=57.295779523;

void exit(){}

void display ()
{
	TestWorld1.draw();
}

void animate()
{
	TestWorld1.update();
	deltay = TestWorld1.getCamY() - TestWorld1.getObjAttribute("cube2", "y");
	speed += 0.0005 * (TestWorld1.getTimeDelta()/4);
	TestWorld1.setObjAttribute("cube2", "y", TestWorld1.getObjAttribute("cube2", "y")-speed);
	if(TestWorld1.getBBCollide("cube1", "cube2")==true)
	{
		TestWorld1.setObjAttribute("cube2", "y", TestWorld1.getObjAttribute("cube2", "y")+speed);
		speed = (-speed)+0.05;
	}
	else
	{
		TestWorld1.setObjAttribute("cube2", "zangle", TestWorld1.getObjAttribute("cube2", "zangle")+0.2 * (TestWorld1.getTimeDelta()/4));
		TestWorld1.setObjAttribute("cube2", "xangle", TestWorld1.getObjAttribute("cube2", "xangle")+0.2 * (TestWorld1.getTimeDelta()/4));
	}
	TestWorld1.setCamAngleX((rad2degree*atan(deltaz/deltay))-90);
}

int main(int argc, char** argv)
{
	TDML::setupAll(&argc, argv, 800, 600, "3D Model Loader - Collisions", 1.0, 1.0, 1.0, display, animate, exit);
	TestWorld1 = TDML::loadWorld("world1.wor");
	TestWorld1.setCamPosition(0.0, 50.0, 100.0);
	TDML::start();
	return 0;
}