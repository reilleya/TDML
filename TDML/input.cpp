//input.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	input::input()
	{
		keys = new bool[256];
		for(int k = 0; k < 256; k++) keys[k] = false;
		specialkeys = new bool[256];
		for(int sk = 0; sk < 256; sk++) specialkeys[sk] = false;
		mousekeys = new bool[3];
		for(int mk = 0; mk < 3; mk++) mousekeys[mk] = false;
		mousekeypresses = new bool[3];
		for(int mkp = 0; mkp < 3; mkp++) mousekeypresses[mkp] = false;
		xpos=0;
		ypos=0;
	}

	bool input::getKeyState(char key)
	{
		return keys[key];
	}

	bool input::getSpecialKeyState(int key)
	{
		return specialkeys[key];
	}

	bool input::getMouseKeyState(int key)
	{
		return mousekeys[key];
	}

	bool input::getMouseKeyPressed(int key)
	{
		return mousekeypresses[key];
	}

	int input::getMouseX()
	{
		return xpos;
	}

	int input::getMouseY()
	{
		return ypos;
	}

	void input::KeyDownFunc(unsigned char key, int x, int y)
	{
		keys[key] = true;
	}

	void input::KeyUpFunc(unsigned char key, int x, int y)
	{
		keys[key] = false;
	}

	void input::SpecialKeyDownFunc(int key, int x, int y)
	{
		specialkeys[key]=true;
	}

	void input::SpecialKeyUpFunc(int key, int x, int y)
	{
		specialkeys[key]=false;
	}

	void input::MouseKeyFunc(int button, int state, int x, int y)
	{
		state=!state;
		mousekeys[button]=state!=0;
		mousekeypresses[button]=state!=0;
	}

	void input::MousePosFunc(int x, int y)
	{
		xpos=x;
		ypos=y;
	}

	void input::resetMouseKeyPressed()
	{
		mousekeypresses[0]=false;
		mousekeypresses[1]=false;
		mousekeypresses[2]=false;
	}

	void input::setCursorPosition(int x, int y)
	{
		glutWarpPointer(x, y);
	}

	void input::centerCursor()
	{
		glutWarpPointer(Window.getWidth()/2, Window.getHeight()/2);
	}
}