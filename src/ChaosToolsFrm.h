/*!! \file ChaosToolsFrm.h
    \brief ChaosToolsFrm class declaration
    
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

#ifndef __CHAOSTOOLSFRM_h__
#define __CHAOSTOOLSFRM_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif

#include <wx/statusbr.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/stattext.h>
#include <wx/statbmp.h>
#include <wx/grid.h>
#include <wx/panel.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <wx/utils.h>
#include <wx/aboutdlg.h>
#include <wx/fileconf.h>
#include <cstdlib>
#include "optionsdlg.h"

//thread classes
#include "MandelThread.h"
#include "JuliaThread.h"

//Image includes
#include "Images/cos.xpm"
#include "Images/sin.xpm"
#include "Images/logistic.xpm"
#include "Images/quadratic.xpm"
#include "Images/tent.xpm"

#undef ChaosToolsFrm_STYLE
#define ChaosToolsFrm_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX

//! ChaosToolsFrm class
/*!
	Handles all GUI interaction with the user. Computations are passed to worker threads of type MandelThread and JuliaThread.
*/
class ChaosToolsFrm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		//! ChaosToolsFrm Constructor
		/*!
			\param parent Specifies the parent wxWindow object.

			Constructs a ChaosToolsFrm object. This is only ever done once.
		*/
		ChaosToolsFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("ChaosTools"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = ChaosToolsFrm_STYLE);
		//! ChaosToolsFrm destructor
		virtual ~ChaosToolsFrm();
		//! Called when the function dropdown box is changed on the Bifurcations Tab
		/*!
			\param event The wxCommandEvent raised by functionBifChoice.
		*/
        void functionBifChoiceSelected(wxCommandEvent& event );
		//! Called when the main tab notebook changes tabs
		/*!
			\param event The wxNotebookEvent raised by mainBook.
		*/
		void mainBookPageChanged(wxNotebookEvent& event);
		//! Called when the iterations tab sub notebook changes tabs
		/*!
			\param event The wxNotebookEvent raised by iterBook.
		*/
		void iterBookPageChanged(wxNotebookEvent& event);

		
	private:
		wxMenuBar *menuBar;
		wxMenu *fileMenu;
		wxMenu *helpMenu;
		wxMenu *toolsMenu;
		wxTextCtrl *ymaxIterText;
		wxStaticText *ymaxIterLabel;
		wxTextCtrl *yminIterText;
		wxStaticText *yminIterLabel;
		wxTextCtrl *xmaxIterText;
		wxStaticText *xmaxIterLabel;
		wxTextCtrl *xminIterText;
		wxStaticText *xminIterLabel;
		wxStatusBar *statusBar;
		wxButton *resetIfsButton;
		wxTextCtrl *txtIfsTheta;
		wxStaticText *rotText;
		wxTextCtrl *ifsCfText;
		wxStaticText *ifsCfLabel;
		wxTextCtrl *txtIfsMaxIter;
		wxStaticText *ifsIterLabel;
		wxButton *ifsIterButton;
		wxBoxSizer *ifsSideSizer;
		wxStaticBitmap *plotIfsArea;
		wxFlexGridSizer *mainIfsFlexGrid;
		wxPanel *ifsPage;
		wxStaticBitmap *mandelOrbitArea;
		wxStaticBoxSizer *mandelOrbitBoxSizer;
		wxStaticBitmap *mandelJuliaArea;
		wxStaticBoxSizer *mandelJuliaBoxSizer;
		wxButton *resetMandelButton;
		wxTextCtrl *txtMandelMaxIter;
		wxStaticText *mandelIterLabel;
		wxButton *plotMandelButton;
		wxStaticBoxSizer *mandelBoxSizer;
		wxBoxSizer *mandelSideSizer;
		wxStaticBitmap *plotMandelArea;
		wxFlexGridSizer *mainMandelFlexGrid;
		wxPanel *mandelPage;
		wxStaticBitmap *juliaOrbitArea;
		wxStaticBoxSizer *WxStaticBoxSizer1;
		wxButton *juliaResetButton;
		wxTextCtrl *juliaImagText;
		wxStaticText *juliaImagLabel;
		wxTextCtrl *juliaRealText;
		wxStaticText *juliaRealLabel;
		wxFlexGridSizer *juliaFlexGrid;
		wxStaticText *juliaParamLabel;
		wxTextCtrl *txtJuliaMaxIter;
		wxStaticText *juliaIterLabel;
		wxButton *plotJuliaButton;
		wxStaticBoxSizer *juliaBoxSizer;
		wxBoxSizer *juliaSideSizer;
		wxStaticBitmap *plotJuliaArea;
		wxFlexGridSizer *mainJuliaFlexGrid;
		wxPanel *juliaPage;
		wxButton *resetBifButton;
		wxButton *calcBifButton;
		wxTextCtrl *xmaxBifText;
		wxStaticText *xmaxBifLabel;
		wxTextCtrl *xminBifText;
		wxStaticText *xminBifLabel;
		wxTextCtrl *rmaxBifText;
		wxStaticText *rmaxBifLabel;
		wxTextCtrl *rminBifText;
		wxStaticText *rminBifLabel;
		wxTextCtrl *iterBifText;
		wxStaticText *iterBifLabel;
		wxFlexGridSizer *bifSideGridSizer;
		wxStaticBitmap *functionBifBitmap;
		wxChoice *functionBifChoice;
		wxStaticText *bifFunctionLabel;
		wxBoxSizer *bifSideSizer;
		wxStaticBitmap *plotBifArea;
		wxFlexGridSizer *mainBifFlexGrid;
		wxPanel *bifPage;
		wxButton *resetIterButton;
		wxButton *calcIterButton;
		wxTextCtrl *iterSeedText;
		wxStaticText *iterSeedLabel;
		wxTextCtrl *rIterText;
		wxStaticText *rIterLabel;
		wxTextCtrl *iterIterText;
		wxStaticText *iterIterLabel;
		wxFlexGridSizer *iterSideGridSizer;
		wxStaticBitmap *functionIterBitmap;
		wxChoice *functionIterChoice;
		wxStaticText *iterFuncLbl;
		wxBoxSizer *iterSideSizer;
		wxStaticBitmap *plotIterArea;
		wxPanel *WxNoteBookPage4;
		wxStaticBitmap *plotChartArea;
		wxPanel *WxNoteBookPage3;
		wxStaticBitmap *plotHistArea;
		wxPanel *WxNoteBookPage2;
		wxGrid *iterGrid;
		wxPanel *WxNoteBookPage1;
		wxNotebook *iterBook;
		wxFlexGridSizer *mainIterFlexGrid;
		wxPanel *iterPage;
		wxNotebook *mainBook;
		wxBoxSizer *mainSizer;
		
	private:
		enum
		{
			ID_YMAXITERTEXT = wxID_HIGHEST,
			ID_YMAXITERLABEL,
			ID_YMINITERTEXT,
			ID_YMINITERLABEL,
			ID_XMAXITERTEXT,
			ID_XMAXITERLABEL,
			ID_XMINITERTEXT,
			ID_XMINITERLABEL,
			ID_STATUSBAR,
			ID_RESETIFSBUTTON,
			ID_TXTIFSTHETA,
			ID_ROTTEXT,
			ID_IFSCFTEXT,
			ID_IFSCFLABEL,
			ID_TXTIFSMAXITER,
			ID_IFSITERLABEL,
			ID_IFSITERBUTTON,
			ID_PLOTIFSAREA,
			ID_IFSPAGE,
			ID_MANDELORBITAREA,
			ID_MANDELJULIAAREA,
			ID_RESETMANDELBUTTON,
			ID_TXTMANDELMAXITER,
			ID_MANDELITERLABEL,
			ID_PLOTMANDELBUTTON,
			ID_PLOTMANDELAREA,
			ID_MANDELPAGE,
			ID_JULIAORBITAREA,
			ID_JULIARESETBUTTON,
			ID_JULIAIMAGTEXT,
			ID_JULIAIMAGLABEL,
			ID_JULIAREALTEXT,
			ID_JULIAREALLABEL,
			ID_JULIAPARAMLABEL,
			ID_TXTJULIAMAXITER,
			ID_JULIAITERLABEL,
			ID_PLOTJULIABUTTON,
			ID_PLOTJULIAAREA,
			ID_JULIAPAGE,
			ID_CALCBIFBUTTON,
			ID_XMAXBIFTEXT,
			ID_XMAXBIFLABEL,
			ID_XMINBIFTEXT,
			ID_XMINBIFLABEL,
			ID_RMINBIFTEXT,
			ID_RMINBIFLABEL,
			ID_FUNCTIONBIFCHOICE,
			ID_PLOTBIFAREA,
			ID_BIFPAGE,
			ID_RESETBIFBUTTON,
			ID_CALCITERBUTTON,
			ID_ITERSEEDTEXT,
			ID_ITERSEEDLABEL,
			ID_RMAXBIFTEXT,
			ID_RMAXBIFLABEL,
			ID_ITERBIFTEXT,
			ID_ITERBIFLABEL,
			ID_FUNCTIONBIFBITMAP,
			ID_FUNCTIONITERCHOICE,
			ID_BIFFUNCTIONLABEL,
			ID_PLOTITERAREA,
			ID_WXNOTEBOOKPAGE4,
			ID_PLOTCHARTAREA,
			ID_WXNOTEBOOKPAGE3,
			ID_PLOTHISTAREA,
			ID_WXNOTEBOOKPAGE2,
			ID_ITERGRID,
			ID_WXNOTEBOOKPAGE1,
			ID_ITERBOOK,
			ID_ITERPAGE,
			ID_MAINBOOK,
			ID_OPTIONS,
		};
		
	private:
		//! Called when the wxWindow is closed.
		void OnClose(wxCloseEvent& event);
		//! Called when the wxWindow is closed from the menu.
		void OnExit(wxCommandEvent& event);
		//! Called when the about menu item is selected. Displays the about window.
		void OnAbout(wxCommandEvent& event);
		//! Called when the options menu item is selected. Displays the options window.
		void OnOptions(wxCommandEvent& event);
		//! Called by the constructor. Constructs every GUI element and sets initial properties.
		void CreateGUIControls();

		////////////////
		//For Iterations
		////////////////

		double iterxmin, iterxmax, iterymin, iterymax;

		//! Called when a selection is made with the function dropdown box on the Iterations tab.
		/*!
			\param event The wxCommandEvent raised by functionIterChoice.

			Changes the image of the function that is displayed and modifies the iteration loop to use that function.
		*/
		void functionIterChoiceSelected(wxCommandEvent& event);
		//! Called when the Calculate button is clicked on the Iterations tab.
		/*!
			\param event The wxCommandEvent raised by calcIterButton.

			Begins iteration and displaying data in a way determined by the current tab.
		*/
		void OnIterCalcClick(wxCommandEvent& event);
		//! Populates the iteration grid under the List tab.
		void makeIterTable();
		//! Begins drawing the histogram under the Histogram tab.
		void drawHistogram();
		//! Begins drawing the chart under the Chart tab.
		void drawChart();
		//! Begins graphically iterating under the Graphical Iteration tab.
		void drawGraph();
		//! Converts from math to screen x-coordinates for the Iteration tab.
		/*!
			\param x The mathematical x-coordinate.
			\return The screen x-coordinate.
		*/
		int toIterScreenX(double x);
		//! Converts from math to screen y-coordinates for the Iteration tab.
		/*!
			\param y The mathematical y-coordinate.
			\return The screen y-coordinate
		*/
        int toIterScreenY(double y);
		//! Converts from screen to math x-coordinates for the Iteration tab.
		/*!
			\param x The screen x-coordinate.
			\return The 
		*/
        double toIterMathX(int x);
		//! Converts from screen to math y-coordinates for the Iteration tab.
		/*!
			\param y The screen y-coordinate.
			\return The mathematical y-coordinate.
		*/
        double toIterMathY(int y);

		//////////////////
		//For Bifurcations
		//////////////////

		double bifxmin, bifxmax, bifrmin, bifrmax, bifseed;
        int bifxstart, bifystart, bifxend, bifyend, bifiter;

		//! Called when the left mouse button is pressed over plotBifArea.
		/*!
			\param event The wxMouseEvent raised by plotBifArea.

			Starts tracking mouse position to draw the zoom box.
		*/
        void OnBifLeftDown(wxMouseEvent& event);
		//! Called when the left mouse button is released over plotBifArea.
		/*!
			\param event The wxMouseEvent raised by plotBifArea.

			If the mouse has just drawn a box for zooming, resets the window view and redraws the bifurcation diagram.
		*/
        void OnBifLeftUp(wxMouseEvent& event);
		//! Called when the left mouse button is moved over plotBifArea.
		/*!
			\param event The wxMouseEvent raised by plotBifArea.

			Modifies the x and y positions displayed in the status bar.

			If left mouse button is pressed, handles drawing the box for zooming.
		*/
        void OnBifMouseMove(wxMouseEvent& event);
		//! Called when the Calculate button is clicked on the Bifurcations tab.
		/*!
			\param event The wxCommandEvent raised by calcBifButton.

			Calculates and displays the appropriate bifurcation diagram.
		*/
        void OnBifCalcClick(wxCommandEvent& event);
		//! Called when the Reset button is clicked on the Bifurcations tab.
		/*!
			\param event The wxCommandEvent raised by resetBifButton.

			Resets the viewing window to default.
		*/
        void OnBifResetClick(wxCommandEvent& event);
		//! Handles the actual iteration and display of the currently selected function.
        void drawBif();
		//! Converts from screen to math r-coordinates for the Bifurcation tab.
		/*!
			\param r The screen r-coordinate. (Displayed on the x-axis)
			\return The math r-coordinate.
		*/
        double toBifMathR(int r);
		//! Converts from screen to math x-coordinates for the Bifurcation tab.
		/*!
			\param x The screen x-coordinate. (Displayed on the y-axis)
			\return The math x-coordinate.
		*/
        double toBifMathX(int x);
		//! Converts from math to screen r-coordinates for the Bifurcation tab.
		/*!
			\param r The math r-coordinate. (Displayed on the x-axis)
			\return The screen r-coordinate.
		*/
        int toBifScreenR(double r);
		//! Converts from math to screen x-coordinates for the Bifurcation tab.
		/*!
			\param x The math x-coordinate. (Displayed on the y-axis)
			\return The screen x-coordinate.
		*/
        int toBifScreenX(double x);

		////////////////////
        //For Mandelbrot Set
		////////////////////

        double manxmax, manxmin, manymax, manymin;
        int manxstart, manystart, manxend, manyend;

		//! Handles calculating and displaying the Mandelbrot Set.
		/*!
			Calculations handed out to MandelThread objects.
		*/
		void drawMandel();
		//! Handles calculating and drawing the mini Julia set side-view.
		/*!
			\param atX The real component of the current mouse position.
			\param atY The imaginary component of the current mouse position.

			Calculates Julia set for current position.
		*/
		void drawMandelJulia(double atX, double atY);
		//! Handles calculating and drawing the mini Orbit side-view.
		/*!
			\param atX The real component of the current mouse position.
			\param atY The imaginary component of the current mouse position.

			Calculates Orbit for current position.
		*/
		void drawMandelOrbit(double atX, double atY);
		//! Called when a MandelThread finishes calculating a row.
		/*!
			\param event The wxCommandEvent object used to pass the data between threads.
		*/
		void OnMandelThread(wxCommandEvent& event);
		//! Called when the last row is finished calculating, signals the GUI thread to display the image of the Mandelbrot set.
		void OnMandelFinished();
		//! Called when the left mouse button is pressed over plotMandelArea.
		/*!
			\param event The wxMouseEvent raised by plotMandelArea.

			Begins tracking mouse position and drawing zoom box.
		*/
		void OnMandelLeftDown(wxMouseEvent& event);
		//! Called when the left mouse button is released over plotMandelArea.
		/*!
			\param event The wxMouseEvent raised by plotMandelArea.

			Calculates new boundaries and zooms into the set.
		*/
		void OnMandelLeftUp(wxMouseEvent& event);
		//! Called when the right mouse button is pressed over plotMandelArea.
		/*!
			\param event The wxMouseEvent raised by plotMandelArea.

			Switches tabs to the Julia set, and displays the Julia set for the current point.
		*/
		void OnMandelRightDown(wxMouseEvent& event);
		//! Called when the mouse is moved over plotMandelArea.
		/*!
			\param event The wxMouseEvent raised by plotMandelArea.

			If left mouse button is down, draws a zoom box.

			Calls drawMandelJulia and drawMandelOrbit to display Julia set and Orbit for current point.
		*/
		void OnMandelMouseMove(wxMouseEvent& event);
		//! Called when plotMandelButton is clicked.
		/*!
			\param event The wxCommandEvent raised by plotMandelButton.

			Calculates mandelbrot set by calling drawMandel.
		*/
		void OnMandelPlotClick(wxCommandEvent& event);
		//! Called when resetMandelButton is clicked.
		/*!
			\param event The wxCommandEvent raised by resetMandelButton.

			Sets parameters to defaults and displays the Mandelbrot set.
		*/
		void OnMandelResetClick(wxCommandEvent& event);
		//! Converts from screen to math x-coordinates for the Mandelbrot tab.
		/*!
			\param x The screen x-coordinate.
			\return The math x-coordinate.
		*/
		double toMandelMathY(int y);
		//! Converts from screen to math y-coordinates for the Mandelbrot tab.
		/*!
			\param y The screen y-coordinate.
			\return The math y-coordinate.
		*/
		double toMandelMathX(int x);

		///////////////
		//For Julia Set
		//////////////

		double julxmax, julxmin, julymax, julymin;
        int julxstart, julystart, julxend, julyend;

		//! Handles calculating and displaying a Julia Set.
		/*!
			Calculations handed out to JuliaThread objects.
		*/
        void drawJulia();
		//! Handles calculating and drawing the mini Orbit side-view.
		/*!
			\param atX The real component of the current mouse position.
			\param atY The imaginary component of the current mouse position.

			Calculates Orbit for current position.
		*/
        void drawJuliaOrbit(double atX, double atY);
		//! Called when a JuliaThread finishes calculating a row.
		/*!
			\param event The wxCommandEvent object used to pass the data between threads.
		*/
        void OnJuliaThread(wxCommandEvent& event);
		//! Called when the last row is finished calculating, signals the GUI thread to display the image of the Julia set.
        void OnJuliaFinished();
		//! Called when the left mouse button is pressed over plotJuliaArea.
		/*!
			\param event The wxMouseEvent raised by plotJuliaArea.

			Begins tracking mouse position and drawing zoom box.
		*/
        void OnJuliaLeftDown(wxMouseEvent& event);
		//! Called when the left mouse button is released over plotJuliaArea.
		/*!
			\param event The wxMouseEvent raised by plotJuliaArea.

			Calculates new boundaries and zooms into the set.
		*/
        void OnJuliaLeftUp(wxMouseEvent& event);
		//! Called when the mouse is moved over plotJuliaArea.
		/*!
			\param event The wxMouseEvent raised by plotJuliaArea.

			If left mouse button is down, draws a zoom box.

			Calls drawJuliaOrbit to display the Orbit for the current point.
		*/
        void OnJuliaMouseMove(wxMouseEvent& event);
		//! Called when plotJuliaButton is clicked.
		/*!
			\param event The wxCommandEvent raised by plotJuliaButton.

			Calculates Julia set by calling drawJulia.
		*/
        void OnJuliaPlotClick(wxCommandEvent& event);
		//! Called when resetJuliaButton is clicked.
		/*!
			\param event The wxJuliaEvent raised by resetMandelButton.

			Sets parameters to defaults and displays the Julia set.
		*/
        void OnJuliaResetClick(wxCommandEvent& event);
		//! Converts from screen to math x-coordinates for the Julia Set tab.
		/*!
			\param x The screen x-coordinate.
			\return The math x-coordinate.
		*/
        double toJuliaMathY(int y);
		//! Converts from screen to math y-coordinates for the Julia Set tab.
		/*!
			\param y The screen y-coordinate.
			\return The math y-coordinate.
		*/
        double toJuliaMathX(int x);

		//////////////////////////////
        //For Iterated Function System
		//////////////////////////////

        double ifsxmax, ifsxmin, ifsymax, ifsymin;

		//! Handles the calculation and display of the Iterated Function System
        void drawIfs();
		//! Called when the left mouse button is pressed over plotIfsArea.
		/*!
			\param event The wxMouseEvent raised by plotIfsArea.

			Adds a point to the xCoords and yCoords vectors. These points are the seeds for the IFS.
		*/
        void OnIfsLeftDown(wxMouseEvent& event);
		//! Called when the left mouse button is released over plotIfsArea.
		/*!
			\param event The wxMouseEvent raised by plotIfsArea.

			Not currently used.
		*/
        void OnIfsLeftUp(wxMouseEvent& event);
		//! Called when the mouse is moved over plotIfsArea.
		/*!
			\param event The wxMouseEvent raised by plotIfsArea.

			Not currently used.
		*/
        void OnIfsMouseMove(wxMouseEvent& event);
		//! Called when ifsIterButton is clicked
		/*!
			\param event The wxCommandEvent raised by ifsIterButton.

			If seed points exist, iterate the function system by calling drawIfs.
		*/
        void OnIfsIterClick(wxCommandEvent& event);
		//! Called when resetIfsButton is clicked
		/*!
			\param event The wxCommandEvent raised by resetIfsButton.

			Removes all seeds from xCoords and yCoords vectors and clears plotIfsArea.
		*/
        void OnIfsResetClick(wxCommandEvent& event);
		//! Converts from math to screen x-coordinates for the Iterated Function System tab.
		/*!
			\param x The mathematial x-coordinate.
		*/
        int toIfsScreenX(double x);
		//! Converts from math to screen y-coordinates for the Iterated Function System tab.
		/*!
			\param y The mathematial y-coordinate.
		*/
        int toIfsScreenY(double y);
		//! Converts from screen to math x-coordinates for the Iterated Function System tab.
		/*!
			\param x The screen x-coordinate.
		*/
        double toIfsMathX(int x);
		//! Converts from screen to math y-coordinates for the Iterated Function System tab.
		/*!
			\param y The screen y-coordinate.
		*/
        double toIfsMathY(int y);
		//! Produces an appropriate color for a pixel in a julia set or mandelbrot set based on iteration count.
		/*!
			\return wxColour object representing the determined color.

			Consider replacing with wxWidgets code if benchmarks show them to be faster.
		*/
		wxColour getColour(double iter);
};
#endif
