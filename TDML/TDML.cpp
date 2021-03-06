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
				for(int polyg = 0; polyg < (int)polys.size()-1; polyg++) //-1 is from the "special" poly... let's just load obj's in the future
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
				Message.errorMessage("Error loading object file: "+fileName+"\nFile not found!", "Loading Error");
				object o;
				return o;
			}
		}
		else
		{
			return cachedObjs[cachedobjid];
		}
	}

	terrain loadTerrain(std::string fileName, std::string textureName, std::string noiseTextureName, float scaleXZ, float scaleY)
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
		newterrain.setTextureIds(loadTextureData(textureName), loadTextureData(noiseTextureName));
		Log.output("\t\tSetting scale\n");
		newterrain.setScale(scaleXZ, scaleY);
		Log.output("\tGenerating VBO\n");
		newterrain.generateVBO();
		Log.output("Done Loading Terrain\n\n");
		newterrain.dispInfo();
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
			world newworld(fileName);
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
					objs[objs.size()-1].setFrameDelay((float)atof(objd[3].c_str()));
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
			Message.errorMessage("Error loading world file: "+fileName+"\nFile not found!","Loading Error");
			world newworld(fileName);
			return newworld;
		}
	}

	menu loadMenu(string fileName)
	{
		menu newmenu(fileName);
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
				menus[menus.size()-1].setName(menud[1]);
				menus[menus.size()-1].setPosX((float)atof(menud[2].c_str()));
				menus[menus.size()-1].setPosY((float)atof(menud[3].c_str()));
				menus[menus.size()-1].setWidth((float)atof(menud[4].c_str()));
				menus[menus.size()-1].setHeight((float)atof(menud[5].c_str()));
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
			unsigned int id = 0;
			glEnable(GL_TEXTURE_2D);
			id = requestBuffer(TEX);
			bindBuffer(TEX, id);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
			int intid = (int) id; 
			return id;
		}
		else
		{
			Message.errorMessage("Error loading texture file: "+fileName+"\nFile not found!", "Loading Error");
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
				if(word=="[")
				{
					coords.resize(coords.size()+1);
					coords[coords.size()-1].resize(1);
				}
				else if(word=="?")
				{
					if(textureline)
					{
						texd.resize(0);
						textureline = false;
					}
					else
					{
						coords[coords.size()-1][coords[coords.size()-1].size()-1].resize(2);
						coords[coords.size()-1][coords[coords.size()-1].size()-1][0] = texd[0];
						coords[coords.size()-1][coords[coords.size()-1].size()-1][1] = texd[1];
						coords[coords.size()-1].resize(coords[coords.size()-1].size()+1);
						texd.resize(0);
					}
					line++;
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
			t.coords = coords;
			return t;
		}
		else
		{
			Message.errorMessage("Error loading material data file: " + fileName + "\nFile not found!", "Loading Error");
			texture t;
			return t;
		}
	}

	bool running = true;

	int crotorder = 1;
	int orotorder = 4;
	matrix4x4 modelMatrix;
	matrix4x4 projMatrix;

	vector<GLuint> allVBO;
	vector<GLuint> allVAO;
	vector<GLuint> allTex;

	int boundVBO;
	int boundVAO;
	int boundTex;

	file File;
	version Version;
	message Message;
	input Input;
	TDMLmath Math;
	window Window;
	log Log;
	config Config;
	shaders Shaders;
	draw2D Draw2D;
	draw3D Draw3D;
	clock Clock;
	void (*theirdisplayfunction)();
	void (*theirupdatefunction)();
	void (*theirexitfunction)();
	int nexttextureid = 0;
	GLuint menuvboid = 0;
	GLuint menuvaoid = 0;
	HWND windowhandle;

	void setupMenuVBO()
	{
		menuvaoid = requestBuffer(VAO);
		bindBuffer(VAO, menuvaoid);

		menuvboid = requestBuffer(VBO);
		GLfloat *geometry;
		GLfloat *coords;
		geometry = new GLfloat[12];
		coords = new GLfloat[8];
		geometry[0] = 0; geometry[1] = 0; geometry[2] = 0;
		coords[0] = 0; coords[1] = 0;
		geometry[3] = 0; geometry[4] = 1; geometry[5] = 0;
		coords[2] = 0; coords[3] = 1;
		geometry[6] = 1; geometry[7] = 1; geometry[8] = 0;
		coords[4] = 1; coords[5] = 1;
		geometry[9] = 1; geometry[10] = 0; geometry[11] = 0;
		coords[6] = 1; coords[7] = 0;
		bindBuffer(VBO, menuvboid);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*20, NULL, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*12, geometry);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*12, sizeof(float)*8, coords);

		glEnableVertexAttribArray(0); //Position
		glEnableVertexAttribArray(1); //Normals...
		glEnableVertexAttribArray(2); //Texture Coords
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //Position
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0); //...Normals... Shouldn't need these... Dummy Placeholder
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(12 * sizeof(GLfloat))); //Texture Coords

		delete geometry;
		delete coords;
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
		resetProjection();
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
		glClearDepth(1.0f);
		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glutReshapeFunc(reshape);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glewInit();
		Config.reload();
		Shaders.setupShaders();
		if(Shaders.getUseLighting())
		{
			Shaders.setupLighting();
		}
		Window.setPos(30, 30);
		Window.setSize(width, height);
		Window.setFullscreen(false);
		glutSetWindowTitle(title);
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
		setupWindow(argc, argv, width, height, title, SkyRed, SkyGreen, SkyBlue);
		setupFunctions(displayfunction, updatefunction, exitfunction);
		Math.setupRandom();
		setupInput();
		setupMenuVBO();
		Draw3D.setup();
	}

	void start()
	{
		//Hook for start
		resetProjection(); //DON'T DO THIS HERE!!!
		glutMainLoop();
	}

	void update()
	{
		//Log.output(appTime); Log.output("\n");
		if(running)
		{
			Shaders.update();
			(*theirupdatefunction)();
			Input.update();
			glutPostRedisplay();
			//Hook for updates
		}
		Clock.update();
	}

	void display()
	{
		Clock.newFrame();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		(*theirdisplayfunction)();
		glutSwapBuffers();
	}

	void exit()
	{
		(*theirexitfunction)();

		Shaders.cleanup();

		for(unsigned int clearVBO = 0; clearVBO < allVBO.size(); clearVBO++)
		{
			glDeleteBuffers(1, &allVBO[clearVBO]);
		}
		for(unsigned int clearVAO = 0; clearVAO < allVAO.size(); clearVAO++)
		{
			glDeleteVertexArrays(1, &allVAO[clearVAO]);
		}
		for(unsigned int clearTex = 0; clearTex < allTex.size(); clearTex++)
		{
			glDeleteTextures(1, &allTex[clearTex]);
		}

		glutLeaveMainLoop();
		
		Log.cleanup();
	}

	bool useCulling = false;
	void enableCulling(bool state)
	{
		useCulling = state;
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

	int getCameraRotationOrder()
	{
		return crotorder;
	}

	int getObjectRotationOrder()
	{
		return orotorder;
	}

	int invertRotationOrder(int order)
	{
		switch(order)
		{
		case 0:
			return 2;
		case 1:
			return 5;
		case 2:
			return 0;
		case 3:
			return 4;
		case 4:
			return 3;
		case 5:
			return 1;
		default:
			return -1;
		}
	}

	void resetProjection()
	{
		projMatrix.loadIdentity();
		projMatrix.perspective(Config.getFOV(), (float)Window.getWidth()/(float)Window.getHeight(), 1.000f, 1000000.0f);
		Shaders.setProjMat(projMatrix.glForm());
	}

	int requestBuffer(int type)
	{
		GLuint id;
		switch(type)
		{
			case VBO:
				glGenBuffers(1, &id);
				allVBO.push_back(id);
			break;

			case VAO:
				glGenVertexArrays(1, &id);
				allVAO.push_back(id);
			break;

			case TEX:
				glGenTextures(1, &id);
				allTex.push_back(id);
			break;
		}
		return id;
	}

	void bindBuffer(int type, int id)
	{
		switch(type)
		{
			case VBO:
				if(id != boundVBO)
				{
					boundVBO = id;
					glBindBuffer(GL_ARRAY_BUFFER, id);
				}
				break;
			case VAO:
				if(id != boundVAO)
				{
					boundVAO = id;
					glBindVertexArray(id);
				}
				break;
			case TEX:
				if(id != boundTex)
				{
					boundTex = id;
					glBindTexture(GL_TEXTURE_2D, id);
				}
				break;
																																				}
	}

	int getBoundBuffer(int type)
	{
		switch(type)
		{
			case VBO:
				return boundVBO;
				break;
			case VAO:
				return boundVAO;
				break;
			case TEX:
				return boundTex;
				break;
		}
	}
	
	void setPause(bool state)
	{
		running = !state;
	}

	std::vector<std::string> splitString(std::string str, char split)
	{
		std::vector<std::string> splitVec;
		std::vector<int> startStop;
		startStop.push_back(0);
		for (unsigned int strpos = 0; strpos < str.length(); strpos++)
		{
			if (str[strpos] == split) startStop.push_back(strpos+1);
		}
		startStop.push_back(str.length()+1);
		std::string part;
		for (unsigned int strppos = 0; strppos < startStop.size() - 1; strppos++)
		{
			part = "";
			for (int instrpos = startStop[strppos]; instrpos < startStop[strppos + 1]-1; instrpos++) part += str[instrpos];
			splitVec.push_back(part);
		}
		return splitVec;
	}

	float strToFloat(std::string str)
	{
		return (float)atof(str.c_str());
	}

	int strToInt(std::string str)
	{
		return (int)atoi(str.c_str());

	}
};