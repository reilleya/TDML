//version.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	version::version()
	{
		major = "0.5";
		build = "0999";
	}

	string version::getMajorRevision()
	{
		return major;
	}

	string version::getBuildNumber()
	{
		return build;
	}

	string version::getFullVersion()
	{
		return major+" Build: "+build;
	}
}