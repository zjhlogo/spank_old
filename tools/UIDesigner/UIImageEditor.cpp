/*!
 * \file UIImageEditor.cpp
 * \date 01-09-2011 21:21:45
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "UIImageEditor.h"
#include <wx/dcclient.h>

BEGIN_EVENT_TABLE(UIImageEditor, wxScrolledWindow)
	EVT_MOUSEWHEEL(UIImageEditor::OnMouseWheel)
	EVT_MOTION(UIImageEditor::OnMouseMove)
	EVT_LEFT_DOWN(UIImageEditor::OnMouseLButtonDown)
	EVT_LEFT_UP(UIImageEditor::OnMouseLButtonUp)
END_EVENT_TABLE()

IMPLEMENT_DYNAMIC_CLASS(UIImageEditor, wxScrolledWindow)

UIImageEditor::UIImageEditor()
{
	Init();
}

UIImageEditor::UIImageEditor(wxWindow *parent, wxWindowID winid /*= wxID_ANY*/, const wxPoint& pos /*= wxDefaultPosition*/, const wxSize& size /*= wxDefaultSize*/, long style /*= wxScrolledWindowStyle*/, const wxString& name /*= wxPanelNameStr*/)
{
	Init();
	Create(parent, winid, pos, size, style, name);
}

UIImageEditor::~UIImageEditor()
{
	for (int i = 0; i < NUM_CT; ++i)
	{
		delete m_pCursors[i];
		m_pCursors[i] = NULL;
	}
}

void UIImageEditor::Init()
{
	m_bmpGrid.LoadFile(wxT("images/grid.png"), wxBITMAP_TYPE_PNG);
	m_dcMemory.SelectObject(wxNullBitmap);

	m_penBlue.SetColour(0, 0, 255);
	m_penRed.SetColour(255, 0, 0);

	m_brushTransparent.SetStyle(wxBRUSHSTYLE_TRANSPARENT);
	m_brushBlue.SetStyle(wxBRUSHSTYLE_SOLID);
	m_brushBlue.SetColour(0, 0, 255);
	m_brushGrid.SetStyle(wxBRUSHSTYLE_STIPPLE);
	m_brushGrid.SetStipple(m_bmpGrid);

	m_rectSelected = wxRect(100, 100, 100, 100);
	m_nZoom = ZOOM_MIN;

	m_eCurType = CT_DEFAULT;
	m_pCursors[CT_DEFAULT] = new wxCursor(wxT("images/size3_r.cur"), wxBITMAP_TYPE_CUR);
	m_pCursors[CT_HORIZONTAL] = new wxCursor(wxT("images/size3_r.cur"), wxBITMAP_TYPE_CUR);
	m_pCursors[CT_VERTICAL] = new wxCursor(wxT("images/size4_r.cur"), wxBITMAP_TYPE_CUR);
	m_pCursors[CT_DIAGONAL] = new wxCursor(wxT("images/size2_r.cur"), wxBITMAP_TYPE_CUR);
	m_pCursors[CT_DIAGONAL_INV] = new wxCursor(wxT("images/size1_r.cur"), wxBITMAP_TYPE_CUR);
	m_pCursors[CT_MOVE] = new wxCursor(wxT("images/move_r.cur"), wxBITMAP_TYPE_CUR);

	m_CurrDragMode = PIC_UNKNOWN;
}

bool UIImageEditor::Create(wxWindow *parent, wxWindowID winid /*= wxID_ANY*/, const wxPoint& pos /*= wxDefaultPosition*/, const wxSize& size /*= wxDefaultSize*/, long style /*= wxScrolledWindowStyle*/, const wxString& name /*= wxPanelNameStr*/)
{
	if (!wxScrolledWindow::Create(parent, winid, pos, size, style, name)) return false;

	return true;
}

wxSize UIImageEditor::DoGetBestSize() const
{
	// TODO: 
	return wxSize(2000, 2000);
}

