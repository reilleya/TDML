//world.h
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#pragma once

#include "TDML.h"

namespace TDML
{
	class world
	{
		private:
			bool hasterrain;
			unsigned int timer;
			int nobjs;
			float lastTime;
			float timeElapsed;
			std::vector<object> objects;
			terrain map;
			float camx;
			float camy;
			float camz;
			float camxangle;
			float camyangle;
			float camzangle;

		public:
			world();
			void update();
			float getTimeDelta();
			float getAdjustedTime(float value, float targetTimeStep);
			unsigned int getTimer();
			void draw();
			void addObject(object Obj);
			void setTerrain(terrain newterrain);
			void setCamAngleX(float newXangle);
			void setCamAngleY(float newYangle);
			void setCamAngleZ(float newZangle);
			void setCamAngle(float newXangle, float newYangle, float newZangle);
			void setCamPosition(float newX, float newY, float newZ);
			float getCamAngleX();
			float getCamAngleY();
			float getCamAngleZ();
			void setCamX(float newX);
			void setCamY(float newY);
			void setCamZ(float newZ);
			float getCamX();
			float getCamY();
			float getCamZ();
			int getFirstIDByName(std::string name);
			object getFirstObjByName(std::string name);
			//vector<int> getIDsByName(std::string name);
			//vector<object*>* getObjsByName(std::string name);
			std::vector<object> getObjects();
			object getObjectById(int id);
			object& getObjectRef(std::string Name);
			//vector<object*>* getObjectsById(int* ids);
			float getHeightMapAt(float x, float z);
			float getObjAttribute(std::string name, std::string attr);
			void setObjAttribute(std::string name, std::string attr, float value);
			float getDistance(std::string firstName, std::string secondName);
			bool getBBCollideName(std::string firstName, std::string secondName);
			bool getBBCollideType(std::string name, std::string type);
			bool getBoundingSphereCollide(std::string firstName, std::string secondName);
	};
}