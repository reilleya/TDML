//shaders.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	shaders::shaders()
	{
		useLighting = false;
		useTextures = true;
		shadersInitialized = false;
		useNoise = false;
		uniforms.push_back("useLighting");
		uniforms.push_back("useTextures");
		uniforms.push_back("modelMat");
		uniforms.push_back("normalMat");
		uniforms.push_back("sunVec");
		uniforms.push_back("projMat");
		uniforms.push_back("diffuseColor");
		uniforms.push_back("tex");
		uniforms.push_back("noise");
		uniforms.push_back("useNoise");
	}

	void shaders::update()
	{
		changeUniform(UNI_USELIGHTING, useLighting);
	}

	void shaders::dispInfo()
	{
		Log.output("Shaders: ");
		Log.output("\tUsing Lighting: "); Log.output(useLighting); Log.output("\n");
		Log.output("\tShaders Initialized: "); Log.output(shadersInitialized); Log.output("\n");
		Log.output("\tUniforms:\n");
		for(int uni = 0; uni < (int)uniforms.size(); uni++)
		{
			Log.output("\t\t"); Log.output(uniforms[uni]); Log.output(": "); Log.output((float)uniformIDs[uni]); Log.output("\n");
		}
	}

	void shaders::populateUniformIDs()
	{
		for(int uni = 0; uni < (int)uniforms.size(); uni++)
		{
			uniformIDs.push_back(glGetUniformLocation(programID,  uniforms[uni].c_str()));
		}
	}

	GLuint shaders::getUniformID(int ID)
	{
		return uniformIDs[ID];
	}

	void shaders::changeUniform(int uniform, float val)
	{
		glUniform1f(getUniformID(uniform), val);
	}

	void shaders::changeUniform(int uniform, float val1, float val2)
	{
		glUniform2f(getUniformID(uniform), val1, val2);
	}

	void shaders::changeUniform(int uniform, float val1, float val2, float val3)
	{
		glUniform3f(getUniformID(uniform), val1, val2, val3);
	}

	void shaders::changeUniform(int uniform, float val1, float val2, float val3, float val4)
	{
		glUniform4f(getUniformID(uniform), val1, val2, val3, val4);
	}

	void shaders::setupShaders()
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);	
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		ifstream vinfile;
		ifstream finfile;

		if(File.fileExists(shaderPath+"/0.vert")) vinfile.open(shaderPath+"/0.vert", ios::in);
		else
		{
			Message.errorMessage("Error loading vertex shader: "+shaderPath+"/0.vert\nFile not found!", "Loading Error");
		}
		
		if(File.fileExists(shaderPath+"/0.frag")) finfile.open(shaderPath+"/0.frag", ios::in);
		else
		{
			Message.errorMessage("Error loading fragment shader: "+shaderPath+"/0.frag\nFile not found!", "Loading Error");
		}

		string vcode;
		string fcode;
		string temp;

		while(vinfile>>temp)
		{
			vcode.append(temp);
			if(*(vcode.end()-1) == ';')
			{
				vcode.append("\n");
			}
			vcode.append(" ");
		}

		while(finfile>>temp)
		{
			fcode.append(temp);
			if(*(fcode.end()-1) == ';' || *(fcode.end()-1) == '{' || *(fcode.end()-1) == '}')
			{
				fcode.append("\n");
			}
			fcode.append(" ");
		}

		vinfile.close();
		finfile.close();

		const GLchar* vvcode = vcode.c_str(); 
		const GLchar* ffcode = fcode.c_str(); 

		glShaderSource(vertexShader, 1, &vvcode, NULL);
		glShaderSource(fragmentShader, 1, &ffcode,NULL);

		GLint vertexCompiled = 0;
		glCompileShader(vertexShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexCompiled);
		if(vertexCompiled==GL_FALSE)
		{
			TDML::Message.errorMessage("Error compiling vertex shader file.", "Shader Error");
		}

		GLint fragmentCompiled = 0;
		glCompileShader(fragmentShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &fragmentCompiled);
		if(fragmentCompiled==GL_FALSE)
		{
			TDML::Message.errorMessage("Error compiling fragment shader file.", "Shader Error");
		}

		programID = glCreateProgram();

		glAttachShader(programID, vertexShader);
		glAttachShader(programID, fragmentShader);

		glLinkProgram(programID);
		glDetachShader(programID, vertexShader);
		glDetachShader(programID, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		
		glBindAttribLocation(programID, 0, "v_pos");
		glBindAttribLocation(programID, 1, "n_dir");
		glBindAttribLocation(programID, 2, "t_coo");

		glUseProgram(programID);

		populateUniformIDs();

		shadersInitialized = true;

		changeUniform(UNI_USELIGHTING, 0);
		changeUniform(UNI_USETEXTURES, 1);
		changeUniform(UNI_USENOISE, 0);
		setDiffuseColor(1.0, 1.0, 1.0, 1.0);
		glUniform1i(getUniformID(UNI_TEXUNITBASE), 0);
		glUniform1i(getUniformID(UNI_TEXUNITNOISE), 1);
		glActiveTexture(TU_BASE);
	}

	void shaders::setupLighting()
	{
		changeUniform(UNI_USELIGHTING, 1);
	}

	void shaders::setUseLighting(bool use)
	{
		useLighting = use;
	}

	bool shaders::getUseLighting()
	{
		return useLighting;
	}

	void shaders::setUseTextures(bool use)
	{
		useTextures = use;
		changeUniform(UNI_USETEXTURES, useTextures);
	}

	bool shaders::getUseTextures()
	{
		return useTextures;
	}

	void shaders::setUseNoise(bool use)
	{
		useNoise = use;
		changeUniform(UNI_USENOISE, useNoise);
	}

	bool shaders::getUseNoise()
	{
		return useNoise;
	}

	void shaders::setModelMat(float mat[])
	{
		glUniformMatrix4fv(getUniformID(UNI_MODELMAT), 1, false, mat);
	}

	void shaders::setProjMat(float mat[])
	{
		glUniformMatrix4fv(getUniformID(UNI_PROJMAT), 1, false, mat);
	}

	void shaders::setNormalMat(float mat[])
	{
		glUniformMatrix3fv(getUniformID(UNI_NORMALMAT), 1, false, mat);
	}

	void shaders::setDiffuseColor(float r,float g,float b,float a)
	{
		changeUniform(UNI_DIFFCOLOR, r/255, g/255, b/255, a/255);
	}

	void shaders::setSunVector(float x, float y, float z)
	{
		sunVec.x = x;
		sunVec.y = y;
		sunVec.z = z;
		updateSunVector();
	}

	void shaders::setSunVectorX(float val)
	{
		sunVec.x = val;
		updateSunVector();
	}

	void shaders::setSunVectorY(float val)
	{
		sunVec.y = val;
		updateSunVector();
	}

	void shaders::setSunVectorZ(float val)
	{
		sunVec.z = val;
		updateSunVector();
	}

	void shaders::setSunVector(vector3d sunvec)
	{
		sunVec = sunvec;
		updateSunVector();
	}

	vector3d shaders::getSunVector()
	{
		return sunVec;
	}

	float shaders::getSunVectorX()
	{
		return sunVec.x;
	}

	float shaders::getSunVectorY()
	{
		return sunVec.y;
	}

	float shaders::getSunVectorZ()
	{
		return sunVec.z;
	}

	void shaders::updateSunVector()
	{
		changeUniform(UNI_SUNVEC, sunVec.x, sunVec.y, sunVec.z);
	}

	void shaders::setShaderPath(std::string path)
	{
		shaderPath = path;
	}

	std::string shaders::getShaderPath()
	{
		return shaderPath;
	}

	void shaders::cleanup()
	{
		glDeleteProgram(programID);
	}
}