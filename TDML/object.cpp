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
		drawingBB = false;
	}

	void object::dispInfo()
	{
		Log.output("Object:\n");
		Log.output("\tFilename: "); Log.output(fileName); Log.output("\n");
		Log.output("\tName: "); Log.output(name); Log.output("\n");
		Log.output("\tType: "); Log.output(type); Log.output("\n");
		Log.output("\tPolys: "); Log.output((float)npolys); Log.output("\n");
		Log.output("\tPosition: "); Log.output(x); Log.output(", "); Log.output(y); Log.output(", "); Log.output(z); Log.output("\n");
		Log.output("\tAngle: "); Log.output(xangle); Log.output(", "); Log.output(yangle); Log.output(", "); Log.output(zangle); Log.output("\n");
		Log.output("\tScale: "); Log.output(scalex); Log.output(", "); Log.output(scaley); Log.output(", "); Log.output(scalez); Log.output("\n");
		Log.output("\tRadius: "); Log.output(radius); Log.output("\n");
		Log.output("\tDimensions: "); Log.output(xsize); Log.output(", "); Log.output(ysize); Log.output(", "); Log.output(zsize); Log.output("\n");
		Log.output("\tBehaviours: "); Log.output((float)nbehaviors); Log.output("\n");
		Log.output("\tAdjust bounding box: "); Log.output(adjustBB); Log.output("\n");
		Log.output("\tDraw bounding box: "); Log.output(drawingBB); Log.output("\n");
		Log.output("\tVisible: "); Log.output(visible); Log.output("\n");
		Log.output("\tWireframe: "); Log.output(wireframe); Log.output("\n");
		Log.output("\tAnimated Texture framedelay: "); Log.output(framedelay); Log.output("\n");
		Log.output("\tAnimated Texture frametime: "); Log.output(frametime); Log.output("\n");
		Log.output("\tUpdate Function Set: "); Log.output(updateFuncSet); Log.output("\n");
		Log.output("\tVBO ID: "); Log.output((float)vboid); Log.output("\n");
		Log.output("\tVAO ID: "); Log.output((float)vaoid); Log.output("\n");
	}

	void object::display()
	{
		if(visible)
		{
			bindBuffer(VBO, vboid);
			bindBuffer(TEX, material.getID(frame));
			bindBuffer(VAO, vaoid);
			if(wireframe) glDrawArrays(GL_LINES, 0, npolys*3); //-1 is a hack! FIX THE ROOT CAUSE!
			else glDrawArrays(GL_TRIANGLES, 0, npolys*3);
		}
	}

	void object::drawBB()
	{
		Draw3D.cube(adjustedmaxx+adjustedminx, adjustedmaxy+adjustedminy, adjustedmaxz+adjustedminz,
			xangle, yangle, zangle, 
			adjustedmaxx-adjustedminx, adjustedmaxy-adjustedminy, adjustedmaxz-adjustedminz, 
			255, 0, 0, 255, false);
	}

	void object::update()
	{
		if(updateFuncSet) updatefunction(this);
		if(framedelay!=0)
		{
			frametime -= Clock.getTimeDelta();
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
					x = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * (float)0.01745 * Clock.getTimer()));
				}
				else 
				{
					x += behaviors[b].speed * Clock.getTimeDelta();
				}
			}
			if(behaviors[b].type=="y")
			{
				if(behaviors[b].repeat)
				{
					if (!behaviors[b].relative) y = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * (float)0.01745 * Clock.getTimer()));
					if (behaviors[b].relative) y += behaviors[b].max * sin(behaviors[b].speed * (float)0.01745 * Clock.getTimer());
				}
				else 
				{
					y += behaviors[b].speed * Clock.getTimeDelta();
				}

			}
			if(behaviors[b].type=="z")
			{
				if(behaviors[b].repeat)
				{
					z = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * (float)0.01745 * Clock.getTimer()));
				}
				else 
				{
					z += behaviors[b].speed * Clock.getTimeDelta();
				}
			}
			if(behaviors[b].type=="xangle")
			{
				if(behaviors[b].repeat)
				{
					xangle = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * (float)0.01745 * Clock.getTimer()));
				}
				else 
				{
					xangle += behaviors[b].speed * Clock.getTimeDelta();
				}
				}
			if(behaviors[b].type=="yangle")
			{
				if(behaviors[b].repeat)
				{
					yangle = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * (float)0.01745 * Clock.getTimer()));
				}
				else 
				{
					yangle += behaviors[b].speed * Clock.getTimeDelta();
				}
			}
			if(behaviors[b].type=="zangle")
			{
				if(behaviors[b].repeat)
				{
					zangle = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * (float)0.01745 * Clock.getTimer()));
				}
				else 
				{
					zangle += behaviors[b].speed * Clock.getTimeDelta();
				}
			}
			if(behaviors[b].type=="scalex")
			{
				if(behaviors[b].repeat)
				{
					scalex = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * (float)0.01745 * Clock.getTimer()));
				}
				else 
				{
					scalex += behaviors[b].speed * Clock.getTimeDelta();
				}
			}
			if(behaviors[b].type=="scaley")
			{
				if(behaviors[b].repeat)
				{
					scaley = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * (float)0.01745 * Clock.getTimer()));
				}
				else 
				{
					scaley += behaviors[b].speed * Clock.getTimeDelta();
				}
			}
			if(behaviors[b].type=="scalez")
			{
				if(behaviors[b].repeat)
				{
					scalez = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * (float)0.01745 * Clock.getTimer()));
				}
				else 
				{
					scalez += behaviors[b].speed * Clock.getTimeDelta();
				}
			}
			if(behaviors[b].type=="wireframe")
			{
				if (behaviors[b].min>0) behaviors[b].min -= Clock.getTimeDelta();
				else
				{
					behaviors[b].min = behaviors[b].max;
					wireframe = !wireframe;
				}
			}
			if(behaviors[b].type=="visible")
			{
				if (behaviors[b].min>0) behaviors[b].min -= Clock.getTimeDelta();
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
		points[0] = new point(maxx, maxy, maxz);
		points[1] = new point(maxx, maxy, minz);
		points[2] = new point(maxx, miny, maxz);
		points[3] = new point(maxx, miny, minz);
		points[4] = new point(minx, maxy, maxz);
		points[5] = new point(minx, maxy, minz);
		points[6] = new point(minx, miny, maxz);
		points[7] = new point(minx, miny, minz);

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

	void object::setDrawBB(bool draw)
	{
		drawingBB = draw;
	}

	bool object::getDrawBB()
	{
		return drawingBB;
	}

	void object::createBoundingSphere()
	{
		radius = 0;
		for(int p = 0; p<(int)npolys-1; p++)
		{
			for(int p1 = 0; p1<3; p1++)
			{
				float dist = sqrtf(
									(polygons[p].getX(p1)*scalex*polygons[p].getX(p1)*scalex)+
									(polygons[p].getY(p1)*scaley*polygons[p].getY(p1)*scaley)+
									(polygons[p].getZ(p1)*scalez*polygons[p].getZ(p1)*scalez)
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

	void object::setPosition(vector3d position)
	{
		x = position.x;
		y = position.y;
		z = position.z;
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

	void object::setAngle(vector3d newAngle)
	{
		if(newAngle.x!=xangle || newAngle.y!=yangle || newAngle.z!=zangle)
		{
			xangle = newAngle.x;
			yangle = newAngle.y;
			zangle = newAngle.z;
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
		vaoid = requestBuffer(VAO);
		bindBuffer(VAO, vaoid);

		vboid = requestBuffer(VBO);
		GLuint numverts = npolys*3;
		GLfloat *geometry;
		GLfloat *normals;
		GLfloat *coords;
		geometry = new GLfloat[3*numverts];
		normals = new GLfloat[3*numverts];
		coords = new GLfloat[2*numverts];
		for(int p = 0; p<(int)npolys; p++)
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
		bindBuffer(VBO, vboid);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*8*numverts, NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*3*numverts, geometry);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*3*numverts, sizeof(float)*2*numverts, coords);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*5*numverts, sizeof(float)*3*numverts, normals);


		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Position
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(npolys * 15 * sizeof(GLfloat))); // Normals
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(npolys * 9 * sizeof(GLfloat))); // Texture Coords

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		bindBuffer(VAO, 0);

		delete geometry;
		delete normals;
		delete coords;
	}

	int object::getVBOId()
	{
		return vboid;
	}

	void object::setVBOId(int newId)
	{
		vboid = newId;
	}

	int object::getVAOId()
	{
		return vaoid;
	}

	void object::setVAOId(int newId)
	{
		vaoid = newId;
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