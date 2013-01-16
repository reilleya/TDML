//poly.h
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#pragma once

#include "TDML.h"

namespace TDML
{
	class poly
	{
		private:
			//std::vector<point> points;
			point* points[3];
			int npoints;

		public:
			poly();
			//point* getPoints();
			void addPoint(float x,float y,float z, float nX, float nY, float nZ);
			float getX(int point);
			float getY(int point);
			float getZ(int point);
			float getNormalX(int point);
			float getNormalY(int point);
			float getNormalZ(int point);
			void removePoints();
	};
}