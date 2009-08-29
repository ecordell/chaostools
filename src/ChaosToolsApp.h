/*! \file ChaosToolsApp.h
    \brief ChaosToolsApp class declaration
    
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
/*! \mainpage ChaosTools Documentation
 *
 * \section intro_sec Introduction
 *
 * Feel free to look around. Click on classes for more detailed information for each class in this project.
 *
 */
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

#include <wx/fileconf.h>

class ChaosToolsFrmApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
	private:
		wxFileConfig* config;
};

#endif
