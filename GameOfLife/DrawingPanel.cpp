#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

DrawingPanel::DrawingPanel(wxFrame* parent,wxSize size ) 
	: wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(200, 200))
{
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	SetDoubleBuffered(true);

	this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
}

DrawingPanel::~DrawingPanel()
{

}

void DrawingPanel::OnPaint(wxPaintEvent& event)
{
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

	wxGraphicsContext* context = wxGraphicsContext::Create(dc);
	/*if (!context)
	{

	}return;*/

	context->SetPen(*wxBLACK);
	context->SetBrush(*wxWHITE);
	
	float CellWidth = GetSize().x / (float)GridSize;
	float CellHeight = GetSize().y / (float)GridSize;
	
	for (int i = 0; i <GridSize ; i++)
	{
		for (int j = 0; j < GridSize; j++)
		{
			
			context->DrawRectangle(CellWidth * i,CellHeight * j ,CellWidth,CellHeight );
			
		}
	}
}