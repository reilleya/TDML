//time.h
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#pragma once

#include "TDML.h"

namespace TDML
{
	class clock
	{
	private:
		unsigned int timer;
		float lastTime;
		float timeElapsed;
		float lastFrame;
		vector<int> frameTimes;
		int nFrames;

	public:
		clock();
		void begin();
		void update();
		void newFrame();
		unsigned int getTimer();
		float getTimeDelta();
		float getAdjustedTime(float value, float targetTimeStep);
		float getFramerate();
	};
}