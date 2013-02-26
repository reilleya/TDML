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
	void world::cameraRotate()
	{
		switch(crotorder)
			{
				case 0:
					glRotatef(-camxangle, 1, 0, 0);
					glRotatef(-camyangle, 0, 1, 0);
					glRotatef(-camzangle, 0, 0, 1);
					break;

				case 1:
					glRotatef(-camxangle, 1, 0, 0);
					glRotatef(-camzangle, 0, 0, 1);
					glRotatef(-camyangle, 0, 1, 0);
					break;

				case 2:
					glRotatef(-camzangle, 0, 0, 1);
					glRotatef(-camyangle, 0, 1, 0);
					glRotatef(-camxangle, 1, 0, 0);
					break;

				case 3:
					glRotatef(-camzangle, 0, 0, 1);
					glRotatef(-camxangle, 1, 0, 0);
					glRotatef(-camyangle, 0, 1, 0);
					break;

				case 4:
					glRotatef(-camyangle, 0, 1, 0);
					glRotatef(-camxangle, 1, 0, 0);
					glRotatef(-camzangle, 0, 0, 1);
					break;

				case 5:
					glRotatef(-camyangle, 0, 1, 0);
					glRotatef(-camzangle, 0, 0, 1);
					glRotatef(-camxangle, 1, 0, 0);
					break;
			}
	}

	void world::objectRotate(float x, float y, float z)
	{
		switch(orotorder)
			{
				case 0:
					glRotatef(x, 1, 0, 0);
					glRotatef(y, 0, 1, 0);
					glRotatef(z, 0, 0, 1);
					break;

				case 1:
					glRotatef(x, 1, 0, 0);
					glRotatef(z, 0, 0, 1);
					glRotatef(y, 0, 1, 0);
					break;

				case 2:
					glRotatef(z, 0, 0, 1);
					glRotatef(y, 0, 1, 0);
					glRotatef(x, 1, 0, 0);
					break;

				case 3:
					glRotatef(z, 0, 0, 1);
					glRotatef(x, 1, 0, 0);
					glRotatef(y, 0, 1, 0);
					break;

				case 4:
					glRotatef(y, 0, 1, 0);
					glRotatef(x, 1, 0, 0);
					glRotatef(z, 0, 0, 1);
					break;

				case 5:
					glRotatef(y, 0, 1, 0);
					glRotatef(z, 0, 0, 1);
					glRotatef(x, 1, 0, 0);
					break;
			}
	}

	world::world()
	{
		lastTime=(float)glutGet(GLUT_ELAPSED_TIME);
		timeElapsed = 0;
		nobjs=0;
		camx=0;
		camy=0;
		camz=0;
		camxangle=0;
		camyangle=0;
		camzangle=0;
		hasterrain = false;
	}

	void world::update()
	{
		timeElapsed = glutGet(GLUT_ELAPSED_TIME)-lastTime;
		lastTime=(float)glutGet(GLUT_ELAPSED_TIME);
		//output(1000.0/timeElapsed);
		//output("\n");
		timer+=(int)timeElapsed;
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
		//glDrawArrays(GL_LINE_LOOP, 0, 4);
		//std::cout << camx << endl;
		cameraRotate();
		glTranslatef(-camx, -camy, -camz);
		if(hasterrain)
		{
			glScalef(map.getScaleXZ(), map.getScaleY(), map.getScaleXZ());
			map.display();
		}
		//GLfloat lightpos[] = {-1.0, 1.0, 0.0, 1.0};

		//glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
		glLoadIdentity();
		for(int obj = 0; obj < (int)nobjs; obj++)
		{
			cameraRotate();
			glTranslatef(-camx, -camy, -camz);
			glTranslatef(objects[obj].getX(), objects[obj].getY(), objects[obj].getZ());
			//objects[obj].drawBB();
			glScalef(objects[obj].getScaleX(), objects[obj].getScaleY(), objects[obj].getScaleZ());
			objectRotate(objects[obj].getXangle(), objects[obj].getYangle(), objects[obj].getZangle());
			objects[obj].display();
			glLoadIdentity();
		}
			
		//glLoadIdentity();
	}

	void world::addObject(object Obj)
	{
		objects.resize(objects.size()+1);
		objects[objects.size()-1]=Obj;
		nobjs++;
	}

	void world::setTerrain(terrain newterrain)
	{
		hasterrain = true;
		map = newterrain;
	}

	void world::setCamAngleX(float newXangle)
	{
		//std::cout << newXangle<<endl;
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

	void world::setCamPosition(float newX, float newY, float newZ)
	{
		camx = newX;
		camy = newY;
		camz = newZ;
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

	float world::getHeightMapAt(float x, float z)
	{
		return map.getHeightMapAt(x,z);
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
		float distance = sqrt(
								pow(objects[fid].getX()-objects[sid].getX(),2)+
								pow(objects[fid].getY()-objects[sid].getY(),2)+
								pow(objects[fid].getZ()-objects[sid].getZ(),2)
							);
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