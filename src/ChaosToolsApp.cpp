/*! \file ChaosToolsApp.cpp
    \brief ChaosToolsApp class implementation
    
    Author: Evan Cordell

	Copyright 2009 Evan Cordell

	This file is part of ChaosTools.

    ChaosTools is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ChaosTools is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ChaosTools.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ChaosToolsApp.h"
#include "ChaosToolsFrm.h"

IMPLEMENT_APP(ChaosToolsFrmApp)

bool ChaosToolsFrmApp::OnInit()
{
    ChaosToolsFrm* frame = new ChaosToolsFrm(NULL);

	config = new wxFileConfig("ChaosTools", "Evan Cordell", wxEmptyString, wxEmptyString, wxCONFIG_USE_LOCAL_FILE | wxCONFIG_USE_RELATIVE_PATH);
	wxConfigBase::Set(config);

	//fixes display issues on mac
	frame->SetSize(500, 500);
    SetTopWindow(frame);
    frame->Show();
    return true;
}
 
int ChaosToolsFrmApp::OnExit()
{
	delete config;
	return 0;
}
