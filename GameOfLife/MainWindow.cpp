#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <vector>
#include "MainWindow.h"
#include "DrawingPanel.h"
wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
     EVT_SIZE(MainWindow::OnSizedChanged)
END_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game Of Life", wxPoint(0, 0), wxSize(300, 200))
{
	_Background = new DrawingPanel(this, wxSize(100, 100), Gameboard);


	_BoxSize = new wxBoxSizer(wxVERTICAL);
	_BoxSize->Add(_Background, 1, wxEXPAND | wxALL);
	//Bind(wxEVT_SIZE, &MainWindow::OnSizedChanged, this);

	SetSizer(_BoxSize);
	InitializeGrid();
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
