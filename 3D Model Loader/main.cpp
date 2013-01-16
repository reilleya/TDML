#include <windows.h>
#include <Gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h> 
#include <vector>
#include <string>
#include <math.h>
#include <iostream>
#include <time.h>
#include <fstream>
#include <sstream>

using namespace std;

void ChannelKeyboardToInput(unsigned char key, int x, int y);
void ChannelSpecialKeyboardToInput(int key, int x, int y);
void ChannelKeyboardUpToInput(unsigned char key, int x, int y);
void ChannelSpecialKeyboardUpToInput(int key, int x, int y);

class point
{
	private:
		float x;
		float y;
		float z;
		float r;
		float g;
		float b;

	public:
		/*point(float nx, float ny, float nz, float nr, float ng, float nb)
		{
			x=nx;
			y=ny;
			z=nz;
			r=nr;
			g=ng;
			b=nb;
		}*/
		void dispInfo()
		{
			cout << "X: "<<x<<" Y:"<< y << " Z:"<<z<<endl;
		}
		float getX()
		{
			return x;
		}
		void setX(float newX)
		{
			x = newX;
		}
		float getY()
		{
			return y;
		}
		void setY(float newY)
		{
			y = newY;
		}
		float getZ()
		{
			return z;
		}
		void setZ(float newZ)
		{
			z = newZ;
		}
		float getR()
		{
			return r;
		}
		void setR(float newR)
		{
			r = newR;
		}
		float getG()
		{
			return g;
		}
		void setG(float newG)
		{
			g = newG;
		}
		float getB()
		{
			return b;
		}
		void setB(float newB)
		{
			b = newB;
		}
		void setPos(float newX, float newY, float newZ)
		{
			x=newX;
			y=newY;
			z=newZ;
		}
		void setColor(float newR, float newG, float newB)
		{
			r = newR;
			g = newG;
			b = newB;
		}
		void moveX(float value)
		{
			x += value;
		}
		void moveY(float value)
		{
			y += value;
		}
		void moveZ(float value)
		{
			z += value;
		}
};

class poly
{
	private:
		vector<point> points;
		int npoints;

	public:
		poly()
		{
			npoints=0;
		}
		vector<point> getPoints()
		{
			return points;
		}
		void addPoint(float x,float y,float z,float r,float g,float b)
		{
			points.resize(points.size()+1);
			points[points.size()-1].setX(x);
			points[points.size()-1].setY(y);
			points[points.size()-1].setZ(z);
			points[points.size()-1].setR(r);
			points[points.size()-1].setG(g);
			points[points.size()-1].setB(b);
			npoints+=1;
		}
		void draw(bool wireframe, bool outline, float sx, float sy, float sz)
		{
			//cout << wireframe << endl;
			if(wireframe)
			{
				//cout << "Wireframe!"<<endl;
				glBegin(GL_LINE_LOOP);
			}
			else
			{
				glBegin(GL_POLYGON);
			}
			for(int p = 0; p < npoints; p++)
			{
				//points[p].dispInfo();
				glColor3f (points[p].getR(), points[p].getG(), points[p].getB());
				//glColor3f ((rand()%100)/100.0, (rand()%100)/100.0, (rand()%100)/100.0);
				glVertex3f(points[p].getX()*sx, points[p].getY()*sy, points[p].getZ()*sz);
			}
			glEnd();
			if(outline&&!wireframe)
			{
				glBegin(GL_LINE_LOOP);
				for(int p = 0; p < npoints; p++)
				{
					glColor3f (0.0, 0.0, 0.0);
					glVertex3f(points[p].getX()*sx, points[p].getY()*sy, points[p].getZ()*sz);
				}
				glEnd();
			}
		}
		void removePoints()
		{
			points.resize(0);
			npoints = 0;
		}
};

struct behavior
{
	string type;
	float min;
	float max;
	bool repeat;
	float speed;
};

