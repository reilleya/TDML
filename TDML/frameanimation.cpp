//frameanimation.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#pragma once

#include "TDML.h"

namespace TDML
{
	frameanimation::frameanimation()
	{
		currFrame = 0;
	}

	frameanimation::frameanimation(std::string filename)
	{
		if (File.fileExists(filename))
		{
			ifstream infile;
			string word;
			infile.open(filename, ios::in);
			while (infile >> word)
			{
				if (word[0] == '+')
				{
					Log.output(word + "\n");
					Log.output("Sequence!\n");
					std::vector<std::string> seqPart = splitString(word, '*');
					Log.output(seqPart[1]+"\n");
				}
				else
				{
					texIDs.push_back(loadTextureData(word));
				}
			}
		}
		else
		{
			Message.errorMessage("Unable to load animation file with name: "+filename+".", "Animation Error");
		}
	}
}