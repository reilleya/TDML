//object.h
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#pragma once

#include "TDML.h"

namespace TDML
{
	struct behavior
	{
		std::string type;
		float min;
		float max;
		bool repeat;
		bool relative;
		float speed;
	};

	class object
	{
		private:
			std::vector<poly> polygons;
			texture material;
			int frame;
			float framedelay;
			float frametime;
			bool wireframe;
			bool visible;
			float x;
			float y;
			float z;
			float scalex;
			float scaley;
			float scalez;
			float xangle;
			float yangle;
			float zangle;
			float xsize;
			float ysize;
			float zsize;
			float maxx;
			float minx;
			float maxy;
			float miny;
			float maxz;
			float minz;
			float adjustedmaxx;
			float adjustedminx;
			float adjustedmaxy;
			float adjustedminy;
			float adjustedmaxz;
			float adjustedminz;
			bool adjustBB;
			float radius;
			std::string name;
			std::string type;
			std::vector<TDML::behavior> behaviors;
			int nbehaviors;
			int npolys;
			bool updateFuncSet;
			void (*updatefunction)(object* me);
			GLuint vboid;
			GLuint vaoid;
			std::string fileName;

		public:
			object();
			void dispInfo();
			void display();
			void drawBB();
			void update(int time, int timedelta);
			void addBehavior(behavior newBehavior);
			void setMaterial(texture newTexture);
			void addPoly(poly Polygon);
			void createBoundingBox();
			void recalcBoundingBox();
			void setAdjustBB(bool adjust);
			bool getAdjustBB();
			void createBoundingSphere();
			int getSize();
			void removePolygons();
			void setWireframe(bool wframe);
			bool getWireframe();
			void setVisible(bool vis);
			bool getVisible();
			float getX();
			void setX(float newX);
			float getY();
			void setY(float newY);
			float getZ();
			void setZ(float newZ);
			void setPosition(float newX, float newY, float newZ);
			void setPosition(vector3d position);
			float getXangle();
			void setXangle(float newXangle);
			float getYangle();
			void setYangle(float newYangle);
			float getZangle();
			void setZangle(float newZangle);
			void setAngle(float newXangle, float newYangle, float newZangle);
			void setAngle(vector3d newAngle);
			float getScaleX();
			void setScaleX(float newScaleX);
			float getScaleY();
			void setScaleY(float newScaleY);
			float getScaleZ();
			void setScaleZ(float newScaleZ);
			void setScale(float newScaleX, float newScaleY, float newScaleZ);
			void setName(std::string newName);
			void setType(std::string newType);
			void generateVBO();
			int getVBOId();
			void setVBOId(int newId);
			int getVAOId();
			void setVAOId(int newId);
			std::string& getName();
			std::string& getType();
			float getMaxX();
			float getMinX();
			float getMaxY();
			float getMinY();
			float getMaxZ();
			float getMinZ();
			float getRadius();
			int getFrame();
			float getFrameDelay();
			void setFrameDelay(float newFrameDelay);
			void setFrame(int newFrame);
			void setUpdateFunction(void (*newupdatefunction)(object* me));
			void setFileName(std::string newFileName);
			std::string getFileName();
	};
}