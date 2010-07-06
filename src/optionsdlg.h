#ifndef OPTIONSDLG_H
#define OPTIONSDLG_H

#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/treectrl.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/fileconf.h>

#include "gradientdlg.h"

class wxOptionsDialog : public wxDialog
{
public:
	wxOptionsDialog();
	wxOptionsDialog(wxWindow *parent);
	virtual ~wxOptionsDialog();
	bool Create(wxWindow *parent);
	virtual int ShowModal();
private:
	void CreateWidgets();
	void OnCloseWindow(wxCloseEvent& event);
	void OnOptionsTreeClick(wxTreeEvent& event);

	wxBoxSizer* mainSizer;
	wxBoxSizer* treeSizer;
	wxBoxSizer* panelSizer;
	wxTreeCtrl* optionsTreeCtrl;
	wxTreeItemId rootId;
	wxTreeItemId iterationsId;
	wxTreeItemId bifurcationsId;
	wxTreeItemId juliaId;
	wxTreeItemId mandelbrotId;
	wxTreeItemId ifsId;

	wxPanel* mandelbrotPanel;
	wxStaticBoxSizer* mandelbrotSizer;
	wxCheckBox* mandelbrotUseGradientCheckBox;
	wxButton* mandelbrotGradientChangeButton;
	void OnMandelbrotGradientChange(wxCommandEvent& event);

	wxPanel* chaosToolsPanel;
	wxStaticBoxSizer* chaosToolsSizer;

	wxFileConfig* optConfig;
	DECLARE_EVENT_TABLE()
    DECLARE_DYNAMIC_CLASS(wxOptionsDialog)

	enum{
		ID_OPTIONSTREECTRL = wxID_HIGHEST + 1,
		ID_MUSEGRADIENT,
		ID_MGRADIENTCHANGE,
	};
};

#endif