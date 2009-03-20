#ifndef __CHAOSTOOLSFRMApp_h__
#define __CHAOSTOOLSFRMApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class ChaosToolsFrmApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
