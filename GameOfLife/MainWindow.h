#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"



class MainWindow : public wxFrame
{
private:
	DrawingPanel* _Background = nullptr;
	wxBoxSizer* _BoxSize = nullptr;
public:
	
	MainWindow();
	~MainWindow();
	void OnSizedChanged(wxSizeEvent& event);
};
