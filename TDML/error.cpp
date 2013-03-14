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
		palcehoolme = 0;
	}
	
	void error::message(string MessageText, string TitleText)
	{
		wstring mtemp = wstring(MessageText.begin(), MessageText.end());
		wstring ttemp = wstring(TitleText.begin(), TitleText.end());
		Log.output(MessageBox(0, mtemp.c_str(), ttemp.c_str(), MB_OK | MB_ICONERROR)); 
	}
}