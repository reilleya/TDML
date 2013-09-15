//vector3d.h
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#pragma once

#include "TDML.h"

namespace TDML
{
	class vector3d 
	{
		public:
			float x;
			float y;
			float z;
			vector3d();
			vector3d(float nx, float ny, float nz);
			vector3d(float x1, float y1, float z1, float x2, float y2, float z2);
			void dispInfo();
			vector3d operator + (vector3d v2);
			void operator += (vector3d v2);
			vector3d operator - (vector3d v2);
			float operator * (vector3d v2); //Dot Product
			vector3d operator * (float s); //Scalar Product
			vector3d operator ^ (vector3d v2); //Cross Product
			float magnitude();
			float angle_to(vector3d v2);
			void normalize();
			void print();
	};
}