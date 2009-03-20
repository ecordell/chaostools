#include "ChaosToolsApp.h"
#include "ChaosToolsFrm.h"

IMPLEMENT_APP(ChaosToolsFrmApp)

bool ChaosToolsFrmApp::OnInit()
{
    ChaosToolsFrm* frame = new ChaosToolsFrm(NULL);
    SetTopWindow(frame);
    frame->Show();
    return true;
}
 
int ChaosToolsFrmApp::OnExit()
{
	return 0;
}
