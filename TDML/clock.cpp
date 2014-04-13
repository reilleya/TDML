//time.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	clock::clock()
	{
		timer = 0;
		lastTime = 0;
		timeElapsed = 0;
		lastFrame = 0;
		nFrames = 0;
	}

	void clock::begin()
	{
		lastTime = (float)glutGet(GLUT_ELAPSED_TIME);
		lastFrame = lastTime;
	}

	void clock::update()
	{
		timeElapsed = glutGet(GLUT_ELAPSED_TIME) - lastTime;
		lastTime = (float)glutGet(GLUT_ELAPSED_TIME);
		timer += (int)timeElapsed;
	}

	void clock::newFrame()
	{
		frameTimes.push_back(glutGet(GLUT_ELAPSED_TIME) - (int)lastFrame);
		lastFrame = (float)glutGet(GLUT_ELAPSED_TIME);
		nFrames++;
		if (nFrames > 100)
		{
			frameTimes.erase(frameTimes.begin());
			nFrames = 100;
		}
	}

	unsigned int clock::getTimer()
	{
		return timer;
	}

	float clock::getTimeDelta()
	{
		return timeElapsed;
	}

	float clock::getAdjustedTime(float value, float targetTimeStep)
	{
		return value*(timeElapsed / targetTimeStep);
	}

	float clock::getFramerate()
	{
		float tot = 0;
		for (int frameTimeID = 0; frameTimeID < nFrames; frameTimeID++)
		{
			tot += frameTimes[frameTimeID];
		}
		return 1000 / (tot / nFrames);
	}
}