/*! \file ChaosToolsFrm.cpp
    \brief ChaosToolsFrm class implementation
    
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
#include "ChaosToolsFrm.h"

DEFINE_EVENT_TYPE(wxEVT_MTHREAD)
DEFINE_EVENT_TYPE(wxEVT_JTHREAD)

BEGIN_EVENT_TABLE(ChaosToolsFrm,wxFrame)
	EVT_COMMAND(wxID_ANY, wxEVT_MTHREAD, ChaosToolsFrm::OnMandelThread)
	EVT_COMMAND(wxID_ANY, wxEVT_JTHREAD, ChaosToolsFrm::OnJuliaThread)
	EVT_MENU(wxID_EXIT, ChaosToolsFrm::OnExit)
	EVT_MENU(ID_OPTIONS, ChaosToolsFrm::OnOptions)
	EVT_MENU(wxID_ABOUT, ChaosToolsFrm::OnAbout)
	EVT_CLOSE(ChaosToolsFrm::OnClose)
	EVT_BUTTON(ID_RESETIFSBUTTON,ChaosToolsFrm::OnIfsResetClick)
	EVT_BUTTON(ID_IFSITERBUTTON,ChaosToolsFrm::OnIfsIterClick)
	EVT_BUTTON(ID_RESETMANDELBUTTON,ChaosToolsFrm::OnMandelResetClick)
	EVT_BUTTON(ID_PLOTMANDELBUTTON,ChaosToolsFrm::OnMandelPlotClick)
	EVT_BUTTON(ID_JULIARESETBUTTON,ChaosToolsFrm::OnJuliaResetClick)
	EVT_BUTTON(ID_PLOTJULIABUTTON,ChaosToolsFrm::OnJuliaPlotClick)
	EVT_BUTTON(ID_RESETBIFBUTTON,ChaosToolsFrm::OnBifResetClick)
	EVT_BUTTON(ID_CALCBIFBUTTON,ChaosToolsFrm::OnBifCalcClick)
	EVT_CHOICE(ID_FUNCTIONBIFCHOICE,ChaosToolsFrm::functionBifChoiceSelected)
	EVT_BUTTON(ID_RESETBIFBUTTON,ChaosToolsFrm::OnBifResetClick)
	EVT_BUTTON(ID_CALCITERBUTTON,ChaosToolsFrm::OnIterCalcClick)
	EVT_CHOICE(ID_FUNCTIONITERCHOICE,ChaosToolsFrm::functionIterChoiceSelected)
	EVT_NOTEBOOK_PAGE_CHANGED(ID_ITERBOOK,ChaosToolsFrm::iterBookPageChanged)
	EVT_NOTEBOOK_PAGE_CHANGED(ID_MAINBOOK,ChaosToolsFrm::mainBookPageChanged)
END_EVENT_TABLE()

const int numThreads = 1;
unsigned char* rgbMandel;
unsigned char* rgbJulia;
wxVector<double> xCoords;
wxVector<double> yCoords;
int lineCtr = 0;

ChaosToolsFrm::ChaosToolsFrm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
	//For Iterations
	functionIterBitmap->SetBitmap(wxBitmap(logistic_xpm));
	//For Bifurcations
	plotBifArea->Connect(ID_PLOTBIFAREA, wxEVT_LEFT_DOWN, wxMouseEventHandler(ChaosToolsFrm::OnBifLeftDown), NULL, this);
    plotBifArea->Connect(ID_PLOTBIFAREA, wxEVT_LEFT_UP, wxMouseEventHandler(ChaosToolsFrm::OnBifLeftUp), NULL, this);
    plotBifArea->Connect(ID_PLOTBIFAREA, wxEVT_MOTION, wxMouseEventHandler(ChaosToolsFrm::OnBifMouseMove), NULL, this);
    plotBifArea->SetCursor(wxCursor(wxCURSOR_CROSS));
    bifrmin = 0;
    bifrmax = 4;
    bifxmin = 0;
    bifxmax = 1;
    bifseed = 0.5;
    functionBifBitmap->SetBitmap(wxBitmap(logistic_xpm));
    //For Mandelbrot Set
    plotMandelArea->Connect(ID_PLOTMANDELAREA, wxEVT_LEFT_DOWN, wxMouseEventHandler(ChaosToolsFrm::OnMandelLeftDown), NULL, this);
    plotMandelArea->Connect(ID_PLOTMANDELAREA, wxEVT_LEFT_UP, wxMouseEventHandler(ChaosToolsFrm::OnMandelLeftUp), NULL, this);
    plotMandelArea->Connect(ID_PLOTMANDELAREA, wxEVT_RIGHT_DOWN, wxMouseEventHandler(ChaosToolsFrm::OnMandelRightDown), NULL, this);
    plotMandelArea->Connect(ID_PLOTMANDELAREA, wxEVT_MOTION, wxMouseEventHandler(ChaosToolsFrm::OnMandelMouseMove), NULL, this);
    plotMandelArea->SetCursor(wxCursor(wxCURSOR_HAND));
    manxmin = -2.5;
    manxmax = 1.5;
    manymin = -1.5;
    manymax = 1.5;
    manxend = manyend = 0;
    //For Julia Set
    plotJuliaArea->Connect(ID_PLOTJULIAAREA, wxEVT_LEFT_DOWN, wxMouseEventHandler(ChaosToolsFrm::OnJuliaLeftDown), NULL, this);
    plotJuliaArea->Connect(ID_PLOTJULIAAREA, wxEVT_LEFT_UP, wxMouseEventHandler(ChaosToolsFrm::OnJuliaLeftUp), NULL, this);
    plotJuliaArea->Connect(ID_PLOTJULIAAREA, wxEVT_MOTION, wxMouseEventHandler(ChaosToolsFrm::OnJuliaMouseMove), NULL, this);
    plotJuliaArea->SetCursor(wxCursor(wxCURSOR_HAND));
    julxmin = -2;
    julxmax = 2;
    julymin = -1.5;
    julymax = 1.5;
    julxend = julyend = 0;
    //For Iterated Function System
    plotIfsArea->Connect(ID_PLOTIFSAREA, wxEVT_LEFT_DOWN, wxMouseEventHandler(ChaosToolsFrm::OnIfsLeftDown), NULL, this);
    plotIfsArea->Connect(ID_PLOTIFSAREA, wxEVT_LEFT_UP, wxMouseEventHandler(ChaosToolsFrm::OnIfsLeftUp), NULL, this);
    plotIfsArea->Connect(ID_PLOTIFSAREA, wxEVT_MOTION, wxMouseEventHandler(ChaosToolsFrm::OnIfsMouseMove), NULL, this);
    plotIfsArea->SetCursor(wxCursor(wxCURSOR_CROSS));
    ifsxmin = -2;
    ifsxmax = 2;
    ifsymin = -1.5;
    ifsymax = 1.5;
    wxBufferedDC buffDC;
    wxBitmap *bmp = new wxBitmap(plotIfsArea->GetSize().GetWidth(), plotIfsArea->GetSize().GetHeight());
    buffDC.SelectObject(*bmp);
    buffDC.Clear();
    buffDC.SetBackground(*wxWHITE_BRUSH);
    buffDC.SelectObject(wxNullBitmap);
    plotIfsArea->SetBitmap(*bmp);
    delete bmp;  
}

ChaosToolsFrm::~ChaosToolsFrm()
{
}

void ChaosToolsFrm::CreateGUIControls()
{
	menuBar = new wxMenuBar();
	fileMenu = new wxMenu();
	fileMenu->Append(wxID_EXIT, wxT("E&xit"), wxT("Exits ChaosTools"));
	toolsMenu = new wxMenu();
	toolsMenu->Append(ID_OPTIONS, wxT("&Options"), wxT("Select Options for ChaosTools"));
	helpMenu = new wxMenu();
	helpMenu->Append(wxID_ABOUT, wxT("&About"), wxT("About ChaosTools"));
	menuBar->Append(fileMenu, wxT("&File"));
	menuBar->Append(toolsMenu, wxT("&Tools"));
	menuBar->Append(helpMenu, wxT("&Help"));
	SetMenuBar(menuBar);
	mainSizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizer(mainSizer);
	this->SetAutoLayout(true);

	mainBook = new wxNotebook(this, ID_MAINBOOK, wxPoint(1, 1), wxSize(745, 439), wxNB_DEFAULT);
	mainBook->SetBackgroundColour(wxColour(*wxWHITE));
	mainSizer->Add(mainBook,1,wxALIGN_CENTER | wxEXPAND | wxTOP | wxBOTTOM,0);

	iterPage = new wxPanel(mainBook, ID_ITERPAGE, wxPoint(4, 26), wxSize(737, 409));
	mainBook->AddPage(iterPage, wxT("Iterations"));

	mainIterFlexGrid = new wxFlexGridSizer(0, 2, 0, 0);
	iterPage->SetSizer(mainIterFlexGrid);
	iterPage->SetAutoLayout(true);

	iterBook = new wxNotebook(iterPage, ID_ITERBOOK, wxPoint(0, 2), wxSize(560, 420), wxNB_DEFAULT);
	mainIterFlexGrid->Add(iterBook,1,wxALIGN_CENTER | wxEXPAND | wxTOP | wxBOTTOM,2);

	WxNoteBookPage1 = new wxPanel(iterBook, ID_WXNOTEBOOKPAGE1, wxPoint(4, 26), wxSize(552, 390));
	iterBook->AddPage(WxNoteBookPage1, wxT("List"));

	iterGrid = new wxGrid(WxNoteBookPage1, ID_ITERGRID, wxPoint(0, 0), wxSize(550, 382));
	iterGrid->SetDefaultColSize(48);
	iterGrid->SetDefaultRowSize(25);
	iterGrid->SetRowLabelSize(48);
	iterGrid->SetColLabelSize(25);
	iterGrid->CreateGrid(1,10,wxGrid::wxGridSelectCells);

	WxNoteBookPage2 = new wxPanel(iterBook, ID_WXNOTEBOOKPAGE2, wxPoint(4, 26), wxSize(552, 390));
	iterBook->AddPage(WxNoteBookPage2, wxT("Histogram"));

	plotHistArea = new wxStaticBitmap(WxNoteBookPage2, ID_PLOTHISTAREA, wxNullBitmap, wxPoint(0, 0), wxSize(550, 388) );
	plotHistArea->Enable(false);
	plotHistArea->SetBackgroundColour(wxColour(*wxWHITE));

	WxNoteBookPage3 = new wxPanel(iterBook, ID_WXNOTEBOOKPAGE3, wxPoint(4, 26), wxSize(552, 390));
	iterBook->AddPage(WxNoteBookPage3, wxT("Chart"));

	plotChartArea = new wxStaticBitmap(WxNoteBookPage3, ID_PLOTCHARTAREA, wxNullBitmap, wxPoint(0, 0), wxSize(550, 388) );
	plotChartArea->Enable(false);
	plotChartArea->SetBackgroundColour(wxColour(*wxWHITE));

	WxNoteBookPage4 = new wxPanel(iterBook, ID_WXNOTEBOOKPAGE4, wxPoint(4, 26), wxSize(552, 390));
	iterBook->AddPage(WxNoteBookPage4, wxT("Graphical Iteration"));

	plotIterArea = new wxStaticBitmap(WxNoteBookPage4, ID_PLOTITERAREA, wxNullBitmap, wxPoint(0, 0), wxSize(550, 388) );
	plotIterArea->Enable(false);
	plotIterArea->SetBackgroundColour(wxColour(*wxWHITE));

	iterSideSizer = new wxBoxSizer(wxVERTICAL);
	mainIterFlexGrid->Add(iterSideSizer, 1, wxALIGN_TOP | wxALIGN_CENTER | wxEXPAND | wxALL, 5);

	iterFuncLbl = new wxStaticText(iterPage, ID_BIFFUNCTIONLABEL, wxT("Function:"), wxPoint(58, 5), wxDefaultSize, 0, wxT("iterFuncLbl"));
	iterSideSizer->Add(iterFuncLbl,0,wxALIGN_CENTER | wxALL,5);

	wxArrayString arrayStringFor_functionIterChoice;
	arrayStringFor_functionIterChoice.Add(wxT("Logistic"));
	arrayStringFor_functionIterChoice.Add(wxT("Sin(x)"));
	arrayStringFor_functionIterChoice.Add(wxT("Cos(x)"));
	arrayStringFor_functionIterChoice.Add(wxT("Tent"));
	arrayStringFor_functionIterChoice.Add(wxT("Quadratic"));
	functionIterChoice = new wxChoice(iterPage, ID_FUNCTIONITERCHOICE, wxPoint(25, 34), wxSize(120, 23), arrayStringFor_functionIterChoice, 0, wxDefaultValidator, wxT("functionIterChoice"));
	functionIterChoice->SetSelection(0);
	iterSideSizer->Add(functionIterChoice,0,wxALIGN_CENTER | wxALL,5);

	functionIterBitmap = new wxStaticBitmap(iterPage, ID_FUNCTIONBIFBITMAP, wxNullBitmap, wxPoint(5, 67), wxSize(160, 50) );
	functionIterBitmap->Enable(false);
	functionIterBitmap->SetBackgroundColour(wxColour(*wxWHITE));
	iterSideSizer->Add(functionIterBitmap,0,wxALIGN_CENTER | wxALL,5);

	iterSideGridSizer = new wxFlexGridSizer(0, 2, 0, 0);
	iterSideSizer->Add(iterSideGridSizer, 0, wxALIGN_CENTER | wxALL, 0);

	iterIterLabel = new wxStaticText(iterPage, ID_ITERBIFLABEL, wxT("Iterations:"), wxPoint(12, 5), wxDefaultSize, 0, wxT("iterIterLabel"));
	iterSideGridSizer->Add(iterIterLabel,0,wxALIGN_RIGHT | wxALL,5);

	iterIterText = new wxTextCtrl(iterPage, ID_ITERBIFTEXT, wxT("20"), wxPoint(86, 5), wxSize(45, 19), 0, wxDefaultValidator, wxT("iterIterText"));
	iterSideGridSizer->Add(iterIterText,0,wxALIGN_CENTER | wxALL,5);

	rIterLabel = new wxStaticText(iterPage, ID_RMAXBIFLABEL, wxT("R:"), wxPoint(33, 34), wxDefaultSize, 0, wxT("rIterLabel"));
	iterSideGridSizer->Add(rIterLabel,0,wxALIGN_RIGHT | wxALL,5);

	rIterText = new wxTextCtrl(iterPage, ID_RMAXBIFTEXT, wxT("4.0"), wxPoint(86, 34), wxSize(45, 19), 0, wxDefaultValidator, wxT("rIterText"));
	iterSideGridSizer->Add(rIterText,0,wxALIGN_CENTER | wxALL,5);

	iterSeedLabel = new wxStaticText(iterPage, ID_ITERSEEDLABEL, wxT("Seed:"), wxPoint(24, 63), wxDefaultSize, 0, wxT("iterSeedLabel"));
	iterSideGridSizer->Add(iterSeedLabel,0,wxALIGN_RIGHT | wxALL,5);

	iterSeedText = new wxTextCtrl(iterPage, ID_ITERSEEDTEXT, wxT("0.5"), wxPoint(86, 63), wxSize(45, 19), 0, wxDefaultValidator, wxT("iterSeedText"));
	iterSideGridSizer->Add(iterSeedText,0,wxALIGN_CENTER | wxALL,5);

	calcIterButton = new wxButton(iterPage, ID_CALCITERBUTTON, wxT("Calculate"), wxPoint(47, 330), wxSize(75, 25), 0, wxDefaultValidator, wxT("calcIterButton"));
	iterSideSizer->Add(calcIterButton,0,wxALIGN_CENTER | wxALL,5);

	resetIterButton = new wxButton(iterPage, ID_RESETBIFBUTTON, wxT("Reset"), wxPoint(47, 365), wxSize(75, 25), 0, wxDefaultValidator, wxT("resetIterButton"));
	iterSideSizer->Add(resetIterButton,0,wxALIGN_CENTER | wxALL,5);

	bifPage = new wxPanel(mainBook, ID_BIFPAGE, wxPoint(4, 26), wxSize(737, 409));
	mainBook->AddPage(bifPage, wxT("Bifurcations"));

	mainBifFlexGrid = new wxFlexGridSizer(0, 2, 0, 0);
	bifPage->SetSizer(mainBifFlexGrid);
	bifPage->SetAutoLayout(true);

	plotBifArea = new wxStaticBitmap(bifPage, ID_PLOTBIFAREA, wxNullBitmap, wxPoint(0, 2), wxSize(560, 420) );
	plotBifArea->Enable(false);
	plotBifArea->SetBackgroundColour(wxColour(*wxWHITE));
	mainBifFlexGrid->Add(plotBifArea,1,wxALIGN_CENTER | wxEXPAND | wxTOP | wxBOTTOM,2);

	bifSideSizer = new wxBoxSizer(wxVERTICAL);
	mainBifFlexGrid->Add(bifSideSizer, 1, wxALIGN_TOP | wxALIGN_CENTER | wxEXPAND | wxALL, 5);

	bifFunctionLabel = new wxStaticText(bifPage, ID_BIFFUNCTIONLABEL, wxT("Function:"), wxPoint(58, 5), wxDefaultSize, 0, wxT("bifFunctionLabel"));
	bifSideSizer->Add(bifFunctionLabel,0,wxALIGN_CENTER | wxALL,5);

	wxArrayString arrayStringFor_functionBifChoice;
	arrayStringFor_functionBifChoice.Add(wxT("Logistic"));
	arrayStringFor_functionBifChoice.Add(wxT("Sin(x)"));
	arrayStringFor_functionBifChoice.Add(wxT("Cos(x)"));
	arrayStringFor_functionBifChoice.Add(wxT("Tent"));
	arrayStringFor_functionBifChoice.Add(wxT("Quadratic"));
	functionBifChoice = new wxChoice(bifPage, ID_FUNCTIONBIFCHOICE, wxPoint(25, 34), wxSize(120, 23), arrayStringFor_functionBifChoice, 0, wxDefaultValidator, wxT("functionBifChoice"));
	functionBifChoice->SetSelection(0);
	bifSideSizer->Add(functionBifChoice,0,wxALIGN_CENTER | wxALL,5);

	functionBifBitmap = new wxStaticBitmap(bifPage, ID_FUNCTIONBIFBITMAP, wxNullBitmap, wxPoint(5, 67), wxSize(160, 50) );
	functionBifBitmap->Enable(false);
	functionBifBitmap->SetBackgroundColour(wxColour(*wxWHITE));
	bifSideSizer->Add(functionBifBitmap,0,wxALIGN_CENTER | wxALL,5);

	bifSideGridSizer = new wxFlexGridSizer(0, 2, 0, 0);
	bifSideSizer->Add(bifSideGridSizer, 0, wxALIGN_CENTER | wxALL, 5);

	iterBifLabel = new wxStaticText(bifPage, ID_ITERBIFLABEL, wxT("Iterations:"), wxPoint(12, 5), wxDefaultSize, 0, wxT("iterBifLabel"));
	bifSideGridSizer->Add(iterBifLabel,0,wxALIGN_RIGHT | wxALL,5);

	iterBifText = new wxTextCtrl(bifPage, ID_ITERBIFTEXT, wxT("200"), wxPoint(86, 5), wxSize(45, 19), 0, wxDefaultValidator, wxT("iterBifText"));
	bifSideGridSizer->Add(iterBifText,0,wxALIGN_CENTER | wxALL,5);

	rminBifLabel = new wxStaticText(bifPage, ID_RMINBIFLABEL, wxT("Minimum R:"), wxPoint(5, 34), wxDefaultSize, 0, wxT("rminBifLabel"));
	bifSideGridSizer->Add(rminBifLabel,0,wxALIGN_RIGHT | wxALL,5);

	rminBifText = new wxTextCtrl(bifPage, ID_RMINBIFTEXT, wxT("0.0"), wxPoint(86, 34), wxSize(45, 19), 0, wxDefaultValidator, wxT("rminBifText"));
	bifSideGridSizer->Add(rminBifText,0,wxALIGN_CENTER | wxALL,5);

	rmaxBifLabel = new wxStaticText(bifPage, ID_RMAXBIFLABEL, wxT("Maximum R:"), wxPoint(5, 63), wxDefaultSize, 0, wxT("rmaxBifLabel"));
	bifSideGridSizer->Add(rmaxBifLabel,0,wxALIGN_RIGHT | wxALL,5);

	rmaxBifText = new wxTextCtrl(bifPage, ID_RMAXBIFTEXT, wxT("4.0"), wxPoint(86, 63), wxSize(45, 19), 0, wxDefaultValidator, wxT("rmaxBifText"));
	bifSideGridSizer->Add(rmaxBifText,0,wxALIGN_CENTER | wxALL,5);

	xminBifLabel = new wxStaticText(bifPage, ID_XMINBIFLABEL, wxT("Minimum X:"), wxPoint(5, 92), wxDefaultSize, 0, wxT("xminBifLabel"));
	bifSideGridSizer->Add(xminBifLabel,0,wxALIGN_RIGHT | wxALL,5);

	xminBifText = new wxTextCtrl(bifPage, ID_XMINBIFTEXT, wxT("0.0"), wxPoint(86, 92), wxSize(45, 19), 0, wxDefaultValidator, wxT("xminBifText"));
	bifSideGridSizer->Add(xminBifText,0,wxALIGN_CENTER | wxALL,5);

	xmaxBifLabel = new wxStaticText(bifPage, ID_XMAXBIFLABEL, wxT("Maximum X:"), wxPoint(5, 121), wxDefaultSize, 0, wxT("xmaxBifLabel"));
	bifSideGridSizer->Add(xmaxBifLabel,0,wxALIGN_RIGHT | wxALL,5);

	xmaxBifText = new wxTextCtrl(bifPage, ID_XMAXBIFTEXT, wxT("1.0"), wxPoint(86, 121), wxSize(45, 19), 0, wxDefaultValidator, wxT("xmaxBifText"));
	bifSideGridSizer->Add(xmaxBifText,0,wxALIGN_CENTER | wxALL,5);

	calcBifButton = new wxButton(bifPage, ID_CALCBIFBUTTON, wxT("Calculate"), wxPoint(47, 282), wxSize(75, 25), 0, wxDefaultValidator, wxT("calcBifButton"));
	bifSideSizer->Add(calcBifButton,0,wxALIGN_CENTER | wxALL,5);

	resetBifButton = new wxButton(bifPage, ID_RESETBIFBUTTON, wxT("Reset"), wxPoint(47, 317), wxSize(75, 25), 0, wxDefaultValidator, wxT("resetBifButton"));
	bifSideSizer->Add(resetBifButton,0,wxALIGN_CENTER | wxALL,5);

	juliaPage = new wxPanel(mainBook, ID_JULIAPAGE, wxPoint(4, 26), wxSize(737, 409));
	mainBook->AddPage(juliaPage, wxT("Julia Sets"));

	mainJuliaFlexGrid = new wxFlexGridSizer(0, 2, 0, 0);
	juliaPage->SetSizer(mainJuliaFlexGrid);
	juliaPage->SetAutoLayout(true);

	plotJuliaArea = new wxStaticBitmap(juliaPage, ID_PLOTJULIAAREA, wxNullBitmap, wxPoint(0, 2), wxSize(560, 420) );
	plotJuliaArea->Enable(false);
	plotJuliaArea->SetBackgroundColour(wxColour(*wxBLACK));
	mainJuliaFlexGrid->Add(plotJuliaArea,0,wxALIGN_CENTER | wxEXPAND | wxTOP | wxBOTTOM,2);

	juliaSideSizer = new wxBoxSizer(wxVERTICAL);
	mainJuliaFlexGrid->Add(juliaSideSizer, 0, wxALIGN_TOP | wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	wxStaticBox* juliaBoxSizer_StaticBoxObj = new wxStaticBox(juliaPage, wxID_ANY, wxT("Julia Set"));
	juliaBoxSizer = new wxStaticBoxSizer(juliaBoxSizer_StaticBoxObj, wxVERTICAL);
	juliaSideSizer->Add(juliaBoxSizer, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 25);

	plotJuliaButton = new wxButton(juliaPage, ID_PLOTJULIABUTTON, wxT("Plot"), wxPoint(32, 20), wxSize(75, 25), 0, wxDefaultValidator, wxT("plotJuliaButton"));
	juliaBoxSizer->Add(plotJuliaButton,0,wxALIGN_CENTER | wxALL,5);

	juliaIterLabel = new wxStaticText(juliaPage, ID_JULIAITERLABEL, wxT("Max Iterations:"), wxPoint(29, 55), wxDefaultSize, 0, wxT("juliaIterLabel"));
	juliaBoxSizer->Add(juliaIterLabel,0,wxALIGN_CENTER | wxALL,5);

	txtJuliaMaxIter = new wxTextCtrl(juliaPage, ID_TXTJULIAMAXITER, wxT("2000"), wxPoint(40, 84), wxSize(60, 19), 0, wxDefaultValidator, wxT("txtJuliaMaxIter"));
	juliaBoxSizer->Add(txtJuliaMaxIter,0,wxALIGN_CENTER | wxALL,5);

	juliaParamLabel = new wxStaticText(juliaPage, ID_JULIAPARAMLABEL, wxT("Parameter:"), wxPoint(39, 113), wxDefaultSize, 0, wxT("juliaParamLabel"));
	juliaBoxSizer->Add(juliaParamLabel,0,wxALIGN_CENTER | wxALL,5);

	juliaFlexGrid = new wxFlexGridSizer(0, 2, 0, 0);
	juliaBoxSizer->Add(juliaFlexGrid, 0, wxALIGN_CENTER | wxALL, 0);

	juliaRealLabel = new wxStaticText(juliaPage, ID_JULIAREALLABEL, wxT("Real:"), wxPoint(20, 5), wxDefaultSize, 0, wxT("juliaRealLabel"));
	juliaFlexGrid->Add(juliaRealLabel,0,wxALIGN_RIGHT | wxALL,5);

	juliaRealText = new wxTextCtrl(juliaPage, ID_JULIAREALTEXT, wxT("0.0"), wxPoint(70, 5), wxSize(60, 19), 0, wxDefaultValidator, wxT("juliaRealText"));
	juliaFlexGrid->Add(juliaRealText,0,wxALIGN_CENTER | wxALL,0);

	juliaImagLabel = new wxStaticText(juliaPage, ID_JULIAIMAGLABEL, wxT("Imaginary:"), wxPoint(5, 34), wxDefaultSize, 0, wxT("juliaImagLabel"));
	juliaFlexGrid->Add(juliaImagLabel,0,wxALIGN_RIGHT | wxALL,5);

	juliaImagText = new wxTextCtrl(juliaPage, ID_JULIAIMAGTEXT, wxT("0.0"), wxPoint(70, 34), wxSize(60, 19), 0, wxDefaultValidator, wxT("juliaImagText"));
	juliaFlexGrid->Add(juliaImagText,0,wxALIGN_CENTER | wxALL,0);

	juliaResetButton = new wxButton(juliaPage, ID_JULIARESETBUTTON, wxT("Reset"), wxPoint(32, 200), wxSize(75, 25), 0, wxDefaultValidator, wxT("juliaResetButton"));
	juliaBoxSizer->Add(juliaResetButton,0,wxALIGN_CENTER | wxALL,5);

	wxStaticBox* WxStaticBoxSizer1_StaticBoxObj = new wxStaticBox(juliaPage, wxID_ANY, wxT("Orbit "));
	WxStaticBoxSizer1 = new wxStaticBoxSizer(WxStaticBoxSizer1_StaticBoxObj, wxHORIZONTAL);
	juliaSideSizer->Add(WxStaticBoxSizer1, 0, wxALIGN_CENTER | wxALL, 5);

	juliaOrbitArea = new wxStaticBitmap(juliaPage, ID_JULIAORBITAREA, wxNullBitmap, wxPoint(10, 20), wxSize(100, 75) );
	juliaOrbitArea->Enable(false);
	juliaOrbitArea->SetBackgroundColour(wxColour(*wxBLACK));
	WxStaticBoxSizer1->Add(juliaOrbitArea,0,wxALIGN_CENTER | wxALL,5);

	mandelPage = new wxPanel(mainBook, ID_MANDELPAGE, wxPoint(4, 26), wxSize(737, 409));
	mainBook->AddPage(mandelPage, wxT("Mandelbrot Set"));

	mainMandelFlexGrid = new wxFlexGridSizer(0, 2, 0, 0);
	mandelPage->SetSizer(mainMandelFlexGrid);
	mandelPage->SetAutoLayout(true);

	plotMandelArea = new wxStaticBitmap(mandelPage, ID_PLOTMANDELAREA, wxNullBitmap, wxPoint(0, 2), wxSize(560, 420) );
	plotMandelArea->Enable(false);
	plotMandelArea->SetBackgroundColour(wxColour(*wxBLACK));
	mainMandelFlexGrid->Add(plotMandelArea,1,wxALIGN_CENTER | wxEXPAND | wxTOP | wxBOTTOM,2);

	mandelSideSizer = new wxBoxSizer(wxVERTICAL);
	mainMandelFlexGrid->Add(mandelSideSizer, 1, wxALIGN_TOP | wxALIGN_CENTER | wxALIGN_CENTER_HORIZONTAL | wxEXPAND | wxLEFT | wxRIGHT, 25);

	wxStaticBox* mandelBoxSizer_StaticBoxObj = new wxStaticBox(mandelPage, wxID_ANY, wxT("Mandelbrot "));
	mandelBoxSizer = new wxStaticBoxSizer(mandelBoxSizer_StaticBoxObj, wxVERTICAL);
	mandelSideSizer->Add(mandelBoxSizer, 0, wxALIGN_CENTER | wxALL, 5);

	plotMandelButton = new wxButton(mandelPage, ID_PLOTMANDELBUTTON, wxT("Plot"), wxPoint(13, 20), wxSize(75, 25), 0, wxDefaultValidator, wxT("plotMandelButton"));
	mandelBoxSizer->Add(plotMandelButton,0,wxALIGN_CENTER | wxALL,5);

	mandelIterLabel = new wxStaticText(mandelPage, ID_MANDELITERLABEL, wxT("Max Iterations:"), wxPoint(10, 55), wxDefaultSize, 0, wxT("mandelIterLabel"));
	mandelBoxSizer->Add(mandelIterLabel,0,wxALIGN_CENTER | wxALL,5);

	txtMandelMaxIter = new wxTextCtrl(mandelPage, ID_TXTMANDELMAXITER, wxT("2000"), wxPoint(20, 84), wxSize(60, 19), 0, wxDefaultValidator, wxT("txtMandelMaxIter"));
	mandelBoxSizer->Add(txtMandelMaxIter,0,wxALIGN_CENTER | wxALL,5);

	resetMandelButton = new wxButton(mandelPage, ID_RESETMANDELBUTTON, wxT("Reset"), wxPoint(13, 113), wxSize(75, 25), 0, wxDefaultValidator, wxT("resetMandelButton"));
	mandelBoxSizer->Add(resetMandelButton,0,wxALIGN_CENTER | wxALL,5);

	wxStaticBox* mandelJuliaBoxSizer_StaticBoxObj = new wxStaticBox(mandelPage, wxID_ANY, wxT("Julia Set "));
	mandelJuliaBoxSizer = new wxStaticBoxSizer(mandelJuliaBoxSizer_StaticBoxObj, wxVERTICAL);
	mandelSideSizer->Add(mandelJuliaBoxSizer, 0, wxALIGN_CENTER | wxALL, 5);

	mandelJuliaArea = new wxStaticBitmap(mandelPage, ID_MANDELJULIAAREA, wxNullBitmap, wxPoint(10, 20), wxSize(100, 75) );
	mandelJuliaArea->Enable(false);
	mandelJuliaArea->SetBackgroundColour(wxColour(*wxBLACK));
	mandelJuliaBoxSizer->Add(mandelJuliaArea,0,wxALIGN_CENTER | wxALL,5);

	wxStaticBox* mandelOrbitBoxSizer_StaticBoxObj = new wxStaticBox(mandelPage, wxID_ANY, wxT("Orbit "));
	mandelOrbitBoxSizer = new wxStaticBoxSizer(mandelOrbitBoxSizer_StaticBoxObj, wxVERTICAL);
	mandelSideSizer->Add(mandelOrbitBoxSizer, 0, wxALIGN_CENTER | wxALL, 5);

	mandelOrbitArea = new wxStaticBitmap(mandelPage, ID_MANDELORBITAREA, wxNullBitmap, wxPoint(10, 20), wxSize(100, 75) );
	mandelOrbitArea->Enable(false);
	mandelOrbitArea->SetBackgroundColour(wxColour(*wxBLACK));
	mandelOrbitBoxSizer->Add(mandelOrbitArea,0,wxALIGN_CENTER | wxALL,5);

	ifsPage = new wxPanel(mainBook, ID_IFSPAGE, wxPoint(4, 26), wxSize(737, 409));
	mainBook->AddPage(ifsPage, wxT("Iterated Function System"));

	mainIfsFlexGrid = new wxFlexGridSizer(0, 2, 0, 0);
	ifsPage->SetSizer(mainIfsFlexGrid);
	ifsPage->SetAutoLayout(true);

	plotIfsArea = new wxStaticBitmap(ifsPage, ID_PLOTIFSAREA, wxNullBitmap, wxPoint(0, 2), wxSize(560, 420) );
	plotIfsArea->Enable(false);
	plotIfsArea->SetBackgroundColour(*wxWHITE);
	mainIfsFlexGrid->Add(plotIfsArea,1,wxALIGN_CENTER | wxEXPAND | wxTOP | wxBOTTOM,2);

	ifsSideSizer = new wxBoxSizer(wxVERTICAL);
	mainIfsFlexGrid->Add(ifsSideSizer, 0, wxALIGN_CENTER | wxEXPAND | wxLEFT | wxRIGHT, 30);

	ifsIterButton = new wxButton(ifsPage, ID_IFSITERBUTTON, wxT("Iterate"), wxPoint(20, 5), wxSize(75, 25), 0, wxDefaultValidator, wxT("ifsIterButton"));
	ifsSideSizer->Add(ifsIterButton,0,wxALIGN_CENTER | wxALL,5);

	ifsIterLabel = new wxStaticText(ifsPage, ID_IFSITERLABEL, wxT("Max Iterations:"), wxPoint(17, 40), wxDefaultSize, 0, wxT("ifsIterLabel"));
	ifsSideSizer->Add(ifsIterLabel,0,wxALIGN_CENTER | wxALL,5);

	txtIfsMaxIter = new wxTextCtrl(ifsPage, ID_TXTIFSMAXITER, wxT("2000"), wxPoint(28, 69), wxSize(60, 19), 0, wxDefaultValidator, wxT("txtIfsMaxIter"));
	ifsSideSizer->Add(txtIfsMaxIter,0,wxALIGN_CENTER | wxALL,5);

	ifsCfLabel = new wxStaticText(ifsPage, ID_IFSCFLABEL, wxT("Contraction Factor:"), wxPoint(5, 98), wxDefaultSize, 0, wxT("ifsCfLabel"));
	ifsSideSizer->Add(ifsCfLabel,0,wxALIGN_CENTER | wxALL,5);

	ifsCfText = new wxTextCtrl(ifsPage, ID_IFSCFTEXT, wxT("0.5"), wxPoint(28, 127), wxSize(60, 19), 0, wxDefaultValidator, wxT("ifsCfText"));
	ifsSideSizer->Add(ifsCfText,0,wxALIGN_CENTER | wxALL,5);

	rotText = new wxStaticText(ifsPage, ID_ROTTEXT, wxT("Rotation: (degrees)"), wxPoint(6, 156), wxDefaultSize, 0, wxT("rotText"));
	ifsSideSizer->Add(rotText,0,wxALIGN_CENTER | wxALL,5);

	txtIfsTheta = new wxTextCtrl(ifsPage, ID_TXTIFSTHETA, wxT("0"), wxPoint(28, 185), wxSize(60, 19), 0, wxDefaultValidator, wxT("txtIfsTheta"));
	ifsSideSizer->Add(txtIfsTheta,0,wxALIGN_CENTER | wxALL,5);

	resetIfsButton = new wxButton(ifsPage, ID_RESETIFSBUTTON, wxT("Reset"), wxPoint(20, 214), wxSize(75, 25), 0, wxDefaultValidator, wxT("resetIfsButton"));
	ifsSideSizer->Add(resetIfsButton,0,wxALIGN_CENTER | wxALL,5);

	statusBar = new wxStatusBar(this, ID_STATUSBAR);
	statusBar->SetFieldsCount(3);
	statusBar->SetStatusText(wxT(""),0);
	statusBar->SetStatusText(wxT(""),1);
	statusBar->SetStatusText(wxT(""),2);
	int statusBar_Widths[3];
	statusBar_Widths[0] = 200;
	statusBar_Widths[1] = 200;
	statusBar_Widths[2] = -1;
	statusBar->SetStatusWidths(3,statusBar_Widths);

	xminIterLabel = new wxStaticText(iterPage, ID_XMINITERLABEL, wxT("Minimum X:"), wxPoint(5, 92), wxDefaultSize, 0, wxT("xminIterLabel"));
	iterSideGridSizer->Add(xminIterLabel,0,wxALIGN_RIGHT | wxALL,5);

	xminIterText = new wxTextCtrl(iterPage, ID_XMINITERTEXT, wxT("-2.0"), wxPoint(86, 92), wxSize(45, 19), 0, wxDefaultValidator, wxT("xminIterText"));
	iterSideGridSizer->Add(xminIterText,0,wxALIGN_CENTER | wxALL,5);

	xmaxIterLabel = new wxStaticText(iterPage, ID_XMAXITERLABEL, wxT("Maximum X:"), wxPoint(5, 121), wxDefaultSize, 0, wxT("xmaxIterLabel"));
	iterSideGridSizer->Add(xmaxIterLabel,0,wxALIGN_RIGHT | wxALL,5);

	xmaxIterText = new wxTextCtrl(iterPage, ID_XMAXITERTEXT, wxT("2.0"), wxPoint(86, 121), wxSize(45, 19), 0, wxDefaultValidator, wxT("xmaxIterText"));
	iterSideGridSizer->Add(xmaxIterText,0,wxALIGN_CENTER | wxALL,5);

	yminIterLabel = new wxStaticText(iterPage, ID_YMINITERLABEL, wxT("Minimum Y:"), wxPoint(5, 150), wxDefaultSize, 0, wxT("yminIterLabel"));
	iterSideGridSizer->Add(yminIterLabel,0,wxALIGN_RIGHT | wxALL,5);

	yminIterText = new wxTextCtrl(iterPage, ID_YMINITERTEXT, wxT("-2.0"), wxPoint(86, 150), wxSize(45, 19), 0, wxDefaultValidator, wxT("yminIterText"));
	iterSideGridSizer->Add(yminIterText,0,wxALIGN_CENTER | wxALL,5);

	ymaxIterLabel = new wxStaticText(iterPage, ID_YMAXITERLABEL, wxT("Maximum Y:"), wxPoint(5, 179), wxDefaultSize, 0, wxT("ymaxIterLabel"));
	iterSideGridSizer->Add(ymaxIterLabel,0,wxALIGN_RIGHT | wxALL,5);

	ymaxIterText = new wxTextCtrl(iterPage, ID_YMAXITERTEXT, wxT("2.0"), wxPoint(86, 179), wxSize(45, 19), 0, wxDefaultValidator, wxT("ymaxIterText"));
	iterSideGridSizer->Add(ymaxIterText,0,wxALIGN_CENTER | wxALL,5);

	SetStatusBar(statusBar);
	SetTitle(wxT("ChaosTools"));
	SetIcon(wxNullIcon);
	
	GetSizer()->Layout();
	GetSizer()->Fit(this);
	GetSizer()->SetSizeHints(this);
	Center();
	
	mainIterFlexGrid->AddGrowableCol(0);
	mainIterFlexGrid->AddGrowableRow(0);
	mainBifFlexGrid->AddGrowableCol(0);
	mainBifFlexGrid->AddGrowableRow(0);
	mainMandelFlexGrid->AddGrowableCol(0);
    mainMandelFlexGrid->AddGrowableRow(0);
    mainJuliaFlexGrid->AddGrowableCol(0);
    mainJuliaFlexGrid->AddGrowableRow(0);
    mainIfsFlexGrid->AddGrowableCol(0);
    mainIfsFlexGrid->AddGrowableRow(0);
    
    plotBifArea->Enable();
    plotMandelArea->Enable();
    plotJuliaArea->Enable();
    plotIfsArea->Enable();
    plotHistArea->Enable();
}

void ChaosToolsFrm::OnClose(wxCloseEvent& event)
{
	Destroy();
}
void ChaosToolsFrm::OnExit(wxCommandEvent& event)
{
	Destroy();
}
void ChaosToolsFrm::OnAbout(wxCommandEvent& event)
{
	wxAboutDialogInfo info;
	info.AddDeveloper(wxT("Evan Cordell"));
	info.SetCopyright(wxT("(c) 2009 Evan Cordell <cordell.evan@gmail.com>"));
	info.SetDescription(wxT("ChaosTools is a compilation of several methods for investigating mathematical chaos and related topics. It was written in completion of requirements for Evan Cordell's LSMSA Distinction project."));
	info.SetName(wxT("ChaosTools"));
	info.SetVersion(wxT("1.0.0"));
	wxAboutBox(info);
}
void ChaosToolsFrm::OnOptions(wxCommandEvent& event)
{

}
void ChaosToolsFrm::mainBookPageChanged(wxNotebookEvent& event)
{
    /*
	switch(event.GetSelection()){
        case 0:
            break;
        case 1:
            break;
        case 2:
            drawBif();
            break;
        case 3:
            drawJulia();
            break;
        case 4:
            drawMandel();
            break;
    }
    */
}
void ChaosToolsFrm::OnBifLeftDown(wxMouseEvent& event)
{
    plotBifArea->CaptureMouse();
    bifxstart = event.GetX();
    bifystart = event.GetY();
    event.Skip();
}
void ChaosToolsFrm::OnBifLeftUp(wxMouseEvent& event)
{
    double tbifrmin, tbifrmax, tbifxmin, tbifxmax;
    tbifrmin = toBifMathR((bifxstart<event.GetX()) ? bifxstart : event.GetX());
    tbifrmax = toBifMathR((event.GetX()>bifxstart) ? event.GetX() : bifxstart);
    tbifxmin = toBifMathX((event.GetY()>bifystart) ? event.GetY() : bifystart);
    tbifxmax = toBifMathX((bifystart<event.GetY()) ? bifystart : event.GetY());
    bifrmin = tbifrmin;
    bifrmax = tbifrmax;
    bifxmin = tbifxmin;
    bifxmax = tbifxmax;
    bifxend = bifyend = 0;
    rminBifText->SetValue(wxString(wxString::Format("%f", bifrmin)));
    rmaxBifText->SetValue(wxString(wxString::Format("%f", bifrmax)));
    xminBifText->SetValue(wxString(wxString::Format("%f", bifxmin)));
    xmaxBifText->SetValue(wxString(wxString::Format("%f", bifxmax)));
    drawBif();
    plotBifArea->ReleaseMouse();
    event.Skip();
}
void ChaosToolsFrm::OnBifMouseMove(wxMouseEvent& event)
{
    wxString rt = wxString::Format(wxT("%.17f"), toBifMathR(event.GetX()));
    rt = wxT("R: ") + rt;
    statusBar->SetStatusText(rt,0);
    wxString xt = wxString::Format(wxT("%.17f"), toBifMathX(event.GetY()));
    xt = wxT("X: ") + xt;
    statusBar->SetStatusText(xt,1);
    statusBar->SetStatusText(wxT("Click+Drag to zoom."),2);
    if(event.Dragging() && event.LeftIsDown())
    {
        wxClientDC dc(plotBifArea);
        dc.ResetBoundingBox();
        dc.SetBrush(wxBrush(*wxWHITE, wxTRANSPARENT));
        dc.SetPen(wxPen(wxColour(12,12,12),1,wxDOT));
        dc.SetLogicalFunction(wxINVERT);
        if (bifxend>0 && bifyend>0)
            dc.DrawRectangle(bifxstart, bifystart, bifxend - bifxstart, bifyend - bifystart);
        dc.DrawRectangle(bifxstart, bifystart, event.GetX() - bifxstart, event.GetY()-bifystart);
        bifxend = event.GetX();
        bifyend = event.GetY();
    }
    event.Skip();
}
void ChaosToolsFrm::OnBifCalcClick(wxCommandEvent& event)
{
    drawBif();
}
void ChaosToolsFrm::OnBifResetClick(wxCommandEvent& event)
{
    bifiter=200;
    switch(functionBifChoice->GetSelection())
    {
        case 0:
            bifrmin = 0;
            bifrmax = 4;
            bifxmin = 0;
            bifxmax = 1;
            bifseed = 0.5;
            functionBifBitmap->SetBitmap(wxBitmap(logistic_xpm));
            break;
        case 1:
            bifrmin = 1.4;
            bifrmax = 4.75;
            bifxmin = -4.75;
            bifxmax = 4.75;
            bifseed = 0.5;
            functionBifBitmap->SetBitmap(wxBitmap(sin_xpm));
            break;
        case 2:
            bifrmin = 1;
            bifrmax = 4.75;
            bifxmin = -4.75;
            bifxmax = 4.75;
            bifseed = 0.5;
            functionBifBitmap->SetBitmap(wxBitmap(cos_xpm));
            break;
        case 3:
            bifrmin = 0;
            bifrmax = 2;
            bifxmin = 0;
            bifxmax = 1;
            bifseed = 0.5;
            functionBifBitmap->SetBitmap(wxBitmap(tent_xpm));
            break;
        case 4:
            bifrmin = -2;
            bifrmax = .25;
            bifxmin = -2;
            bifxmax = 2;
            bifseed = 0;
            functionBifBitmap->SetBitmap(wxBitmap(quadratic_xpm));
            break;
    }
    iterBifText->SetValue(wxString(wxString::Format("%i", bifiter)));
    rminBifText->SetValue(wxString(wxString::Format("%.1f", bifrmin)));
    rmaxBifText->SetValue(wxString(wxString::Format("%.1f", bifrmax)));
    xminBifText->SetValue(wxString(wxString::Format("%.1f", bifxmin)));
    xmaxBifText->SetValue(wxString(wxString::Format("%.1f", bifxmax)));
    drawBif();
}
void ChaosToolsFrm::drawBif()
{
    double r, x;
    int i;
    int height = plotBifArea->GetSize().GetHeight();
    int width = plotBifArea->GetSize().GetWidth();
    double dr = (bifrmax-bifrmin)/(width);
    xminBifText->GetValue().ToDouble((double*) &bifxmin);
    xmaxBifText->GetValue().ToDouble((double*) &bifxmax);
    rminBifText->GetValue().ToDouble((double*) &bifrmin);
    rmaxBifText->GetValue().ToDouble((double*) &bifrmax);
    iterBifText->GetValue().ToLong((long*) &bifiter);
    wxBufferedDC buffDC;
    wxBitmap *bmp = new wxBitmap(width, height);
    buffDC.SelectObject(*bmp);
    buffDC.Clear();
    buffDC.SetBackground(*wxWHITE_BRUSH);
    buffDC.SetPen(wxPen(wxColour(0, 0, 0)));
    switch(functionBifChoice->GetSelection())
    {
        case 0:
            for(r = bifrmin; r<=bifrmax; r+=dr)
            {
                x = bifseed;
                for(i = 0; i<=50; i++)
                    x = r * x - r * x * x;
                for(i = 0; i<=50+bifiter; i++)
                {
                    x = r * x - r * x * x;
                    if(r>=bifrmin && r<=bifrmax && x>=bifxmin && x<= bifxmax && i>50)
                        buffDC.DrawPoint(toBifScreenR(r), toBifScreenX(x));
                }
            }
            break;
        case 1:
            for(r = bifrmin; r<=bifrmax; r+=dr)
            {
                x = bifseed;
                for(i = 0; i<=50; i++)
                    x = r * sin(x);
                for(i = 0; i<=50+bifiter; i++)
                {
                    x = r * sin(x);
                    if(r>=bifrmin && r<=bifrmax && x>=bifxmin && x<= bifxmax)
                        buffDC.DrawPoint(toBifScreenR(r), toBifScreenX(x));
                }
            }
            break;
        case 2:
            for(r = bifrmin; r<=bifrmax; r+=dr)
            {
                x = bifseed;
                for(i = 0; i<=50; i++)
                    x = r * cos(x);
                for(i = 0; i<=50+bifiter; i++)
                {
                    x = r * cos(x);
                    if(r>=bifrmin && r<=bifrmax && x>=bifxmin && x<= bifxmax)
                        buffDC.DrawPoint(toBifScreenR(r), toBifScreenX(x));
                }
            } 
            break;
        case 3:
            for(r = bifrmin; r<=bifrmax; r+=dr)
            {
                x = bifseed;
                for(i = 0; i<=50; i++)
                {
                   if(0<=x && x<=.5)
                        x = r*x;
                   else
                        x = r-r*x;
                }
                for(i = 0; i<=50+bifiter; i++)
                {
                    if(0<=x && x<=.5)
                        x = r*x;
                    else
                        x = r-r*x;
                    if(r>=bifrmin && r<=bifrmax && x>=bifxmin && x<= bifxmax)
                        buffDC.DrawPoint(toBifScreenR(r), toBifScreenX(x));
                }
            }
            break;
        case 4:
            for(r = bifrmin; r<=bifrmax; r+=dr)
            {
                x = bifseed;
                for(i = 0; i<=50; i++)
                    x = x*x + r;
                for(i = 0; i<=50+bifiter; i++)
                {
                    x = x*x + r;
                    if(r>=bifrmin && r<=bifrmax && x>=bifxmin && x<= bifxmax)
                        buffDC.DrawPoint(toBifScreenR(r), toBifScreenX(x));
                }   
            }
            break;
    }
    buffDC.SelectObject(wxNullBitmap);
    plotBifArea->SetBitmap(*bmp);
    delete bmp;
}
double ChaosToolsFrm::toBifMathR(int r)
{ 
    return (r - (plotBifArea->GetSize().GetWidth()) / 2) * ((bifrmax - bifrmin) / (plotBifArea->GetSize().GetWidth())) + ((bifrmax + bifrmin) / 2);
}
double ChaosToolsFrm::toBifMathX(int x)
{
    return ((plotBifArea->GetSize().GetHeight()) / 2 - x) * ((bifxmax - bifxmin) / (plotBifArea->GetSize().GetHeight())) + ((bifxmax + bifxmin) / 2);
}
int ChaosToolsFrm::toBifScreenR(double r)
{
    return (int)((plotBifArea->GetSize().GetWidth() / 2) + (r - (bifrmax + bifrmin) / 2) * (plotBifArea->GetSize().GetWidth() / (bifrmax - bifrmin)));
}
int ChaosToolsFrm::toBifScreenX(double x)
{
    return (int)((plotBifArea->GetSize().GetHeight() / 2) - (x - (bifxmax + bifxmin) / 2) * (plotBifArea->GetSize().GetHeight() / (bifxmax - bifxmin)));
}
void ChaosToolsFrm::functionBifChoiceSelected(wxCommandEvent& event)
{
    OnBifResetClick(event);
	iterBifText->SetValue(wxString(wxString::Format("%i", bifiter)));
    rminBifText->SetValue(wxString(wxString::Format("%.1f", bifrmin)));
    rmaxBifText->SetValue(wxString(wxString::Format("%.1f", bifrmax)));
    xminBifText->SetValue(wxString(wxString::Format("%.1f", bifxmin)));
    xmaxBifText->SetValue(wxString(wxString::Format("%.1f", bifxmax)));
}
void ChaosToolsFrm::OnMandelThread(wxCommandEvent& event)
{
	unsigned char* temp = (unsigned char*)event.GetClientData();
	int width = plotMandelArea->GetSize().GetWidth();
	for(int ctr=0; ctr<(width*3); ctr++)
		rgbMandel[event.GetInt()*width*3+ctr] = temp[ctr]; 
	delete[] temp;
	lineCtr++;
	if (lineCtr == plotMandelArea->GetSize().GetHeight())
		OnMandelFinished();
}
void ChaosToolsFrm::OnMandelFinished()
{
	wxImage *mandy = new wxImage(plotMandelArea->GetSize().GetWidth(), plotMandelArea->GetSize().GetHeight(), rgbMandel);
	wxBitmap *bmp = new wxBitmap(*mandy);
	plotMandelArea->SetBitmap(*bmp);
	delete bmp;
	delete mandy;
	rgbMandel = NULL;
}
void ChaosToolsFrm::OnMandelLeftDown(wxMouseEvent& event)
{
    plotMandelArea->CaptureMouse();
    manxstart = event.GetX();
    manystart = event.GetY();
    event.Skip();
}
void ChaosToolsFrm::OnMandelLeftUp(wxMouseEvent& event)
{
    double tmanxmin, tmanxmax, tmanymin, tmanymax;
    tmanxmin = toMandelMathX((manxstart<event.GetX()) ? manxstart : event.GetX());
    tmanxmax = toMandelMathX((event.GetX()>manxstart) ? event.GetX() : manxstart);
    tmanymin = toMandelMathY((event.GetY()>manystart) ? event.GetY() : manystart);
    tmanymax = toMandelMathY((manystart<event.GetY()) ? manystart : event.GetY());
    double dx = (tmanxmax-tmanxmin)/(plotMandelArea->GetSize().GetWidth());
    double dy = (tmanymax-tmanymin)/(plotMandelArea->GetSize().GetHeight());
    if((tmanxmax-tmanxmin)/(tmanymax-tmanymin) < 4/3)
        while((tmanxmax-tmanxmin)/(tmanymax-tmanymin) < 4/3)
            if(tmanymax-tmanymin>tmanxmax-tmanxmin)
                tmanxmax+=dx;
            else
                tmanymax+=dy;
    else
        while((tmanxmax-tmanxmin)/(tmanymax-tmanymin) > 4/3)
            if(tmanymax-tmanymin>tmanxmax-tmanxmin)
                tmanymax-=dx;
            else
                tmanxmax-=dy;
    manxmin = tmanxmin;
    manxmax = tmanxmax;
    manymin = tmanymin;
    manymax = tmanymax;
    manxend = manyend = 0;
    //reverse box
    wxClientDC dc(plotMandelArea);
    dc.ResetBoundingBox();
    dc.SetBrush(wxBrush(*wxWHITE, wxTRANSPARENT));
    dc.SetPen(wxPen(wxColour(12,12,12),1,wxDOT));
    dc.SetLogicalFunction(wxINVERT);
    if (manxend>0 && manyend>0)
        dc.DrawRectangle(manxstart, manystart, manxend - manxstart, manyend - manystart);
    dc.DrawRectangle(manxstart, manystart, event.GetX() - manxstart, event.GetY()-manystart);
    drawMandel();
    plotMandelArea->ReleaseMouse();
    event.Skip();
}
void ChaosToolsFrm::OnMandelRightDown(wxMouseEvent& event)
{
    wxString xt = wxString::Format(wxT("%.17f"), toMandelMathX(event.GetX()));
    wxString yt = wxString::Format(wxT("%.17f"), toMandelMathY(event.GetY()));
    juliaRealText->SetValue(xt);
    juliaImagText->SetValue(yt);
    mainBook->ChangeSelection(2);
    julxmin = -2;
    julxmax = 2;
    julymin = -2;
    julymax = 2;
	txtJuliaMaxIter->SetValue(wxT("2000"));
    drawJulia();
    event.Skip();
}
void ChaosToolsFrm::OnMandelMouseMove(wxMouseEvent& event)
{
     
    wxString xt = wxString::Format(wxT("%.17f"), toMandelMathX(event.GetX()));
    xt = wxT("X: ") + xt;
    statusBar->SetStatusText(xt,0);
    wxString yt = wxString::Format(wxT("%.17f"), toMandelMathY(event.GetY()));
    yt = wxT("Y: ") + yt;
    statusBar->SetStatusText(yt,1);
    statusBar->SetStatusText(wxT("Click+Drag to zoom."),2);
    if(event.Dragging() && event.LeftIsDown())
    {
        wxClientDC dc(plotMandelArea);
        dc.ResetBoundingBox();
        dc.SetBrush(wxBrush(*wxWHITE, wxTRANSPARENT));
        dc.SetPen(wxPen(wxColour(12,12,12),1,wxDOT));
        dc.SetLogicalFunction(wxINVERT);
        if (manxend>0 && manyend>0)
            dc.DrawRectangle(manxstart, manystart, manxend - manxstart, manyend - manystart);
        dc.DrawRectangle(manxstart, manystart, event.GetX() - manxstart, event.GetY()-manystart);
        manxend = event.GetX();
        manyend = event.GetY();
    }
    drawMandelJulia(toMandelMathX(event.GetX()), toMandelMathY(event.GetY()));
    drawMandelOrbit(toMandelMathX(event.GetX()), toMandelMathY(event.GetY()));
    event.Skip();
}
void ChaosToolsFrm::OnMandelPlotClick(wxCommandEvent& event)
{
    drawMandel();
}
void ChaosToolsFrm::OnMandelResetClick(wxCommandEvent& event)
{
    manxmin = -2.5;
    manxmax = 1.5;
    manymin = -1.5;
    manymax = 1.5;
	txtMandelMaxIter->SetValue(wxT("2000"));
    drawMandel();
}
void ChaosToolsFrm::drawMandel()
{
    int width, height, maxiter;
	lineCtr=0;
    height = plotMandelArea->GetSize().GetHeight();
    width = plotMandelArea->GetSize().GetWidth();
    txtMandelMaxIter->GetValue().ToLong((long*) &maxiter);
    rgbMandel = (unsigned char*)malloc(width*height*3);
    for (int r = 0; r<height; r+=numThreads) //rows: y
    {
        MandelThread *newRow[numThreads];
        for(int i = 0; i<numThreads; i++)
        {
            newRow[i] = new MandelThread(this, r+i, manxmin, manxmax, manymin, manymax, width, height, maxiter);
            newRow[i]->Create();
            newRow[i]->Run();
        }  
    } 
}

