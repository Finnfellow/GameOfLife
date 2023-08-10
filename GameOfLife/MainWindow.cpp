#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <vector>
#include "MainWindow.h"
#include "DrawingPanel.h"
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"

#define TOOLBAR_PLAY_ICON_ 10001
#define TOOLBAR_PAUSE_ICON 10002
#define TOOLBAR_NEXT_ICON 10003
#define TOOLBAR_TRASH_ICON 10004

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
     EVT_SIZE(MainWindow::OnSizedChanged)
	 EVT_MENU(10001,MainWindow::OnPlayButtonClick)
	 
END_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game Of Life", wxPoint(0, 0), wxSize(300, 200))
{
	wxBitmap PlayIcon(play_xpm);
	wxBitmap PauseIcon(pause_xpm);
	wxBitmap NextIcon(next_xpm);
	wxBitmap TrashIcon(trash_xpm);
	_ToolBar = CreateToolBar();
	_ToolBar->AddTool(TOOLBAR_PLAY_ICON_, "Play Game", PlayIcon);
	_ToolBar->AddTool(TOOLBAR_PAUSE_ICON, "Pause Game", PauseIcon);
	_ToolBar->AddTool(TOOLBAR_NEXT_ICON, " Next Generation", NextIcon);
	_ToolBar->AddTool(TOOLBAR_TRASH_ICON, "Reset Game", TrashIcon);
	_ToolBar->Realize();

	StatusBar = CreateStatusBar(2);
	wxString Bar1 = UpdateStatusBar(Gen,Generations);
	wxString Bar2 = UpdateStatusBar(Cells, LivingCells);
    SetStatusText(Bar1, 0);
	SetStatusText(Bar2, 1);

	

	_Background = new DrawingPanel(this, wxSize(100, 100), Gameboard);
	_BoxSize = new wxBoxSizer(wxVERTICAL);
	_BoxSize->Add(_Background, 1, wxEXPAND | wxALL);
	

	SetSizer(_BoxSize);
	InitializeGrid();

	this->Layout();
}

MainWindow::~MainWindow()
{

}

 void MainWindow::OnSizedChanged(wxSizeEvent& event)
{
	if (_Background)
	{
		wxSize size = event.GetSize();
		_Background->SetSize(size);
		event.Skip();

	}
}

void MainWindow::InitializeGrid()
{
	Gameboard.resize(GameBoardGridSize);
	for (int i = 0; i < Gameboard.size(); i++)
	{
		Gameboard[i].resize(GameBoardGridSize);
	}
	_Background->SetGridSize(GameBoardGridSize);
}
wxString MainWindow::UpdateStatusBar( wxString name, int Barnum)
{
	wxString statusText;
	if (name == Gen) 
	{
		
		statusText.Printf("Generation:   %d   ", Generations);
	}
	else if(name == Cells)
	{
		statusText.Printf("Living Cells:   %d   ", LivingCells);
	}
		
		//StatusBar->SetStatusText(statusText);
	
	return statusText;
}

void MainWindow::OnPlayButtonClick(wxCommandEvent& cEvent)
{

}

int MainWindow::NeighborCount(int row, int column)
{
	int CellsAlive = 0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			if(i==0 && j == 0)
			{
				continue;
			}
			if (i && j > 2 | i && j > -1)
			{
				continue;
		   }
			if (i + row && j+column == true)
			{
				CellsAlive++;
			}
			

		}
	}

	return CellsAlive;
}