/*!
 * \file UIImageEditor.cpp
 * \date 01-09-2011 21:21:45
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "UIImageEditor.h"
#include <wx/dcclient.h>

BEGIN_EVENT_TABLE(UIImageEditor, wxWindow)
	EVT_PAINT(UIImageEditor::OnPaint)
	EVT_MOUSEWHEEL(UIImageEditor::OnMouseWheel)
	EVT_MOTION(UIImageEditor::OnMouseMove)
	EVT_LEFT_DOWN(UIImageEditor::OnMouseLButtonDown)
	EVT_LEFT_UP(UIImageEditor::OnMouseLButtonUp)
	EVT_SIZE(UIImageEditor::OnSize)
	EVT_SCROLLWIN_LINEUP(UIImageEditor::OnScrollLineUp)
	EVT_SCROLLWIN_LINEDOWN(UIImageEditor::OnScrollLineDown)
	EVT_SCROLLWIN_PAGEUP(UIImageEditor::OnScrollPageUp)
	EVT_SCROLLWIN_PAGEDOWN(UIImageEditor::OnScrollPageDown)
	EVT_SCROLLWIN_THUMBTRACK(UIImageEditor::OnScrollThumbTrack)
	EVT_SCROLLWIN_THUMBRELEASE(UIImageEditor::OnScrollThumbRelease)
END_EVENT_TABLE()

IMPLEMENT_DYNAMIC_CLASS(UIImageEditor, wxWindow)

UIImageEditor::UIImageEditor()
{
	Init();
}

UIImageEditor::UIImageEditor(wxWindow *parent, wxWindowID winid, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = 0 */, const wxString& name /* = wxPanelNameStr */)
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

	m_sizeVirtual.Set(DEFAULT_VIRTUAL_SIZE*m_nZoom, DEFAULT_VIRTUAL_SIZE*m_nZoom);
	m_ptOrigin.x = 0;
	m_ptOrigin.y = 0;
}

bool UIImageEditor::Create(wxWindow *parent, wxWindowID winid, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = 0 */, const wxString& name /* = wxPanelNameStr */)
{
	if (!wxWindow::Create(parent, winid, pos, size, style, name)) return false;

	return true;
}

wxSize UIImageEditor::DoGetBestSize() const
{
	return m_sizeVirtual;
}

bool UIImageEditor::LoadBitmapFile(const wxString& path)
{
	if (!m_bmpImage.LoadFile(path, wxBITMAP_TYPE_PNG)) return false;
	m_dcImage.SelectObject(m_bmpImage);

	UpdateVirtualSize();
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));

	return true;
}

bool UIImageEditor::ZoomIn()
{
	return Zoom(m_nZoom+1);
}

bool UIImageEditor::ZoomOut()
{
	return Zoom(m_nZoom-1);
}

bool UIImageEditor::Zoom(int zoom)
{
	if (zoom < ZOOM_MIN || zoom > ZOOM_MAX) return false;
	if (m_nZoom == zoom) return true;

	m_ptOrigin = (m_ptOrigin/m_nZoom)*zoom;
	m_nZoom = zoom;
	UpdateVirtualSize();
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));

	return true;
}

int UIImageEditor::GetZoom() const
{
	return m_nZoom;
}

void UIImageEditor::UpdateVirtualSize()
{
	m_sizeVirtual = m_bmpImage.GetSize();
	m_sizeVirtual *= m_nZoom;

	wxRect rect = GetClientRect();

	// hide unnessary scroll bar
	bool bShowHorizontal = true;
	if (m_sizeVirtual.GetWidth() <= rect.GetWidth())
	{
		SetScrollbar(wxHORIZONTAL, 0, 0, 0, true);
		bShowHorizontal = false;
	}

	bool bShowVertical = true;
	if (m_sizeVirtual.GetHeight() <= rect.GetHeight())
	{
		SetScrollbar(wxVERTICAL, 0, 0, 0, true);
		bShowVertical = false;
	}

	// get the rect again, it may be difference from the old rect after hide the scroll bar
	rect = GetClientRect();

	// recalculate the scroll bar range
	if (bShowHorizontal)
	{
		SetScrollbar(wxHORIZONTAL, m_ptOrigin.x, rect.GetWidth(), m_sizeVirtual.GetWidth(), true);
	}
	if (bShowVertical)
	{
		SetScrollbar(wxVERTICAL, m_ptOrigin.y, rect.GetHeight(), m_sizeVirtual.GetHeight(), true);
	}
}

