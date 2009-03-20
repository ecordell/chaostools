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
#include <cstdlib>
#include <vector>

BEGIN_DECLARE_EVENT_TYPES()
 DECLARE_EVENT_TYPE(wxEVT_MTHREAD, -1)
 DECLARE_EVENT_TYPE(wxEVT_JTHREAD, -1)
END_DECLARE_EVENT_TYPES()

#undef ChaosToolsFrm_STYLE
#define ChaosToolsFrm_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxTHICK_FRAME | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX

class ChaosToolsFrm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		ChaosToolsFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("ChaosTools"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = ChaosToolsFrm_STYLE);
		virtual ~ChaosToolsFrm();
        void functionBifChoiceSelected(wxCommandEvent& event );
		void mainBookPageChanged(wxNotebookEvent& event);
		void iterBookPageChanged(wxNotebookEvent& event);

		
	private:
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
			ID_YMAXITERTEXT = 1126,
			ID_YMAXITERLABEL = 1125,
			ID_YMINITERTEXT = 1124,
			ID_YMINITERLABEL = 1123,
			ID_XMAXITERTEXT = 1122,
			ID_XMAXITERLABEL = 1121,
			ID_XMINITERTEXT = 1120,
			ID_XMINITERLABEL = 1119,
			ID_STATUSBAR = 1035,
			ID_RESETIFSBUTTON = 1091,
			ID_TXTIFSTHETA = 1089,
			ID_ROTTEXT = 1088,
			ID_IFSCFTEXT = 1086,
			ID_IFSCFLABEL = 1085,
			ID_TXTIFSMAXITER = 1080,
			ID_IFSITERLABEL = 1082,
			ID_IFSITERBUTTON = 1079,
			ID_PLOTIFSAREA = 1087,
			ID_IFSPAGE = 1075,
			ID_MANDELORBITAREA = 1056,
			ID_MANDELJULIAAREA = 1053,
			ID_RESETMANDELBUTTON = 1051,
			ID_TXTMANDELMAXITER = 1050,
			ID_MANDELITERLABEL = 1054,
			ID_PLOTMANDELBUTTON = 1049,
			ID_PLOTMANDELAREA = 1045,
			ID_MANDELPAGE = 1006,
			ID_JULIAORBITAREA = 1074,
			ID_JULIARESETBUTTON = 1071,
			ID_JULIAIMAGTEXT = 1068,
			ID_JULIAIMAGLABEL = 1067,
			ID_JULIAREALTEXT = 1066,
			ID_JULIAREALLABEL = 1065,
			ID_JULIAPARAMLABEL = 1070,
			ID_TXTJULIAMAXITER = 1069,
			ID_JULIAITERLABEL = 1063,
			ID_PLOTJULIABUTTON = 1062,
			ID_PLOTJULIAAREA = 1058,
			ID_JULIAPAGE = 1005,
			ID_CALCBIFBUTTON = 1033,
			ID_XMAXBIFTEXT = 1030,
			ID_XMAXBIFLABEL = 1029,
			ID_XMINBIFTEXT = 1028,
			ID_XMINBIFLABEL = 1027,
			ID_RMINBIFTEXT = 1023,
			ID_RMINBIFLABEL = 1022,
			ID_FUNCTIONBIFCHOICE = 1014,
			ID_PLOTBIFAREA = 1010,
			ID_BIFPAGE = 1004,
			ID_RESETBIFBUTTON = 1034,
			ID_CALCITERBUTTON = 1104,
			ID_ITERSEEDTEXT = 1101,
			ID_ITERSEEDLABEL = 1100,
			ID_RMAXBIFTEXT = 1026,
			ID_RMAXBIFLABEL = 1024,
			ID_ITERBIFTEXT = 1021,
			ID_ITERBIFLABEL = 1020,
			ID_FUNCTIONBIFBITMAP = 1015,
			ID_FUNCTIONITERCHOICE = 1103,
			ID_BIFFUNCTIONLABEL = 1013,
			ID_PLOTITERAREA = 1106,
			ID_WXNOTEBOOKPAGE4 = 1097,
			ID_PLOTCHARTAREA = 1105,
			ID_WXNOTEBOOKPAGE3 = 1096,
			ID_PLOTHISTAREA = 1102,
			ID_WXNOTEBOOKPAGE2 = 1095,
			ID_ITERGRID = 1099,
			ID_WXNOTEBOOKPAGE1 = 1094,
			ID_ITERBOOK = 1093,
			ID_ITERPAGE = 1002,
			ID_MAINBOOK = 1008,
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
		//For Iterations
		double iterxmin, iterxmax, iterymin, iterymax;
		void functionIterChoiceSelected(wxCommandEvent& event);
		void OnIterCalcClick(wxCommandEvent& event);
		void makeIterTable();
		void drawHistogram();
		void drawChart();
		void drawGraph();
		int toIterScreenX(double x);
        int toIterScreenY(double y);
        double toIterMathX(int x);
        double toIterMathY(int y);
		//For Bifurcations
		double bifxmin, bifxmax, bifrmin, bifrmax, bifseed;
        int bifxstart, bifystart, bifxend, bifyend, bifiter;
        void OnBifLeftDown(wxMouseEvent& event);
        void OnBifLeftUp(wxMouseEvent& event);
        void OnBifMouseMove(wxMouseEvent& event);
        void OnBifCalcClick(wxCommandEvent& event);
        void OnBifResetClick(wxCommandEvent& event);
        void drawBif();
        double toBifMathR(int r);
        double toBifMathX(int x);
        int toBifScreenR(double r);
        int toBifScreenX(double x);
        //For Mandelbrot Set
        double manxmax, manxmin, manymax, manymin;
        int manxstart, manystart, manxend, manyend;
		void drawMandel();
		void drawMandelJulia(double atX, double atY);
		void drawMandelOrbit(double atX, double atY);
		void OnMandelThread(wxCommandEvent& event);
		void OnMandelFinished();
		void OnMandelLeftDown(wxMouseEvent& event);
		void OnMandelLeftUp(wxMouseEvent& event);
		void OnMandelRightDown(wxMouseEvent& event);
		void OnMandelMouseMove(wxMouseEvent& event);
		void OnMandelPlotClick(wxCommandEvent& event);
		void OnMandelResetClick(wxCommandEvent& event);
		double toMandelMathY(int y);
		double toMandelMathX(int x);
		//For Julia Set
		double julxmax, julxmin, julymax, julymin;
        int julxstart, julystart, julxend, julyend;
        void drawJulia();
        void drawJuliaOrbit(double atX, double atY);
        void OnJuliaThread(wxCommandEvent& event);
        void OnJuliaFinished();
        void OnJuliaLeftDown(wxMouseEvent& event);
        void OnJuliaLeftUp(wxMouseEvent& event);
        void OnJuliaMouseMove(wxMouseEvent& event);
        void OnJuliaPlotClick(wxCommandEvent& event);
        void OnJuliaResetClick(wxCommandEvent& event);
        double toJuliaMathY(int y);
        double toJuliaMathX(int x);
        //For Iterated Function System
        double ifsxmax, ifsxmin, ifsymax, ifsymin;
        void drawIfs();
        void OnIfsLeftDown(wxMouseEvent& event);
        void OnIfsLeftUp(wxMouseEvent& event);
        void OnIfsMouseMove(wxMouseEvent& event);
        void OnIfsIterClick(wxCommandEvent& event);
        void OnIfsResetClick(wxCommandEvent& event);
        int toIfsScreenX(double x);
        int toIfsScreenY(double y);
        double toIfsMathX(int x);
        double toIfsMathY(int y);
		wxColour getColour(double iter);
};

class MandelThread : public wxThread
{
public:
    MandelThread(wxEvtHandler* pParent, int row, double &xmint, double &xmaxt, double &ymint, double &ymaxt, int &widtht, int &heightt, int &max);
private:
	void* Entry();
	unsigned char* DrawMandelRow();
	double xmin, xmax, ymin, ymax, dx, dy;
	int width, height, maxiter, r;
	unsigned char* getColour(double iter);
protected:
	wxEvtHandler* m_pParent;
};
class JuliaThread: public wxThread
{
public:
    JuliaThread(wxEvtHandler* pParent, int row, double &cxt, double &cyt, double &xmint, double &xmaxt, double &ymint, double &ymaxt, int &widtht, int &heightt, int &max);
private:
	double xmin, xmax, ymin, ymax, dx, dy, cx, cy;
	int width, height, maxiter, r;
	void* Entry();
	unsigned char* DrawJuliaRow();
	unsigned char* getColour(double iter);
protected:
	wxEvtHandler* m_pParent;
};
#endif