void ChaosToolsFrm::drawMandelJulia(double atX, double atY)
{
    wxBufferedDC buffDC;
    int i, r, iter, width, height, maxiter;
    double x, y, xtemp, y0, x0, dx, dy;
    double jmanxmin = -2, jmanxmax = 2, jmanymin = -2, jmanymax = 2;
    height = mandelJuliaArea->GetSize().GetHeight();
    width = mandelJuliaArea->GetSize().GetWidth();
    wxBitmap *bmp = new wxBitmap(width,height);
    buffDC.SelectObject(*bmp);
    dx = (jmanxmax-jmanxmin)/(width);
    dy = (jmanymax-jmanymin)/(height);
    maxiter = 200;
    x0 = atX;
    y0 = atY;
    for (r = 0; r<=height;r++) //rows: y
    {
        for (i=0; i<=width; i++) //columns: x
        {
            y = jmanymax - r*dy;
            x = jmanxmin + i*dx;
            iter = 0;
            while (x*x+y*y < 6 && iter<maxiter)
            {
                xtemp = x*x - y*y + x0;
                y = x*y + x*y + y0;
                x = xtemp;
                iter++;
            }
            if (iter==maxiter)
                buffDC.SetPen(*wxBLACK_PEN);
            else
                buffDC.SetPen(wxPen(getColour((4*(iter - (log(log(x*x+y*y)))/log(2.0))))));
            buffDC.DrawPoint(i,r);
        }
    }
    buffDC.SelectObject(wxNullBitmap);
    mandelJuliaArea->SetBitmap(*bmp);
    delete bmp;
}
void ChaosToolsFrm::drawMandelOrbit(double atX, double atY)
{
    wxBufferedDC buffDC;
    int iter, width, height, maxiter;
    double x, y, xtemp;
    double omanxmin = -2, omanxmax = 2, omanymin = -2, omanymax = 2;
    height = 75;
    width = 100;
    wxBitmap *bmp = new wxBitmap(width,height);
    buffDC.SelectObject(*bmp);
    buffDC.SetPen(*wxWHITE_PEN);
    txtMandelMaxIter->GetValue().ToLong((long*) &maxiter);
    iter = 0;
    x=y=0;
    buffDC.DrawLine(0, height/2, width, height/2);
    buffDC.DrawLine(width/2, 0, width/2, height);
    buffDC.SetPen(*wxRED_PEN);
    while (x*x+y*y < 4 && iter<maxiter)
    {
        xtemp = x*x - y*y + atX;
        y = x*y + x*y + atY;
        x = xtemp;
        buffDC.DrawPoint((int)((width / 2) + (x - (omanxmax + omanxmin) / 2) * (width / (omanxmax - omanxmin))), (int)((height / 2) - (y - (omanymax + omanymin) / 2) * (height / (omanymax - omanymin))));
        iter++;
    }
    buffDC.SelectObject(wxNullBitmap);
    mandelOrbitArea->SetBitmap(*bmp);
    delete bmp;
}
double ChaosToolsFrm::toMandelMathX(int x)
{ 
    return (x - (plotMandelArea->GetSize().GetWidth()) / 2) * ((manxmax - manxmin) / (plotMandelArea->GetSize().GetWidth())) + ((manxmax + manxmin) / 2);
}
double ChaosToolsFrm::toMandelMathY(int y)
{
    return ((plotMandelArea->GetSize().GetHeight()) / 2 - y) * ((manymax - manymin) / (plotMandelArea->GetSize().GetHeight())) + ((manymax + manymin) / 2);
}
void ChaosToolsFrm::OnJuliaThread(wxCommandEvent& event)
{
	unsigned char* temp = (unsigned char*)event.GetClientData();
	int width = plotJuliaArea->GetSize().GetWidth();
	for(int ctr=0; ctr<(width*3); ctr++)
		rgbJulia[event.GetInt()*width*3+ctr] = temp[ctr];
	delete[] temp;
	lineCtr++;
	if (lineCtr == plotJuliaArea->GetSize().GetHeight())
		OnJuliaFinished();
}
void ChaosToolsFrm::OnJuliaFinished()
{
	wxImage *julie = new wxImage(plotJuliaArea->GetSize().GetWidth(), plotJuliaArea->GetSize().GetHeight(), rgbJulia);
	wxBitmap *bmp = new wxBitmap(*julie);
	plotJuliaArea->SetBitmap(*bmp);
	delete bmp;
	delete julie;
	rgbJulia = NULL;
}
void ChaosToolsFrm::OnJuliaLeftDown(wxMouseEvent& event)
{
    plotJuliaArea->CaptureMouse();
    julxstart = event.GetX();
    julystart = event.GetY();
    event.Skip();
}
void ChaosToolsFrm::OnJuliaLeftUp(wxMouseEvent& event)
{
    double tjulxmin, tjulxmax, tjulymin, tjulymax;
    tjulxmin = toJuliaMathX((julxstart<event.GetX()) ? julxstart : event.GetX());
    tjulxmax = toJuliaMathX((event.GetX()>julxstart) ? event.GetX() : julxstart);
    tjulymin = toJuliaMathY((event.GetY()>julystart) ? event.GetY() : julystart);
    tjulymax = toJuliaMathY((julystart<event.GetY()) ? julystart : event.GetY());
    double dx = (tjulxmax-tjulxmin)/(plotJuliaArea->GetSize().GetWidth());
    double dy = (tjulymax-tjulymin)/(plotJuliaArea->GetSize().GetHeight());
    if((tjulxmax-tjulxmin)/(tjulymax-tjulymin) < 4/3)
        while((tjulxmax-tjulxmin)/(tjulymax-tjulymin) < 4/3)
            if(tjulymax-tjulymin>tjulxmax-tjulxmin)
                tjulxmax+=dx;
            else
                tjulymax+=dy;
    else
        while((tjulxmax-tjulxmin)/(tjulymax-tjulymin) > 4/3)
            if(tjulymax-tjulymin>tjulxmax-tjulxmin)
                tjulymax-=dx;
            else
                tjulxmax-=dy;
    julxmin = tjulxmin;
    julxmax = tjulxmax;
    julymin = tjulymin;
    julymax = tjulymax;
    julxend = julyend = 0;
    //reverse box
    wxClientDC dc(plotJuliaArea);
    dc.ResetBoundingBox();
    dc.SetBrush(wxBrush(*wxWHITE, wxTRANSPARENT));
    dc.SetPen(wxPen(wxColour(12,12,12),1,wxDOT));
    dc.SetLogicalFunction(wxINVERT);
    if (julxend>0 && julyend>0)
        dc.DrawRectangle(julxstart, julystart, julxend - julxstart, julyend - julystart);
    dc.DrawRectangle(julxstart, julystart, event.GetX() - julxstart, event.GetY()-julystart);
    drawJulia();
    plotJuliaArea->ReleaseMouse();
    event.Skip();
}
void ChaosToolsFrm::OnJuliaMouseMove(wxMouseEvent& event)
{

    wxString xt = wxString::Format(wxT("%.17f"), toJuliaMathX(event.GetX()));
    xt = wxT("X: ") + xt;
    statusBar->SetStatusText(xt,0);
    wxString yt = wxString::Format(wxT("%.17f"), toJuliaMathY(event.GetY()));
    yt = wxT("Y: ") + yt;
    statusBar->SetStatusText(yt,1);
    statusBar->SetStatusText(wxT("Click+Drag to zoom."),2);
    if(event.Dragging() && event.LeftIsDown())
    {
        wxClientDC dc(plotJuliaArea);
        dc.ResetBoundingBox();
        dc.SetBrush(wxBrush(*wxWHITE, wxTRANSPARENT));
        dc.SetPen(wxPen(wxColour(12,12,12),1,wxDOT));
        dc.SetLogicalFunction(wxINVERT);
        if (julxend>0 && julyend>0)
            dc.DrawRectangle(julxstart, julystart, julxend - julxstart, julyend - julystart);
        dc.DrawRectangle(julxstart, julystart, event.GetX() - julxstart, event.GetY()-julystart);
        julxend = event.GetX();
        julyend = event.GetY();
    }
    drawJuliaOrbit(toJuliaMathX(event.GetX()), toJuliaMathY(event.GetY()));
    event.Skip();
}
void ChaosToolsFrm::OnJuliaPlotClick(wxCommandEvent& event)
{
    drawJulia();
}
void ChaosToolsFrm::OnJuliaResetClick(wxCommandEvent& event)
{
    julxmin = -2;
    julxmax = 2;
    julymin = -2;
    julymax = 2;
	txtJuliaMaxIter->SetValue(wxT("2000"));
    drawJulia();
}
void ChaosToolsFrm::drawJulia()
{
    int width, height, maxiter;
    double real, imag;
    juliaRealText->GetValue().ToDouble((double*) &real);
    juliaImagText->GetValue().ToDouble((double*) &imag);
	lineCtr=0;
    height = plotJuliaArea->GetSize().GetHeight();
    width = plotJuliaArea->GetSize().GetWidth();
    txtJuliaMaxIter->GetValue().ToLong((long*) &maxiter);
    rgbJulia = (unsigned char*)malloc(width*height*3);
    for (int r = 0; r<height; r+=numThreads) //rows: y
    {
        JuliaThread *newRow[numThreads];
        for(int i = 0; i<numThreads; i++)
        {
            newRow[i] = new JuliaThread(this, r+i, real, imag, julxmin, julxmax, julymin, julymax, width, height, maxiter);
            newRow[i]->Create();
            newRow[i]->Run();
        }
    }
    
}
void ChaosToolsFrm::drawJuliaOrbit(double atX, double atY)
{
    wxBufferedDC buffDC;
    int iter, width, height, maxiter;
    double x, y, xtemp;
    double ojulxmin = -2, ojulxmax = 2, ojulymin = -2, ojulymax = 2;
    height = 75;
    width = 100;
    wxBitmap *bmp = new wxBitmap(width,height);
    buffDC.SelectObject(*bmp);
    buffDC.SetPen(*wxWHITE_PEN);
    txtJuliaMaxIter->GetValue().ToLong((long*) &maxiter);
    iter = 0;
    x=y=0;
    buffDC.DrawLine(0, height/2, width, height/2);
    buffDC.DrawLine(width/2, 0, width/2, height);
    buffDC.SetPen(*wxRED_PEN);
    while (x*x+y*y < 4 && iter<maxiter)
    {
        xtemp = x*x - y*y + atX;
        y = x*y + x*y + atY;
        x = xtemp;
        buffDC.DrawPoint((int)((width / 2) + (x - (ojulxmax + ojulxmin) / 2) * (width / (ojulxmax - ojulxmin))), (int)((height / 2) - (y - (ojulymax + ojulymin) / 2) * (height / (ojulymax - ojulymin))));
        iter++;
    }
    buffDC.SelectObject(wxNullBitmap);
    juliaOrbitArea->SetBitmap(*bmp);
    delete bmp;
}
double ChaosToolsFrm::toJuliaMathX(int x)
{
    return (x - (plotJuliaArea->GetSize().GetWidth()) / 2) * ((julxmax - julxmin) / (plotJuliaArea->GetSize().GetWidth())) + ((julxmax + julxmin) / 2);
}
double ChaosToolsFrm::toJuliaMathY(int y)
{
    return ((plotJuliaArea->GetSize().GetHeight()) / 2 - y) * ((julymax - julymin) / (plotJuliaArea->GetSize().GetHeight())) + ((julymax + julymin) / 2);
}
void ChaosToolsFrm::OnIfsLeftDown(wxMouseEvent& event)
{
    wxBufferedDC buffDC;
    int height = plotBifArea->GetSize().GetHeight();
    int width = plotBifArea->GetSize().GetWidth();
    wxBitmap *bmp = new wxBitmap(width, height);
    *bmp = plotIfsArea->GetBitmap();
    buffDC.SelectObject(*bmp);
    buffDC.SetPen(wxPen(wxColour(0, 0, 0)));
    buffDC.DrawRectangle(event.GetX()-1, event.GetY()-1, 3, 3);
    xCoords.push_back(toIfsMathX(event.GetX()));
    yCoords.push_back(toIfsMathY(event.GetY()));
    buffDC.SelectObject(wxNullBitmap);
    plotIfsArea->SetBitmap(*bmp);
    delete bmp;
    
}
void ChaosToolsFrm::OnIfsLeftUp(wxMouseEvent& event)
{
}
void ChaosToolsFrm::OnIfsMouseMove(wxMouseEvent& event)
{
}
void ChaosToolsFrm::OnIfsIterClick(wxCommandEvent& event)
{
    if(xCoords.size()>0)
        drawIfs();
}
void ChaosToolsFrm::OnIfsResetClick(wxCommandEvent& event)
{
    while(!xCoords.empty())
    {
        xCoords.pop_back();
        yCoords.pop_back();
    }
    wxBufferedDC buffDC;
    int height = plotBifArea->GetSize().GetHeight();
    int width = plotBifArea->GetSize().GetWidth();
    wxBitmap *bmp = new wxBitmap(width, height);
    *bmp = plotIfsArea->GetBitmap();
    buffDC.SelectObject(*bmp);
    buffDC.Clear();
    buffDC.SetBackground(*wxWHITE_BRUSH);
    buffDC.SelectObject(wxNullBitmap);
    plotIfsArea->SetBitmap(*bmp);
    delete bmp;
}
void ChaosToolsFrm::drawIfs()
{
    int r, width, height, maxiter;
    const double pi = 3.14159;
    double x = 0, y = 0, cont, theta;
    width = plotIfsArea->GetSize().GetWidth();
    height = plotIfsArea->GetSize().GetHeight();
    wxBufferedDC buffDC;
    wxBitmap *bmp = new wxBitmap(width,height);
    buffDC.SelectObject(*bmp);
    buffDC.Clear();
    buffDC.SetBackground(*wxWHITE_BRUSH);
    buffDC.SetPen(wxPen(wxColour(0, 0, 0)));
    txtIfsMaxIter->GetValue().ToLong((long*) &maxiter);
    txtIfsTheta->GetValue().ToDouble((double*) &theta);
    theta *= (pi/180);
    ifsCfText->GetValue().ToDouble((double*) &cont);
    for(int i = 0; i<maxiter; i++)
    {
        r = rand()%xCoords.size();
        if(x<xCoords[r])
            x = x+cont*fabs(xCoords[r]-x);
        else
            x = x-cont*fabs(xCoords[r]-x);
        if(y<yCoords[r])
            y = y+cont*fabs(yCoords[r]-y);
        else
            y = y-cont*fabs(yCoords[r]-y);
        x = (x*cos(theta) - y*sin(theta));
        y = (x*sin(theta) + y*cos(theta));
        buffDC.DrawPoint(toIfsScreenX(x), toIfsScreenY(y));
    }
    buffDC.SelectObject(wxNullBitmap);
    plotIfsArea->SetBitmap(*bmp);
    delete bmp;
}
int ChaosToolsFrm::toIfsScreenX(double x)
{
    return (int)((plotIfsArea->GetSize().GetWidth() / 2) + (x - (ifsxmax + ifsxmin) / 2) * (plotIfsArea->GetSize().GetWidth() / (ifsxmax - ifsxmin)));
}
int ChaosToolsFrm::toIfsScreenY(double y)
{
    return (int)((plotIfsArea->GetSize().GetHeight() / 2) - (y - (ifsymax + ifsymin) / 2) * (plotIfsArea->GetSize().GetHeight() / (ifsymax - ifsymin)));
}
double ChaosToolsFrm::toIfsMathX(int x)
{
    return (x - (plotIfsArea->GetSize().GetWidth()) / 2) * ((ifsxmax - ifsxmin) / (plotIfsArea->GetSize().GetWidth())) + ((ifsxmax + ifsxmin) / 2);
}
double ChaosToolsFrm::toIfsMathY(int y)
{
    return ((plotIfsArea->GetSize().GetHeight()) / 2 - y) * ((ifsymax - ifsymin) / (plotIfsArea->GetSize().GetHeight())) + ((ifsymax + ifsymin) / 2);
}
wxColour ChaosToolsFrm::getColour(double iter)
{
    double R = 1, G = 0, B = 0;
    double H, S, V;
    H = iter;
    S = 1;
    V = 1;                                                                                                                                 
    int hi = (int)floor(H / 60.0)%6;                                                      
	double f  = H/60 - floor(H/60);                                         
    double pv  = V * ( 1 - S );                                 
    double qv  = V * ( 1 - S * f );                             
    double tv  = V * ( 1 - S * ( 1 - f ) );                     
	switch(hi)                                                       
	{
	case 0:                                                         
		R = V;                                                        
		G = tv;                                                       
		B = pv;                                                       
		break;  
	case 1:                                                         
		R = qv;                                                       
		G = V;                                                        
		B = pv;                                                       
		break;                                                        
	case 2:                                                         
		R = pv;                                                       
		G = V;                                                        
		B = tv;                                                       
		break;
	case 3:                                                         
		R = pv;                                                       
		G = qv;                                                       
		B = V;                                                        
		break;                                                        
	case 4:                                                         
		R = tv;                                                       
		G = pv;                                                       
		B = V;                                                        
		break;  
	case 5:                                                         
		R = V;                                                        
		G = pv;                                                       
		B = qv;                                                       
		break;                                                        
	default:                                                        
		break;                                                        
	}                                                                
    R *= 255.0F;                                                        
    G *= 255.0F;                                                        
    B *= 255.0F;
    return wxColour((int)R,(int)G,(int)B); 
}

