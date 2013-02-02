//poly.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	poly::poly()
	{
		npoints=0;
	}

	void poly::dispInfo()
	{
		Log.output("Polygon:\n");
		Log.output("\tVertices: "); Log.output(npoints); Log.output("\n");
		for(int v = 0; v < npoints; v++)
		{
			Log.output("\tCoordinates: "); Log.output(points[v]->getX()); Log.output(", "); Log.output(points[v]->getY()); Log.output(", "); Log.output(points[v]->getZ()); Log.output(";\n");
			Log.output("\tNormal: "); Log.output(points[v]->getNormalX()); Log.output(", "); Log.output(points[v]->getNormalY()); Log.output(", "); Log.output(points[v]->getNormalZ()); Log.output(";\n");
		}
	}

	/*point* poly::getPoints()
	{
		return points;
	}*/

	void poly::addPoint(float x,float y,float z, float Nx,float Ny,float Nz)
	{
		points[npoints] = new point;
		points[npoints]->setPos(x,y,z);
		points[npoints]->setNormals(Nx,Ny,Nz);
		npoints++;
	}

	float poly::getX(int point)
	{
		return points[point]->getX();
	}

	float poly::getY(int point)
	{
		return points[point]->getY();
	}

	float poly::getZ(int point)
	{
		return points[point]->getZ();
	}

	float poly::getNormalX(int point)
	{
		return points[point]->getNormalX();
	}

	float poly::getNormalY(int point)
	{
		return points[point]->getNormalY();
	}

	float poly::getNormalZ(int point)
	{
		return points[point]->getNormalZ();
	}

	void poly::removePoints()
	{
		//TODO: Fix this!
	}
}