class object
{
	private:
		vector<poly> polygons;
		bool wireframe;
		bool outline;
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
		string name;
		vector<behavior> behaviors;
		int nbehaviors;

	public:
		object()
		{
			nbehaviors = 0;
			visible = true;
		}
		void draw()
		{
			if(visible)
			{
				for(int p = 0; p<(int)polygons.size(); p++)
				{
					polygons[p].draw(wireframe, outline, scalex, scaley, scalez);
				}
			}
		}
		void update(int time, int timedelta)
		{
			for(int b = 0; b < nbehaviors; b++)
			{
				if(behaviors[b].type=="x")
				{
					if(behaviors[b].repeat)
					{
						x = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * 0.01745 * time));
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
						y = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * 0.01745 * time));
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
						z = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * 0.01745 * time));
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
						xangle = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * 0.01745 * time));
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
						yangle = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * 0.01745 * time));
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
						zangle = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * 0.01745 * time));
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
						scalex = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * 0.01745 * time));
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
						scaley = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * 0.01745 * time));
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
						scalez = behaviors[b].min + behaviors[b].max * abs(sin(behaviors[b].speed * 0.01745 * time));
					}
					else 
					{
						scalez += behaviors[b].speed * timedelta;
					}
				}
			}
		}
		void addBehavior(behavior newBehavior)
		{
			behaviors.resize(behaviors.size()+1);
			behaviors[behaviors.size()-1] = newBehavior;
			nbehaviors++;
		}
		void addPoly(poly Polygon)
		{
			polygons.resize(polygons.size()+1);
			polygons[polygons.size()-1] = Polygon;
		}
		void removePolygons()
		{
			polygons.resize(0);
		}
		void setWireframe(bool wframe)
		{
			wireframe = wframe;
		}
		bool getWireframe()
		{
			return wireframe;
		}
		void setOutline(bool oline)
		{
			outline = oline;
		}
		bool getOutline()
		{
			return outline;
		}
		void setVisible(bool vis)
		{
			visible = vis;
		}
		bool getVisible()
		{
			return visible;
		}
		float getX()
		{
			return x;
		}
		void setX(float newX)
		{
			x = newX;
		}
		float getY()
		{
			return y;
		}
		void setY(float newY)
		{
			y = newY;
		}
		float getZ()
		{
			return z;
		}
		void setZ(float newZ)
		{
			z = newZ;
		}
		void setPosition(float newX, float newY, float newZ)
		{
			x=newX;
			y=newY;
			z=newZ;
		}
		float getXangle()
		{
			return xangle;
		}
		void setXangle(float newXangle)
		{
			xangle = newXangle;
		}
		float getYangle()
		{
			return yangle;
		}
		void setYangle(float newYangle)
		{
			yangle = newYangle;
		}
		float getZangle()
		{
			return zangle;
		}
		void setZangle(float newZangle)
		{
			zangle = newZangle;
		}
		void setAngle(float newXangle, float newYangle, float newZangle)
		{
			xangle = newXangle;
			yangle = newYangle;
			zangle = newZangle;
		}
		float getScaleX()
		{
			return scalex;
		}
		void setScaleX(float newScaleX)
		{
			scalex = newScaleX;
		}
		float getScaleY()
		{
			return scaley;
		}
		void setScaleY(float newScaleY)
		{
			scaley = newScaleY;
		}
		float getScaleZ()
		{
			return scalez;
		}
		void setScaleZ(float newScaleZ)
		{
			scalez = newScaleZ;
		}
		void setScale(float newScaleX, float newScaleY, float newScaleZ)
		{
			scalex = newScaleX;
			scaley = newScaleY;
			scalez = newScaleZ;
		}
		void setName(string newName)
		{
			name=newName;
		}
		string getName()
		{
			return name;
		}
};

class world
{
	private:
		unsigned int timer;
		int nobjs;
		float lastTime;
		float timeElapsed;
		vector<object> objects;
		float camx;
		float camy;
		float camz;
		float camxangle;
		float camyangle;
		float camzangle;

