//error.cpp
//Created by Andrew Reilley
//Development began 7/26/12
//Do not redistribute, modify, or claim ownership of this library!
//If you use this library, please credit Andrew Reilley or eggplantanimation.com
//Contact email: areill1337@gmail.com

#include "TDML.h"

using namespace std;

namespace TDML
{
	error::error()
	{
		logErrors = true;
	}
	
	void error::setLogErrors(bool LogErrors)
	{
		logErrors = LogErrors;
	}

	void error::errorMessage(string MessageText, string TitleText)
	{
		wstring mtemp = wstring(MessageText.begin(), MessageText.end());
		wstring ttemp = wstring(TitleText.begin(), TitleText.end());
		//LPCWSTR mstr = mtemp.c_str();
		int output = MessageBox(0,  mtemp.c_str(), ttemp.c_str(), MB_OKCANCEL | MB_ICONERROR); 
		Log.output(output); Log.output("\n");
		if(output == IDOK)
		{
			//IDK what tah do? U bwoke it?
		}
		else
		{
			std::exit(EXIT_FAILURE);
		}
	}
}