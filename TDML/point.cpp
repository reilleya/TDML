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
	point::point()
	{
		x = 0;
		y = 0;
		z = 0;
		normalx = 0;
		normaly = 0;
		normalz = 0;
	}

	point::point(float nX, float nY, float nZ)
	{
		x = nX;
		y = nY;
		z = nZ;
		normalx = 0;
		normaly = 0;
		normalz = 0;
	}

	point::point(float nX, float nY, float nZ, float nnX, float nnY, float nnZ)
	{
		x = nX;
		y = nY;
		z = nZ;
		normalx = nnX;
		normaly = nnY;
		normalz = nnZ;
	}

	void point::dispInfo()
	{
		Log.output("Point:\n");
		Log.output("\tCoordinates: "); Log.output(x); Log.output(", "); Log.output(y); Log.output(", "); Log.output(z); Log.output(";\n");
		Log.output("\tNormal: "); Log.output(normalx); Log.output(", "); Log.output(normaly); Log.output(", "); Log.output(normalz); Log.output(";\n");
	}

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