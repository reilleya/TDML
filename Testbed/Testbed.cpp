#include "TDML.h"

using namespace std;

TDML::menu testmenu1;

void exit()
{
	
}

void display ()
{
	testmenu1.draw();
}


void animate()
{

}

int main(int argc, char** argv)
{
	TDML::Log.setDebugMode(true);
	TDML::setupAll(&argc, argv, 500, 500, "3D Model Loader - Vector Testbed", 0.5, 0.8, 1.0, display, animate, exit);
	testmenu1 = TDML::loadMenu("test.mnu");
	testmenu1.dispInfo();
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