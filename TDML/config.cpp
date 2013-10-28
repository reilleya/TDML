//config.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	config::config()
	{
		multisample = true;
		fov = 45;
	}

	void config::save()
	{
		//put stuff in a config.cfg file somewhere
	}

	void config::reload()
	{
		Log.output("Loading Settings...\n");
		ifstream infile;
		vector<string> configd(0);
		string word;
		infile.open("config.cfg", ios::in);
		while (infile >> word) 
		{
			configd.resize(configd.size()+1);
			configd[configd.size()-1].append(word);
		}
		multisample = atof(configd[0].c_str())!=0;
		Log.output("\tMultisampling: "); Log.output(configd[0]); Log.output("\n");
		fov = (float) atof(configd[1].c_str());
		Log.output("\tField of View: "); Log.output(configd[1]); Log.output("\n");
		Shaders.setShaderPath(configd[2].c_str());
		Log.output("\tShader Path: "); Log.output(configd[2]); Log.output("\n");
		Log.output("Loaded Settings!\n");
	}

	void config::setAA(bool AA)
	{
		multisample = AA;
	}

	bool config::getAA()
	{
		return multisample;
	}

	void config::setFOV(float FOV)
	{
		if(FOV>5)
		{
			if(FOV<120)
			{
				fov = FOV;
			}
			else
			{
				fov = 120;
			}
		}
		else
		{
			fov = 5;
		}
	}

	float config::getFOV()
	{
		return fov;
	}
}