//matrix3x3.h
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#pragma once
#include "matrix4x4.h"
#include "TDML.h"

namespace TDML
{
	class matrix3x3
	{
		public:
			float p11;
			float p12;
			float p13;
			float p21;
			float p22;
			float p23;
			float p31;
			float p32;
			float p33;
			matrix3x3();
			//matrix3x3(matrix4x4 mat);
			void dispInfo();
			matrix3x3 operator * (matrix3x3 b);
			void xRotFromAngle(float angle);
			void yRotFromAngle(float angle);
			void zRotFromAngle(float angle);
			vector3d apply(vector3d original);
			point apply(point original);
	};
}