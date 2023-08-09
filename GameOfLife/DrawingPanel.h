#pragma once
#include "wx/wx.h"
#include <vector>
#include <iostream>
class DrawingPanel : public wxPanel
{
private:

	int GridSize = 15;
	std::vector<std::vector<bool>>& rGridVector;
public:
	DrawingPanel(wxFrame* parent, wxSize sizes, std::vector<std::vector<bool>>& Grid);
	~DrawingPanel();

	void OnPaint(wxPaintEvent& event);
	void SetSize(wxSize& sizes);
	void SetGridSize(int size);
	void OnMouseClick(wxMouseEvent& event);



	wxDECLARE_EVENT_TABLE();
};



