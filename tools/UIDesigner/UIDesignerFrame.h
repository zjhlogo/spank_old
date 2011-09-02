/*!
 * \file UIDesignerFrame.h
 * \date 8-31-2011 13:11:14
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __UIDESIGNERFRAME_H__
#define __UIDESIGNERFRAME_H__

#include <wx/frame.h>
#include <wx/aui/aui.h>
#include "UIImageEditor.h"

class UIDesignerFrame : public wxFrame
{
public:
	enum CONTROL_ID
	{
		ID_UIDESIGNERFRAME = 10000,
		ID_FILE_NEW = 10018,
		ID_FILE_OPEN = 10019,
		ID_FILE_CLOSE = 10022,
		ID_FILE_SAVE = 10020,
		ID_FILE_SAVE_AS = 10021,
		ID_FILE_EXIT = 10023,
		ID_EDIT_UNDO = 10048,
		ID_EDIT_REDO = 10049,
		ID_EDIT_COPY = 10025,
		ID_EDIT_CUT = 10026,
		ID_EDIT_PAST = 10027,
		ID_EDIT_DELETE = 10050,
		ID_LAYOUT_ALIGN = 10051,
		ID_LAYOUT_ALIGN_LEFT = 10028,
		ID_LAYOUT_ALIGN_RIGHT = 10029,
		ID_LAYOUT_ALIGN_TOP = 10030,
		ID_LAYOUT_ALIGN_BOTTOM = 10031,
		ID_LAYOUT_ALIGN_CENTER = 10032,
		ID_LAYOUT_ALIGN_MIDDLE = 10033,
		ID_LAYOUT_MOVE = 10052,
		ID_LAYOUT_MOVE_LEFT = 10052,
		ID_LAYOUT_MOVE_RIGHT = 10035,
		ID_LAYOUT_MOVE_UP = 10036,
		ID_LAYOUT_MOVE_DOWN = 10037,
		ID_VIEW_GRID = 10038,
		ID_VIEW_ZOOM_FIXED = 10045,
		ID_VIEW_ZOOM_IN = 10046,
		ID_VIEW_ZOOM_OUT = 10047,
		ID_TOOL_PREFERENCES = 10042,
		ID_HELP_SUPPORT = 10043,
		ID_HELP_ABOUT = 10044,
		ID_TOOLBAR = 10018,
		IDC_PROJECT = 10003,
		IDC_PROPERTY = 10002,
		ID_INPUT_VIEW = 10004,
		ID_OUTPUT_VIEW = 10001
	};

public:
	DECLARE_DYNAMIC_CLASS(UIDesignerFrame)
	DECLARE_EVENT_TABLE()

public:
	UIDesignerFrame();
	virtual ~UIDesignerFrame();

private:
	void CreateControls();
	void CreateMenu();
	void CreateToolbar();
	void CreateProjectControl();
	void CreatePropertyControl();
	void CreateInputView();
	void CreateOutputView();

	void OnZoomIn(wxCommandEvent& event);
	void OnZoomOut(wxCommandEvent& event);
	void OnZoomFixed(wxCommandEvent& event);

private:
	wxAuiManager m_auiManager;
	UIImageEditor* m_pImageEditor;

};
#endif // __UIDESIGNERFRAME_H__
