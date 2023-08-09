#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"
#include <vector>
#include <iostream>


class MainWindow : public wxFrame
{
private:
	int GameBoardGridSize = 15;
	DrawingPanel* _Background = nullptr;

	wxBoxSizer* _BoxSize = nullptr;
	std::vector<std::vector<bool>> Gameboard;
public:

	MainWindow();
	~MainWindow();
	void OnSizedChanged(wxSizeEvent& event);
	void InitializeGrid();




	wxDECLARE_EVENT_TABLE();
};