	public:
		world()
		{
			lastTime=glutGet(GLUT_ELAPSED_TIME);
			timeElapsed = 0;
			nobjs=0;
			camx=0;
			camy=0;
			camz=0;
			camxangle=0;
			camyangle=0;
			camzangle=0;
		}
		void update()
		{
			timeElapsed = glutGet(GLUT_ELAPSED_TIME)-lastTime;
			lastTime=glutGet(GLUT_ELAPSED_TIME);
			//cout << 1000.0/timeElapsed << endl;
			timer+=timeElapsed;
			//cout << timer << endl;
			for(int updater = 0; updater < nobjs; updater++)
			{
				objects[updater].update(timer, timeElapsed);
			}
		}
		float getTimeDelta()
		{
			return timeElapsed;
		}
		unsigned int getTimer()
		{
			return timer;
		}
		void draw()
		{
			for(int obj = 0; obj < (int)objects.size(); obj++)
			{
				glRotatef(camxangle, 1, 0, 0);
				glRotatef(camyangle, 0, 1, 0);
				glRotatef(camzangle, 0, 0, 1);
				glTranslatef(camx, camy, camz);
				glTranslatef(objects[obj].getX(), objects[obj].getY(), objects[obj].getZ());
				glRotatef(objects[obj].getXangle(), 1, 0, 0);
				glRotatef(objects[obj].getYangle(), 0, 1, 0);
				glRotatef(objects[obj].getZangle(), 0, 0, 1);
				objects[obj].draw();
				glLoadIdentity();
			}
		}
		void addObject(object Obj)
		{
			cout << Obj.getName() << endl;
			objects.resize(objects.size()+1);
			objects[objects.size()-1]=Obj;
			nobjs++;
		}
		void setCamAngleX(float newXangle)
		{
			//cout << newXangle<<endl;
			camxangle = newXangle; 
		}
		void setCamAngleY(float newYangle)
		{
			camyangle = newYangle; 
		}
		void setCamAngleZ(float newZangle)
		{
			camzangle = newZangle; 
		}
		void setCamAngle(float newXangle, float newYangle, float newZangle)
		{
			camxangle = newXangle;
			camyangle = newYangle;
			camzangle = newZangle;
		}
		void setCamPosition(float newX, float newY, float newZ)
		{
			camx = newX;
			camy = newY;
			camz = newZ;
		}
		float getCamAngleX()
		{
			return camxangle;
		}
		float getCamAngleY()
		{
			return camyangle;
		}
		float getCamAngleZ()
		{
			return camzangle;
		}
		void setCamX(float newX)
		{
			camx = newX; 
		}
		void setCamY(float newY)
		{
			camy = newY; 
		}
		void setCamZ(float newZ)
		{
			camz = newZ; 
		}
		float getCamX()
		{
			return camx;
		}
		float getCamY()
		{
			return camy;
		}
		float getCamZ()
		{
			return camz;
		}
		int getIDByName(string name)
		{
			for(int counter = 0; counter < (int)objects.size(); counter++)
			{
				if(objects[counter].getName()==name)
				{
					return counter;
				}
			}
			return -1;
		}
		object getObjByName(string name)
		{
			return getObjectById(getIDByName(name));
		}
		vector<object> getObjects()
		{
			return objects;
		}
		object getObjectById(int id)
		{
			return objects[id];
		}
		float getObjAttribute(string name, string attr)
		{
			int id = getIDByName(name);
			if(attr=="x") return objects[id].getX();
			if(attr=="y") return objects[id].getY();
			if(attr=="z") return objects[id].getZ();
			if(attr=="xscale") return objects[id].getScaleX();
			if(attr=="yscale") return objects[id].getScaleY();
			if(attr=="zscale") return objects[id].getScaleZ();
			if(attr=="xangle") return objects[id].getXangle();
			if(attr=="yangle") return objects[id].getYangle();
			if(attr=="zangle") return objects[id].getZangle();
			if(attr=="wireframe") return objects[id].getWireframe();
			if(attr=="outline") return objects[id].getOutline();
			if(attr=="visible") return objects[id].getVisible();
		}
		void setObjAttribute(string name, string attr, float value)
		{
			if(name!="*")
			{
				int id = getIDByName(name);
				//cout << id<<endl;
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
				if(attr=="outline")
				{
					if(value==1.0) objects[id].setOutline(true);
					if(value==0.0) objects[id].setOutline(false);
				}
				if(attr=="visible")
				{
					if(value==1.0) objects[id].setVisible(true);
					if(value==0.0) objects[id].setVisible(false);
				}
			}
			else
			{
				for(int id = 0; id < objects.size(); id++)
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
					if(attr=="outline")
					{
						if(value==1.0) objects[id].setOutline(true);
						if(value==0.0) objects[id].setOutline(false);
					}
					if(attr=="visible")
					{
						if(value==1.0) objects[id].setVisible(true);
						if(value==0.0) objects[id].setVisible(false);
					}
				}
			}
		}
};

