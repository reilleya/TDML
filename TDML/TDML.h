//TDML.h
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

using namespace std;

#pragma once

#define RIGHT 102
#define LEFT 100
#define UP 101
#define DOWN 103
#define SPACE 32

#define XYZ 0
#define XZY 1
#define ZYX 2
#define ZXY 3
#define YXZ 4
#define YZX 5

#define GLEW_STATIC

#include "LodePNG.h"
#include <glew.h>
#include <Gl/freeglut.h>
#include <gl/gl.h>
#include <gl/glu.h> 
#include <windows.h>
#include <vector>
#include <string>
#include <math.h>
#include <iostream>
#include <time.h>
#include <fstream>
#include <ostream>

#include "point.h"
#include "poly.h"
#include "object.h"
#include "terrain.h"
#include "world.h"
#include "log.h"
#include "vector3d.h"
#include "input.h"
#include "window.h"
#include "menuobject.h"
#include "menu.h"
#include "TDMLmath.h"

namespace TDML
{
	extern std::vector<GLuint> cachedTexId;
	extern std::vector<std::string> cachedTexName;
	extern std::vector<GLuint> cachedVBOId;
	extern std::vector<std::string> cachedVBOName;
	extern std::vector<object> cachedObjs;
	extern std::vector<std::string> cachedObjName;

	object loadObject(std::string fileName);
	terrain loadTerrain(std::string imageName, std::string textureName, int scaleXZ, int scaleY);
	std::vector<behavior> loadBehaviors(std::string fileName);
	world loadWorld(std::string fileName);
	int loadTextureData(std::string fileName);
	texture loadTexture(std::string fileName);

	extern bool running;

	extern int crotorder;

	extern input Input;
	extern TDMLmath Math;
	extern window Window;
	extern log Log;

	extern void (*theirdisplayfunction)();
	extern void (*theirupdatefunction)();
	extern void (*theirexitfunction)();
	extern int nexttextureid;

	extern GLuint menuvboid;
	void setupMenuVBO();

	void ChannelKeyboardToInput(unsigned char key, int x, int y);
	void ChannelSpecialKeyboardToInput(int key, int x, int y);
	void ChannelKeyboardUpToInput(unsigned char key, int x, int y);
	void ChannelSpecialKeyboardUpToInput(int key, int x, int y);
	void ChannelMouseKeysToInput(int button, int state, int x, int y);
	void ChannelMouseMotionToInput(int x, int y);
	void setupInput();
	void reshape(int wi, int hi);
	void setupWindow (int *argc, char **argv, int width, int height, const char * title, float SkyRed, float SkyGreen, float SkyBlue);
	void setupFunctions(void (*displayfunction)(), void (*updatefunction)(), void (*exitfunction)());

	void setupAll(int *argc, char **argv, int width, int height, const char * title, float SkyRed, float SkyGreen, float SkyBlue, void (*displayfunction)(), void (*updatefunction)(), void (*exitfunction)());
	void start();
	void stop();

	void update();
	void display();
	void exit();

	void enableCulling(bool state);
	void setRotationOrder(int order);

	void setPause(bool state);
}