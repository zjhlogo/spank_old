/*!
 * \file UIImageEditor.h
 * \date 01-09-2011 21:21:40
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __UIIMAGEEDITOR_H__
#define __UIIMAGEEDITOR_H__

#include <wx/scrolwin.h>
#include <wx/bitmap.h>
#include <wx/dcmemory.h>

class UIImageEditor : public wxScrolledWindow
{
public:
	enum CONST_DEFINE
	{
		MOUSE_WHEEL_DISTANCE = 10,
		ZOOM_MIN = 1,
		ZOOM_STEP = 1,
		ZOOM_MAX = 10,
		RECT_SPOT_SIZE = 2,
		RECT_SENSOR_SIZE = 4,
	};

	enum POINT_IN_CONNER
	{
		PIC_UNKNOWN = 0,
		PIC_TOP_LEFT,
		PIC_TOP_CENTER,
		PIC_TOP_RIGHT,
		PIC_MIDDLE_LEFT,
		PIC_MIDDLE_CENTER,
		PIC_MIDDLE_RIGHT,
		PIC_BOTTOM_LEFT,
		PIC_BOTTOM_CENTER,
		PIC_BOTTOM_RIGHT,
	};

	enum CURSOR_TYPE
	{
		CT_DEFAULT = 0,
		CT_HORIZONTAL,
		CT_VERTICAL,
		CT_DIAGONAL,
		CT_DIAGONAL_INV,
		CT_MOVE,
		NUM_CT,
	};

public:
	DECLARE_DYNAMIC_CLASS(UIImageEditor)
	DECLARE_EVENT_TABLE()

public:
	UIImageEditor();
	UIImageEditor(wxWindow *parent,
		wxWindowID winid = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxScrolledWindowStyle,
		const wxString& name = wxPanelNameStr);

	virtual ~UIImageEditor();

	bool Create(wxWindow *parent,
		wxWindowID winid = wxID_ANY,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = wxScrolledWindowStyle,
		const wxString& name = wxPanelNameStr);

	virtual wxSize DoGetBestSize() const;

	virtual void OnDraw(wxDC& dc);

	bool OpenBitmap(const wxString& path);

	bool ZoomIn();
	bool ZoomOut();
	bool Zoom(int zoom);
	int GetZoom() const;

private:
	void Init();
	void UpdateVirtualSize();
	void DrawSelectedRect(wxDC& dc, const wxRect& rect);
	void DrawDragRect(wxDC& dc, const wxRect& rect);
	POINT_IN_CONNER CheckPointInConner(const wxRect& rect, const wxPoint& pt);
	void SetCursorByType(CURSOR_TYPE eType);

	void OnMouseWheel(wxMouseEvent& event);
	void OnMouseMove(wxMouseEvent& event);
	void OnMouseLButtonDown(wxMouseEvent& event);
	void OnMouseLButtonUp(wxMouseEvent& event);

private:
	wxBitmap m_bmpDC;
	wxBitmap m_bmpGrid;
	wxMemoryDC m_dcMemory;

	int m_nZoom;

	wxPen m_penBlue;
	wxPen m_penRed;
	wxBrush m_brushTransparent;
	wxBrush m_brushBlue;
	wxBrush m_brushGrid;

	wxRect m_rectSelected;
	wxRect m_rectDrag;

	wxCursor* m_pCursors[NUM_CT];
	CURSOR_TYPE m_eCurType;

	POINT_IN_CONNER m_CurrDragMode;
	wxPoint m_ptMouseDown;

};
#endif // __UIIMAGEEDITOR_H__
