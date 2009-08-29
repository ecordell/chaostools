#ifndef WXGRADIENT_H
#define WXGRADIENT_H

#include <wx/vector.h>
#include <wx/colour.h>
#include <wx/string.h>

class wxGradient{
public:
	wxGradient();
	wxGradient(wxVector<wxColor> stops, int min, int max);
	bool Create(wxVector<wxColor> stops, int min, int max);
	virtual ~wxGradient();
	wxColour getColorAt(int value);
	void addColorStop(wxColor col);
	void insertColorStop(int index, wxColour col);
	void removeColorStop(int index);
	void editColorStop(int index, wxColour col);
	void setMin(int min);
	int getMin();
	void setMax(int max);
	int getMax();
	void setStops(wxVector<wxColor> stops);
	void fromString(wxString str);
	wxString toString();
	wxVector<wxColor> getStops();

protected:
	wxColor lerp(wxColor c1, wxColor c2, double value);
	wxVector<wxColor> m_stops;
	int m_min, m_max;
};

#endif