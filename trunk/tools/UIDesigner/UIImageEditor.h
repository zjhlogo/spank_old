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

class UIImageEditor : public wxScrolledWindow
{
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

private:
	void Init();

	void OnMouseWhell(wxMouseEvent& event);

private:
	wxBitmap* m_pBitmap;

};
#endif // __UIIMAGEEDITOR_H__
