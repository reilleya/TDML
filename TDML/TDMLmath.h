//TDMLmath.h
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#pragma once

#include "TDML.h"

namespace TDML
{
	class TDMLmath
	{
		public:
			float simpleRoundUp(float value);
			float simpleRoundDown(float value);
			float round(float value, float interval, float offset);
			float larger(float value_a,  float value_b);
			float smaller(float value_a, float value_b);
			float distance(float x1, float y1, float z1, float x2, float y2, float z2);
			float radToDegree(float rad);
			float degreeToRad(float degree);
			float sin(float degrees);
			float cos(float degrees);
			float tan(float degrees);
			float csc(float degrees);
			float sec(float degrees);
			float cot(float degrees);
			float arcsin(float value);
			float arccos(float value);
			float arctan(float value);
			float pi();
			void setupRandom();
			float randomFloat();
			int randomRangeInt(int min, int max);
			float randomRangeFloat(float min, float max);
			bool randomBool(int percentTrue);
			float plusOrMinus(float value);
			void rotate(vector3d& vector, float angleX, float angleY, float angleZ, int order);
			vector3d orbit(float x, float y, float z, float distance, float rotation, float inclination);
			vector3d angleTo(float x1, float y1, float z1, float x2, float y2, float z2);
	};
}