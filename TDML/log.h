//log.h
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#pragma once

#include "TDML.h"

namespace TDML
{
	class log
	{
		private:
			int debugMode;
			std::string outputBuffer;
			std::ofstream outputfile;

		public:
			log();
			void output(std::string Message);
			void setDebugMode(int debug);
			bool getDebugMode();
			void outputWindow(std::string Message);
			void outputLog(std::string Message);
			void outputPopup(std::string Message);
			void output(float Number);
			void outputWindow(float Number);
			void outputLog(float Number);
			void outputPopup(float Number);
			void cleanup();
	};
}