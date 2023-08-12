#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <vector>
#include "MainWindow.h"
#include "DrawingPanel.h"
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

#define TOOLBAR_PLAY_ICON_ 10001
#define TOOLBAR_PAUSE_ICON 10002
#define TOOLBAR_NEXT_ICON 10003
#define TOOLBAR_TRASH_ICON 10004
#define TIMER_EVENT 10005

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
     EVT_SIZE(MainWindow::OnSizedChanged)
	 EVT_MENU(10001,MainWindow::OnPlayButtonClick)
	 EVT_MENU(10002,MainWindow::OnPauseButtonClick)
	 EVT_MENU(10003,MainWindow::OnNextButtonClick)
	 EVT_MENU(10004,MainWindow::OnTrashButtonClick)
     EVT_TIMER(10005, MainWindow::StartTimer)
END_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game Of Life", wxPoint(0, 0), wxSize(700, 900))
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
	GenBar = UpdateStatusBar(Gen,Generations);
	LivingBar = UpdateStatusBar(Cells, LivingCells);
    SetStatusText(GenBar, 0);
	SetStatusText(LivingBar, 1);
	
	

	_Background = new DrawingPanel(this, wxSize(100, 100), Gameboard);
	_BoxSize = new wxBoxSizer(wxVERTICAL);
	_BoxSize->Add(_Background, 1, wxEXPAND | wxALL);
	_Time = new wxTimer(this, 10005);

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

	
	SandBox.resize(GameBoardGridSize);
	for (int i = 0; i < SandBox.size(); i++)
	{
		SandBox[i].resize(GameBoardGridSize);
	}
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

	return statusText;
}



int MainWindow::NeighborCount(int row, int column)
{
	int livingNeighbors = 0;

	for (int i = row - 1; i <= row + 1; ++i)
	{
		for (int j = column - 1; j <= column + 1; ++j)
		{
			if (i == row && j == column)
			{
				continue;
			}

			if (i >= 0 && i < GameBoardGridSize && j >= 0 && j < GameBoardGridSize)
			{
				if (Gameboard[i][j])
				{
					livingNeighbors++;
				}
			}
		}
	}
	return livingNeighbors;
}

void MainWindow::NextGeneration()
{
	
	
	int alivetracker = 0;
	for (int i = 0; i < Gameboard.size(); i++)
	{
		for (int j = 0; j < Gameboard.size(); j++)
		{
			
			int Neighbors = NeighborCount(i, j);
			
			if (Gameboard[i][j] || Gameboard[i][j] == false)
			{
				if (Gameboard[i][j] == true)
				{
					if (Neighbors < 2)
					{
						SandBox[i][j] = false;
					}
					if (Neighbors > 3)
					{
						SandBox[i][j] = false;
					}
					if (Neighbors == 2)
					{
						SandBox[i][j] = true;
						alivetracker++;
					}
					if (Neighbors == 3)
					{
						SandBox[i][j] = true;
						alivetracker++;
					}
				}
				if (Gameboard[i][j] == false)
				{
					if (Neighbors == 3)
					{
						SandBox[i][j] = true;
						alivetracker++;
					}
					
				}
			}
			
		}
			
			
	}
	LivingCells = alivetracker;
	Gameboard.swap(SandBox);
	Generations++;
	LivingBar = UpdateStatusBar(Cells, LivingCells);
	GenBar = UpdateStatusBar(Gen, Generations);
	SetStatusText(GenBar, 0);
	SetStatusText(LivingBar, 1);
	Refresh();
}

void MainWindow::OnTrashButtonClick(wxCommandEvent& tEvent)
{
	for (int i = 0; i < Gameboard.size(); i++)
	{
		for (int j = 0; j < Gameboard.size(); j++)
		{
			Gameboard[i][j] = false;
		}
	}

	for (int i = 0; i < SandBox.size(); i++)
	{
		for (int j = 0; j <SandBox.size(); j++)
		{
			SandBox[i][j] = false;
		}
	}

	LivingCells = 0;
	Generations = 0;
	LivingBar = UpdateStatusBar(Cells, LivingCells);
	GenBar = UpdateStatusBar(Gen, Generations);
	SetStatusText(GenBar, 0);
	SetStatusText(LivingBar, 1);
	Refresh();

}
void MainWindow::OnPauseButtonClick(wxCommandEvent& pEvent)
{
	if (_Time->IsRunning())
	{
		_Time->Stop();
	}
}
void MainWindow::OnNextButtonClick(wxCommandEvent& nEvent) 
{
	NextGeneration();

}
void MainWindow::StartTimer(wxTimerEvent& tEvent)
{
	NextGeneration();
}
void MainWindow::OnPlayButtonClick(wxCommandEvent& cEvent)
{
	_Time->Start(Timer);
}