void UIImageEditor::OnDraw(wxDC& dc)
{
	int ppuX = 0, ppuY = 0;
	GetScrollPixelsPerUnit(&ppuX, &ppuY);

	int startX = 0, startY = 0;
	GetViewStart(&startX, &startY);

	wxRect clientRect = GetClientRect();
	dc.SetBrush(m_brushGrid);
	dc.DrawRectangle(ppuX*startX, ppuY*startY, clientRect.GetWidth(), clientRect.GetHeight());

	dc.StretchBlit(0, 0,
		m_bmpDC.GetWidth()*m_nZoom,
		m_bmpDC.GetHeight()*m_nZoom,
		&m_dcMemory,
		0, 0,
		m_bmpDC.GetWidth(),
		m_bmpDC.GetHeight(),
		wxCOPY);

	DrawSelectedRect(dc, m_rectSelected);
	if (m_CurrDragMode != PIC_UNKNOWN)
	{
		DrawDragRect(dc, m_rectDrag);
	}
}

bool UIImageEditor::OpenBitmap(const wxString& path)
{
	if (!m_bmpDC.LoadFile(path, wxBITMAP_TYPE_PNG)) return false;
	m_dcMemory.SelectObject(m_bmpDC);

	UpdateVirtualSize();

	return true;
}

bool UIImageEditor::ZoomIn()
{
	m_nZoom += ZOOM_STEP;
	if (m_nZoom > ZOOM_MAX)
	{
		m_nZoom = ZOOM_MAX;
		return false;
	}

	UpdateVirtualSize();
	return true;
}

bool UIImageEditor::ZoomOut()
{
	m_nZoom -= ZOOM_STEP;
	if (m_nZoom < ZOOM_MIN)
	{
		m_nZoom = ZOOM_MIN;
		return false;
	}

	UpdateVirtualSize();
	return true;
}

bool UIImageEditor::Zoom(int zoom)
{
	if (zoom < ZOOM_MIN || zoom > ZOOM_MAX) return false;

	m_nZoom = zoom;
	UpdateVirtualSize();
	return true;
}

int UIImageEditor::GetZoom() const
{
	return m_nZoom;
}

void UIImageEditor::UpdateVirtualSize()
{
	wxSize size = m_bmpDC.GetSize();
	SetVirtualSize(size.x*m_nZoom, size.y*m_nZoom);
	SetScrollRate(m_nZoom, m_nZoom);
	Refresh(true);
}

void UIImageEditor::DrawSelectedRect(wxDC& dc, const wxRect& rect)
{
	dc.SetPen(m_penBlue);
	dc.SetBrush(m_brushTransparent);

	wxRect zoomedRect(rect.x*m_nZoom, rect.y*m_nZoom, rect.width*m_nZoom, rect.height*m_nZoom);
	dc.DrawRectangle(zoomedRect);

	dc.SetBrush(m_brushBlue);
	dc.DrawRectangle(zoomedRect.x-RECT_SPOT_SIZE, zoomedRect.y-RECT_SPOT_SIZE, RECT_SPOT_SIZE*2, RECT_SPOT_SIZE*2);
	dc.DrawRectangle(zoomedRect.x+zoomedRect.width/2-RECT_SPOT_SIZE, zoomedRect.y-RECT_SPOT_SIZE, RECT_SPOT_SIZE*2, RECT_SPOT_SIZE*2);
	dc.DrawRectangle(zoomedRect.x+zoomedRect.width-RECT_SPOT_SIZE, zoomedRect.y-RECT_SPOT_SIZE, RECT_SPOT_SIZE*2, RECT_SPOT_SIZE*2);
	dc.DrawRectangle(zoomedRect.x-RECT_SPOT_SIZE, zoomedRect.y+zoomedRect.height/2-RECT_SPOT_SIZE, RECT_SPOT_SIZE*2, RECT_SPOT_SIZE*2);
	dc.DrawRectangle(zoomedRect.x+zoomedRect.width-RECT_SPOT_SIZE, zoomedRect.y+zoomedRect.height/2-RECT_SPOT_SIZE, RECT_SPOT_SIZE*2, RECT_SPOT_SIZE*2);
	dc.DrawRectangle(zoomedRect.x-RECT_SPOT_SIZE, zoomedRect.y+zoomedRect.height-RECT_SPOT_SIZE, RECT_SPOT_SIZE*2, RECT_SPOT_SIZE*2);
	dc.DrawRectangle(zoomedRect.x+zoomedRect.width/2-RECT_SPOT_SIZE, zoomedRect.y+zoomedRect.height-RECT_SPOT_SIZE, RECT_SPOT_SIZE*2, RECT_SPOT_SIZE*2);
	dc.DrawRectangle(zoomedRect.x+zoomedRect.width-RECT_SPOT_SIZE, zoomedRect.y+zoomedRect.height-RECT_SPOT_SIZE, RECT_SPOT_SIZE*2, RECT_SPOT_SIZE*2);
}

