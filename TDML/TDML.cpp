//TDML.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	vector<GLuint> cachedTexId;
	vector<string> cachedTexName;
	vector<GLuint> cachedVBOId;
	vector<string> cachedVBOName;
	vector<object> cachedObjs;
	vector<string> cachedObjName;

	unsigned int appTime = 0;
	unsigned int applastTime = 0;
	unsigned int apptimeElapsed = 0;

	/*struct behavior
	{
		string type;
		float min;
		float max;
		bool repeat;
		float speed;
	};*/

	object loadObject(string fileName)
	{
		bool cachedFound = false;
		int cachedobjid=0;
		for(unsigned int ob = 0; ob < cachedObjName.size(); ob++)
		{
			if(cachedObjName[ob] == fileName)
			{
				Log.output("\t\tFound!\n");
				cachedFound = true;
				cachedobjid = ob;
			}
		}
		if(cachedFound==false)
		{
			Log.output("\t\tNot Found!\n");
			if(File.fileExists(fileName))
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
					if(word=="[")
					{
						polys.resize(polys.size()+1);
					}
					else if(word=="?")
					{
						polys[polys.size()-1].addPoint(pointd[0],pointd[1],pointd[2],pointd[3],pointd[4],pointd[5]);
						pointd.resize(0);
					}
					else
					{
						pointd.resize(pointd.size()+1);
						pointd[pointd.size()-1] = (float)atof(word.c_str());
					}
				}
				for(int polyg = 0; polyg < (int)polys.size(); polyg++)
				{
					newobj.addPoly(polys[polyg]);
				}
				cachedObjs.resize(cachedObjs.size()+1);
				cachedObjs[cachedObjs.size()-1] = newobj;
				cachedObjName.resize(cachedObjName.size()+1);
				cachedObjName[cachedObjName.size()-1] = fileName;
				return newobj;
			}
			else
			{
				Message.errorMessage("Error loading object file: "+fileName+"\nFile not found!\nPress 'OK' to attempt to continue, or 'Cancel' to exit.", "Loading Error");
				object o;
				return o;
			}
		}
		else
		{
			return cachedObjs[cachedobjid];
		}
	}

	terrain loadTerrain(std::string fileName, std::string textureName, float scaleXZ, float scaleY)
	{
		terrain newterrain;
		ifstream infile;
		std::vector<float> line;
		std::vector<std::vector<float>> heightmap;
		Log.output("Loading terrain heightmap from file: "); Log.output(fileName); Log.output("\n");		
		string word;
		infile.open(fileName, ios::in);
		Log.output("\tLoading height data\n");
		while (infile >> word) 
		{
			if(word=="?")
			{
				heightmap.resize(heightmap.size()+1);
				heightmap[heightmap.size()-1]=line;
				line.resize(0);
			}
			else
			{
				//cout << word << endl;
				line.resize(line.size()+1);
				line[line.size()-1] = (float)atof(word.c_str());
			}
		}
		Log.output("\tSetting properties\n");
		Log.output("\t\tSetting heightmap\n");
		newterrain.setHeightMap(heightmap);
		Log.output("\t\tSetting dimensions\n");
		newterrain.setDimensions(heightmap.size());
		Log.output("\t\tSetting texture\n");
		Log.output("\t\t\tLoading texture image\n");
		newterrain.setTextureId(loadTextureData(textureName));
		Log.output("\t\tSetting scale\n");
		newterrain.setScale(scaleXZ, scaleY);
		Log.output("\tGenerating VBO\n");
		newterrain.generateVBO();
		Log.output("Done Loading Terrain\n\n");
		return newterrain;
	}

	vector<behavior> loadBehaviors(string fileName)
	{
		Log.output("\t\t\tLoading behaviors from: "+fileName+"\n");
		vector<behavior> newBehaviors;
		ifstream infile;
		vector<string> behd;
		string word;
		infile.open(fileName, ios::in);
		while (infile >> word) 
		{
			//std::cout << word << endl;
			if(word=="?")
			{
				//for(int b = 0; b<behd.size(); b++)
				//{
				//	std::cout << b << " " << behd[b] << endl;
				//}
				//std::cout << endl << endl << endl;
				newBehaviors.resize(newBehaviors.size()+1);
				newBehaviors[newBehaviors.size()-1].type = behd[0];
				//std::cout << behd[0] << endl;
				if(behd[0]!="visible" && behd[0]!="outline" && behd[0]!="wireframe")
				{
					newBehaviors[newBehaviors.size()-1].speed = (float)atof(behd[1].c_str());
					if(behd[2]=="{")
					{
						newBehaviors[newBehaviors.size()-1].repeat = true;
						newBehaviors[newBehaviors.size()-1].relative = false;
						newBehaviors[newBehaviors.size()-1].min = (float)atof(behd[3].c_str());
						newBehaviors[newBehaviors.size()-1].max = (float)atof(behd[5].c_str());
					}
					else if(behd[2]=="[")
					{
						newBehaviors[newBehaviors.size()-1].repeat = true;
						newBehaviors[newBehaviors.size()-1].relative = true;
						newBehaviors[newBehaviors.size()-1].min = (float)atof(behd[3].c_str());
						newBehaviors[newBehaviors.size()-1].max = (float)atof(behd[5].c_str());
					}
					else
					{
						newBehaviors[newBehaviors.size()-1].repeat = false;
					}
				}
				else
				{
					//std::cout << "in"<<endl;
					newBehaviors[newBehaviors.size()-1].min = (float)atof(behd[1].c_str());
					newBehaviors[newBehaviors.size()-1].max = (float)atof(behd[1].c_str());
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
		Log.output("Loading world from file: "); Log.output(fileName); Log.output(":\n");
		if(File.fileExists(fileName))
		{
			world newworld;
			ifstream infile;
			vector<string> objd(1);
			vector<object> objs(0);
			string word;
			infile.open(fileName, ios::in);
			while (infile >> word) 
			{
				//std::cout << word << endl;
				if(word=="[")
				{
					Log.output("\tCreating OBJ from data file: "); Log.output(objd[0]); Log.output("| Data length: "); Log.output((float)objd.size()); Log.output(":\n");
					objs.resize(objs.size()+1);
					Log.output("\t\tLoading point data.\n");
					objs[objs.size()-1] = loadObject(objd[0]);
					Log.output("\t\t\tNumber of Polys: "); Log.output((float)objs[objs.size()-1].getSize()); Log.output("\n");
					Log.output("\t\tLoading wireframe data.\n");
					objs[objs.size()-1].setWireframe(atof(objd[1].c_str())!=0);
					Log.output("\t\tLoading visible data.\n");
					objs[objs.size()-1].setVisible(atof(objd[2].c_str())!=0);
					Log.output("\t\tLoading framedelay data.\n");
					objs[objs.size()-1].setFrameDelay(atof(objd[3].c_str()));
					Log.output("\t\tLoading position data.\n");
					objs[objs.size()-1].setPosition((float)atof(objd[4].c_str()), (float)atof(objd[5].c_str()), (float)atof(objd[6].c_str()));
					Log.output("\t\tLoading angle data.\n");
					objs[objs.size()-1].setAngle((float)atof(objd[7].c_str()), (float)atof(objd[8].c_str()), (float)atof(objd[9].c_str()));
					Log.output("\t\tLoading scale data.\n");
					objs[objs.size()-1].setScale((float)atof(objd[10].c_str()), (float)atof(objd[11].c_str()), (float)atof(objd[12].c_str()));
					Log.output("\t\tLoading name.\n");
					objs[objs.size()-1].setName(objd[13]);
					Log.output("\t\tLoading type.\n");
					objs[objs.size()-1].setType(objd[14]);
					Log.output("\t\tSetting filename\n");
					objs[objs.size()-1].setFileName(objd[0]);
					Log.output("\t\tLoading behaviors.\n");
					vector<behavior> behaviors = loadBehaviors(objd[15]);
					Log.output("\t\tLoaded behavior data. Parsing...\n");
					for(std::size_t be = 0; be < behaviors.size(); be++) objs[objs.size()-1].addBehavior(behaviors[be]);
					Log.output("\t\tLoading texture data.\n");
					objs[objs.size()-1].setMaterial(loadTexture(objd[16]));
					objd[0]="";
					objd.resize(1);
					Log.output("\t\tObject created.\n\n");
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
				//std::cout << "FIrst:" <<endl;
				Log.output("\tAdding Object: "); Log.output(objs[objc].getName()); Log.output("\n");
				Log.output("\t\tChecking Cache...\n");
				bool found = false;
				for(unsigned int search = 0; search < cachedVBOId.size(); search++)
				{
					if(objs[objc].getFileName() == cachedVBOName[search])
					{
						found = true;
						Log.output("\t\t\tFound...\n");
						objs[objc].setVBOId(cachedVBOId[search]);
					}
				}
				if(!found)
				{
					Log.output("\t\t\tNot Found...\n");
					objs[objc].generateVBO();
					cachedVBOName.resize(cachedVBOName.size()+1);
					cachedVBOName[cachedVBOName.size()-1] = objs[objc].getFileName();
					cachedVBOId.resize(cachedVBOId.size()+1);
					cachedVBOId[cachedVBOId.size()-1] = objs[objc].getVBOId();
				}
				objs[objc].createBoundingBox();
				objs[objc].createBoundingSphere();
				newworld.addObject(objs[objc]);
				//std::cout << "Adding"<<endl;
			}
			Log.output("Done Loading World!\n\n");
			return newworld;
		}
		else
		{
			Message.errorMessage("Error loading world file: "+fileName+"\nFile not found!\nPress 'OK' to attempt to continue, or 'Cancel' to exit.","Loading Error");
			world newworld;
			return newworld;
		}
	}

	menu loadMenu(string fileName)
	{
		menu newmenu;
		ifstream infile;
		vector<string> menud(1);
		vector<menuobject> menus(0);
		string word;
		infile.open(fileName, ios::in);
		while (infile >> word) 
		{
			if(word=="[")
			{
				//Log.output("Creating MenuOBJ from data file: "); Log.output(menud[0]); Log.output("| Data length: "); Log.output(menu.size()); Log.output(":\n");
				menus.resize(menus.size()+1);
				menus[menus.size()-1].setTexture(menud[0]);
				menus[menus.size()-1].setPosX(atoi(menud[1].c_str()));
				menus[menus.size()-1].setPosY(atoi(menud[2].c_str()));
				menus[menus.size()-1].setWidth(atoi(menud[3].c_str()));
				menus[menus.size()-1].setHeight(atoi(menud[4].c_str()));
				menud[0]="";
				menud.resize(1);
				Log.output("\tObject created.\n\n");
			}
			else if(word=="?")
			{
				menud.resize(menud.size()+1);
			}
			else
			{
				if(menud.size()-1 == 0)
				{
					menud[menud.size()-1].append(word+" ");
				}
				else
				{
					menud[menud.size()-1].append(word);
				}
			}
		}
		for(int objc = 0; objc < (int)menus.size(); objc++)
		{
			//Log.output("Adding Object: "); Log.output(menus[objc].get
			newmenu.addObject(menus[objc]);
		}
		newmenu.loadTextures();
		return newmenu;
	}

	int loadTextureData(string fileName)
	{
		Log.output("\t\t\t\tLoading texture from file: "); Log.output(fileName); Log.output("\n");	
		if(File.fileExists(fileName))
		{
			std::vector<unsigned char> image;
			unsigned width, height;
			unsigned error = lodepng::decode(image, width, height, fileName);
			if(error != 0)
			{
				Log.output("PNG Loading error: "); Log.output(lodepng_error_text(error)); Log.output("\n");
			}
			size_t u2 = 1; 
			while(u2 < width) u2 *= 2;
			size_t v2 = 1; 
			while(v2 < height) v2 *= 2;
		
			double u3 = (double)width / u2;
			double v3 = (double)height / v2;

			std::vector<unsigned char> image2(u2 * v2 * 4);
			for(size_t y = 0; y < height; y++)
			{
				for(size_t x = 0; x < width; x++)
				{
					for(size_t c = 0; c < 4; c++)
					{
						image2[4 * u2 * y + 4 * x + c] = image[4 * width * y + 4 * x + c];
					}
				}
			}
			unsigned int id = 0;
			glEnable(GL_TEXTURE_2D);
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST = no smoothing
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image2[0]);
			int intid = (int) id; 
			return id;
		}
		else
		{
			Message.errorMessage("Error loading texture file: "+fileName+"\nFile not found!\nPress 'OK' to attempt to continue, or 'Cancel' to exit.", "Loading Error");
			return -1;
		}
	}

	texture loadTexture(string fileName)
	{
		Log.output("\t\tLoading Material Data from file: "); Log.output(fileName); Log.output("\n");
		vector<vector<vector<float> > > coords;
		coords.resize(1);
		coords[0].resize(1);
		string imname;
		texture t;
		int line = 0;
		ifstream infile;
		vector<float> texd;
		string word;
		if(File.fileExists(fileName))
		{
			infile.open(fileName, ios::in);
			GLuint id = 0;
			bool textureline = true;
			while (infile >> word) 
			{
				//std::cout << word << endl;
				if(word=="[")
				{
					//std::cout << "\t Expanding Polygon table" << endl;
					coords.resize(coords.size()+1);
					coords[coords.size()-1].resize(1);
				}
				else if(word=="?")
				{
					//std::cout << pointd[0]<<","<<pointd[1]<<","<<pointd[2]<<","<<pointd[3]<<","<<pointd[4]<<","<<pointd[5]<<endl;
				
					if(textureline)
					{
						//std::cout << "\t Read image file name, setting" << endl;
						texd.resize(0);
						textureline = false;
					}
					else
					{
						//std::cout << "\t Adding point to polygon table" << endl;
						//std::cout << "\t" << texd[0] << "," << texd[1] << endl;
						coords[coords.size()-1][coords[coords.size()-1].size()-1].resize(2);
						//std::cout << "\t\t Resized" << endl;
						coords[coords.size()-1][coords[coords.size()-1].size()-1][0] = texd[0];
						//std::cout << "\t\t Added 1" << endl;
						coords[coords.size()-1][coords[coords.size()-1].size()-1][1] = texd[1];
						//std::cout << "\t\t Added 2" << endl;
						coords[coords.size()-1].resize(coords[coords.size()-1].size()+1);
						//std::cout << "\t Resized point table" << endl;
						texd.resize(0);
						//std::cout << "\t Reset coordinate buffer" << endl;
					}
					line++;
					//std::cout << "out" << endl;
				}
				else
				{
					if(word.find(".png") != word.npos)
					{
						Log.output("\t\t\tLoading texture image...\n");
						Log.output("\t\t\t\tChecking Cache...\n");
						bool found = false;
						for(unsigned int search = 0; search < cachedTexId.size(); search++)
						{
							if(word == cachedTexName[search])
							{
								found = true;
								Log.output("\t\t\t\t\tFound...\n");
								t.addNewId(cachedTexId[search]);
							}
						}
						if(!found)
						{
							Log.output("\t\t\t\t\tNot Found...\n");
							t.addNewId(loadTextureData(word));
							cachedTexName.resize(cachedTexName.size()+1);
							cachedTexName[cachedTexName.size()-1] = word;
							cachedTexId.resize(cachedTexId.size()+1);
							cachedTexId[cachedTexId.size()-1] = t.getID(t.getLastID());
						}
						Log.output("\t\t\tLoaded texture image, TexID is "); Log.output((float)t.getID(t.getLastID())); Log.output("\n");
						textureline = true;
					}
					else
					{
						texd.resize(texd.size()+1);
						texd[texd.size()-1] = (float)atof(word.c_str());
					}
				}
			}
			//std::cout << imname << endl;
			t.coords = coords;
			return t;
		}
		else
		{
			Message.errorMessage("Error loading material data file: " + fileName + "\nFile not found!\nPress 'OK' to attempt to continue, or 'Cancel' to exit.", "Loading Error");
			texture t;
			return t;
		}
	}

	bool running = true;

	int crotorder = 1;
	int orotorder = 4;

	file File;
	version Version;
	message Message;
	input Input;
	TDMLmath Math;
	window Window;
	log Log;
	config Config;
	shaders Shaders;
	void (*theirdisplayfunction)();
	void (*theirupdatefunction)();
	void (*theirexitfunction)();
	int nexttextureid = 0;
	GLuint menuvboid = 0;
	HWND windowhandle;

	void setupMenuVBO()
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glGenBuffers(1, &menuvboid);
		GLfloat *geometry;
		GLfloat *coords;
		GLuint *indices;
		geometry = new GLfloat[12];
		indices = new GLuint[4];
		coords = new GLfloat[8];
		geometry[0] = 0;
		geometry[1] = 0;
		geometry[2] = 0;
		coords[0] = 0;
		coords[1] = 0;
		geometry[3] = 0;
		geometry[4] = 1;
		geometry[5] = 0;
		coords[2] = 0;
		coords[3] = 1;
		geometry[6] = 1;
		geometry[7] = 1;
		geometry[8] = 0;
		coords[4] = 1;
		coords[5] = 1;
		geometry[9] = 1;
		geometry[10] = 0;
		geometry[11] = 0;
		coords[6] = 1;
		coords[7] = 0;
		glBindBuffer(GL_ARRAY_BUFFER, menuvboid);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*20, NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*12, geometry);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*12, sizeof(float)*8, coords);
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
		Log.output(key); Log.output("\n");
		Input.SpecialKeyUpFunc(key, x, y);
	}

	void ChannelMouseKeysToInput(int button, int state, int x, int y)
	{
		Input.MouseKeyFunc(button, state, x, y);
	}

	void ChannelMouseMotionToInput(int x, int y)
	{
		Input.MousePosFunc(x, y);
	}

	void setupInput()
	{
		glutKeyboardFunc(ChannelKeyboardToInput);
		glutSpecialFunc(ChannelSpecialKeyboardToInput);
		glutKeyboardUpFunc(ChannelKeyboardUpToInput);
		glutSpecialUpFunc(ChannelSpecialKeyboardUpToInput);
		glutMouseFunc(ChannelMouseKeysToInput);
		glutMotionFunc(ChannelMouseMotionToInput);
		glutPassiveMotionFunc(ChannelMouseMotionToInput);
	}

	void reshape(int wi, int hi)
	{
		running = false;
		float w = (float) wi;
		float h = (float) hi;
		Window.updateSize(wi, hi);
		glViewport(0, 0, (GLsizei) w, (GLsizei) h);              
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();  
		gluPerspective(Config.getFOV(), w/h, 1.000f, 1000000.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		Window.updatePos(glutGet(GLUT_WINDOW_X), glutGet(GLUT_WINDOW_Y));
		running = true;
	}

	void setupWindow (int *argc, char **argv, int width, int height, const char * title, float SkyRed, float SkyGreen, float SkyBlue)
	{
		float w = (float) width;
		float h = (float) height;
		glutInit(argc, argv);     
		if(Config.getAA())
		{
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
		}
		else
		{
			glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
		}
		glutInitWindowSize(width, height);
		glutInitWindowPosition (30, 30);
		glutCreateWindow("TDML_WINDOW");
		windowhandle = FindWindow(NULL, TEXT("TDML_WINDOW"));
		glClearColor(SkyRed, SkyGreen, SkyBlue, 1.0);               
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();  
		gluPerspective(Config.getFOV(), w/h, 1.0f, 10000.0f);
		glClearDepth(1.0f);
		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glutReshapeFunc (reshape);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glewInit();
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		if(Shaders.getUseShaders()) 
		{
			Shaders.setupShaders();
		}
		if(Shaders.getUseShaders() && Shaders.getUseLighting())
		{
			Shaders.setupLighting();
		}
		Window.setPos(30, 30);
		Window.setSize(width, height);
		Window.setFullscreen(false);
		glutSetWindowTitle(title);
		/*
		glEnable (GL_LIGHTING);
		glEnable(GL_NORMALIZE);
		glEnable (GL_LIGHT0);
		glShadeModel(GL_SMOOTH);
		GLfloat lightpos[] = {0.0, 0.0, 1.0, 0.25};
		glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
		*/
	}

	void setupFunctions(void (*displayfunction)(), void (*updatefunction)(), void (*exitfunction)())
	{
		theirdisplayfunction = *displayfunction;
		theirupdatefunction = *updatefunction;
		theirexitfunction = *exitfunction;
		glutDisplayFunc(display);
		glutIdleFunc(update);
		//atexit(exit);
	}

	void setupAll(int *argc, char **argv, int width, int height, const char * title, float SkyRed, float SkyGreen, float SkyBlue, void (*displayfunction)(), void (*updatefunction)(), void (*exitfunction)())
	{
		if(!Log.getDebugMode()) FreeConsole();
		setupWindow(argc, argv, width, height, title, SkyRed, SkyGreen, SkyBlue);
		setupFunctions(displayfunction, updatefunction, exitfunction);
		Math.setupRandom();
		setupInput();
		setupMenuVBO();
	}

	void start()
	{
		//Hook for start
		glutMainLoop();
	}

	void stop()
	{
		//glutDestroyWindow(0);
		for(unsigned int buf = 0; buf < cachedVBOId.size(); buf++)
		{
			glDeleteBuffers(1, &cachedVBOId[buf]);
		}
		glutLeaveMainLoop();
		
		exit();
	}

	void update()
	{
		apptimeElapsed = glutGet(GLUT_ELAPSED_TIME)-applastTime;
		applastTime=glutGet(GLUT_ELAPSED_TIME);
		appTime+=apptimeElapsed;
		//Log.output(appTime); Log.output("\n");
		if(running)
		{
			Shaders.update();
			(*theirupdatefunction)();
			Input.resetMouseKeyPressed();
			Input.resetKeysPressed();
			glutPostRedisplay();
			//Hook for updates
		}
	}

	void display()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		(*theirdisplayfunction)();
		glutSwapBuffers();
	}

	void exit()
	{
		(*theirexitfunction)();
		Log.cleanup();
	}

	void enableCulling(bool state)
	{
		if(state)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}
	}

	void setCameraRotationOrder(int order)
	{
		crotorder = order;
	}

	void setObjectRotationOrder(int order)
	{
		orotorder = order;
	}
	
	void setPause(bool state)
	{
		running = !state;
	}
};