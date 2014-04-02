//frameanimation.h
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#pragma once

#include "TDML.h"

namespace TDML
{
	struct framesequence
	{
		std::vector<int> frameIDs;
		int nFrames;
		std::string name;
	};

	class frameanimation
	{
		private:
			std::string filename;
			std::vector<framesequence> sequences;
			std::vector<int> texIDs;
			int currFrame;
			
		public:
			frameanimation();
			frameanimation(std::string filename);
			void setSequence(std::string sequence);
			int getFrame();
			void update();
	};
}