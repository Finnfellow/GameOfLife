#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

DrawingPanel::DrawinngPanel(wxFrame* parent) : wxPanel(parent, wxID_ANY, wxPoint(0, 0), wxSize(200, 200))
{
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	SetDoubeBuffered(true);

	this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this)
}

DrawingPanel::~DrawingPanel()
{

}