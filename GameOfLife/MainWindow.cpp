


#include "MainWindow.h"

 MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game Of Life", wxPoint(0, 0), wxSize(300, 200))
 {
	   _Background = new DrawingPanel(this, wxSize(100,100));


	 _BoxSize = new wxBoxSizer(wxVERTICAL);
	 _BoxSize->Add(_Background, 1, wxEXPAND | wxALL);
	 Bind(wxEVT_SIZE, &MainWindow::OnSizedChanged, this);

	 SetSizer(_BoxSize);
	 
 }

 MainWindow::~MainWindow()
 {
	
 }

 void MainWindow::OnSizedChanged(wxSizeEvent& event)
 {
	 _Background->SetSize(event.GetSize());
	 _Background->Refresh();
 }


