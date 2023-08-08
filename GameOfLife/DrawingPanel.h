#pragma once
#include "wx/wx.h"
class DrawingPanel :  public wxPanel
{
private :

	int GridSize= 15;

public:
	DrawingPanel(wxFrame* parent, wxSize size);
	
	~DrawingPanel();

	void OnPaint(wxPaintEvent& event);
};

