//transformation.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	transformation::transformation()
	{
		rotation = matrix3x3();
		translation = vector3d(0,0,0);
	}

	void transformation::loadIdentity()
	{
		rotation = matrix3x3();
		translation = vector3d(0,0,0);
	}

	matrix4x4 transformation::toMat4x4()
	{
		matrix4x4 m = matrix4x4();
		m.p11 = rotation.p11; m.p12 = rotation.p12; m.p13 = rotation.p13; m.p41 = 0;
		m.p21 = rotation.p21; m.p22 = rotation.p22; m.p23 = rotation.p23; m.p41 = 0;
		m.p31 = rotation.p31; m.p32 = rotation.p12; m.p33 = rotation.p33; m.p41 = 0;
		m.p41 = translation.x; m.p12 = translation.y; m.p13 = translation.z; m.p41 = 1;

	}

	void transformation::rotate(float x, float y, float z, int order)
	{
		matrix3x3 rot;

		matrix3x3 xrot = matrix3x3();
		xrot.xRotFromAngle(x);

		matrix3x3 yrot = matrix3x3();
		yrot.yRotFromAngle(y);

		matrix3x3 zrot = matrix3x3();
		zrot.zRotFromAngle(z);

		switch(order)
		{
			case 0:
				rot = (xrot*yrot) * zrot;
				break;

			case 1:
				rot = (xrot*zrot) * yrot;
				break;

			case 2:
				rot = (zrot*yrot) * xrot;
				break;

			case 3:
				rot = (zrot*xrot) * yrot;
				break;

			case 4:
				rot = (yrot*xrot) * zrot;
				break;

			case 5:
				rot = (yrot*zrot) * xrot;
				break;
		}
		rotation = rot * rotation;
	}

	void transformation::translate(float x, float y, float z)
	{
		translation += vector3d(x,y,z);
	}

	void transformation::scale(float x, float y, float z)
	{
		rotation.p11 *= x;
		rotation.p22 *= y;
		rotation.p33 *= z;
	}

	float* transformation::glForm()
	{
		float glFormArray[16] = { 
		rotation.p11, rotation.p12, rotation.p13, 0,
		rotation.p21, rotation.p22, rotation.p23, 0,
		rotation.p31, rotation.p32, rotation.p33, 0,
		translation.x, translation.y, translation.z, 1,
		};
		return glFormArray;
	}
}