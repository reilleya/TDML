//world.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	world::world()
	{
		fileName = "";
		lastTime=(float)glutGet(GLUT_ELAPSED_TIME);
		timeElapsed = 0;
		nobjs=0;
		nparts=0;
		camx=0;
		camy=0;
		camz=0;
		camxangle=0;
		camyangle=0;
		camzangle=0;
		hasterrain = false;
		modelMatrix = matrix4x4();
	}

	world::world(std::string filename)
	{
		fileName = filename;
		lastTime=(float)glutGet(GLUT_ELAPSED_TIME);
		timeElapsed = 0;
		nobjs=0;
		nparts=0;
		camx=0;
		camy=0;
		camz=0;
		camxangle=0;
		camyangle=0;
		camzangle=0;
		hasterrain = false;
		modelMatrix = matrix4x4();
	}

	void world::dispInfo()
	{
		Log.output("World:\n");
		Log.output("\tFilename: "+fileName+"\n");
		Log.output("\tTime: "); Log.output((float)timer); Log.output("\n");
		Log.output("\tTime Since Last Frame: "); Log.output(timeElapsed); Log.output("\n");
		Log.output("\tTerrain: "); Log.output((float)hasterrain); Log.output("\n");
		Log.output("\tObjects: "); Log.output((float)nobjs); Log.output("\n");
		Log.output("\tParticle Systems: "); Log.output((float)nparts); Log.output("\n");
		Log.output("\tCamera Information:\n");
		Log.output("\t\tPosition: "); Log.output(camx); Log.output(","); Log.output(camy); Log.output(","); Log.output(camz); Log.output("\n");
		Log.output("\t\tAngle: "); Log.output(camxangle); Log.output(","); Log.output(camyangle); Log.output(","); Log.output(camzangle); Log.output("\n");
	}

	void world::update()
	{
		timeElapsed = glutGet(GLUT_ELAPSED_TIME)-lastTime;
		lastTime=(float)glutGet(GLUT_ELAPSED_TIME);
		timer+=(int)timeElapsed;
		
		for(int updater = 0; updater < nparts; updater++)
		{
			particlesystems[updater].update(timeElapsed);
		}

		for(int updater = 0; updater < nobjs; updater++)
		{
			objects[updater].update(timer, (int)timeElapsed);
		}
	}

	float world::getTimeDelta()
	{
		return timeElapsed;
	}

	float world::getAdjustedTime(float value, float targetTimeStep)
	{
		return value*(timeElapsed/targetTimeStep);
	}

	unsigned int world::getTimer()
	{
		return timer;
	}

	void world::draw()
	{
		modelMatrix.loadIdentity();
		if(hasterrain)
		{
			modelMatrix.rotate(camxangle, camyangle, camzangle, crotorder);
			modelMatrix.translate(-camx, -camy, -camz);
			modelMatrix.scale(map.getScaleXZ(), map.getScaleY(), map.getScaleXZ());
			//matrix3x3 nmat = modelMatrix.rotPart();
			//nmat = nmat.inverse();
			//nmat = nmat.transpose();
			//Shaders.setNormalMat(nmat.glForm());
			Shaders.setModelMat(modelMatrix.glForm());
			map.display();
		}
		modelMatrix.loadIdentity();
		Shaders.setModelMat(modelMatrix.glForm());
		//
		
		//
		
		for(int obj = 0; obj < (int)nobjs; obj++)
		{
			modelMatrix.rotate(camxangle, camyangle, camzangle, crotorder);
			modelMatrix.translate(-camx, -camy, -camz);
			modelMatrix.translate(objects[obj].getX(), objects[obj].getY(), objects[obj].getZ());
			modelMatrix.scale(objects[obj].getScaleX(), objects[obj].getScaleY(), objects[obj].getScaleZ());
			modelMatrix.rotate(-objects[obj].getXangle(), -objects[obj].getYangle(), -objects[obj].getZangle(), orotorder);
			matrix3x3 nmat = modelMatrix.rotPart();
			/*nmat = nmat.inverse();
			nmat = nmat.transpose();
			matrix4x4 nmat = matrix4x4();
			nmat.rotate(objects[obj].getXangle(), objects[obj].getYangle(), objects[obj].getZangle(), orotorder);
			matrix3x3 nm = nmat.rotPart();
			nm = nm.inverse();
			nm = nm.transpose();
			Shaders.setNormalMat(nmat.glForm());*/
			Shaders.setModelMat(modelMatrix.glForm());
			Shaders.setProjMat(projMatrix.glForm());
			objects[obj].display();
			if(objects[obj].getDrawBB()) objects[obj].drawBB();
			modelMatrix.loadIdentity();
		}

		for(int par = 0; par < (int)nparts; par++)
		{
			modelMatrix.loadIdentity();
			modelMatrix.rotate(camxangle, camyangle, camzangle, crotorder);
			modelMatrix.translate(-camx, -camy, -camz);
			Shaders.setModelMat(modelMatrix.glForm());
			particlesystems[par].display(this);
			modelMatrix.loadIdentity();
		}
	}

	void world::addObject(object Obj)
	{
		objects.resize(objects.size()+1);
		objects[objects.size()-1]=Obj;
		nobjs++;
	}

	void world::addParticleSystem(particlesystem newsystem)
	{
		particlesystems.resize(particlesystems.size()+1);
		particlesystems[particlesystems.size()-1]=newsystem;
		nparts++;
	}

	void world::setTerrain(terrain newterrain)
	{
		hasterrain = true;
		map = newterrain;
	}

	void world::setCamAngleX(float newXangle)
	{
		camxangle = newXangle; 
	}

	void world::setCamAngleY(float newYangle)
	{
		camyangle = newYangle; 
	}

	void world::setCamAngleZ(float newZangle)
	{
		camzangle = newZangle; 
	}

	void world::setCamAngle(float newXangle, float newYangle, float newZangle)
	{
		camxangle = newXangle;
		camyangle = newYangle;
		camzangle = newZangle;
	}

	void world::setCamAngle(vector3d newAngle)
	{
		camxangle = newAngle.x;
		camyangle = newAngle.y;
		camzangle = newAngle.z;
	}

	void world::setCamPosition(float newX, float newY, float newZ)
	{
		camx = newX;
		camy = newY;
		camz = newZ;
	}

	void world::setCamPosition(vector3d position)
	{
		camx = position.x;
		camy = position.y;
		camz = position.z;
	}

	float world::getCamAngleX()
	{
		return camxangle;
	}

	float world::getCamAngleY()
	{
		return camyangle;
	}

	float world::getCamAngleZ()
	{
		return camzangle;
	}

	void world::setCamX(float newX)
	{
		camx = newX; 
	}

	void world::setCamY(float newY)
	{
		camy = newY; 
	}

	void world::setCamZ(float newZ)
	{
		camz = newZ; 
	}

	float world::getCamX()
	{
		return camx;
	}

	float world::getCamY()
	{
		return camy;
	}

	float world::getCamZ()
	{
		return camz;
	}

	int world::getFirstIDByName(string name)
	{
		for(int counter = 0; counter < (int)nobjs; counter++)
		{
			if(objects[counter].getName()==name)
			{
				return counter;
			}
		}

		Message.errorMessage("World Error:\n\tFound no object with name "+name+" in world loaded from file "+fileName, "World Error"); 

		return -1;
	}

	object world::getFirstObjByName(string name)
	{
		return getObjectById(getFirstIDByName(name));
	}

	/*vector<int> world::getIDsByName(std::string name)
	{
		vector<int> ids;
		int idsize=0;
		for(int counter = 0; counter < (int)objects.size(); counter++)
		{
			if(objects[counter].getName()==name)
			{
				ids.resize(idsize+1);
				ids[idsize] = counter;
				idsize++;
			}
		}
		return ids;
	}*/

	/*object* world::getObjsByName(string name)
	{
		return getObjsById(getFirstIDByName(name));
	}*/

	vector<object> world::getObjects()
	{
		return objects;
	}

	object world::getObjectById(int id)
	{
		return objects[id];
	}

	/*vector<object*>* world::getObjectsById(int* id)
	{
		vector<object*> objs;
		for(int iter = 0; iter < nobjs; iter++)
		{
			if(
		}
		return objs
	}*/

	object& world::getObjectRef(std::string Name)
	{
		return objects.at(getFirstIDByName(Name));
	}

	void world::removeObjectById(int id)
	{
		objects.erase(objects.begin()+id);
		nobjs--;
	}

	void world::removeObjectByName(string Name)
	{
		removeObjectById(getFirstIDByName(Name));
	}

	void world::removeObjectByType(string Type)
	{
		//TODO
	}

	int world::getParticleSystemNameById(string Name)
	{
		int id = -1;
		for(int ps = 0; ps < nparts; ps++)
		{
			Log.output(particlesystems[ps].getName());
			if(particlesystems[ps].getName()==Name)
			{
				
				id = ps;
				break;
			}
		}
		return id;
	}

	particlesystem& world::getParticleSystemRef(std::string Name)
	{
		int id = getParticleSystemNameById(Name);
		if(id!=-1)
		{
			return particlesystems.at(id);
		}
		else
		{
			Message.errorMessage("Attempted to reference a particle system that doesn't exist.\nWorld: \tParticle System: "+Name+"\nPossibilities: "+particlesystems[0].getName(), "Particle System Reference Error");
		}
	}

	float world::getHeightMapAt(float x, float z)
	{
		if(hasterrain)
		{
			return map.getHeightMapAt(x,z);
		}
		else
		{
			Message.errorMessage("Attempted to read terrain height from a world that doesn't have a terrain object.\n\tWorld: " + fileName, "Terrain Height Error");
			return 0;
		}
	}

	vector3d& world::getAngleMapAt(float x, float z)
	{
		if(hasterrain)
		{
			return map.getAngleAt(x, z);
		}
		else
		{
			Message.errorMessage("Attempted to read terrain angle from a world that doesn't have a terrain object.\n\tWorld: " + fileName, "Terrain Angle Error");
			return vector3d(0, 0, 0);
		}
	}

	float world::getObjAttribute(string name, string attr)
	{
		int id = getFirstIDByName(name);
		if(attr=="x") return objects[id].getX();
		else if(attr=="y") return objects[id].getY();
		else if(attr=="z") return objects[id].getZ();
		else if(attr=="xscale") return objects[id].getScaleX();
		else if(attr=="yscale") return objects[id].getScaleY();
		else if(attr=="zscale") return objects[id].getScaleZ();
		else if(attr=="xangle") return objects[id].getXangle();
		else if(attr=="yangle") return objects[id].getYangle();
		else if(attr=="zangle") return objects[id].getZangle();
		else if(attr=="wireframe") return objects[id].getWireframe();
		else if(attr=="visible") return objects[id].getVisible();
		else return 0;
	}

	void world::setObjAttribute(string name, string attr, float value)
	{
		if(name!="*")
		{
			int id = getFirstIDByName(name);
			//std::cout << id<<endl;
			if(attr=="x") objects[id].setX(value);
			if(attr=="y") objects[id].setY(value);
			if(attr=="z") objects[id].setZ(value);
			if(attr=="xscale") objects[id].setScaleX(value);
			if(attr=="yscale") objects[id].setScaleY(value);
			if(attr=="zscale") objects[id].setScaleZ(value);
			if(attr=="xangle") objects[id].setXangle(value);
			if(attr=="yangle") objects[id].setYangle(value);
			if(attr=="zangle") objects[id].setZangle(value);
			if(attr=="wireframe") 
			{
				if(value==1.0) objects[id].setWireframe(true);
				if(value==0.0) objects[id].setWireframe(false);
			}
			if(attr=="visible")
			{
				if(value==1.0) objects[id].setVisible(true);
				if(value==0.0) objects[id].setVisible(false);
			}
		}
		else
		{
			for(std::size_t id = 0; id < objects.size(); id++)
			{
				if(attr=="x") objects[id].setX(value);
				if(attr=="y") objects[id].setY(value);
				if(attr=="z") objects[id].setZ(value);
				if(attr=="xscale") objects[id].setScaleX(value);
				if(attr=="yscale") objects[id].setScaleY(value);
				if(attr=="zscale") objects[id].setScaleZ(value);
				if(attr=="xangle") objects[id].setXangle(value);
				if(attr=="yangle") objects[id].setYangle(value);
				if(attr=="zangle") objects[id].setZangle(value);
				if(attr=="wireframe") 
				{
					if(value==1.0) objects[id].setWireframe(true);
					if(value==0.0) objects[id].setWireframe(false);
				}
				if(attr=="visible")
				{
					if(value==1.0) objects[id].setVisible(true);
					if(value==0.0) objects[id].setVisible(false);
				}
			}
		}
	}
	
	float world::getDistance(std::string firstName, std::string secondName)
	{
		int fid = getFirstIDByName(firstName);
		int sid = getFirstIDByName(secondName);
		float xdist = objects[fid].getX()-objects[sid].getX();
		float ydist = objects[fid].getY()-objects[sid].getY();
		float zdist = objects[fid].getZ()-objects[sid].getZ();
		float distance = sqrtf((xdist*xdist)+(ydist*ydist)+(zdist*zdist));
		return distance;
	}

	bool world::getBBCollideName(std::string firstName, std::string secondName)
	{
		int fid = getFirstIDByName(firstName);
		int sid = getFirstIDByName(secondName);
		bool collided = false;
		bool collidedx = false;
		bool collidedy = false;
		bool collidedz = false;
		if((objects[fid].getMaxX() >= objects[sid].getMinX() && objects[fid].getMaxX() <= objects[sid].getMaxX()) || (objects[sid].getMaxX() >= objects[fid].getMinX() && objects[sid].getMaxX() <= objects[fid].getMaxX()))
		{
			collidedx = true;
		}
		if((objects[fid].getMaxY() >= objects[sid].getMinY() && objects[fid].getMaxY() <= objects[sid].getMaxY()) || (objects[sid].getMaxY() >= objects[fid].getMinY() && objects[sid].getMaxY() <= objects[fid].getMaxY()))
		{
			collidedy = true;
		}
		if((objects[fid].getMaxZ() >= objects[sid].getMinZ() && objects[fid].getMaxZ() <= objects[sid].getMaxZ()) || (objects[sid].getMaxX() >= objects[fid].getMinZ() && objects[sid].getMaxZ() <= objects[fid].getMaxZ()))
		{
			collidedz = true;
		}		
		if(collidedx&&collidedy&&collidedz)
		{
			collided = true;
		}
		return collided;
	}

	bool world::getBBCollideType(std::string name, std::string type)
	{
		bool collided = false;
		for(int v = 0; v < nobjs; v++)
		{
			if(objects[v].getType()==type)
			{
				if(getBBCollideName(name,objects[v].getName()))
				{
					collided = true;
					break;
				}
			}
		}
		return collided;
	}

	bool world::getBoundingSphereCollide(std::string firstName, std::string secondName)
	{
		int fid = getFirstIDByName(firstName);
		int sid = getFirstIDByName(secondName);
		if(getDistance(firstName,secondName)<(objects[fid].getRadius()+objects[sid].getRadius()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}