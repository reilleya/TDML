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
			float posx;
			float posy;
			float width;
			float height;
			int texid;
			bool updateFuncSet;
			void (*updatefunction)(menuobject* me);
			std::string texname;
			std::string name;

		public:
			menuobject();
			void update();
			std::string getName();
			void setName(std::string newName);
			void dispInfo();
			void draw();
			void loadTexture();
			float getPosX();
			float getPosY();
			float getWidth();
			float getHeight();
			void setPosX(float posX);
			void setPosY(float posY);
			void setWidth(float newWidth);
			void setHeight(float newHeight);
			void setTexture(std::string newTex);
			void setUpdateFunction(void (*newupdatefunction)(menuobject* me));
			bool pointCollide(float x, float y);
			bool rectCollide(float x, float y, float w, float h);
	};
}