/*!! \file MandelThread.h
    \brief MandelThread class declaration
    
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

#ifndef MANDELTHREAD_H
#define MANDELTHREAD_H

#include <wx/thread.h>
#include <wx/event.h>
#include "gradient.h"

BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE(wxEVT_MTHREAD, -1)
END_DECLARE_EVENT_TYPES()

//! MandelThread class
/*!
	Handles the calculation of a single row of the mandelbrot set.
*/
class MandelThread : public wxThread
{
public:
	//! MandelThread Constructor
	/*!
		\param pParent A pointer to the parent object that will handle the events produced by this thread.
		\param row The row index of the row to be rendered.
		\param xmint The minimum mathematical x-value of the viewing window.
		\param xmaxt The maximum mathematical x-value of the viewing window.
		\param ymint The minimum mathematical y-value of the viewing window.
		\param ymaxt The maximum mathematical y-value of the viewing window.
		\param widtht The width, in pixels, of the viewing window.
		\param heightt The height, in pixels, of the viewing window.
		\param max The maximum number of iterations per pixel.
		\param grad The gradient to use to display the set

		Transfers necessary information to the thread for calculating a row.
	*/
    MandelThread(wxEvtHandler* pParent, int row, double &xmint, double &xmaxt, double &ymint, double &ymaxt, int &widtht, int &heightt, int &max, wxGradient &grad);
private:
	double xmin, xmax, ymin, ymax, dx, dy;
	int width, height, maxiter, r;
	wxGradient mGrad;
	//! Called when the thread's path of execution is entered.
	/*!
		Creates a wxCommandEvent of type wxEVT_MTHREAD, calls functions to calculate the row, and passes that data back through the event system.
	*/
	void* Entry();
	//! Calculates a single row of the Mandelbrot Set
	/*!
		\return An array of unsigned char values representing RGB pixel data
	*/
	unsigned char* DrawMandelRow();
	//! Generates the necessary color for a pixel based on iteration count.
	/*!
		\return A 3 unsigned char long array of pixel data representing an RGB color.
		Consider replacing with wxWidgets code if benchmarks prove it more efficient.
	*/
	unsigned char* getColour(double iter);
protected:
	wxEvtHandler* m_pParent;
};
#endif 