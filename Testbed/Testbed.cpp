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
	TDML::object& cube = world1.getObjectRef("cube");
	world1.update();
	//world1.setCamAngleX(world1.getCamAngleX()+0.05);
	if(TDML::Input.getMouseKeyState(0))
	{
		world1.setCamPosition(cube.getX(),50,cube.getZ());
		world1.setCamAngle(-90,0,0);
	}
	else
	{
		world1.setCamPosition(0,5,150);
		world1.setCamAngle(0,0,0);
	}
	if(TDML::Input.getKeyState('w')) cube.setZ(cube.getZ()-0.075);
	if(TDML::Input.getKeyState('s')) cube.setZ(cube.getZ()+0.075);
	if(TDML::Input.getKeyState('a')) cube.setX(cube.getX()-0.075);
	if(TDML::Input.getKeyState('d')) cube.setX(cube.getX()+0.075);
	cube.setY(world1.getHeightMapAt(cube.getX(),cube.getZ())+1);
	//TDML::Log.output(cube.getY()); TDML::Log.output("\n");
}

int main(int argc, char** argv)
{
	TDML::Log.setDebugMode(true);
	TDML::enableCulling(false);
	TDML::setupAll(&argc, argv, 500, 500, "3D Model Loader - Terrain Testbed", 0.5, 0.8, 1.0, display, animate, exit);
	world1 = TDML::loadWorld("world.wor");
	world1.setTerrain(TDML::loadTerrain("small.hgt", "height.png", 100, 0.1));
	//TDML::vector3d test1 = TDML::vector3d(50, 30, 20);
	///test1.print();
	//test1.normalize();
	//test1.print();
	//TDML::vector3d test2 = TDML::vector3d(28, 3, 23);
	//test2.print();
	//TDML::Log.output(test1.angle_to(test2));
	//TDML::vector3d test3 = test1^test2;
	//test3.print();
	TDML::start();
	return 0;
}