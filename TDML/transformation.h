//transformation.h
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#pragma once

#include "TDML.h"

namespace TDML
{
	class transformation
	{
		public:
			transformation();
			void loadIdentity();
			matrix3x3 rotation;
			vector3d translation;
			matrix4x4 toMat4x4();
			void rotate(float x, float y, float z, int order);
			void translate(float x, float y, float z);
			void scale(float x, float y, float z);
			float* glForm();
	};
}