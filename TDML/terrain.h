//terrain.h
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#pragma once

#include "TDML.h"

namespace TDML
{
	class terrain
	{
		private:
			std::vector<std::vector<float>> heightmap;
			int dimensions;
			float scalexz;
			float scaley;
			GLuint vboid;
			GLuint vaoid;
			GLuint texid;

		public:
			void dispInfo();
			void setHeightMap(std::vector<std::vector<float>> newheightmap);
			void setDimensions(int dim);
			void setTextureId(int textureid);
			void setScale(float xz, float y);
			float getScaleXZ();
			float getScaleY();
			float getHeightMapAt(float x, float z);
			void generateVBO();
			void display();
	};
}