class input
{
	private:
		bool* keys;
		bool* specialkeys;

	public:
		// TODO : Make mouse input functions
		input()
		{
			keys = new bool[256];
			for(int k = 0; k < 256; k++) keys[k]=false;
			specialkeys = new bool[256];
			for(int sk = 0; sk < 256; sk++) specialkeys[sk]=false;
			//glutKeyboardFunc (KeyDownFunc);
			//glutSpecialFunc(specialKeyboard);
		}
		bool getKeyState(char key)
		{
			return keys[key];
		}
		bool getSpecialKeyState(int key)
		{
			return specialkeys[key];
		}
		void KeyDownFunc(unsigned char key, int x, int y)
		{
			keys[key] = true;
		}
		void KeyUpFunc(unsigned char key, int x, int y)
		{
			keys[key] = false;
		}
		void SpecialKeyDownFunc(int key, int x, int y)
		{
			specialkeys[key]=true;
		}
		void SpecialKeyUpFunc(int key, int x, int y)
		{
			specialkeys[key]=false;
		}
};

input Input;

void setupInput()
{
	glutKeyboardFunc(ChannelKeyboardToInput);
	glutSpecialFunc(ChannelSpecialKeyboardToInput);
	glutKeyboardUpFunc(ChannelKeyboardUpToInput);
	glutSpecialUpFunc(ChannelSpecialKeyboardUpToInput);
}

void ChannelKeyboardToInput(unsigned char key, int x, int y)
{
	Input.KeyDownFunc(key, x, y);
}
void ChannelSpecialKeyboardToInput(int key, int x, int y)
{
	Input.SpecialKeyDownFunc(key, x, y);
}
void ChannelKeyboardUpToInput(unsigned char key, int x, int y)
{
	Input.KeyUpFunc(key, x, y);
}
void ChannelSpecialKeyboardUpToInput(int key, int x, int y)
{
	Input.SpecialKeyUpFunc(key, x, y);
}

world TestWorld1;

