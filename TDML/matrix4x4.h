//matrix4x4.h
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#pragma once

#include "TDML.h"
#include "matrix3x3.h"

namespace TDML
{
	class matrix4x4
	{
		public:
			float p11;
			float p12;
			float p13;
			float p14;
			float p21;
			float p22;
			float p23;
			float p24;
			float p31;
			float p32;
			float p33;
			float p34;
			float p41;
			float p42;
			float p43;
			float p44;
			matrix4x4();
			void dispInfo();
			void translate(float x, float y, float z);
			void rotate(float x, float y, float z, int order);
			void rotateAxis(float degrees, int axis);
			void applyRotation(matrix3x3& rot);
			void scale(float x, float y, float z);
			void loadIdentity();
			void perspective(float fieldOfView, float aspectRatio, float near, float far);
			void ortho(float left, float top, float right, float bottom, float nearZ, float farZ);
			void ortho2D(float left, float top, float right, float bottom);
			matrix3x3 rotPart();
			matrix4x4 operator * (matrix4x4 b);
			matrix4x4 operator * (matrix4x4* b);
			void timesEquals(matrix4x4& b);
			void copy(matrix4x4& b);
			vector3d apply(vector3d original);
			point apply(point original);
			float* glForm(); 
	};
}