//point.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	float point::getX()
	{
		return x;
	}
	void point::setX(float newX)
	{
		x = newX;
	}

	float point::getY()
	{
		return y;
	}

	void point::setY(float newY)
	{
		y = newY;
	}

	float point::getZ()
	{
		return z;
	}

	float point::getNormalX()
	{
		return normalx;
	}

	float point::getNormalY()
	{
		return normalx;
	}

	float point::getNormalZ()
	{
		return normalz;
	}

	void point::setZ(float newZ)
	{
		z = newZ;
	}

	void point::setNormals(float newX, float newY, float newZ)
	{
		normalx = newX;
		normaly = newY;
		normalz = newZ;
	}

	void point::setPos(float newX, float newY, float newZ)
	{
		x=newX;
		y=newY;
		z=newZ;
	}

	void point::moveX(float value)
	{
		x += value;
	}

	void point::moveY(float value)
	{
		y += value;
	}

	void point::moveZ(float value)
	{
		z += value;
	}
}