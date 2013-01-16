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
			int scalexz;
			int scaley;
			GLuint vboid;
			GLuint texid;
			texture material;

		public:
			void setHeightMap(std::vector<std::vector<float>> newheightmap);
			void setDimensions(int dim);
			void setTextureId(int textureid);
			void setScale(int xz, int y);
			int getScaleXZ();
			int getScaleY();
			float getHeightMapAt(float x, float z);
			void generateVBO();
			void display();
	};
}