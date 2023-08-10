#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"
#include <vector>
#include <iostream>


class MainWindow : public wxFrame
{
private:
	int GameBoardGridSize = 15;
	int Generations = 0;
	int LivingCells = 0;

	wxString Gen = "Generations:";
	wxString Cells = "Living Cells:";
	DrawingPanel* _Background = nullptr;
	wxStatusBar* StatusBar = nullptr;
	wxBoxSizer* _BoxSize = nullptr;
	wxToolBar* _ToolBar = nullptr;

	std::vector<std::vector<bool>> Gameboard;
public:

	MainWindow();
	~MainWindow();
	void OnSizedChanged(wxSizeEvent& event);
	void InitializeGrid();
	wxString UpdateStatusBar( wxString name, int number);
	void OnPlayButtonClick(wxCommandEvent& cEvent);
	int NeighborCount(int row, int column);

	wxDECLARE_EVENT_TABLE();
};