void UIImageEditor::DrawDragRect(wxDC& dc, const wxRect& rect)
{
	dc.SetPen(m_penRed);
	dc.SetBrush(m_brushTransparent);

	wxRect zoomedRect(rect.x*m_nZoom, rect.y*m_nZoom, rect.width*m_nZoom, rect.height*m_nZoom);
	dc.DrawRectangle(zoomedRect);
}

UIImageEditor::POINT_IN_CONNER UIImageEditor::CheckPointInConner(const wxRect& rect, const wxPoint& pt)
{
	wxRect rectTopLeft(rect.x-RECT_SENSOR_SIZE, rect.y-RECT_SENSOR_SIZE, RECT_SENSOR_SIZE*2, RECT_SENSOR_SIZE*2);
	if (rectTopLeft.Contains(pt)) return PIC_TOP_LEFT;

	wxRect rectTopCenter(rect.x+rect.width/2-RECT_SENSOR_SIZE, rect.y-RECT_SENSOR_SIZE, RECT_SENSOR_SIZE*2, RECT_SENSOR_SIZE*2);
	if (rectTopCenter.Contains(pt)) return PIC_TOP_CENTER;

	wxRect rectTopRight(rect.x+rect.width-RECT_SENSOR_SIZE, rect.y-RECT_SENSOR_SIZE, RECT_SENSOR_SIZE*2, RECT_SENSOR_SIZE*2);
	if (rectTopRight.Contains(pt)) return PIC_TOP_RIGHT;

	wxRect rectMiddleLeft(rect.x-RECT_SENSOR_SIZE, rect.y+rect.height/2-RECT_SENSOR_SIZE, RECT_SENSOR_SIZE*2, RECT_SENSOR_SIZE*2);
	if (rectMiddleLeft.Contains(pt)) return PIC_MIDDLE_LEFT;

	wxRect rectMiddleRight(rect.x+rect.width-RECT_SENSOR_SIZE, rect.y+rect.height/2-RECT_SENSOR_SIZE, RECT_SENSOR_SIZE*2, RECT_SENSOR_SIZE*2);
	if (rectMiddleRight.Contains(pt)) return PIC_MIDDLE_RIGHT;

	wxRect rectBottomLeft(rect.x-RECT_SENSOR_SIZE, rect.y+rect.height-RECT_SENSOR_SIZE, RECT_SENSOR_SIZE*2, RECT_SENSOR_SIZE*2);
	if (rectBottomLeft.Contains(pt)) return PIC_BOTTOM_LEFT;

	wxRect rectBottomCenter(rect.x+rect.width/2-RECT_SENSOR_SIZE, rect.y+rect.height-RECT_SENSOR_SIZE, RECT_SENSOR_SIZE*2, RECT_SENSOR_SIZE*2);
	if (rectBottomCenter.Contains(pt)) return PIC_BOTTOM_CENTER;

	wxRect rectBottomRight(rect.x+rect.width-RECT_SENSOR_SIZE, rect.y+rect.height-RECT_SENSOR_SIZE, RECT_SENSOR_SIZE*2, RECT_SENSOR_SIZE*2);
	if (rectBottomRight.Contains(pt)) return PIC_BOTTOM_RIGHT;

	if (rect.Contains(pt)) return PIC_MIDDLE_CENTER;

	return PIC_UNKNOWN;
}

void UIImageEditor::SetCursorByType(CURSOR_TYPE eType)
{
	if (m_eCurType == eType) return;
	m_eCurType = eType;

	if (m_eCurType == CT_DEFAULT)
	{
		SetCursor(wxNullCursor);
	}
	else
	{
		SetCursor(*m_pCursors[eType]);
	}
}

