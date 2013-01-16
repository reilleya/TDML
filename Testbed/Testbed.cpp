#include "TDML.h"
#include <windows.h>
#include <Gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h> 
#include <vector>
#include <string>
#include <math.h>
#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

TDML::world TestWorld1;

void exit()
{
	
}

void display ()
{
	TestWorld1.draw();
}

void keyboard ()
{
	if(TDML::Input.getKeyState('w'))
	{
		TestWorld1.setObjAttribute("*", "wireframe", !TestWorld1.getObjAttribute("house1", "wireframe"));
	}
	if(TDML::Input.getKeyState('o'))
	{
		TestWorld1.setObjAttribute("*", "outline",  !TestWorld1.getObjAttribute("house1", "outline"));
	}
	if(TDML::Input.getKeyState('v'))
	{
		TestWorld1.setObjAttribute("*", "visible",  !TestWorld1.getObjAttribute("house1", "visible"));
	}
}

void specialKeyboard()
{
	//if(TDML::Input.getSpecialKeyState(GLUT_KEY_LEFT)) TestWorld1.setCamAngleY(TestWorld1.getCamAngleY()-0.0625*TestWorld1.getTimeDelta());
	//if(TDML::Input.getSpecialKeyState(GLUT_KEY_RIGHT)) TestWorld1.setCamAngleY(TestWorld1.getCamAngleY()+0.0625*TestWorld1.getTimeDelta());
	if(TDML::Input.getSpecialKeyState(GLUT_KEY_DOWN)) 
	{
		TestWorld1.setCamX(TestWorld1.getCamX()+TestWorld1.getTimeDelta()*0.25*(sinf(0.01745*TestWorld1.getCamAngleY())));
		TestWorld1.setCamZ(TestWorld1.getCamZ()-TestWorld1.getTimeDelta()*0.25*(cosf(0.01745*TestWorld1.getCamAngleY())));
	}
	if(TDML::Input.getSpecialKeyState(GLUT_KEY_UP))
	{
		TestWorld1.setCamX(TestWorld1.getCamX()-TestWorld1.getTimeDelta()*0.25*(sinf(0.01745*TestWorld1.getCamAngleY())));
		TestWorld1.setCamZ(TestWorld1.getCamZ()+TestWorld1.getTimeDelta()*0.25*(cosf(0.01745*TestWorld1.getCamAngleY())));
	}
	if(TDML::Input.getSpecialKeyState(GLUT_KEY_RIGHT)) 
	{
		TestWorld1.setCamX(TestWorld1.getCamX()+TestWorld1.getTimeDelta()*0.25*(sinf(0.01745*TestWorld1.getCamAngleY())));
		TestWorld1.setCamZ(TestWorld1.getCamZ()-TestWorld1.getTimeDelta()*0.25*(cosf(0.01745*TestWorld1.getCamAngleY())));
	}
	if(TDML::Input.getSpecialKeyState(GLUT_KEY_LEFT))
	{
		TestWorld1.setCamX(TestWorld1.getCamX()-TestWorld1.getTimeDelta()*0.25*(sinf(0.01745*TestWorld1.getCamAngleY())));
		TestWorld1.setCamZ(TestWorld1.getCamZ()+TestWorld1.getTimeDelta()*0.25*(cosf(0.01745*TestWorld1.getCamAngleY())));
	}
	if(TDML::Input.getSpecialKeyState(GLUT_KEY_LEFT)) TestWorld1.setCamX(TestWorld1.getCamX()+TestWorld1.getTimeDelta()*0.25);
	if(TDML::Input.getSpecialKeyState(GLUT_KEY_RIGHT)) TestWorld1.setCamX(TestWorld1.getCamX()-TestWorld1.getTimeDelta()*0.25);
	//if(TDML::Input.getSpecialKeyState(GLUT_KEY_DOWN)) TestWorld1.setCamZ(TestWorld1.getCamZ()-TestWorld1.getTimeDelta()*0.25);
	//if(TDML::Input.getSpecialKeyState(GLUT_KEY_UP))TestWorld1.setCamZ(TestWorld1.getCamZ()+TestWorld1.getTimeDelta()*0.25);
	//TestWorld1.setCamAngleY(TestWorld1.getCamAngleY()+0.5);
	//TestWorld1.setCamAngleZ(TestWorld1.getCamAngleZ()+0.5);
	TestWorld1.setCamAngleX((TDML::Input.getMouseY()-250)/2);
	TestWorld1.setCamAngleY((TDML::Input.getMouseX()-250)/2);
}

void animate()
{
	TestWorld1.update();
	keyboard();
	specialKeyboard();
}

int main(int argc, char** argv)
{
	TDML::setupAll(&argc, argv, 500, 500, "3D Model Loader - Testbed", 0.5, 0.8, 1.0, display, animate, exit);
	//TDML::hideCursor();
	cout << "Loading World"<<endl;
	TestWorld1 = TDML::loadWorld("world1.wor");
	cout << "Done. " << endl;
	TestWorld1.setCamPosition(0.0, 0.0, 100.0);
	TDML::start();
	return 0;
}