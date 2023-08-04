#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"



class MainWindow : public wxFrame
{
	DrawingPanel* Panel = nullptr;
public:
	Window();
	~Window();
};
