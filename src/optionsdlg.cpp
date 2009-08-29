#include "optionsdlg.h"

IMPLEMENT_DYNAMIC_CLASS(wxOptionsDialog, wxDialog)

BEGIN_EVENT_TABLE(wxOptionsDialog, wxDialog)
	EVT_BUTTON(ID_MGRADIENTCHANGE, wxOptionsDialog::OnMandelbrotGradientChange)
	EVT_CLOSE(wxOptionsDialog::OnCloseWindow)
END_EVENT_TABLE()

wxOptionsDialog::wxOptionsDialog()
{
}
wxOptionsDialog::wxOptionsDialog(wxWindow *parent)
{
	Create(parent);
}
wxOptionsDialog::~wxOptionsDialog()
{
}
bool wxOptionsDialog::Create(wxWindow *parent)
{
	if ( !wxDialog::Create(GetParentForModalDialog(parent), wxID_ANY, wxT("ChaosTools Options")) )
        return false;
	CreateWidgets();
	optConfig = (wxFileConfig*)wxConfigBase::Get();
	return true;
}
int wxOptionsDialog::ShowModal()
{
	return wxDialog::ShowModal();
}
void wxOptionsDialog::CreateWidgets()
{
	mainSizer = new wxBoxSizer(wxHORIZONTAL);

	treeSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(treeSizer);

	optionsTreeCtrl = new wxTreeCtrl(this, ID_OPTIONSTREECTRL, wxDefaultPosition, wxSize(100,300));
	treeSizer->Add(optionsTreeCtrl, 1, wxALIGN_LEFT);

	panelSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(panelSizer, 1, wxEXPAND);

	mandelbrotPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500, 300));
	panelSizer->Add(mandelbrotPanel, 1, wxEXPAND | wxLEFT, 2);

	mandelbrotSizer = new wxStaticBoxSizer(wxVERTICAL, mandelbrotPanel, "Mandelbrot Options");
	mandelbrotPanel->SetSizer(mandelbrotSizer);

	mandelbrotGradientChangeButton = new wxButton(mandelbrotPanel, ID_MGRADIENTCHANGE, wxT("Change Gradient..."));
	mandelbrotSizer->Add(mandelbrotGradientChangeButton, 0, wxEXPAND | wxALL, 50);

	this->SetSizer(mainSizer);
	GetSizer()->Fit(this); 
    GetSizer()->SetSizeHints(this);
}

//For Mandelbrot
void wxOptionsDialog::OnMandelbrotGradientChange(wxCommandEvent& event)
{
	wxString mGradStr;
	optConfig->Read("Mandelbrot/Gradient", &mGradStr);

	wxGradient mGrad;
	mGrad.fromString(mGradStr);
	mGrad.setMin(0);
	mGrad.setMax(300);

	wxGradientDialog grad(this, mGrad);
	grad.ShowModal();

	mGrad = grad.GetGradient();
	optConfig->Write("Mandelbrot/Gradient", mGrad.toString());
}

void wxOptionsDialog::OnCloseWindow(wxCloseEvent& event)
{
	EndModal(wxID_CANCEL);
}