#include "TDML.h"
#include <math.h>

using namespace std;

TDML::world TestWorld1;

float rad = 0.01745;
float speed = 0.15;

void display ()
{
	TestWorld1.draw();
}

void animate()
{
	TestWorld1.update();
	if(TDML::Input.getKeyState('w'))
	{
		TestWorld1.setObjAttribute("plane", "x", TestWorld1.getObjAttribute("plane","x")-TestWorld1.getTimeDelta()*speed*(sinf(rad*TestWorld1.getObjAttribute("plane","yangle"))));
		TestWorld1.setObjAttribute("plane", "z", TestWorld1.getObjAttribute("plane","z")-TestWorld1.getTimeDelta()*speed*(cosf(rad*TestWorld1.getObjAttribute("plane","yangle"))));
	}
	if(TDML::Input.getKeyState('s'))
	{
		TestWorld1.setObjAttribute("plane", "x", TestWorld1.getObjAttribute("plane","x")+TestWorld1.getTimeDelta()*speed*(sinf(rad*TestWorld1.getObjAttribute("plane","yangle"))));
		TestWorld1.setObjAttribute("plane", "z", TestWorld1.getObjAttribute("plane","z")+TestWorld1.getTimeDelta()*speed*(cosf(rad*TestWorld1.getObjAttribute("plane","yangle"))));
	}
	if(TDML::Input.getKeyState('a'))
	{
		TestWorld1.setObjAttribute("plane", "yangle", TestWorld1.getObjAttribute("plane","yangle")+(speed/4)*TestWorld1.getTimeDelta());
	}
	if(TDML::Input.getKeyState('d'))
	{
		TestWorld1.setObjAttribute("plane", "yangle", TestWorld1.getObjAttribute("plane","yangle")-(speed/4)*TestWorld1.getTimeDelta());
	}
	if(TDML::Input.getSpecialKeyState(UP))
	{
		TestWorld1.setObjAttribute("plane", "y", TestWorld1.getObjAttribute("plane","y")+speed*TestWorld1.getTimeDelta());
	}
	if(TDML::Input.getSpecialKeyState(DOWN))
	{
		TestWorld1.setObjAttribute("plane", "y", TestWorld1.getObjAttribute("plane","y")-speed*TestWorld1.getTimeDelta());
	}
	if(TDML::Input.getSpecialKeyState(LEFT))
	{
		TestWorld1.setObjAttribute("plane", "z", TestWorld1.getObjAttribute("plane","z")-TestWorld1.getTimeDelta()*speed*(sinf(rad*TestWorld1.getObjAttribute("plane","yangle"))));
		TestWorld1.setObjAttribute("plane", "x", TestWorld1.getObjAttribute("plane","x")-TestWorld1.getTimeDelta()*speed*(cosf(rad*TestWorld1.getObjAttribute("plane","yangle"))));
	}
	if(TDML::Input.getSpecialKeyState(RIGHT))
	{
		TestWorld1.setObjAttribute("plane", "z", TestWorld1.getObjAttribute("plane","z")+TestWorld1.getTimeDelta()*speed*(sinf(rad*TestWorld1.getObjAttribute("plane","yangle"))));
		TestWorld1.setObjAttribute("plane", "x", TestWorld1.getObjAttribute("plane","x")+TestWorld1.getTimeDelta()*speed*(cosf(rad*TestWorld1.getObjAttribute("plane","yangle"))));	
	}
	if(TDML::Input.getKeyState(' '))
	{
		speed=0.45;
	}
	else
	{
		speed=0.15;
	}
	if(TestWorld1.getObjAttribute("plane","yangle") > 360) TestWorld1.setObjAttribute("plane", "yangle", TestWorld1.getObjAttribute("plane","yangle")-360);
	if(TestWorld1.getObjAttribute("plane","yangle") < 0) TestWorld1.setObjAttribute("plane", "yangle", 360-TestWorld1.getObjAttribute("plane","yangle"));
	if(TestWorld1.getObjAttribute("plane","xangle") > 360) TestWorld1.setObjAttribute("plane", "xangle", TestWorld1.getObjAttribute("plane","xangle")-360);
	if(TestWorld1.getObjAttribute("plane","xangle") < 0) TestWorld1.setObjAttribute("plane", "xangle", 360-TestWorld1.getObjAttribute("plane","xangle"));
	if(TestWorld1.getObjAttribute("plane","zangle") > 360) TestWorld1.setObjAttribute("plane", "zangle", TestWorld1.getObjAttribute("plane","zangle")-360);
	if(TestWorld1.getObjAttribute("plane","zangle") < 0) TestWorld1.setObjAttribute("plane", "zangle", 360-TestWorld1.getObjAttribute("plane","zangle"));
	
	//if(TestWorld1.getObjAttribute("plane","zangle") > 0) TestWorld1.setObjAttribute("plane", "zangle", TestWorld1.getObjAttribute("plane","zangle")-0.25);
	//if(TestWorld1.getObjAttribute("plane","zangle") < 0) TestWorld1.setObjAttribute("plane", "zangle", TestWorld1.getObjAttribute("plane","zangle")+0.25);

	//TestWorld1.setObjAttribute("plane", "x", TestWorld1.getObjAttribute("plane","x")-TestWorld1.getTimeDelta()*speed*(sinf(rad*TestWorld1.getObjAttribute("plane","yangle"))*cosf(rad*TestWorld1.getObjAttribute("plane","xangle"))));
	//TestWorld1.setObjAttribute("plane", "z", TestWorld1.getObjAttribute("plane","z")-TestWorld1.getTimeDelta()*speed*(cosf(rad*TestWorld1.getObjAttribute("plane","yangle"))*cosf(rad*TestWorld1.getObjAttribute("plane","xangle"))));
	//TestWorld1.setObjAttribute("plane", "y", TestWorld1.getObjAttribute("plane","y")+TestWorld1.getTimeDelta()*speed*(sinf(rad*TestWorld1.getObjAttribute("plane","xangle"))));
	

	TestWorld1.setCamX((TestWorld1.getObjAttribute("plane", "x"))+30*sinf(0.01745*TestWorld1.getObjAttribute("plane","yangle")));
	TestWorld1.setCamZ(TestWorld1.getObjAttribute("plane","z")+30*cosf(0.01745*TestWorld1.getObjAttribute("plane","yangle")));
	TestWorld1.setCamY(TestWorld1.getObjAttribute("plane","y"));
	TestWorld1.setCamAngleY(TestWorld1.getObjAttribute("plane","yangle"));
}

int main(int argc, char** argv)
{
	TDML::setupAll(&argc, argv, 500, 500, "3D Model Loader - Crocodile", 0.5, 0.8, 1.0, display, animate);
	cout << "Loading World"<<endl;
	TestWorld1 = TDML::loadWorld("world1.wor");
	cout << "Done. " << endl;
	TDML::start();
	return 0;
}