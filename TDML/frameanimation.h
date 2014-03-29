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
		
	};

	class frameanimation
	{
		private:
			int nFrames;
			std::vector<int> frameIDs;

		public:
			int getFrames();
	};
}