MandelThread::MandelThread(wxEvtHandler* pParent, int row, double &xmint, double &xmaxt, double &ymint, double &ymaxt, int &widtht, int &heightt, int &max) : wxThread(wxTHREAD_DETACHED), m_pParent(pParent)
{
    width = widtht;
    height = heightt;
    xmin = xmint;
    xmax = xmaxt;
    ymin = ymint;
    ymax = ymaxt;
    dx = (xmax-xmin)/(width);
    dy = (ymax-ymin)/(height);
    maxiter = max;
    r = row;
}
void* MandelThread::Entry()
{
	wxCommandEvent evt(wxEVT_MTHREAD, GetId());
	evt.SetInt(r);
	evt.SetClientData(DrawMandelRow());
	wxPostEvent(m_pParent, evt);
    return 0;
}
unsigned char* MandelThread::DrawMandelRow()
{
    int i, iter=0;
    double x, y, x0, y0, xtemp;
    unsigned char* rgbdata = new unsigned char[width*3];
        y0 = ymax - r*dy;
        for (i=0; i<width; i++) //columns: x
        {
           y = y0;
           x = x0 = xmin + i*dx;
           iter = 0;
           while (x*x+y*y < 4 && iter<maxiter)
           {
                xtemp = x*x - y*y + x0;
                y = x*y + x*y + y0;
                x = xtemp;
                iter++;
           }
           
           if(iter==maxiter)
           {
               rgbdata[i*3] = (unsigned char)0;
        	   rgbdata[i*3+1] = (unsigned char)0;
        	   rgbdata[i*3+2] = (unsigned char)0;
           }
           else
           {
               unsigned char* temp = getColour(4*(iter - (log(log(x*x+y*y)))/log(2.0)));
               rgbdata[i*3] = temp[0];
        	   rgbdata[i*3+1] = temp[1];
        	   rgbdata[i*3+2] = temp[2];
        	   delete[] temp;
           }
        }
    return rgbdata;
}
unsigned char* MandelThread::getColour(double iter)
{
    double R = 1, G = 0, B = 0;
    double H, S, V;
    H = iter;
    S = 1;
    V = 1;
    int hi = (int)floor(H / 60.0)%6;
	double f  = H/60 - floor(H/60);
    double pv  = V * ( 1 - S );
    double qv  = V * ( 1 - S * f );
    double tv  = V * ( 1 - S * ( 1 - f ) );
	switch(hi)
	{
	case 0:
		R = V;
		G = tv;
		B = pv;
		break;
	case 1:
		R = qv;
		G = V;
		B = pv;
		break;
	case 2:
		R = pv;
		G = V;
		B = tv;
		break;
	case 3:
		R = pv;
		G = qv;
		B = V;
		break;
	case 4:
		R = tv;
		G = pv;
		B = V;
		break;
	case 5:
		R = V;
		G = pv;
		B = qv;
		break;
	default:
		break;
	}
    unsigned char* res = new unsigned char[3];
    res[0] = (unsigned char)(int)(R*255.0F);
    res[1] = (unsigned char)(int)(G*255.0F);
    res[2] = (unsigned char)(int)(B*255.0F);
    return res;
}

