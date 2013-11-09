//file.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	bool file::fileExists(string fileName)
	{
		ifstream testfile(fileName);
		if(testfile) 
		{
			testfile.close();
			return true;
		}
		else
		{
			testfile.close();
			return false;
		}
	}

	void file::takeScreenshot()
	{
		GLuint* pixdata;
		glReadPixels(0, 0, Window.getWidth(), Window.getHeight(), GL_RGBA, GL_INT, (GLvoid*) *pixdata);
		cout << pixdata << endl;
	}
}