#include "optionsdlg.h"

IMPLEMENT_DYNAMIC_CLASS(wxOptionsDialog, wxDialog)

BEGIN_EVENT_TABLE(wxOptionsDialog, wxDialog)
	EVT_BUTTON(ID_MGRADIENTCHANGE, wxOptionsDialog::OnMandelbrotGradientChange)
	EVT_CLOSE(wxOptionsDialog::OnCloseWindow)
	EVT_TREE_ITEM_ACTIVATED(ID_OPTIONSTREECTRL, wxOptionsDialog::OnOptionsTreeClick)
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

	optionsTreeCtrl = new wxTreeCtrl(this, ID_OPTIONSTREECTRL, wxDefaultPosition, wxSize(180,300));
	treeSizer->Add(optionsTreeCtrl, 1, wxALIGN_LEFT);
	rootId = optionsTreeCtrl->AddRoot(wxT("ChaosTools"));
	iterationsId = optionsTreeCtrl->AppendItem(rootId, wxT("Iterations"));
	bifurcationsId = optionsTreeCtrl->AppendItem(rootId, wxT("Bifurcations"));
	juliaId = optionsTreeCtrl->AppendItem(rootId, wxT("Julia Sets"));
	mandelbrotId = optionsTreeCtrl->AppendItem(rootId, wxT("Mandelbrot Set"));
	ifsId = optionsTreeCtrl->AppendItem(rootId, wxT("Iterated Function System"));

	panelSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(panelSizer, 1, wxEXPAND);

	chaosToolsPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500, 300));
	panelSizer->Add(chaosToolsPanel, 1, wxEXPAND | wxLEFT, 2);

	chaosToolsSizer = new wxStaticBoxSizer(wxVERTICAL, chaosToolsPanel, "General Options");
	chaosToolsPanel->SetSizer(chaosToolsSizer);

	mandelbrotPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500, 300));
	panelSizer->Add(mandelbrotPanel, 1, wxEXPAND | wxLEFT, 2);

	mandelbrotSizer = new wxStaticBoxSizer(wxVERTICAL, mandelbrotPanel, "Mandelbrot Set Options");
	mandelbrotPanel->SetSizer(mandelbrotSizer);

	mandelbrotUseGradientCheckBox = new wxCheckBox(mandelbrotPanel, ID_MUSEGRADIENT, wxT("Use Custom Gradient"));
	mandelbrotSizer->Add(mandelbrotUseGradientCheckBox, 0, wxEXPAND | wxALL, 30);

	mandelbrotGradientChangeButton = new wxButton(mandelbrotPanel, ID_MGRADIENTCHANGE, wxT("Change Gradient..."));
	mandelbrotSizer->Add(mandelbrotGradientChangeButton, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 50);
	

	
	panelSizer->Hide(mandelbrotPanel, true);
	panelSizer->Show(chaosToolsPanel, true);
	panelSizer->Layout();

	this->SetSizer(mainSizer);
	GetSizer()->Fit(this); 
    GetSizer()->SetSizeHints(this);
}
void wxOptionsDialog::OnOptionsTreeClick(wxTreeEvent& event)
{
	if (event.GetItem() == rootId)
	{
		panelSizer->Hide(mandelbrotPanel, true);
		panelSizer->Show(chaosToolsPanel, true);
	}
	else if (event.GetItem() == mandelbrotId)
	{
		panelSizer->Hide(chaosToolsPanel, true);
		panelSizer->Show(mandelbrotPanel, true);
	}
	mainSizer->Layout();
	GetSizer()->Fit(this);
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