JuliaThread::JuliaThread(wxEvtHandler* pParent, int row,  double &cxt, double &cyt, double &xmint, double &xmaxt, double &ymint, double &ymaxt, int &widtht, int &heightt, int &max) : wxThread(wxTHREAD_DETACHED), m_pParent(pParent)
{
    width = widtht;
    height = heightt;
    xmin = xmint;
    xmax = xmaxt;
    ymin = ymint;
    ymax = ymaxt;
    dx = (xmax-xmin)/(width);
    dy = (ymax-ymin)/(height);
    maxiter = max;
	cx = cxt;
    cy = cyt;
    r = row;
}
void* JuliaThread::Entry()
{
	wxCommandEvent evt(wxEVT_JTHREAD, GetId());
	evt.SetInt(r);
	evt.SetClientData(DrawJuliaRow());
	wxPostEvent(m_pParent, evt);
    return 0;
}
unsigned char* JuliaThread::DrawJuliaRow()
{
    int i, iter=0;
    double x, y, xtemp;
    unsigned char* rgbdata = new unsigned char[width*3];
        for (i=0; i<width; i++) //columns: x
        {
           y = ymax - r*dy;
           x = xmin + i*dx;
           iter = 0;
           while (x*x+y*y < 4 && iter<maxiter)
           {
                xtemp = x*x - y*y + cx;
                y = x*y + x*y + cy;
                x = xtemp;
                iter++;
           }

           if(iter==maxiter)
           {
               rgbdata[i*3] = (unsigned char)0;
        	   rgbdata[i*3+1] = (unsigned char)0;
        	   rgbdata[i*3+2] = (unsigned char)0;
           }
           else
           {
               unsigned char* temp = getColour((4*(iter - (log(log(x*x+y*y)))/log(2.0))));
               rgbdata[i*3] = temp[0];
        	   rgbdata[i*3+1] = temp[1];
        	   rgbdata[i*3+2] = temp[2];
        	   delete[] temp;
           }
        }
    return rgbdata;
}
unsigned char* JuliaThread::getColour(double iter)
{
    double R = 1, G = 0, B = 0;
    double H, S, V;
    H = iter;
    S = 1;
    V = 1;
    int hi = (int)floor(H / 60.0)%6;
	double f  = H/60 - floor(H/60);
    double pv  = V * ( 1 - S );
    double qv  = V * ( 1 - S * f );
    double tv  = V * ( 1 - S * ( 1 - f ) );
	switch(hi)
	{
	case 0:
		R = V;
		G = tv;
		B = pv;
		break;
	case 1:
		R = qv;
		G = V;
		B = pv;
		break;
	case 2:
		R = pv;
		G = V;
		B = tv;
		break;
	case 3:
		R = pv;
		G = qv;
		B = V;
		break;
	case 4:
		R = tv;
		G = pv;
		B = V;
		break;
	case 5:
		R = V;
		G = pv;
		B = qv;
		break;
	default:
		break;
	}
    unsigned char* res = new unsigned char[3];
    res[0] = (unsigned char)(int)(R*255.0F);
    res[1] = (unsigned char)(int)(G*255.0F);
    res[2] = (unsigned char)(int)(B*255.0F);
    return res;
}