const wxSize& UIImageEditor::GetVirtualSize()
{
	return m_sizeVirtual;
}

void UIImageEditor::UpdateScrollPosition(int x, int y)
{
	m_ptOrigin.x = x;
	m_ptOrigin.y = y;

	Refresh(false);
}

void UIImageEditor::DrawSelectedRect(wxDC& dc, const wxRect& rect)
{
// 	dc.SetPen(m_penBlue);
// 	dc.SetBrush(m_brushTransparent);
// 
// 	wxRect zoomedRect(rect.x*m_nZoom, rect.y*m_nZoom, rect.width*m_nZoom, rect.height*m_nZoom);
// 	dc.DrawRectangle(zoomedRect);
// 
// 	dc.SetBrush(m_brushBlue);
// 	dc.DrawRectangle(zoomedRect.x-RECT_SPOT_SIZE, zoomedRect.y-RECT_SPOT_SIZE, RECT_SPOT_SIZE*2, RECT_SPOT_SIZE*2);
// 	dc.DrawRectangle(zoomedRect.x+zoomedRect.width/2-RECT_SPOT_SIZE, zoomedRect.y-RECT_SPOT_SIZE, RECT_SPOT_SIZE*2, RECT_SPOT_SIZE*2);
// 	dc.DrawRectangle(zoomedRect.x+zoomedRect.width-RECT_SPOT_SIZE, zoomedRect.y-RECT_SPOT_SIZE, RECT_SPOT_SIZE*2, RECT_SPOT_SIZE*2);
// 	dc.DrawRectangle(zoomedRect.x-RECT_SPOT_SIZE, zoomedRect.y+zoomedRect.height/2-RECT_SPOT_SIZE, RECT_SPOT_SIZE*2, RECT_SPOT_SIZE*2);
// 	dc.DrawRectangle(zoomedRect.x+zoomedRect.width-RECT_SPOT_SIZE, zoomedRect.y+zoomedRect.height/2-RECT_SPOT_SIZE, RECT_SPOT_SIZE*2, RECT_SPOT_SIZE*2);
// 	dc.DrawRectangle(zoomedRect.x-RECT_SPOT_SIZE, zoomedRect.y+zoomedRect.height-RECT_SPOT_SIZE, RECT_SPOT_SIZE*2, RECT_SPOT_SIZE*2);
// 	dc.DrawRectangle(zoomedRect.x+zoomedRect.width/2-RECT_SPOT_SIZE, zoomedRect.y+zoomedRect.height-RECT_SPOT_SIZE, RECT_SPOT_SIZE*2, RECT_SPOT_SIZE*2);
// 	dc.DrawRectangle(zoomedRect.x+zoomedRect.width-RECT_SPOT_SIZE, zoomedRect.y+zoomedRect.height-RECT_SPOT_SIZE, RECT_SPOT_SIZE*2, RECT_SPOT_SIZE*2);
}

