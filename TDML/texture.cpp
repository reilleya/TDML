//texture.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	texture::texture()
	{
		ids = 0;	
	}

	void texture::addNewId(int newID)
	{
		id.resize(ids+1);
		id[ids] = newID;
		ids++;
	}

	int texture::getLastID()
	{
		return ids-1;
	}

	int texture::getID(int frame)
	{
		return id[frame];
	}
}