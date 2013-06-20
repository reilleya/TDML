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
	message::message()
	{
		logErrors = true;
	}
	
	void message::setLogErrors(bool LogErrors)
	{
		logErrors = LogErrors;
	}

	void message::popupMessage(string MessageText, string TitleText)
	{
		wstring mtemp = wstring(MessageText.begin(), MessageText.end());
		wstring ttemp = wstring(TitleText.begin(), TitleText.end());
		MessageBox(windowhandle,  mtemp.c_str(), ttemp.c_str(), MB_OK | MB_APPLMODAL); 
	}

	void message::errorMessage(string MessageText, string TitleText)
	{
		wstring mtemp = wstring(MessageText.begin(), MessageText.end());
		wstring ttemp = wstring(TitleText.begin(), TitleText.end());
		int output = MessageBox(windowhandle,  mtemp.c_str(), ttemp.c_str(), MB_OKCANCEL | MB_ICONERROR | MB_APPLMODAL); 
		if(logErrors)
		{
			Log.output(TitleText+":"+MessageText+"\n");
		}
		if(output == IDOK)
		{
			//IDK what tah do? U bwoke it?
		}
		else
		{
			std::exit(EXIT_FAILURE);
		}
	}

	bool message::choiceMessage(string MessageText, string TitleText)
	{
		wstring mtemp = wstring(MessageText.begin(), MessageText.end());
		wstring ttemp = wstring(TitleText.begin(), TitleText.end());
		int output = MessageBox(windowhandle,  mtemp.c_str(), ttemp.c_str(), MB_YESNO | MB_APPLMODAL);
		if(output == IDYES)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}