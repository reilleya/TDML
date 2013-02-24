#include "TDML.h"

using namespace std;

//TDML::world world1;
//TDML::menu menu1;

void exit()
{
	
}

void display ()
{
	//world1.draw();
	//menu1.draw();
}


void animate()
{
	/*TDML::object& cube = world1.getObjectRef("tv");
	cube.setYangle(cube.getYangle()+0.05);
	if(TDML::Input.getMouseKeyPressed(LEFTMOUSE))
	{
		if(cube.getFrame()==2) cube.setFrame(0);
		else cube.setFrame(cube.getFrame()+1);
	}
	world1.update();*/
}

int main(int argc, char** argv)
{
	TDML::Log.setDebugMode(true);
	TDML::Log.output("Hello, World!\n");
	TDML::setupAll(&argc, argv, 500, 500, "3D Model Loader - Matrix Testbed", 1.0, 1.0, 1.0, display, animate, exit);
	TDML::matrix3x3 m1 = TDML::matrix3x3();
	m1.xRotFromAngle(90);
	m1.dispInfo();
	TDML::Log.output("\n");
	TDML::matrix3x3 m2 = TDML::matrix3x3();
	m2.yRotFromAngle(45);
	m2.dispInfo();
	TDML::Log.output("\n");
	TDML::matrix3x3 m3 = TDML::matrix3x3();
	m3.zRotFromAngle(-15);
	m3.dispInfo();
	TDML::Log.output("\n");
	TDML::matrix3x3 m4 = (m1*m2)*m3;
	m4.dispInfo();
	TDML::start();
	return 0;
}