void ChaosToolsFrm::iterBookPageChanged(wxNotebookEvent& event)
{
}
void ChaosToolsFrm::OnIterCalcClick(wxCommandEvent &event)
{
    switch(iterBook->GetSelection()){
        case 0:
            makeIterTable();
            break;
        case 1:
            drawHistogram();
            break;
        case 2:
            drawChart();
            break;
        case 3:
            drawGraph();
            break;
    }
}
void ChaosToolsFrm::functionIterChoiceSelected(wxCommandEvent& event)
{
    switch(event.GetSelection())
    {
        case 0:
            functionIterBitmap->SetBitmap(wxBitmap(logistic_xpm));
            break;
        case 1:
            functionIterBitmap->SetBitmap(wxBitmap(sin_xpm));
            break;
        case 2:
            functionIterBitmap->SetBitmap(wxBitmap(cos_xpm));
            break;
        case 3:
            functionIterBitmap->SetBitmap(wxBitmap(tent_xpm));
            break;
        case 4:
            functionIterBitmap->SetBitmap(wxBitmap(quadratic_xpm));
            break;
    }
}
void ChaosToolsFrm::makeIterTable()
{
    double x, r, seed;
    int iter;
    iterIterText->GetValue().ToLong((long*) &iter);
    rIterText->GetValue().ToDouble((double*) &r);
    iterSeedText->GetValue().ToDouble((double*) &seed);
    iterGrid->DeleteRows(0, iterGrid->GetRows());
    iterGrid->AppendRows(iter);
    switch(functionIterChoice->GetSelection()){
        case 0:
            for(int i = 0; i<=10; i++)
            {
                x = seed + .01*i;
                iterGrid->SetLabelValue(wxHORIZONTAL, wxString::Format(wxT("%.3f"), x), i);
                for(int j = 0; j<iter; j++)
                {
                    x = r*x -r*x*x;
                    iterGrid->SetCellValue(j, i, wxString::Format(wxT("%.3f"), x));
                }
            }
            break;
        case 1:
            for(int i = 0; i<=10; i++)
            {
                x = seed + .01*i;
                iterGrid->SetLabelValue(wxHORIZONTAL, wxString::Format(wxT("%.3f"), x), i);
                for(int j = 0; j<iter; j++)
                {
                    x = r * sin(x);
                    iterGrid->SetCellValue(j, i, wxString::Format(wxT("%.3f"), x));
                }
            }
            break;
        case 2:
            for(int i = 0; i<=10; i++)
            {
                x = seed + .01*i;
                iterGrid->SetLabelValue(wxHORIZONTAL, wxString::Format(wxT("%.3f"), x), i);
                for(int j = 0; j<iter; j++)
                {
                    x = r * cos(x);
                    iterGrid->SetCellValue(j, i, wxString::Format(wxT("%.3f"), x));
                }
            }
            break;
        case 3:
            for(int i = 0; i<=10; i++)
            {
                x = seed + .01*i;
                iterGrid->SetLabelValue(wxHORIZONTAL, wxString::Format(wxT("%.3f"), x), i);
                for(int j = 0; j<iter; j++)
                {
                    if(0<=x && x<=.5)
                        x = r*x;
                    else
                        x = r-r*x;
                    iterGrid->SetCellValue(j, i, wxString::Format(wxT("%.3f"), x));
                }
            }
            break;
        case 4:
            for(int i = 0; i<=10; i++)
            {
                x = seed + .01*i;
                iterGrid->SetLabelValue(wxHORIZONTAL, wxString::Format(wxT("%.3f"), x), i);
                for(int j = 0; j<iter; j++)
                {
                    x = x*x+r;
                    iterGrid->SetCellValue(j, i, wxString::Format(wxT("%.3f"), x));
                }
            }
            break;
    }
}
void ChaosToolsFrm::drawHistogram()
{
    double x, r, xmin, xmax;
    int iter, width, height, xcoord = 0, ycoord = 0;
    wxColour *black = new wxColour();
    iterIterText->GetValue().ToLong((long*) &iter);
    rIterText->GetValue().ToDouble((double*) &r);
    iterSeedText->GetValue().ToDouble((double*) &x);
    xminIterText->GetValue().ToDouble((double*) &xmin);
    xmaxIterText->GetValue().ToDouble((double*) &xmax);
    wxBufferedDC buffDC;
    width = plotHistArea->GetSize().GetWidth();
    height = plotHistArea->GetSize().GetHeight();
    wxBitmap *bmp = new wxBitmap(width, height);
    buffDC.SelectObject(*bmp);
    buffDC.Clear();
    buffDC.SetBackground(*wxWHITE_BRUSH);
    buffDC.SetPen(wxPen(wxColour(0, 0, 0)));
    switch(functionIterChoice->GetSelection()){
        case 0:
            for(int i = 0; i<=iter; i++)
            {
                x = r*x - r*x*x;
                xcoord = (int)((width / 2) + (x - (xmax + xmin) / 2) * (width / (xmax - xmin)));
                for(ycoord = height-1; ycoord>=0; --ycoord)
                {
                    buffDC.GetPixel(xcoord, ycoord, black);
                    if(*black==*wxWHITE)
                    {
                        buffDC.DrawPoint(xcoord, ycoord);
                        break;
                    }
                }                
            }
            break;
        case 1:
            for(int i = 0; i<=iter; i++)
            {
                x = r*sin(x);
                xcoord = (int)((width / 2) + (x - (xmax + xmin) / 2) * (width / (xmax - xmin)));
                for(ycoord = height-1; ycoord>=0; --ycoord)
                {
                    buffDC.GetPixel(xcoord, ycoord, black);
                    if(*black==*wxWHITE)
                    {
                        buffDC.DrawPoint(xcoord, ycoord);
                        break;
                    }
                }
            }
            break;
        case 2:
            for(int i = 0; i<=iter; i++)
            {
                x = r*cos(x);
                xcoord = (int)((width / 2) + (x - (xmax + xmin) / 2) * (width / (xmax - xmin)));
                for(ycoord = height-1; ycoord>=0; --ycoord)
                {
                    buffDC.GetPixel(xcoord, ycoord, black);
                    if(*black==*wxWHITE)
                    {
                        buffDC.DrawPoint(xcoord, ycoord);
                        break;
                    }
                }
            }
            break;
        case 3:
            for(int i = 0; i<=iter; i++)
            {
                if(0<=x && x<=.5)
                    x = r*x;
                else
                    x = r-r*x;
                xcoord = (int)((width / 2) + (x - (xmax + xmin) / 2) * (width / (xmax - xmin)));
                for(ycoord = height-1; ycoord>=0; --ycoord)
                {
                    buffDC.GetPixel(xcoord, ycoord, black);
                    if(*black==*wxWHITE)
                    {
                        buffDC.DrawPoint(xcoord, ycoord);
                        break;
                    }
                }
            }
            break;  
        case 4:
            for(int i = 0; i<=iter; i++)
            {
                x = x*x+r;
                xcoord = (int)((width / 2) + (x - (xmax + xmin) / 2) * (width / (xmax - xmin)));
                for(ycoord = height-1; ycoord>=0; --ycoord)
                {
                    buffDC.GetPixel(xcoord, ycoord, black);
                    if(*black==*wxWHITE)
                    {
                        buffDC.DrawPoint(xcoord, ycoord);
                        break;
                    }
                }
            }
            break;
            
    }
    buffDC.SelectObject(wxNullBitmap);
    plotHistArea->SetBitmap(*bmp);
    delete black;
    delete bmp;
}
void ChaosToolsFrm::drawChart()
{
    double x, x2, r, xmin, xmax;
    int iter, width, height;
    iterIterText->GetValue().ToLong((long*) &iter);
    rIterText->GetValue().ToDouble((double*) &r);
    iterSeedText->GetValue().ToDouble((double*) &x);
    xminIterText->GetValue().ToDouble((double*) &xmin);
    xmaxIterText->GetValue().ToDouble((double*) &xmax);
    wxBufferedDC buffDC;
    width = plotChartArea->GetSize().GetWidth();
    height = plotChartArea->GetSize().GetHeight();
    wxBitmap *bmp = new wxBitmap(width, height);
    buffDC.SelectObject(*bmp);
    buffDC.Clear();
    buffDC.SetBackground(*wxWHITE_BRUSH);
    buffDC.SetPen(*wxBLACK_PEN);
    switch(functionIterChoice->GetSelection()){
        case 0:
            for(int i = 0; i<=iter; i++)
            {
                buffDC.SetPen(*wxBLACK_PEN);
                x = r*x - r*x*x;
                buffDC.SelectObject(*bmp);
                int ycoord = (int)((height / 2) - (x - (xmax + xmin) / 2) * (height / (xmax - xmin)));
                buffDC.DrawRectangle(width - 4 - width/8, ycoord, 2, 2);              
                x2 = r*x - r*x*x;
                int ycoord2 = (int)((height / 2) - (x2 - (xmax + xmin) / 2) * (height / (xmax - xmin)));
                buffDC.DrawRectangle(width - 4, ycoord2, 2, 2);
                buffDC.DrawLine(width-4-(width/8), ycoord, width-4, ycoord2);
                buffDC.Blit(0,0,width-width/8, height, &buffDC, width/8,0);
                buffDC.SetPen(*wxWHITE_PEN);
                buffDC.DrawRectangle(width-width/8, 0, width/8, height);
                buffDC.DrawLine(width-4-(width/8), ycoord, width-4, ycoord2);
                buffDC.SelectObject(wxNullBitmap);
                plotChartArea->SetBitmap(*bmp);
                wxMilliSleep(250);
            }
            break;
        case 1:
            for(int i = 0; i<=iter; i++)
            {
                buffDC.SetPen(*wxBLACK_PEN);
                x = r*sin(x);
                buffDC.SelectObject(*bmp);
                int ycoord = (int)((height / 2) - (x - (xmax + xmin) / 2) * (height / (xmax - xmin)));
                buffDC.DrawRectangle(width - 4 - width/8, ycoord, 2, 2);
                x2 = r*sin(x);
                int ycoord2 = (int)((height / 2) - (x2 - (xmax + xmin) / 2) * (height / (xmax - xmin)));
                buffDC.DrawRectangle(width - 4, ycoord2, 2, 2);
                buffDC.DrawLine(width-4-(width/8), ycoord, width-4, ycoord2);
                buffDC.Blit(0,0,width-width/8, height, &buffDC, width/8,0);
                buffDC.SetPen(*wxWHITE_PEN);
                buffDC.DrawRectangle(width-width/8, 0, width/8, height);
                buffDC.DrawLine(width-4-(width/8), ycoord, width-4, ycoord2);
                buffDC.SelectObject(wxNullBitmap);
                plotChartArea->SetBitmap(*bmp);
                wxMilliSleep(250);
            }
            break;
        case 2:
            for(int i = 0; i<=iter; i++)
            {
                buffDC.SetPen(*wxBLACK_PEN);
                x = r*cos(x);
                buffDC.SelectObject(*bmp);
                int ycoord = (int)((height / 2) - (x - (xmax + xmin) / 2) * (height / (xmax - xmin)));
                buffDC.DrawRectangle(width - 4 - width/8, ycoord, 2, 2);
                x2 = r*cos(x);
                int ycoord2 = (int)((height / 2) - (x2 - (xmax + xmin) / 2) * (height / (xmax - xmin)));
                buffDC.DrawRectangle(width - 4, ycoord2, 2, 2);
                buffDC.DrawLine(width-4-(width/8), ycoord, width-4, ycoord2);
                buffDC.Blit(0,0,width-width/8, height, &buffDC, width/8,0);
                buffDC.SetPen(*wxWHITE_PEN);
                buffDC.DrawRectangle(width-width/8, 0, width/8, height);
                buffDC.DrawLine(width-4-(width/8), ycoord, width-4, ycoord2);
                buffDC.SelectObject(wxNullBitmap);
                plotChartArea->SetBitmap(*bmp);
                wxMilliSleep(250);
            }
            break;
        case 3:
            for(int i = 0; i<=iter; i++)
            {
                buffDC.SetPen(*wxBLACK_PEN);
                if(0<=x && x<=.5)
                    x = r*x;
                else
                    x = r-r*x;
                buffDC.SelectObject(*bmp);
                int ycoord = (int)((height / 2) - (x - (xmax + xmin) / 2) * (height / (xmax - xmin)));
                buffDC.DrawRectangle(width - 4 - width/8, ycoord, 2, 2);
                if(0<=x && x<=.5)
                    x2 = r*x;
                else
                    x2 = r-r*x;
                int ycoord2 = (int)((height / 2) - (x2 - (xmax + xmin) / 2) * (height / (xmax - xmin)));
                buffDC.DrawRectangle(width - 4, ycoord2, 2, 2);
                buffDC.DrawLine(width-4-(width/8), ycoord, width-4, ycoord2);
                buffDC.Blit(0,0,width-width/8, height, &buffDC, width/8,0);
                buffDC.SetPen(*wxWHITE_PEN);
                buffDC.DrawRectangle(width-width/8, 0, width/8, height);
                buffDC.DrawLine(width-4-(width/8), ycoord, width-4, ycoord2);
                buffDC.SelectObject(wxNullBitmap);
                plotChartArea->SetBitmap(*bmp);
                wxMilliSleep(250);
            }
            break;
        case 4:
            for(int i = 0; i<=iter; i++)
            {
                buffDC.SetPen(*wxBLACK_PEN);
                x = x*x+r;
                buffDC.SelectObject(*bmp);
                int ycoord = (int)((height / 2) - (x - (xmax + xmin) / 2) * (height / (xmax - xmin)));
                buffDC.DrawRectangle(width - 4 - width/8, ycoord, 2, 2);
                x2 = x*x+r;
                int ycoord2 = (int)((height / 2) - (x2 - (xmax + xmin) / 2) * (height / (xmax - xmin)));
                buffDC.DrawRectangle(width - 4, ycoord2, 2, 2);
                buffDC.DrawLine(width-4-(width/8), ycoord, width-4, ycoord2);
                buffDC.Blit(0,0,width-width/8, height, &buffDC, width/8,0);
                buffDC.SetPen(*wxWHITE_PEN);
                buffDC.DrawRectangle(width-width/8, 0, width/8, height);
                buffDC.DrawLine(width-4-(width/8), ycoord, width-4, ycoord2);
                buffDC.SelectObject(wxNullBitmap);
                plotChartArea->SetBitmap(*bmp);
                wxMilliSleep(250);
            }
            break;
    }
}
void ChaosToolsFrm::drawGraph()
{
    double r, seed, x, x2;
    int iter, width, height;
    iterIterText->GetValue().ToLong((long*) &iter);
    rIterText->GetValue().ToDouble((double*) &r);
    iterSeedText->GetValue().ToDouble((double*) &seed);
    xminIterText->GetValue().ToDouble((double*) &iterxmin);
    xmaxIterText->GetValue().ToDouble((double*) &iterxmax);
    yminIterText->GetValue().ToDouble((double*) &iterymin);
    ymaxIterText->GetValue().ToDouble((double*) &iterymax);
    wxBufferedDC buffDC;
    width = plotIterArea->GetSize().GetWidth();
    height = plotIterArea->GetSize().GetHeight();
    wxBitmap *bmp = new wxBitmap(width, height);
    buffDC.SelectObject(*bmp);
    buffDC.Clear();
    buffDC.SetBackground(*wxWHITE_BRUSH);
    buffDC.SetPen(*wxBLACK_PEN);
    buffDC.DrawLine(0, height/2, width, height/2);
    buffDC.DrawLine(width/2, 0, width/2, height);
    buffDC.SetPen(*wxBLACK_DASHED_PEN);
    buffDC.DrawLine(0, height, width, 0);
    switch(functionIterChoice->GetSelection()){
        case 0:
            for(int i = 0; i<=width; i++)
            {
                x = toIterMathX(i);
                x2 = toIterMathX(i+1);
                buffDC.SetPen(*wxGREY_PEN);
                buffDC.DrawLine(i, toIterScreenY(r*x+r*x*x), i+1, toIterScreenY(r*x2+r*x2*x2));
            }
            buffDC.SelectObject(wxNullBitmap);
            plotIterArea->SetBitmap(*bmp);
            buffDC.SelectObject(*bmp);
            buffDC.SetPen(*wxRED_PEN);
            x = seed;
            buffDC.DrawLine(toIterScreenX(x), toIterScreenY(0), toIterScreenX(x), toIterScreenY(r*x+r*x*x));
            for(int i = 0; i<=iter; i++)
            {
                buffDC.SelectObject(*bmp);
                x2 = r*x+r*x*x;
                buffDC.DrawLine(toIterScreenX(x), toIterScreenY(x2), toIterScreenX(x2), toIterScreenY(x2));
                wxMilliSleep(250);
                x = x2;
                buffDC.DrawLine(toIterScreenX(x), toIterScreenY(x), toIterScreenX(x), toIterScreenY(r*x+r*x*x));
                wxMilliSleep(250);
                buffDC.SelectObject(wxNullBitmap);
                plotIterArea->SetBitmap(*bmp);
                if(x>iterxmax || x<iterxmin)
                    break;
            }
            break;
        case 1:
            for(int i = 0; i<=width; i++)
            {
                x = toIterMathX(i);
                x2 = toIterMathX(i+1);
                buffDC.SetPen(*wxGREY_PEN);
                buffDC.DrawLine(i, toIterScreenY(r*sin(x)), i+1, toIterScreenY(r*sin(x2)));
            }
            buffDC.SelectObject(wxNullBitmap);
            plotIterArea->SetBitmap(*bmp);
            buffDC.SelectObject(*bmp);
            buffDC.SetPen(*wxRED_PEN);
            x = seed;
            buffDC.DrawLine(toIterScreenX(x), toIterScreenY(0), toIterScreenX(x), toIterScreenY(r*sin(x)));
            for(int i = 0; i<=iter; i++)
            {
                buffDC.SelectObject(*bmp);
                x2 = r*sin(x);
                buffDC.DrawLine(toIterScreenX(x), toIterScreenY(x2), toIterScreenX(x2), toIterScreenY(x2));
                wxMilliSleep(250);
                x = x2;
                buffDC.DrawLine(toIterScreenX(x), toIterScreenY(x), toIterScreenX(x), toIterScreenY(r*sin(x)));
                wxMilliSleep(250);
                buffDC.SelectObject(wxNullBitmap);
                plotIterArea->SetBitmap(*bmp);
                if(x>iterxmax || x<iterxmin)
                    break;
            }
            break;
        case 2:
            for(int i = 0; i<=width; i++)
            {
                x = toIterMathX(i);
                x2 = toIterMathX(i+1);
                buffDC.SetPen(*wxGREY_PEN);
                buffDC.DrawLine(i, toIterScreenY(r*cos(x)), i+1, toIterScreenY(r*cos(x2)));
            }
            buffDC.SelectObject(wxNullBitmap);
            plotIterArea->SetBitmap(*bmp);
            buffDC.SelectObject(*bmp);
            buffDC.SetPen(*wxRED_PEN);
            x = seed;
            buffDC.DrawLine(toIterScreenX(x), toIterScreenY(0), toIterScreenX(x), toIterScreenY(r*cos(x)));
            for(int i = 0; i<=iter; i++)
            {
                buffDC.SelectObject(*bmp);
                x2 = r*x+r*x*x;
                buffDC.DrawLine(toIterScreenX(x), toIterScreenY(x2), toIterScreenX(x2), toIterScreenY(x2));
                wxMilliSleep(250);
                x = x2;
                buffDC.DrawLine(toIterScreenX(x), toIterScreenY(x), toIterScreenX(x), toIterScreenY(r*cos(x)));
                wxMilliSleep(250);
                buffDC.SelectObject(wxNullBitmap);
                plotIterArea->SetBitmap(*bmp);
                if(x>iterxmax || x<iterxmin)
                    break;
            }
            break;
        case 3:
            for(int i = 0; i<=width; i++)
            {
                x = toIterMathX(i);
                x2 = toIterMathX(i+1);
                buffDC.SetPen(*wxGREY_PEN);
                buffDC.DrawLine(i, toIterScreenY(r*(1-2*fabs(x-.5))), i+1, toIterScreenY(r*(1-2*fabs(x2-.5))));
            }
            buffDC.SelectObject(wxNullBitmap);
            plotIterArea->SetBitmap(*bmp);
            buffDC.SelectObject(*bmp);
            buffDC.SetPen(*wxRED_PEN);
            x = seed;
            buffDC.DrawLine(toIterScreenX(x), toIterScreenY(0), toIterScreenX(x), toIterScreenY(r*(1-2*fabs(x-.5))));
            for(int i = 0; i<=iter; i++)
            {
                buffDC.SelectObject(*bmp);
                x2 = r*(1-2*fabs(x-.5));
                buffDC.DrawLine(toIterScreenX(x), toIterScreenY(x2), toIterScreenX(x2), toIterScreenY(x2));
                wxMilliSleep(250);
                buffDC.DrawLine(toIterScreenX(x2), toIterScreenY(x2), toIterScreenX(x2), toIterScreenY(r*(1-2*fabs(x2-.5))));
                wxMilliSleep(250);
                buffDC.SelectObject(wxNullBitmap);
                plotIterArea->SetBitmap(*bmp);
                if(x>iterxmax || x<iterxmin)
                    break;
            }
            break;
        case 4:
            for(int i = 0; i<=width; i++)
            {
                x = toIterMathX(i);
                x2 = toIterMathX(i+1);
                buffDC.SetPen(*wxGREY_PEN);
                buffDC.DrawLine(i, toIterScreenY(x*x+r), i+1, toIterScreenY(x2*x2+r));
            }
            buffDC.SelectObject(wxNullBitmap);
            plotIterArea->SetBitmap(*bmp);
            buffDC.SelectObject(*bmp);
            buffDC.SetPen(*wxRED_PEN);
            x = seed;
            buffDC.DrawLine(toIterScreenX(x), toIterScreenY(0), toIterScreenX(x), toIterScreenY(x*x+r));
            for(int i = 0; i<=iter; i++)
            {
                buffDC.SelectObject(*bmp);
                x2 = x*x+r;
                buffDC.DrawLine(toIterScreenX(x), toIterScreenY(x2), toIterScreenX(x2), toIterScreenY(x2));
                wxMilliSleep(250);
                x = x2;
                buffDC.DrawLine(toIterScreenX(x), toIterScreenY(x), toIterScreenX(x), toIterScreenY(x*x+r));
                wxMilliSleep(250);
                buffDC.SelectObject(wxNullBitmap);
                plotIterArea->SetBitmap(*bmp);
                if(x>iterxmax || x<iterxmin)
                    break;
            }
            break;
    }
}
int ChaosToolsFrm::toIterScreenX(double x)
{
    return (int)((plotIterArea->GetSize().GetWidth() / 2) + (x - (iterxmax + iterxmin) / 2) * (plotIterArea->GetSize().GetWidth() / (iterxmax - iterxmin)));
}
int ChaosToolsFrm::toIterScreenY(double y)
{
    return (int)((plotIterArea->GetSize().GetHeight() / 2) - (y - (iterymax + iterymin) / 2) * (plotIterArea->GetSize().GetHeight() / (iterymax - iterymin)));
}
double ChaosToolsFrm::toIterMathX(int x)
{
    return (x - (plotIterArea->GetSize().GetWidth()) / 2) * ((iterxmax - iterxmin) / (plotIterArea->GetSize().GetWidth())) + ((iterxmax + iterxmin) / 2);
}
double ChaosToolsFrm::toIterMathY(int y)
{
    return ((plotIterArea->GetSize().GetHeight()) / 2 - y) * ((iterymax - iterymin) / (plotIterArea->GetSize().GetHeight())) + ((iterymax + iterymin) / 2);
}

