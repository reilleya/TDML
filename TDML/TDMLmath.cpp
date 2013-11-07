//TDMLmath.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	TDMLmath::TDMLmath()
	{
		pi = (float)3.14159265359;
	}

	float TDMLmath::simpleRoundUp(float value)
	{
		return value+(1-fmodf(value,1));
	}

	float TDMLmath::simpleRoundDown(float value)
	{
		return value - fmodf(value,1);
	}

	float TDMLmath::round(float value, float interval, float offset)
	{
		float rounded;
		rounded = value - offset;
		rounded = rounded / interval;
		if(fmodf(rounded,1.0) < 0.5)
		{
			rounded = rounded - fmodf(rounded,1);
		}
		else
		{
			rounded = rounded+(1-fmodf(rounded,1));
		}

    return (rounded*interval)+offset;
	}

	float TDMLmath::larger(float value_a,  float value_b)
	{
		if(value_a>value_b) return value_a;
		else return value_b;
	}

	float TDMLmath::smaller(float value_a, float value_b)
	{
		if(value_a<value_b) return value_a;
		else return value_b;
	}

	float TDMLmath::distance(float x1, float y1, float z1, float x2, float y2, float z2)
	{
		return sqrtf(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2))+((z1-z2)*(z1-z2)));
	}

	float TDMLmath::radToDegree(float radians)
	{
		return (radians*180)/pi;
	}

	float TDMLmath::degreeToRad(float degrees)
	{
		return (degrees*pi)/180;
	}

	float TDMLmath::sin(float degrees)
	{
		return sinf(degreeToRad(degrees));
	}

	float TDMLmath::cos(float degrees)
	{
		return cosf(degreeToRad(degrees));
	}

	float TDMLmath::tan(float degrees)
	{
		return tanf(degreeToRad(degrees));
	}

	float TDMLmath::csc(float degrees)
	{
		return 1/(sin(degrees));
	}

	float TDMLmath::sec(float degrees)
	{
		return 1/(cos(degrees));
	}

	float TDMLmath::cot(float degrees)
	{
		return 1/(tan(degrees));
	}

	float TDMLmath::arcsin(float value)
	{
		return radToDegree(asin(value));
	}

	float TDMLmath::arccos(float value)
	{
		return radToDegree(acos(value));
	}

	float TDMLmath::arctan(float value)
	{
		return radToDegree(atan(value));
	}

	float TDMLmath::randomFloat()
	{
		return (((float)rand())/((float)RAND_MAX));
	}

	int TDMLmath::randomRangeInt(int min, int max)
	{
		return min + (rand()%(max-min));
	}

	float TDMLmath::randomRangeFloat(float min, float max)
	{
		return min + (randomFloat()*(max-min));
	}

	void TDMLmath::setupRandom()
	{
		srand((unsigned int)time(NULL));
	}

	bool TDMLmath::randomBool(int percentTrue)
	{
		if(Math.randomRangeInt(0, 100)<=percentTrue)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	float TDMLmath::plusOrMinus(float value)
	{
		value = abs(value);
		if(randomBool(50))
		{
			return -1*value;
		}
		else
		{
			return value;
		}
	}

	void TDMLmath::rotate(vector3d& vector, float angleX, float angleY, float angleZ, int order)
	{
		matrix3x3 xrot = matrix3x3();
		xrot.xRotFromAngle(angleX);

		matrix3x3 yrot = matrix3x3();
		yrot.yRotFromAngle(angleY);

		matrix3x3 zrot = matrix3x3();
		zrot.zRotFromAngle(angleZ);

		matrix3x3 rot;
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
		vector = rot.apply(vector);
	}

	vector3d TDMLmath::orbit(float x, float y, float z, float distance, float rotation, float inclination)
	{
		vector3d out;
		matrix4x4 rot;
		out.z-=distance;
		rot.rotate(inclination, rotation,0,XYZ);
		out = rot.apply(out);
		return out + vector3d(x, y, z);
	}

	vector3d TDMLmath::angleTo(float x1, float y1, float z1, float x2, float y2, float z2)
	{
		float dx = x1 - x2;
		float dy = y1 - y2;
		float dz = z1 - z2;
		float xangle;
		float yangle;
		if(dy>0) xangle = 270 + arctan(dz/dy);
		else xangle = 90 + arctan(dz/dy);
		if(dz<0) yangle = 180 + arctan(dx/dz);
		else yangle = arctan(dx/dz);
		return vector3d(xangle, yangle, 0);
	}

	float TDMLmath::angleBetween(float x1, float y1, float x2, float y2)
	{
		float dx = x2-x1;
		float dy = y2-y1;
		if(dy>=0) return 180+arctan(dx/dy);
		else return arctan(dx/dy);
	}
}