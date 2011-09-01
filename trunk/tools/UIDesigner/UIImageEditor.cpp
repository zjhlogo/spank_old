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
	EVT_MOUSEWHEEL(UIImageEditor::OnMouseWhell)
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
	delete m_pBitmap;
}

bool UIImageEditor::Create(wxWindow *parent, wxWindowID winid /*= wxID_ANY*/, const wxPoint& pos /*= wxDefaultPosition*/, const wxSize& size /*= wxDefaultSize*/, long style /*= wxScrolledWindowStyle*/, const wxString& name /*= wxPanelNameStr*/)
{
	if (!wxScrolledWindow::Create(parent, winid, pos, size, style, name)) return false;

	SetScrollRate(1, 1);
	return true;
}

wxSize UIImageEditor::DoGetBestSize() const
{
	// TODO: 
	return wxSize(2000, 2000);
}

void UIImageEditor::Init()
{
	m_pBitmap = NULL;
}

void UIImageEditor::OnDraw(wxDC& dc)
{
	if (!m_pBitmap) return;

	dc.DrawBitmap(*m_pBitmap, 0, 0);
}

void UIImageEditor::OnMouseWhell(wxMouseEvent& event)
{
	int lines = -event.GetWheelRotation() / event.GetWheelDelta();

	wxPoint pt = GetViewStart();

	if (event.ShiftDown())
	{
		Scroll(pt.x + lines * event.GetLinesPerAction() * 30, pt.y);
	}
	else
	{
		Scroll(pt.x, pt.y + lines * event.GetLinesPerAction() * 30);
	}
}

bool UIImageEditor::OpenBitmap(const wxString& path)
{
	if (!m_pBitmap) m_pBitmap = new wxBitmap();

	if (!m_pBitmap->LoadFile(path, wxBITMAP_TYPE_PNG)) return false;

	wxSize size = m_pBitmap->GetSize();
	SetVirtualSize(size.x, size.y);

	return true;
}
