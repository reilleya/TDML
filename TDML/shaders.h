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
			std::vector<std::string> uniforms;
			std::vector<GLuint> uniformIDs;
			bool useShaders;
			bool shadersInitialized;
			bool useLighting;
			bool useTextures;
			GLuint programID;
			void populateUniformIDs();
			GLuint getUniformID(int ID);
			void changeUniform(int uniform, float val);
			void changeUniform(int uniform, float val1, float val2);
			void changeUniform(int uniform, float val1, float val2, float val3);
			void changeUniform(int uniform, float val1, float val2, float val3, float val4);

		public:
			shaders();
			void update();
			void dispInfo();
			void setupShaders();
			void setUseShaders(bool use);
			bool getUseShaders();
			void setupLighting();
			void setUseLighting(bool use);
			bool getUseLighting();
			void setUseTextures(bool use);
			bool getUseTextures();
	};
}