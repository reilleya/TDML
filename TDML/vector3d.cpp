//vector3d.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	vector3d::vector3d(float nx, float ny, float nz)
	{
		x = nx;
		y = ny;
		z = nz;
	}

	vector3d::vector3d(float x1, float y1, float z1, float x2, float y2, float z2)
	{
		x = x1-x2;
		y = y1-y2;
		z = z1-z2;
	}

	vector3d vector3d::operator + (vector3d v2)
	{
		vector3d temp = vector3d(0,0,0);
		temp.x = x + v2.x;
		temp.y = y + v2.y;
		temp.z = z + v2.z;
		return temp;
	}

	vector3d vector3d::operator - (vector3d v2)
	{
		vector3d temp = vector3d(0,0,0);
		temp.x = x - v2.x;
		temp.y = y - v2.y;
		temp.z = z - v2.z;
		return temp;
	}

	float vector3d::operator * (vector3d v2)
	{
		//Dot Product
		return (x * v2.x)+(y * v2.y)+(z * v2.z);
	}

	vector3d vector3d::operator * (float s)
	{
		//Scalar Product
		vector3d temp = vector3d(0,0,0);
		temp.x = x * s;
		temp.y = y * s;
		temp.z = z * s;
		return temp;
	}

	vector3d vector3d::operator ^ (vector3d v2)
	{
		//Cross Product
		vector3d temp = vector3d(0,0,0);
		temp.x = (y * v2.z) - (v2.y * z);
		temp.y = (z * v2.x) - (v2.z * x);
		temp.z = (x * v2.y) - (v2.x * y);
		return temp;
	}

	float vector3d::magnitude()
	{
		return sqrt((x*x)+(y*y)+(z*z));
	}

	float vector3d::angle_to(vector3d v2)
	{
		return Math.arccos(((x * v2.x)+(y * v2.y)+(z * v2.z))/(magnitude()*v2.magnitude()));
	}

	void vector3d::print()
	{
		Log.output("(");
		Log.output(x);
		Log.output(", ");
		Log.output(y);
		Log.output(", ");
		Log.output(z);
		Log.output(")\n");
	}
}