void UIImageEditor::OnMouseWheel(wxMouseEvent& event)
{
	int lines = -event.GetWheelRotation() / event.GetWheelDelta();

	wxPoint pt = GetViewStart();

	int nDistance = (MOUSE_WHEEL_DISTANCE / m_nZoom);
	if (event.ShiftDown())
	{
		Scroll(pt.x + lines * event.GetLinesPerAction() * nDistance, pt.y);
	}
	else if (event.ControlDown())
	{
		if (lines < 0)
		{
			ZoomIn();
		}
		else
		{
			ZoomOut();
		}
	}
	else
	{
		Scroll(pt.x, pt.y + lines * event.GetLinesPerAction() * nDistance);
	}
}

void UIImageEditor::OnMouseMove(wxMouseEvent& event)
{
	wxPoint pt = event.GetPosition();

	if (m_CurrDragMode == PIC_UNKNOWN)
	{
		wxRect zoomedRect(m_rectSelected.x*m_nZoom, m_rectSelected.y*m_nZoom, m_rectSelected.width*m_nZoom, m_rectSelected.height*m_nZoom);

		int ppuX = 0, ppuY = 0;
		GetScrollPixelsPerUnit(&ppuX, &ppuY);

		int startX = 0, startY = 0;
		GetViewStart(&startX, &startY);

		wxPoint zoomedPoint(pt.x+ppuX*startX, pt.y+ppuY*startY);

		POINT_IN_CONNER eType = CheckPointInConner(zoomedRect, zoomedPoint);
		switch (eType)
		{
		case PIC_TOP_LEFT:
		case PIC_BOTTOM_RIGHT:
			{
				SetCursorByType(CT_DIAGONAL);
			}
			break;
		case PIC_TOP_RIGHT:
		case PIC_BOTTOM_LEFT:
			{
				SetCursorByType(CT_DIAGONAL_INV);
			}
			break;
		case PIC_TOP_CENTER:
		case PIC_BOTTOM_CENTER:
			{
				SetCursorByType(CT_VERTICAL);
			}
			break;
		case PIC_MIDDLE_LEFT:
		case PIC_MIDDLE_RIGHT:
			{
				SetCursorByType(CT_HORIZONTAL);
			}
			break;
		case PIC_MIDDLE_CENTER:
			{
				SetCursorByType(CT_MOVE);
			}
			break;
		default:
			{
				SetCursorByType(CT_DEFAULT);
			}
			break;
		}
	}
	else
	{
		// apply drag rect
		m_rectDrag.x = (pt.x - m_ptMouseDown.x)/m_nZoom + m_rectSelected.x;
		m_rectDrag.y = (pt.y - m_ptMouseDown.y)/m_nZoom + m_rectSelected.y;
		Refresh(false);
	}

	event.Skip();
}

void UIImageEditor::OnMouseLButtonDown(wxMouseEvent& event)
{
	m_ptMouseDown = event.GetPosition();

	wxRect zoomedRect(m_rectSelected.x*m_nZoom, m_rectSelected.y*m_nZoom, m_rectSelected.width*m_nZoom, m_rectSelected.height*m_nZoom);

	int ppuX = 0, ppuY = 0;
	GetScrollPixelsPerUnit(&ppuX, &ppuY);

	int startX = 0, startY = 0;
	GetViewStart(&startX, &startY);

	wxPoint zoomedPoint(m_ptMouseDown.x+ppuX*startX, m_ptMouseDown.y+ppuY*startY);

	m_CurrDragMode = CheckPointInConner(zoomedRect, zoomedPoint);
	if (m_CurrDragMode != PIC_UNKNOWN)
	{
		m_rectDrag = m_rectSelected;
// 		this->CaptureMouse();
	}

	event.Skip();
}

void UIImageEditor::OnMouseLButtonUp(wxMouseEvent& event)
{
	if (m_CurrDragMode != PIC_UNKNOWN)
	{
		// TODO: apply drag
		m_CurrDragMode = PIC_UNKNOWN;
// 		this->ReleaseMouse();
		Refresh(false);
	}

	event.Skip();
}
