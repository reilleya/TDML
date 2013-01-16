//window.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{	
	void window::correct()
	{
		glutPositionWindow(posx, posy);
		glutReshapeWindow(width, height);
		if(fullscreen) glutFullScreen();
	}

	int window::getWidth()
	{
		return width;
	}

	int window::getHeight()
	{
		return height;
	}

	void window::setSize(int newWidth, int newHeight)
	{
		width = newWidth;
		height = newHeight;
		correct();
	}

	void window::updateSize(int newWidth, int newHeight)
	{
		width = newWidth;
		height = newHeight;
	}

	int window::getXPos()
	{
		return posx;
	}

	int window::getYPos()
	{
		return posy;
	}

	void window::setPos(int x, int y)
	{
		posx = x;
		posy = y;
		correct();
	}

	void window::updatePos(int x, int y)
	{
		posx = x;
		posy = y;
	}

	void window::setFullscreen(bool full)
	{
		fullscreen = full;
		correct();
	}

	void window::centerWindow()
	{
		posx = (int)((float)glutGet(GLUT_SCREEN_WIDTH)/2)-((float)width/2);
		posy = (int)((float)glutGet(GLUT_SCREEN_HEIGHT)/2)-((float)height/2);
		correct();
	}

	void window::hideCursor()
	{
		ShowCursor(false); 
	}

	void window::showCursor()
	{
		ShowCursor(true); 
	}
}