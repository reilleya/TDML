//input.h
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#pragma once

#include "TDML.h"

namespace TDML
{
	class input
	{
		private:
			bool* keys;
			bool* specialkeys;
			bool* mousekeys;
			bool* mousekeypresses;
			int xpos;
			int ypos;

		public:
			input();
			bool getKeyState(char key);
			bool getSpecialKeyState(int key);
			bool getMouseKeyState(int key);
			bool getMouseKeyPressed(int key);
			int getMouseX();
			int getMouseY();
			void KeyDownFunc(unsigned char key, int x, int y);
			void KeyUpFunc(unsigned char key, int x, int y);
			void SpecialKeyDownFunc(int key, int x, int y);
			void SpecialKeyUpFunc(int key, int x, int y);
			void MouseKeyFunc(int button, int state, int x, int y);
			void MousePosFunc(int x, int y);
			void resetMouseKeyPressed();
			void setCursorPosition(int x, int y);
			void centerCursor();
	};
}