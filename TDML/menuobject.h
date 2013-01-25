//menuobject.h
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#pragma once

#include "TDML.h"

namespace TDML
{
	class menuobject
	{
		private:
			int posx;
			int posy;
			int width;
			int height;
			int texid;
			std::string texname;

		public:
			menuobject();
			//void dispInfo();
			void draw();
			void loadTexture();
			int getPosX();
			int getPosY();
			int getWidth();
			int getHeight();
			void setPosX(int posX);
			void setPosY(int posY);
			void setWidth(int newWidth);
			void setHeight(int newHeight);
			void setTexture(std::string newTex);
	};
}