#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

DrawingPanel::GraphicsPanel(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(200, 200))
{
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	SetDoubeBuffered(true);

	this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
}

DrawingPanel::~GraphicsPanel()
{

}

void DrawingPanel::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

	wxGraphicsContext* context = wxGraphicsContext::Create(dc);
	if (!context)
	{

	}return;

	context->SetPen(*wxBLACK);
	context->SetBrush(*wxWHITE);
	wxSize size = GetSize();
	int CellWidth = size.x / GridSize;
	int CellHeight = size.y / GridSize;
	int StartPointx = 0;
	int StartPointy = 0;
	for (int i = 0; i <GridSize ; i++)
	{
		
		for (int j = 0; j < GridSize; j++)
		{
			context->DrawRectangle(StartPointx,StartPointy ,CellWidth,CellHeight);
			StartPointx = CellWidth * 2 ;
			StartPointy = CellHeight * 2 ;
		}
	}
}