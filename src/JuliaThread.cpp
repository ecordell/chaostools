/*!! \file JuliaThread.cpp
    \brief JuliaThread class implementation
    
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
#include "JuliaThread.h"

DEFINE_EVENT_TYPE(wxEVT_JTHREAD)

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