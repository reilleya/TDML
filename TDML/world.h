//world.h
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#pragma once

#include "TDML.h"
#include "particlesystem.h"

namespace TDML
{
	class world
	{
		private:
			std::string fileName;
			bool hasterrain;
			int nobjs;
			int nparts;
			std::vector<object> objects;
			std::vector<particlesystem> particlesystems;
			terrain map;
			float camx;
			float camy;
			float camz;
			float camxangle;
			float camyangle;
			float camzangle;

		public:
			world();
			world(std::string filename);
			void dispInfo();
			void update();
			void draw();
			void addObject(object Obj);
			void setTerrain(terrain newterrain);
			void addParticleSystem(particlesystem newsystem);
			void setCamAngleX(float newXangle);
			void setCamAngleY(float newYangle);
			void setCamAngleZ(float newZangle);
			void setCamAngle(float newXangle, float newYangle, float newZangle);
			void setCamAngle(vector3d newAngle);
			void setCamPosition(float newX, float newY, float newZ);
			void setCamPosition(vector3d position);
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
			std::vector<object> getObjects();
			object getObjectById(int id);
			object& getObjectRef(std::string Name);
			void removeObjectById(int id);
			void removeObjectByName(std::string Name);
			void removeObjectByType(std::string Type);
			int getParticleSystemNameById(std::string Name);
			particlesystem& getParticleSystemRef(std::string Name);
			void removeParticleSystemById(int id);
			void removeParticleSystemByName(std::string Name);
			//vector<object*>* getObjectsById(int* ids);
			terrain& getTerrainRef();
			float getHeightMapAt(float x, float z);
			vector3d& getAngleMapAt(float x, float z);
			float getInclinationAt(float x, float z);
			float getObjAttribute(std::string name, std::string attr);
			void setObjAttribute(std::string name, std::string attr, float value);
			float getDistance(std::string firstName, std::string secondName);
			bool getBBCollideName(std::string firstName, std::string secondName);
			bool getBBCollideType(std::string name, std::string type);
			bool getBoundingSphereCollide(std::string firstName, std::string secondName);
	};
}