void UIImageEditor::DrawDragRect(wxDC& dc, const wxRect& rect)
{
// 	dc.SetPen(m_penRed);
// 	dc.SetBrush(m_brushTransparent);
// 
// 	wxRect zoomedRect(rect.x*m_nZoom, rect.y*m_nZoom, rect.width*m_nZoom, rect.height*m_nZoom);
// 	dc.DrawRectangle(zoomedRect);
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

void UIImageEditor::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	// get client size
	wxRect clientSize = GetClientSize();

	// draw image
	int nWidth = clientSize.GetWidth() > m_bmpImage.GetWidth() ? clientSize.GetWidth() : m_bmpImage.GetWidth();
	int nHeight = clientSize.GetHeight() > m_bmpImage.GetHeight() ? clientSize.GetHeight() : m_bmpImage.GetHeight();

	m_dcBackBuffer.SetBrush(m_brushGrid);
	m_dcBackBuffer.SetPen(*wxTRANSPARENT_PEN);
	m_dcBackBuffer.DrawRectangle(0, 0, nWidth*m_nZoom, nHeight*m_nZoom);

	m_dcBackBuffer.StretchBlit(-m_ptOrigin.x, -m_ptOrigin.y,
		m_bmpImage.GetWidth()*m_nZoom,
		m_bmpImage.GetHeight()*m_nZoom,
		&m_dcImage,
		0, 0,
		m_bmpImage.GetWidth(),
		m_bmpImage.GetHeight());

	// flush to dc
	dc.Blit(0, 0, m_bmpBackBuffer.GetWidth(), m_bmpBackBuffer.GetHeight(), &m_dcBackBuffer, 0, 0);
}

void UIImageEditor::OnMouseWheel(wxMouseEvent& event)
{
 	int lines = -event.GetWheelRotation() / event.GetWheelDelta();

	if (event.ShiftDown())
 	{
		int nPos = GetScrollPos(wxHORIZONTAL);
		SetScrollPos(wxHORIZONTAL, nPos + lines * event.GetLinesPerAction() * SCROLL_LINE_DISTANCE);
		UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
 	}
 	else if (event.ControlDown())
 	{
 		if (lines < 0) ZoomIn();
 		else ZoomOut();
 	}
 	else
 	{
		int nPos = GetScrollPos(wxVERTICAL);
		SetScrollPos(wxVERTICAL, nPos + lines * event.GetLinesPerAction() * SCROLL_LINE_DISTANCE);
		UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
 	}
	event.Skip();
}

void UIImageEditor::OnMouseMove(wxMouseEvent& event)
{
// 	wxPoint pt = event.GetPosition();
// 
// 	if (m_CurrDragMode == PIC_UNKNOWN)
// 	{
// 		wxRect zoomedRect(m_rectSelected.x*m_nZoom, m_rectSelected.y*m_nZoom, m_rectSelected.width*m_nZoom, m_rectSelected.height*m_nZoom);
// 
// 		int ppuX = 0, ppuY = 0;
// 		GetScrollPixelsPerUnit(&ppuX, &ppuY);
// 
// 		int startX = 0, startY = 0;
// 		GetViewStart(&startX, &startY);
// 
// 		wxPoint zoomedPoint(pt.x+ppuX*startX, pt.y+ppuY*startY);
// 
// 		POINT_IN_CONNER eType = CheckPointInConner(zoomedRect, zoomedPoint);
// 		switch (eType)
// 		{
// 		case PIC_TOP_LEFT:
// 		case PIC_BOTTOM_RIGHT:
// 			{
// 				SetCursorByType(CT_DIAGONAL);
// 			}
// 			break;
// 		case PIC_TOP_RIGHT:
// 		case PIC_BOTTOM_LEFT:
// 			{
// 				SetCursorByType(CT_DIAGONAL_INV);
// 			}
// 			break;
// 		case PIC_TOP_CENTER:
// 		case PIC_BOTTOM_CENTER:
// 			{
// 				SetCursorByType(CT_VERTICAL);
// 			}
// 			break;
// 		case PIC_MIDDLE_LEFT:
// 		case PIC_MIDDLE_RIGHT:
// 			{
// 				SetCursorByType(CT_HORIZONTAL);
// 			}
// 			break;
// 		case PIC_MIDDLE_CENTER:
// 			{
// 				SetCursorByType(CT_MOVE);
// 			}
// 			break;
// 		default:
// 			{
// 				SetCursorByType(CT_DEFAULT);
// 			}
// 			break;
// 		}
// 	}
// 	else
// 	{
// 		// apply drag rect
// 		m_rectDrag.x = (pt.x - m_ptMouseDown.x)/m_nZoom + m_rectSelected.x;
// 		m_rectDrag.y = (pt.y - m_ptMouseDown.y)/m_nZoom + m_rectSelected.y;
// 		Refresh(true);
// 	}

	event.Skip();
}

