#include "DrawingPanel.h"
#include "MainWindow.h"
#include <vector>
#include <iostream>
#include "wx/graphics.h"
#include "wx/dcbuffer.h"
wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
      EVT_PAINT(DrawingPanel::OnPaint)
	  EVT_LEFT_UP(DrawingPanel::OnMouseClick)
wxEND_EVENT_TABLE()

DrawingPanel::DrawingPanel(wxFrame* parent, wxSize size, std::vector<std::vector<bool>>& Grid)
	: wxPanel(parent, wxID_ANY), rGridVector(Grid)
{
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	SetDoubleBuffered(true);

	/*this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
	this->Bind(wxEVT_LEFT_UP, &DrawingPanel::OnMouseClick, this);*/
}

DrawingPanel::~DrawingPanel()
{

}

void DrawingPanel::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

	wxGraphicsContext* context = wxGraphicsContext::Create(dc);


	context->SetPen(*wxBLACK);
	context->SetBrush(*wxWHITE);

	int CellWidth = GetSize().x / GridSize;
	int CellHeight = GetSize().y / GridSize;

	for (int i = 0; i < GridSize; i++)
	{
		for (int j = 0; j < GridSize; j++)
		{
			if (rGridVector[i][j] == true)
			{
				context->SetBrush(*wxLIGHT_GREY);
			}
			else
			{
				context->SetBrush(*wxWHITE);
			}
			context->DrawRectangle(CellWidth * i, CellHeight * j, CellWidth, CellHeight);

		}
	}
}

void DrawingPanel::SetGridSize(int size)
{
	GridSize = size;

}
void DrawingPanel::SetSize(wxSize& sizes)
{
	wxPanel::SetSize(sizes);
	Refresh();
}
void DrawingPanel::OnMouseClick(wxMouseEvent& click)
{
	int x = click.GetX();
	int y = click.GetY();
	int Width = GetSize().x / GridSize;
	int Height = GetSize().y / GridSize;
	int row = x / Width;
	int Column = y / Height;

	if (rGridVector[row][Column] == true)
	{
		rGridVector[row][Column] = false;
	}
	else
	{
		rGridVector[row][Column] = true;
	}
	Refresh();
}