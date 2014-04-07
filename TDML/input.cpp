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
		keyspressed = new bool[256];
		for(int k = 0; k < 256; k++) keyspressed[k] = false;
		specialkeyspressed = new bool[256];
		for(int sk = 0; sk < 256; sk++) specialkeyspressed[sk] = false;
		mousekeys = new bool[5];
		for(int mk = 0; mk < 5; mk++) mousekeys[mk] = false;
		mousekeypresses = new bool[5];
		for(int mkp = 0; mkp < 5; mkp++) mousekeypresses[mkp] = false;
		xpos=0;
		ypos=0;
		centerPerFrame = false;
		centerNextFrame = true;
	}

	void input::update()
	{
		Input.resetMouseKeyPressed();
		Input.resetKeysPressed();
		if(centerPerFrame)
		{
			if(centerNextFrame)
			{
				centerCursor();
			}
			centerNextFrame = !centerNextFrame;
		}
	}

	bool input::getKeyState(char key)
	{
		return keys[key];
	}

	bool input::getSpecialKeyState(int key)
	{
		return specialkeys[key];
	}

	bool input::getKeyPressed(char key)
	{
		return keyspressed[key];
	}

	bool input::getSpecialKeyPressed(int key)
	{
		return specialkeyspressed[key];
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

	int input::getMouseXCenterDiff()
	{
		if (centerNextFrame)
		{
			return xpos - (Window.getWidth() / 2);
		}
		else
		{
			return lxpos - (Window.getWidth() / 2);
		}
	}

	int input::getMouseYCenterDiff()
	{
		if (centerNextFrame)
		{
			return ypos - (Window.getHeight() / 2);
		}
		else
		{
			return lypos - (Window.getHeight() / 2);
		}
	}

	void input::KeyDownFunc(unsigned char key, int x, int y)
	{
		keys[key] = true;
		keyspressed[key] = true;
	}

	void input::KeyUpFunc(unsigned char key, int x, int y)
	{
		keys[key] = false;
	}

	void input::SpecialKeyDownFunc(int key, int x, int y)
	{
		specialkeys[key] = true;
		specialkeyspressed[key] = true;
	}

	void input::SpecialKeyUpFunc(int key, int x, int y)
	{
		specialkeys[key]=false;
	}

	void input::MouseKeyFunc(int button, int state, int x, int y)
	{
		state =! state;
		if(button != 3 && button != 4)
		{
			mousekeypresses[button] = (state != 0);
			mousekeys[button] = (state != 0);
		}
		else
		{
			if(!mousekeypresses[button])
			{
				mousekeypresses[button] = true;
				mousekeys[button] = true;
			}
		}
	}

	void input::MousePosFunc(int x, int y)
	{
		lxpos = xpos;
		lypos = ypos;
		xpos = x;
		ypos = y;
	}

	void input::resetMouseKeyPressed()
	{
		mousekeypresses[0] = false;
		mousekeypresses[1] = false;
		mousekeypresses[2] = false;
		mousekeypresses[3] = false;
		mousekeypresses[4] = false;
		mousekeys[3] = false;
		mousekeys[4] = false;
	}

	void input::resetKeysPressed()
	{
		for(int k = 0; k < 256; k++) keyspressed[k] = false;
		for(int sk = 0; sk < 256; sk++) specialkeyspressed[sk] = false;
	}

	void input::setCursorPosition(int x, int y)
	{
		glutWarpPointer(x, y);
	}

	void input::centerCursor()
	{
		glutWarpPointer(Window.getWidth()/2, Window.getHeight()/2);
	}

	void input::setCenterCursor(bool center)
	{
		centerPerFrame = center;
	}

	bool input::getCenterCursor()
	{
		return centerPerFrame;
	}
}