void UIImageEditor::OnMouseLButtonDown(wxMouseEvent& event)
{
// 	m_ptMouseDown = event.GetPosition();
// 
// 	wxRect zoomedRect(m_rectSelected.x*m_nZoom, m_rectSelected.y*m_nZoom, m_rectSelected.width*m_nZoom, m_rectSelected.height*m_nZoom);
// 
// 	int ppuX = 0, ppuY = 0;
// 	GetScrollPixelsPerUnit(&ppuX, &ppuY);
// 
// 	int startX = 0, startY = 0;
// 	GetViewStart(&startX, &startY);
// 
// 	wxPoint zoomedPoint(m_ptMouseDown.x+ppuX*startX, m_ptMouseDown.y+ppuY*startY);
// 
// 	m_CurrDragMode = CheckPointInConner(zoomedRect, zoomedPoint);
// 	if (m_CurrDragMode != PIC_UNKNOWN)
// 	{
// 		m_rectDrag = m_rectSelected;
// // 		this->CaptureMouse();
// 	}

	event.Skip();
}

void UIImageEditor::OnMouseLButtonUp(wxMouseEvent& event)
{
// 	if (m_CurrDragMode != PIC_UNKNOWN)
// 	{
// 		// TODO: apply drag
// 		m_CurrDragMode = PIC_UNKNOWN;
// // 		this->ReleaseMouse();
// 		Refresh(true);
// 	}

	event.Skip();
}

void UIImageEditor::OnSize(wxSizeEvent& event)
{
	UpdateVirtualSize();
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));

	if (m_bmpBackBuffer.GetSize() != GetClientSize())
	{
		m_dcBackBuffer.SelectObject(wxNullBitmap);
		m_bmpBackBuffer.Create(GetClientSize());
		m_dcBackBuffer.SelectObject(m_bmpBackBuffer);
	}

	event.Skip();
}

void UIImageEditor::OnScrollLineUp(wxScrollWinEvent& event)
{
	int nOrientation = event.GetOrientation();

	int nPos = GetScrollPos(nOrientation);
	SetScrollPos(nOrientation, nPos-SCROLL_LINE_DISTANCE, true);
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
}

void UIImageEditor::OnScrollLineDown(wxScrollWinEvent& event)
{
	int nOrientation = event.GetOrientation();

	int nPos = GetScrollPos(nOrientation);
	SetScrollPos(nOrientation, nPos+SCROLL_LINE_DISTANCE, true);
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
}

void UIImageEditor::OnScrollPageUp(wxScrollWinEvent& event)
{
	int nOrientation = event.GetOrientation();
	int nDistance = GetScrollThumb(nOrientation);
	int nPos = GetScrollPos(nOrientation);
	SetScrollPos(nOrientation, nPos-nDistance, true);
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
}

void UIImageEditor::OnScrollPageDown(wxScrollWinEvent& event)
{
	int nOrientation = event.GetOrientation();
	int nDistance = GetScrollThumb(nOrientation);
	int nPos = GetScrollPos(nOrientation);
	SetScrollPos(nOrientation, nPos+nDistance, true);
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
}

void UIImageEditor::OnScrollThumbTrack(wxScrollWinEvent& event)
{
	int nOrientation = event.GetOrientation();
	int nPos = event.GetPosition();
	if (nOrientation == wxHORIZONTAL)
	{
		UpdateScrollPosition(nPos, GetScrollPos(wxVERTICAL));
	}
	else
	{
		UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), nPos);
	}
}

void UIImageEditor::OnScrollThumbRelease(wxScrollWinEvent& event)
{
	int nOrientation = event.GetOrientation();
	int nPos = event.GetPosition();
	SetScrollPos(nOrientation, nPos, true);
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
}
