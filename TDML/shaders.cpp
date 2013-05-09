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
		useShaders = true;
		useLighting = false;
		shadersInitialized = false;
		uniforms.push_back("useLighting");
	}

	void shaders::populateUniformIDs()
	{
		for(int uni = 0; uni < uniforms.size(); uni++)
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
		vinfile.open("C:/Users/Andrew/Desktop/NCC/OpenGL/3D Model Loader/3D Model Loader/TDML/Shaders/Vertex1.vert", ios::in); //ABSOLUTE PATH ==== BAAAAAD JUJU
		finfile.open("C:/Users/Andrew/Desktop/NCC/OpenGL/3D Model Loader/3D Model Loader/TDML/Shaders/Vertex1.frag", ios::in); //SHIIIIT MAN

		//char* vcode;
		//char* fcode;

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

		//Message.popupMessage(vcode, fcode);

		vinfile.close();
		finfile.close();

		const GLchar* vvcode = vcode.c_str(); 
		const GLchar* ffcode = fcode.c_str(); 

		glShaderSource(vertexShader, 1, &vvcode, NULL);
		glShaderSource(fragmentShader, 1, &ffcode,NULL);

		GLint vertexCompiled = 0;
		glCompileShader(vertexShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexCompiled);
		cout<<endl<<vertexCompiled<<endl;
		if(vertexCompiled==GL_FALSE)
		{
			TDML::Message.errorMessage("Error compiling vertex shader file. Press 'OK' to attempt to continue, or 'Cancel' to exit.", "Shader Error");
		}

		GLint fragmentCompiled = 0;
		glCompileShader(fragmentShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &fragmentCompiled);
		cout<<endl<<fragmentCompiled<<endl;
		if(fragmentCompiled==GL_FALSE)
		{
			TDML::Message.errorMessage("Error compiling fragment shader file. Press 'OK' to attempt to continue, or 'Cancel' to exit.", "Shader Error");
		}

		programID = glCreateProgram();

		glAttachShader(programID, vertexShader);
		glAttachShader(programID, fragmentShader);

		glLinkProgram(programID);
		
		glBindAttribLocation(programID, 0, "v_pos");
		glBindAttribLocation(programID, 1, "n_dir");
		glBindAttribLocation(programID, 2, "t_coo");

		glUseProgram(programID);

		populateUniformIDs();

		shadersInitialized = true;

		changeUniform(UNI_USELIGHTING, 0);
	}

	void shaders::setUseShaders(bool use)
	{
		useShaders = use;
	}

	bool shaders::getUseShaders()
	{
		return useShaders;
	}

	void shaders::setupLighting()
	{
		changeUniform(UNI_USELIGHTING, 1);
	}

	void shaders::setUseLighting(bool use)
	{
		useLighting = use;
		if(use)
		{
			useShaders = true;
		}
	}

	bool shaders::getUseLighting()
	{
		return useLighting;
	}
}