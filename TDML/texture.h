//texture.h
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#pragma once

#include "TDML.h"

namespace TDML
{
	class texture
	{
		private:
			std::vector<int> id;
			int ids;

		public:
			texture();
			void dispInfo();
			void addNewId(int newID);
			int getID(int frame);
			int getLastID();
			std::vector<std::vector<std::vector<float> > > coords;
	};
}