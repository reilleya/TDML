//object.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	object::object()
	{
		nbehaviors = 0;
		npolys = 0;
		vboid = 0;
		frame = 0;
		visible = true;
		updateFuncSet = false;
		adjustBB = true;
	}

	void object::dispInfo()
	{
		Log.output("Object:\n");
		Log.output("\tName: "); Log.output(name); Log.output("\n");
		Log.output("\tType: "); Log.output(type); Log.output("\n");
		Log.output("\tPolys: "); Log.output((float)npolys); Log.output("\n");
		Log.output("\tPosition: "); Log.output(x); Log.output(", "); Log.output(y); Log.output(", "); Log.output(z); Log.output("\n");
		//Log.output
	}

	void object::display()
	{
		if(visible)
		{
			glBindBuffer(GL_ARRAY_BUFFER, vboid);
			glBindTexture(GL_TEXTURE_2D, material.getID(frame));
			glVertexPointer(3, GL_FLOAT, 0, 0);
			glTexCoordPointer(2, GL_FLOAT, 0, (GLvoid*)(npolys * 9 * sizeof(GLfloat)));
			glNormalPointer(GL_FLOAT, 0, (GLvoid*)(npolys * 15 * sizeof(GLfloat)));
			if(wireframe) glDrawArrays(GL_LINE_LOOP, 0, npolys*3);
			else glDrawArrays(GL_TRIANGLES, 0, npolys*3);
		}
	}

	void object::drawBB()
	{
		glBegin(GL_LINE_LOOP);
			glVertex3f(adjustedmaxx*scalex, adjustedmaxy*scaley, adjustedmaxz*scalez);
			glVertex3f(adjustedmaxx*scalex, adjustedminy*scaley, adjustedmaxz*scalez);
			glVertex3f(adjustedmaxx*scalex, adjustedminy*scaley, adjustedminz*scalez);
			glVertex3f(adjustedmaxx*scalex, adjustedmaxy*scaley, adjustedminz*scalez);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(adjustedminx*scalex, adjustedmaxy*scaley, adjustedmaxz*scalez);
			glVertex3f(adjustedminx*scalex, adjustedminy*scaley, adjustedmaxz*scalez);
			glVertex3f(adjustedminx*scalex, adjustedminy*scaley, adjustedminz*scalez);
			glVertex3f(adjustedminx*scalex, adjustedmaxy*scaley, adjustedminz*scalez);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(adjustedminx*scalex, adjustedmaxy*scaley, adjustedmaxz*scalez);
			glVertex3f(adjustedmaxx*scalex, adjustedmaxy*scaley, adjustedmaxz*scalez);
			glVertex3f(adjustedmaxx*scalex, adjustedmaxy*scaley, adjustedminz*scalez);
			glVertex3f(adjustedminx*scalex, adjustedmaxy*scaley, adjustedminz*scalez);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(adjustedminx*scalex, adjustedminy*scaley, adjustedmaxz*scalez);
			glVertex3f(adjustedmaxx*scalex, adjustedminy*scaley, adjustedmaxz*scalez);
			glVertex3f(adjustedmaxx*scalex, adjustedminy*scaley, adjustedminz*scalez);
			glVertex3f(adjustedminx*scalex, adjustedminy*scaley, adjustedminz*scalez);
		glEnd();
	}

	void object::update(int time, int timedelta)
	{
		if(updateFuncSet) updatefunction(this);
		if(framedelay!=0)
		{
			frametime -= timedelta;
			if(frametime <= 0)
			{
				if(frame < material.getLastID())
				{
					frame++;
				}
				else
				{
					frame = 0;
				}
				frametime = framedelay;
			}
		}
		for(int b = 0; b < nbehaviors; b++)
		{
			if(behaviors[b].type=="x")
			{
				if(behaviors[b].repeat)
				{
					x = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * (float)0.01745 * time));
				}
				else 
				{
					x += behaviors[b].speed * timedelta;
				}
			}
			if(behaviors[b].type=="y")
			{
				if(behaviors[b].repeat)
				{
					if(!behaviors[b].relative) y = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * (float)0.01745 * time));
					if(behaviors[b].relative) y += behaviors[b].max * sin(behaviors[b].speed * (float)0.01745 * time);
				}
				else 
				{
					y += behaviors[b].speed * timedelta;
				}

			}
			if(behaviors[b].type=="z")
			{
				if(behaviors[b].repeat)
				{
					z = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * (float)0.01745 * time));
				}
				else 
				{
					z += behaviors[b].speed * timedelta;
				}
			}
			if(behaviors[b].type=="xangle")
			{
				if(behaviors[b].repeat)
				{
					xangle = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * (float)0.01745 * time));
				}
				else 
				{
					xangle += behaviors[b].speed * timedelta;
				}
				}
			if(behaviors[b].type=="yangle")
			{
				if(behaviors[b].repeat)
				{
					yangle = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * (float)0.01745 * time));
				}
				else 
				{
					yangle += behaviors[b].speed * timedelta;
				}
			}
			if(behaviors[b].type=="zangle")
			{
				if(behaviors[b].repeat)
				{
					zangle = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * (float)0.01745 * time));
				}
				else 
				{
					zangle += behaviors[b].speed * timedelta;
				}
			}
			if(behaviors[b].type=="scalex")
			{
				if(behaviors[b].repeat)
				{
					scalex = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * (float)0.01745 * time));
				}
				else 
				{
					scalex += behaviors[b].speed * timedelta;
				}
			}
			if(behaviors[b].type=="scaley")
			{
				if(behaviors[b].repeat)
				{
					scaley = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * (float)0.01745 * time));
				}
				else 
				{
					scaley += behaviors[b].speed * timedelta;
				}
			}
			if(behaviors[b].type=="scalez")
			{
				if(behaviors[b].repeat)
				{
					scalez = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * (float)0.01745 * time));
				}
				else 
				{
					scalez += behaviors[b].speed * timedelta;
				}
			}
			if(behaviors[b].type=="wireframe")
			{
				if(behaviors[b].min>0) behaviors[b].min-=timedelta;
				else
				{
					behaviors[b].min = behaviors[b].max;
					wireframe = !wireframe;
				}
			}
			if(behaviors[b].type=="visible")
			{
				if(behaviors[b].min>0) behaviors[b].min-=timedelta;
				else
				{
						
					behaviors[b].min = behaviors[b].max;
					visible = !visible;
				}
			}
		}
	}

	void object::addBehavior(behavior newBehavior)
	{
		behaviors.resize(behaviors.size()+1);
		behaviors[behaviors.size()-1] = newBehavior;
		nbehaviors++;
	}

	void object::setMaterial(texture newTexture)
	{
		material = newTexture;
	}

	void object::addPoly(poly Polygon)
	{
		polygons.resize(polygons.size()+1);
		polygons[polygons.size()-1] = Polygon;
		npolys++;
		//object::createBoundingBox();
		//polygons[polygons.size()-1].calcNormals();
	}

	void object::createBoundingBox()
	{
		xsize=0;
		ysize=0;
		zsize=0;
		maxx=0;
		minx=0;
		maxy=0;
		miny=0;
		maxz=0;
		minz=0;
		for(int p = 0; p<(int)npolys-1; p++)
		{
			for(int p1 = 0; p1<3; p1++)
			{
				if(polygons[p].getX(p1)>maxx) maxx = polygons[p].getX(p1);
				if(polygons[p].getX(p1)<minx) minx = polygons[p].getX(p1);
				if(polygons[p].getY(p1)>maxy) maxy = polygons[p].getY(p1);
				if(polygons[p].getY(p1)<miny) miny = polygons[p].getY(p1);
				if(polygons[p].getZ(p1)>maxz) maxz = polygons[p].getZ(p1);
				if(polygons[p].getZ(p1)<minz) minz = polygons[p].getZ(p1);
			}
		}
		xsize = maxx - minx;
		ysize = maxy - miny;
		zsize = maxz - minz;
		recalcBoundingBox();
	}

	void object::recalcBoundingBox()
	{
		point* points[8];
		points[0] = new point();
		points[0]->setX(maxx);
		points[0]->setY(maxy);
		points[0]->setZ(maxz);

		points[1] = new point();
		points[1]->setX(maxx);
		points[1]->setY(maxy);
		points[1]->setZ(minz);

		points[2] = new point();
		points[2]->setX(maxx);
		points[2]->setY(miny);
		points[2]->setZ(maxz);

		points[3] = new point();
		points[3]->setX(maxx);
		points[3]->setY(miny);
		points[3]->setZ(minz);

		points[4] = new point();
		points[4]->setX(minx);
		points[4]->setY(maxy);
		points[4]->setZ(maxz);

		points[5] = new point();
		points[5]->setX(minx);
		points[5]->setY(maxy);
		points[5]->setZ(minz);

		points[6] = new point();
		points[6]->setX(minx);
		points[6]->setY(miny);
		points[6]->setZ(maxz);

		points[7] = new point();
		points[7]->setX(minx);
		points[7]->setY(miny);
		points[7]->setZ(minz);

		matrix3x3 xrot = matrix3x3();
		xrot.xRotFromAngle(xangle);

		matrix3x3 yrot = matrix3x3();
		yrot.yRotFromAngle(yangle);

		matrix3x3 zrot = matrix3x3();
		zrot.zRotFromAngle(zangle);

		matrix3x3 rot = (yrot*xrot) * zrot;

		for(int q = 0; q < 8; q++)
		{
			vector3d temp = vector3d(points[q]->getX(), points[q]->getY(), points[q]->getZ());
			temp = rot.apply(temp);
			points[q]->setX(temp.x);
			points[q]->setY(temp.y);
			points[q]->setZ(temp.z);
		}

		adjustedmaxx=0;
		adjustedminx=0;
		adjustedmaxy=0;
		adjustedminy=0;
		adjustedmaxz=0;
		adjustedminz=0;

		for(int q = 0; q < 8; q++)
		{
			if(points[q]->getX()>adjustedmaxx) adjustedmaxx = points[q]->getX();
			if(points[q]->getX()<adjustedminx) adjustedminx = points[q]->getX();
			if(points[q]->getY()>adjustedmaxy) adjustedmaxy = points[q]->getY();
			if(points[q]->getY()<adjustedminy) adjustedminy = points[q]->getY();
			if(points[q]->getZ()>adjustedmaxz) adjustedmaxz = points[q]->getZ();
			if(points[q]->getZ()<adjustedminz) adjustedminz = points[q]->getZ();
		}
	}

	void object::setAdjustBB(bool adjust)
	{
		adjustBB=adjust;
	}

	bool object::getAdjustBB()
	{
		return adjustBB;
	}

	void object::createBoundingSphere()
	{
		radius = 0;
		for(int p = 0; p<(int)npolys-1; p++)
		{
			for(int p1 = 0; p1<3; p1++)
			{
				float dist = sqrt(
									pow(polygons[p].getX(p1)*scalex,2)+
									pow(polygons[p].getY(p1)*scaley,2)+
									pow(polygons[p].getZ(p1)*scalez,2)
								);
				if(dist > radius)
				{
					radius = dist;
				}
			}
		}
	}

	int object::getSize()
	{
		return npolys;
	}

	void object::removePolygons()
	{
		polygons.resize(0);
	}

	void object::setWireframe(bool wframe)
	{
		wireframe = wframe;
	}

	bool object::getWireframe()
	{
		return wireframe;
	}

	void object::setVisible(bool vis)
	{
		visible = vis;
	}

	bool object::getVisible()
	{
		return visible;
	}

	float object::getX()
	{
		return x;
	}

	void object::setX(float newX)
	{
		x = newX;
	}

	float object::getY()
	{
		return y;
	}

	void object::setY(float newY)
	{
		y = newY;
	}

	float object::getZ()
	{
		return z;
	}

	void object::setZ(float newZ)
	{
		z = newZ;
	}

	void object::setPosition(float newX, float newY, float newZ)
	{
		x=newX;
		y=newY;
		z=newZ;
	}

	float object::getXangle()
	{
		return xangle;
	}

	void object::setXangle(float newXangle)
	{
		if(newXangle!=xangle)
		{
			xangle = newXangle;
			if(adjustBB)recalcBoundingBox();
		}
	}

	float object::getYangle()
	{
		return yangle;
	}

	void object::setYangle(float newYangle)
	{
		if(newYangle!=yangle)
		{
			yangle = newYangle;
			if(adjustBB)recalcBoundingBox();
		}
	}

	float object::getZangle()
	{
		return zangle;
	}

	void object::setZangle(float newZangle)
	{
		if(newZangle!=zangle)
		{
			zangle = newZangle;
			if(adjustBB)recalcBoundingBox();
		}
	}

	void object::setAngle(float newXangle, float newYangle, float newZangle)
	{
		if(newXangle!=xangle || newYangle!=yangle || newZangle!=zangle)
		{
			xangle = newXangle;
			yangle = newYangle;
			zangle = newZangle;
			if(adjustBB)recalcBoundingBox();
		}
	}

	float object::getScaleX()
	{
		return scalex;
	}

	void object::setScaleX(float newScaleX)
	{
		scalex = newScaleX;
	}

	float object::getScaleY()
	{
		return scaley;
	}

	void object::setScaleY(float newScaleY)
	{
		scaley = newScaleY;
	}

	float object::getScaleZ()
	{
		return scalez;
	}

	void object::setScaleZ(float newScaleZ)
	{
		scalez = newScaleZ;
	}

	void object::setScale(float newScaleX, float newScaleY, float newScaleZ)
	{
		scalex = newScaleX;
		scaley = newScaleY;
		scalez = newScaleZ;
	}

	void object::setName(string newName)
	{
		name=newName;
	}

	void object::setType(string newType)
	{
		type=newType;
	}

	string& object::getName()
	{
		return name;
	}

	string& object::getType()
	{
		return type;
	}

	void object::generateVBO()
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glGenBuffers(1, &vboid);
		GLuint numverts = npolys*3;
		GLfloat *geometry;
		GLfloat *normals;
		GLfloat *coords;
		GLuint *indices;
		geometry = new GLfloat[3*numverts];
		normals = new GLfloat[3*numverts];
		indices = new GLuint[npolys];
		coords = new GLfloat[2*numverts];
		for(int p = 0; p<(int)npolys-1; p++)
		{
			geometry[(p*9)] = polygons[p].getX(0);
			geometry[(p*9)+1] = polygons[p].getY(0);
			geometry[(p*9)+2] = polygons[p].getZ(0);
			normals[(p*9)] = polygons[p].getNormalX(0);
			normals[(p*9)+1] = polygons[p].getNormalY(0);
			normals[(p*9)+2] = polygons[p].getNormalZ(0);
			coords[(p*6)] = material.coords[p][0][0];
			coords[(p*6)+1] = material.coords[p][0][1];

			geometry[(p*9)+3] = polygons[p].getX(1);
			geometry[(p*9)+4] = polygons[p].getY(1);
			geometry[(p*9)+5] = polygons[p].getZ(1);
			normals[(p*9)+3] = polygons[p].getNormalX(1);
			normals[(p*9)+4] = polygons[p].getNormalY(1);
			normals[(p*9)+5] = polygons[p].getNormalZ(1);
			coords[(p*6)+2] = material.coords[p][1][0];
			coords[(p*6)+3] = material.coords[p][1][1];

			geometry[(p*9)+6] = polygons[p].getX(2);
			geometry[(p*9)+7] = polygons[p].getY(2);
			geometry[(p*9)+8] = polygons[p].getZ(2);
			normals[(p*9)+6] = polygons[p].getNormalX(2);
			normals[(p*9)+7] = polygons[p].getNormalY(2);
			normals[(p*9)+8] = polygons[p].getNormalZ(2);
			coords[(p*6)+4] = material.coords[p][2][0];
			coords[(p*6)+5] = material.coords[p][2][1];
		}
		glBindBuffer(GL_ARRAY_BUFFER, vboid);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*8*numverts, NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*3*numverts, geometry);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*3*numverts, sizeof(float)*2*numverts, coords);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*5*numverts, sizeof(float)*3*numverts, normals);
	}

	int object::getVBOId()
	{
		return vboid;
	}

	void object::setVBOId(int newId)
	{
		vboid = newId;
	}

	float object::getMaxX()
	{
		return x+(adjustedmaxx*scalex);
	}

	float object::getMinX()
	{
		return x+(adjustedminx*scalex);
	}

	float object::getMaxY()
	{
		return y+(adjustedmaxy*scaley);
	}

	float object::getMinY()
	{
		return y+(adjustedminy*scaley);
	}

	float object::getMaxZ()
	{
		return z+(adjustedmaxz*scalez);
	}

	float object::getMinZ()
	{
		return z+(adjustedminz*scalez);
	}

	float object::getRadius()
	{
		return radius;
	}

	int object::getFrame()
	{
		return frame;
	}

	float object::getFrameDelay()
	{
		return framedelay;
	}
			
	void object::setFrameDelay(float newFrameDelay)
	{
		framedelay = newFrameDelay;
		frametime = newFrameDelay;
	}

	void object::setFrame(int newFrame)
	{
		frame = newFrame;
	}

	void object::setUpdateFunction(void (*newupdatefunction)(TDML::object* me))
	{
		updatefunction = *newupdatefunction;
		updateFuncSet = true;
	}

	void object::setFileName(std::string newFileName)
	{
		fileName = newFileName;
	}

	std::string object::getFileName()
	{
		return fileName;
	}
}