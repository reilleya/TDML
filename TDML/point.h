//point.h
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#pragma once

#include "TDML.h"

namespace TDML
{
	class point
	{
		private:
			float x;
			float y;
			float z;
			float normalx;
			float normaly;
			float normalz;

		public:
			float getX();
			void setX(float newX);
			float getY();
			void setY(float newY);
			float getZ();
			void setZ(float newZ);
			void setNormals(float newX, float newY, float newZ);
			void setPos(float newX, float newY, float newZ);
			void moveX(float value);
			void moveY(float value);
			void moveZ(float value);
			float getNormalX();
			float getNormalY();
			float getNormalZ();
	};
}