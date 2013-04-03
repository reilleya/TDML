//window.h
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#pragma once

#include "TDML.h"

namespace TDML
{
	class window
	{
		private:
			int width;
			int height;
			int posx;
			int posy;
			bool fullscreen;
			void correct();

		public:
			int getWidth();
			int getHeight();
			void setSize(int newWidth, int newHeight);
			void updateSize(int newWidth, int newHeight);
			int getXPos();
			int getYPos();
			void setPos(int x, int y);
			void updatePos(int x, int y);
			void setFullscreen(bool full);
			void centerWindow();
			void hideCursor();
			void showCursor();
			void setSkyColor(float SkyRed, float SkyGreen, float SkyBlue);
			void minimize();
			void maximize();
	};
}