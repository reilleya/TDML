//draw3D.h
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#pragma once

#include "TDML.h"

namespace TDML
{
	class draw3D
	{
		private:
			int cubeVBO;
			int cubeVAO;

		public:
			void setup();
			void cube(float x, float y, float z, float xAngle, float yAngle, float zAngle, float xSize, float ySize, float zSize, float r, float g, float b, float a);
	};
}