//shaders.h
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#pragma once

#include "TDML.h"

namespace TDML
{
	class shaders
	{
		private:
			std::string shaderPath;
			std::vector<std::string> uniforms;
			std::vector<GLuint> uniformIDs;
			vector3d sunVec;
			bool shadersInitialized;
			bool useLighting;
			bool useTextures;
			GLuint programID;
			void populateUniformIDs();
			void changeUniform(int uniform, float val);
			void changeUniform(int uniform, float val1, float val2);
			void changeUniform(int uniform, float val1, float val2, float val3);
			void changeUniform(int uniform, float val1, float val2, float val3, float val4);

		public:
			shaders();
			GLuint getUniformID(int ID);
			void update();
			void dispInfo();
			void setupShaders();
			void setupLighting();
			void setUseLighting(bool use);
			bool getUseLighting();
			void setUseTextures(bool use);
			bool getUseTextures();
			void setModelMat(float mat[]);
			void setProjMat(float mat[]);
			void setNormalMat(float mat[]);
			void setDiffuseColor(float r, float g, float b, float a);
			void setSunVector(float x, float y, float z);
			void setSunVectorX(float val);
			void setSunVectorY(float val);
			void setSunVectorZ(float val);
			void setSunVector(vector3d sunvec);
			vector3d getSunVector();
			float getSunVectorX();
			float getSunVectorY();
			float getSunVectorZ();
			void updateSunVector();
			void setShaderPath(std::string path);
			std::string getShaderPath();
			void cleanup();
	};
}