void reshape(int wi, int hi)
{
	float w = (float) wi;
	float h = (float) hi;
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glClearColor (0.53, 0.81, 1.0, 1.0);                 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();  
	gluPerspective(45.0f,w/h,1.000f,1000.0f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init ()
{
	glClearColor (0.53, 0.81, 1.0, 1.0);               
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();  
	gluPerspective(45.0f,500.0f/500.0f,1.0f,1000.0f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLineWidth(1.5);
}

void display ()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
	TestWorld1.draw();
	//glFlush();
	glutSwapBuffers();
}

void keyboard ()
{
	if(Input.getKeyState('w'))
	{
		TestWorld1.setObjAttribute("*", "wireframe", !TestWorld1.getObjAttribute("house1", "wireframe"));
	}
	if(Input.getKeyState('o'))
	{
		TestWorld1.setObjAttribute("*", "outline",  !TestWorld1.getObjAttribute("house1", "outline"));
	}
	if(Input.getKeyState('v'))
	{
		TestWorld1.setObjAttribute("*", "visible",  !TestWorld1.getObjAttribute("house1", "visible"));
	}
	glutPostRedisplay ();
}

void specialKeyboard()
{
	if(Input.getSpecialKeyState(GLUT_KEY_LEFT)) TestWorld1.setCamAngleY(TestWorld1.getCamAngleY()-0.0625*TestWorld1.getTimeDelta());
	if(Input.getSpecialKeyState(GLUT_KEY_RIGHT)) TestWorld1.setCamAngleY(TestWorld1.getCamAngleY()+0.0625*TestWorld1.getTimeDelta());
	if(Input.getSpecialKeyState(GLUT_KEY_DOWN)) 
	{
		TestWorld1.setCamX(TestWorld1.getCamX()+TestWorld1.getTimeDelta()*0.25*(sinf(0.01745*TestWorld1.getCamAngleY())));
		TestWorld1.setCamZ(TestWorld1.getCamZ()-TestWorld1.getTimeDelta()*0.25*(cosf(0.01745*TestWorld1.getCamAngleY())));
	}
	if(Input.getSpecialKeyState(GLUT_KEY_UP))
	{
		TestWorld1.setCamX(TestWorld1.getCamX()-TestWorld1.getTimeDelta()*0.25*(sinf(0.01745*TestWorld1.getCamAngleY())));
		TestWorld1.setCamZ(TestWorld1.getCamZ()+TestWorld1.getTimeDelta()*0.25*(cosf(0.01745*TestWorld1.getCamAngleY())));
	}
	glutPostRedisplay ();
}

void animate()
{
	TestWorld1.update();
	keyboard();
	specialKeyboard();
	//TestWorld1.setObjAttribute("cube1", "xangle", TestWorld1.getObjAttribute("cube1", "xangle")+TestWorld1.getTimeDelta()/2.0);
	//TestWorld1.setObjAttribute("cube1", "yangle", TestWorld1.getObjAttribute("cube1", "yangle")+TestWorld1.getTimeDelta()/4.0);
	//TestWorld1.setObjAttribute("cube1", "zangle", TestWorld1.getObjAttribute("cube1", "zangle")+TestWorld1.getTimeDelta()/2.0);
	//TestWorld1.setObjAttribute("*", "wireframe", !TestWorld1.getObjByName("house1").getWireframe());
	//TestWorld1.setObjAttribute("house2", "yangle", TestWorld1.getObjByName("house2").getYangle()+TestWorld1.getTimeDelta()/2.0);
	//TestWorld1.setObjAttribute("pyramid1", "y", 30*sin(0.25*0.01745*TestWorld1.getTimer()));
	//TestWorld1.setObjAttribute("house3", "xscale", abs(1.2*sin(0.25*0.01745*TestWorld1.getTimer())));
	//TestWorld1.setObjAttribute("house3", "yscale", abs(1.2*sin(0.25*0.01745*TestWorld1.getTimer())));
	//TestWorld1.setObjAttribute("house3", "zscale", abs(1.2*sin(0.25*0.01745*TestWorld1.getTimer())));
	//TestWorld1.setObjAttribute("*", "xscale", abs(1.2*sin(0.01745*TestWorld1.getTimer())));
	//TestWorld1.setObjAttribute("*", "yscale", abs(1.2*sin(0.01745*TestWorld1.getTimer())));
	//TestWorld1.setObjAttribute("*", "zscale", abs(1.2*sin(0.01745*TestWorld1.getTimer())));
	//TestWorld1.setObjAttribute("pyramid1", "xangle", TestWorld1.getObjectById(TestWorld1.getObjByName("pyramid1")).getXangle()+1.0);
	//TestWorld1.setObjAttribute("house1", "x", TestWorld1.getObjectById(TestWorld1.getObjByName("house1")).getX()+1.0);
	//TestWorld1.setObjAttribute("house2", "zangle", TestWorld1.getObjByName("house2").getZangle()+1.0);
	//TestWorld1.setObjAttribute("house2", "xangle", TestWorld1.getObjByName("house2").getXangle()+1.0);
	//TestWorld1.setCamAngleY(TestWorld1.getCamAngleY()+1.0);
	//TestWorld1.setCamAngleX(TestWorld1.getCamAngleX()+0.1);
	//TestWorld1.setCamAngleZ(TestWorld1.getCamAngleZ()+1.0);
	//cout << TestWorld1.getCamAngleY() << endl;
	//TestWorld1.setCamZ(TestWorld1.getCamZ()-2.0);
	//TestWorld1.setCamAngleX(TestWorld1.getCamAngleX() + 0.5);
	//cout << TestWorld1.getCamAngleX() << endl;
	glutPostRedisplay();
}

object loadObject(string fileName)
{
	object newobj;
    ifstream infile;
	vector<float> pointd;
	vector<poly> polys(1);
	poly cpol;
    string word;
    infile.open(fileName, ios::in);
    while (infile >> word) 
	{
		//cout << word << endl;
		if(word=="[")
		{
			polys.resize(polys.size()+1);
		}
		else if(word=="?")
		{
			//cout << pointd[0]<<","<<pointd[1]<<","<<pointd[2]<<","<<pointd[3]<<","<<pointd[4]<<","<<pointd[5]<<endl;
			polys[polys.size()-1].addPoint(pointd[0],pointd[1],pointd[2],pointd[3],pointd[4],pointd[5]);
			pointd.resize(0);
		}
		else
		{
			pointd.resize(pointd.size()+1);
			pointd[pointd.size()-1] = atof(word.c_str());
		}
	}
	for(int polyg = 0; polyg < (int)polys.size(); polyg++)
	{
		newobj.addPoly(polys[polyg]);
		//cout << "Adding"<<endl;
	}
	return newobj;
}

vector<behavior> loadBehaviors(string fileName)
{
	vector<behavior> newBehaviors;
    ifstream infile;
	vector<string> behd;
    string word;
    infile.open(fileName, ios::in);
    while (infile >> word) 
	{
		//cout << word << endl;
		if(word=="?")
		{
			for(int b = 0; b<behd.size(); b++)
			{
				cout << b << " " << behd[b] << endl;
			}
			cout << endl << endl << endl;
			newBehaviors.resize(newBehaviors.size()+1);
			newBehaviors[newBehaviors.size()-1].type = behd[0];
			newBehaviors[newBehaviors.size()-1].speed = atof(behd[1].c_str());
			if(behd[2]=="{")
			{
				newBehaviors[newBehaviors.size()-1].repeat = true;
				newBehaviors[newBehaviors.size()-1].min = atof(behd[3].c_str());
				newBehaviors[newBehaviors.size()-1].max = atof(behd[5].c_str());
			}
			else
			{
				newBehaviors[newBehaviors.size()-1].repeat = false;
			}
			behd.resize(0);
		}
		else
		{
			behd.resize(behd.size()+1);
			behd[behd.size()-1] = word;
		}
	}
	return newBehaviors;
}

world loadWorld(string fileName)
{
	world newworld;
    ifstream infile;
	vector<string> objd(1);
	vector<object> objs(0);
	poly cpol;
    string word;
    infile.open(fileName, ios::in);
    while (infile >> word) 
	{
		//cout << word << endl;
		if(word=="[")
		{
			//cout << "BlARG"<<endl;
			objs.resize(objs.size()+1);
			//cout << objd[0] << endl;
			objs[objs.size()-1] = loadObject(objd[0]);
			objs[objs.size()-1].setWireframe(atof(objd[1].c_str()));
			objs[objs.size()-1].setOutline(atof(objd[2].c_str()));
			objs[objs.size()-1].setPosition(atof(objd[3].c_str()), atof(objd[4].c_str()), atof(objd[5].c_str()));
			objs[objs.size()-1].setAngle(atof(objd[6].c_str()),atof(objd[7].c_str()),atof(objd[8].c_str()));
			objs[objs.size()-1].setScale(atof(objd[9].c_str()),atof(objd[10].c_str()),atof(objd[11].c_str()));
			objs[objs.size()-1].setName(objd[12]);
			vector<behavior> behaviors = loadBehaviors(objd[13]);
			for(int be = 0; be < behaviors.size(); be++) objs[objs.size()-1].addBehavior(behaviors[be]);
			objd[0]="";
			objd.resize(1);
		}
		else if(word=="?")
		{
			objd.resize(objd.size()+1);
		}
		else
		{
			if(objd.size()-1 == 0)
			{
				objd[objd.size()-1].append(word+" ");
			}
			else
			{
				objd[objd.size()-1].append(word);
			}
		}
	}
	for(int objc = 0; objc < (int)objs.size(); objc++)
	{
		//cout << "FIrst:" <<endl;
		cout << objs[objc].getName() << endl;
		newworld.addObject(objs[objc]);
		//cout << "Adding"<<endl;
	}
	return newworld;
}

int main(int argc, char** argv)
{
	/*TestObject1 = loadObject("C:/Users/Andrew/Desktop/NCC/OpenGL/3D Model Loader/3D Model Loader/house.tdm");
	TestObject1.setWireframe(false);
	TestObject1.setOutline(false);
	TestObject1.setPosition(0.0,0.0,0.0);
	TestObject1.setAngle(0.0, 0.0, 0.0);
	TestObject1.setName("house1");
	TestObject2 = loadObject("C:/Users/Andrew/Desktop/NCC/OpenGL/3D Model Loader/3D Model Loader/house.tdm");
	TestObject2.setWireframe(false);
	TestObject2.setOutline(false);
	TestObject2.setPosition(65.0,0.0,0.0);
	TestObject2.setAngle(0.0, 45.0, 0.0);
	TestObject2.setName("house2");
	TestObject3 = loadObject("C:/Users/Andrew/Desktop/NCC/OpenGL/3D Model Loader/3D Model Loader/pyramid.tdm");
	TestObject3.setWireframe(false);
	TestObject3.setOutline(false);
	TestObject3.setPosition(0.0,0.0,-65.0);
	TestObject3.setAngle(0.0, 0.0, 0.0);
	TestObject3.setName("pyramid1");
	TestWorld1.addObject(TestObject1);
	TestWorld1.addObject(TestObject2);
	TestWorld1.addObject(TestObject3);*/
	cout << "Loading world"<<endl;
	TestWorld1 = loadWorld("world1.wor");
	cout << "Done!" <<endl;
	TestWorld1.setCamAngle(0.0,0.0,0.0);
	TestWorld1.setCamPosition(0.0, 0.0, -100.0);
	srand(time(NULL));
	glutInit (&argc, argv);     
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (10, 10);
	glutCreateWindow("3D Model Loader - Testbed");
	init();
	glutDisplayFunc (display);     
	glutIdleFunc (animate);
	//glutTimerFunc(16, );
	glutReshapeFunc (reshape);
	//glutKeyboardFunc (keyboard);
	//glutSpecialFunc(specialKeyboard);
	/*glutKeyboardFunc(ChannelKeyboardToInput);
	glutSpecialFunc(ChannelSpecialKeyboardToInput);
	glutKeyboardUpFunc(ChannelKeyboardUpToInput);
	glutSpecialUpFunc(ChannelSpecialKeyboardUpToInput);*/
	setupInput();
	glutMainLoop();
	return 0;
}