/*!
 * \file UIDesignerFrame.cpp
 * \date 8-31-2011 13:20:00
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "UIDesignerFrame.h"
#include <wx/menu.h>
#include <wx/treectrl.h>

BEGIN_EVENT_TABLE(UIDesignerFrame, wxFrame)
	EVT_MENU(UIDesignerFrame::ID_VIEW_ZOOM_FIXED, UIDesignerFrame::OnZoomFixed)
	EVT_MENU(UIDesignerFrame::ID_VIEW_ZOOM_IN, UIDesignerFrame::OnZoomIn)
	EVT_MENU(UIDesignerFrame::ID_VIEW_ZOOM_OUT, UIDesignerFrame::OnZoomOut)
END_EVENT_TABLE()

IMPLEMENT_DYNAMIC_CLASS(UIDesignerFrame, wxFrame)

UIDesignerFrame::UIDesignerFrame()
:wxFrame(NULL, wxID_ANY, wxT("UI Designer"), wxDefaultPosition, wxSize(800, 600))
{
	m_pImageEditor = NULL;
	CreateControls();
}

UIDesignerFrame::~UIDesignerFrame()
{
	m_auiManager.UnInit();
}

void UIDesignerFrame::CreateControls()
{
	m_auiManager.SetManagedWindow(this);

	CreateMenu();
	CreateToolbar();
	CreateProjectControl();
	CreatePropertyControl();
	CreateInputView();
	CreateOutputView();

	m_auiManager.Update();
}

void UIDesignerFrame::CreateMenu()
{
	wxMenuBar* pMenuBar = new wxMenuBar();

	// file
	wxMenu* pMenuItemFile = new wxMenu();
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemFile, ID_FILE_NEW, wxT("&New...\tCtrl+N"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(wxT("images/document--plus.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		pMenuItemFile->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemFile, ID_FILE_OPEN, wxT("&Open...\tCtrl+O"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(wxT("images/folder-horizontal-open.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		pMenuItemFile->Append(menuItem);
	}
	pMenuItemFile->AppendSeparator();
	pMenuItemFile->Append(ID_FILE_CLOSE, wxT("&Close"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemFile->AppendSeparator();
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemFile, ID_FILE_SAVE, wxT("&Save\tCtrl+S"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(wxT("images/disk.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		pMenuItemFile->Append(menuItem);
	}
	pMenuItemFile->Append(ID_FILE_SAVE_AS, wxT("Save &As...\tCtrl+Shift+S"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemFile->AppendSeparator();
	pMenuItemFile->Append(ID_FILE_EXIT, wxT("E&xit\tAlt+F4"), wxEmptyString, wxITEM_NORMAL);
	pMenuBar->Append(pMenuItemFile, wxT("&File"));

	// edit
	wxMenu* pMenuItemEdit = new wxMenu();
	pMenuItemEdit->Append(ID_EDIT_UNDO, wxT("&Undo\tCtrl+Z"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemEdit->Append(ID_EDIT_REDO, wxT("&Redo\tCtrl+Y"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemEdit->AppendSeparator();
	pMenuItemEdit->Append(ID_EDIT_COPY, wxT("&Copy\tCtrl+C"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemEdit->Append(ID_EDIT_CUT, wxT("Cu&t\tCtrl+X"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemEdit->Append(ID_EDIT_PAST, wxT("&Past\tCtrl+V"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemEdit->Append(ID_EDIT_DELETE, wxT("&Delete\tDel"), wxEmptyString, wxITEM_NORMAL);
	pMenuBar->Append(pMenuItemEdit, wxT("&Edit"));

	// layer
	wxMenu* pMenuItemLayer = new wxMenu();
	wxMenu* pMenuItemLayerAlign = new wxMenu();
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemLayerAlign, ID_LAYOUT_ALIGN_LEFT, wxT("Align &Left"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(wxT("images/shape_aling_left.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		pMenuItemLayerAlign->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemLayerAlign, ID_LAYOUT_ALIGN_RIGHT, wxT("Align &Right"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(wxT("images/shape_aling_right.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		pMenuItemLayerAlign->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemLayerAlign, ID_LAYOUT_ALIGN_TOP, wxT("Align &Top"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(wxT("images/shape_aling_top.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		pMenuItemLayerAlign->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemLayerAlign, ID_LAYOUT_ALIGN_BOTTOM, wxT("Align &Bottom"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(wxT("images/shape_aling_bottom.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		pMenuItemLayerAlign->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemLayerAlign, ID_LAYOUT_ALIGN_CENTER, wxT("Align &Center"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(wxT("images/shape_aling_center.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		pMenuItemLayerAlign->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemLayerAlign, ID_LAYOUT_ALIGN_MIDDLE, wxT("Align &Middle"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(wxT("images/shape_aling_middle.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		pMenuItemLayerAlign->Append(menuItem);
	}
	pMenuItemLayer->Append(ID_LAYOUT_ALIGN, wxT("&Align"), pMenuItemLayerAlign);
	wxMenu* pMenuItemLayerMove = new wxMenu();
	pMenuItemLayerMove->Append(ID_LAYOUT_MOVE_LEFT, wxT("Move &Left"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemLayerMove->Append(ID_LAYOUT_MOVE_RIGHT, wxT("Move &Right"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemLayerMove->Append(ID_LAYOUT_MOVE_UP, wxT("Move &Up"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemLayerMove->Append(ID_LAYOUT_MOVE_DOWN, wxT("Move &Down"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemLayer->Append(ID_LAYOUT_MOVE, wxT("&Move"), pMenuItemLayerMove);
	pMenuBar->Append(pMenuItemLayer, wxT("&Layout"));

	// view
	wxMenu* pMenuItemView = new wxMenu();
	pMenuItemView->Append(ID_VIEW_GRID, wxT("Show &Grid\tCtrl+G"), wxEmptyString, wxITEM_CHECK);
	pMenuItemView->Check(ID_VIEW_GRID, true);
	pMenuItemView->AppendSeparator();
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemView, ID_VIEW_ZOOM_FIXED, wxT("Zoom &Fixed\tCtrl+1"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(wxT("images/zoom.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		pMenuItemView->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemView, ID_VIEW_ZOOM_IN, wxT("Zoom &In\tCtrl++"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(wxT("images/zoom_in.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		pMenuItemView->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemView, ID_VIEW_ZOOM_OUT, wxT("Zoom &Out\tCtrl+-"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(wxT("images/zoom_out.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		pMenuItemView->Append(menuItem);
	}
	pMenuBar->Append(pMenuItemView, wxT("&View"));

	// tool
	wxMenu* pMenuItemTool = new wxMenu();
	pMenuItemTool->Append(ID_TOOL_PREFERENCES, wxT("&Preferences..."), wxEmptyString, wxITEM_NORMAL);
	pMenuBar->Append(pMenuItemTool, wxT("&Tools"));

	// help
	wxMenu* pMenuItemHelp = new wxMenu();
	pMenuItemHelp->Append(ID_HELP_SUPPORT, wxT("&Support"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemHelp->AppendSeparator();
	pMenuItemHelp->Append(ID_HELP_ABOUT, wxT("&About\tF1"), wxEmptyString, wxITEM_NORMAL);
	pMenuBar->Append(pMenuItemHelp, wxT("&Help"));

	SetMenuBar(pMenuBar);
}

void UIDesignerFrame::CreateToolbar()
{
	wxAuiToolBar* pAuiToolBar = new wxAuiToolBar(this, ID_TOOLBAR, wxDefaultPosition, wxDefaultSize, 0);

	{
		wxBitmap bitmap(wxT("images/document--plus.png"), wxBITMAP_TYPE_PNG);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(ID_FILE_NEW, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	{
		wxBitmap bitmap(wxT("images/folder-horizontal-open.png"), wxBITMAP_TYPE_PNG);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(ID_FILE_OPEN, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	{
		wxBitmap bitmap(wxT("images/disk.png"), wxBITMAP_TYPE_PNG);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(ID_FILE_SAVE, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	pAuiToolBar->AddSeparator();

	{
		wxBitmap bitmap(wxT("images/shape_aling_left.png"), wxBITMAP_TYPE_PNG);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(ID_LAYOUT_ALIGN_LEFT, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	{
		wxBitmap bitmap(wxT("images/shape_aling_right.png"), wxBITMAP_TYPE_PNG);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(ID_LAYOUT_ALIGN_RIGHT, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	{
		wxBitmap bitmap(wxT("images/shape_aling_top.png"), wxBITMAP_TYPE_PNG);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(ID_LAYOUT_ALIGN_TOP, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	{
		wxBitmap bitmap(wxT("images/shape_aling_bottom.png"), wxBITMAP_TYPE_PNG);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(ID_LAYOUT_ALIGN_BOTTOM, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	{
		wxBitmap bitmap(wxT("images/shape_aling_center.png"), wxBITMAP_TYPE_PNG);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(ID_LAYOUT_ALIGN_CENTER, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	{
		wxBitmap bitmap(wxT("images/shape_aling_middle.png"), wxBITMAP_TYPE_PNG);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(ID_LAYOUT_ALIGN_MIDDLE, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	pAuiToolBar->AddSeparator();

	{
		wxBitmap bitmap(wxT("images/zoom.png"), wxBITMAP_TYPE_PNG);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(ID_VIEW_ZOOM_FIXED, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	{
		wxBitmap bitmap(wxT("images/zoom_in.png"), wxBITMAP_TYPE_PNG);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(ID_VIEW_ZOOM_IN, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	{
		wxBitmap bitmap(wxT("images/zoom_out.png"), wxBITMAP_TYPE_PNG);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(ID_VIEW_ZOOM_OUT, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	pAuiToolBar->Realize();

	m_auiManager.AddPane(pAuiToolBar, wxAuiPaneInfo()
		.Name(wxT("Toolbar"))
		.Top()
		.Layer(1)
		.Dockable(false)
		.CaptionVisible(false)
		.CloseButton(false)
		.DestroyOnClose(false)
		.Resizable(true)
		.Floatable(false)
		.Movable(false)
		.PaneBorder(false));
}

void UIDesignerFrame::CreateProjectControl()
{
	wxTreeCtrl* pProject = new wxTreeCtrl(this, IDC_PROJECT, wxDefaultPosition, wxSize(100, 100), wxTR_SINGLE|wxNO_BORDER);

	m_auiManager.AddPane(pProject, wxAuiPaneInfo()
		.Name(wxT("Project"))
		.Caption(wxT("Project"))
		.BestSize(wxSize(300, 300))
		.Layer(1)
		.CloseButton(false)
		.DestroyOnClose(false)
		.Resizable(true)
		.Floatable(false)
		.FloatingSize(wxSize(300, 500))
		.Movable(false));
}

void UIDesignerFrame::CreatePropertyControl()
{
	wxTextCtrl* pProperty = new wxTextCtrl(this, IDC_PROPERTY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);

	m_auiManager.AddPane(pProperty, wxAuiPaneInfo()
		.Name(wxT("Property"))
		.Caption(wxT("Property"))
		.Right()
		.BestSize(wxSize(300, 300))
		.Position(1)
		.CloseButton(false)
		.DestroyOnClose(false)
		.Resizable(true)
		.Floatable(false)
		.FloatingSize(wxSize(300, 500))
		.Movable(false));
}

void UIDesignerFrame::CreateInputView()
{
	m_pImageEditor = new UIImageEditor( this, ID_INPUT_VIEW, wxDefaultPosition, wxSize(200, 200), wxNO_BORDER );

	m_auiManager.AddPane(m_pImageEditor, wxAuiPaneInfo()
		.Name(wxT("Input"))
		.Caption(wxT("Input"))
		.Centre()
		.CaptionVisible(false)
		.CloseButton(false)
		.DestroyOnClose(false)
		.Resizable(true)
		.Floatable(false)
		.Movable(false));

	m_pImageEditor->LoadBitmapFile(wxT("test.png"));
}

void UIDesignerFrame::CreateOutputView()
{
	wxWindow* pOutputView = new wxWindow(this, ID_OUTPUT_VIEW, wxDefaultPosition, wxSize(100, 100), wxNO_BORDER);

	m_auiManager.AddPane(pOutputView, wxAuiPaneInfo()
		.Name(wxT("Output"))
		.Caption(wxT("Output"))
		.Bottom()
		.BestSize(wxSize(300, 300))
		.CloseButton(false)
		.DestroyOnClose(false)
		.Resizable(true)
		.Floatable(false)
		.FloatingSize(wxSize(500, 200))
		.Movable(false));
}

void UIDesignerFrame::OnZoomIn(wxCommandEvent& event)
{
	m_pImageEditor->ZoomIn();
}

void UIDesignerFrame::OnZoomOut(wxCommandEvent& event)
{
	m_pImageEditor->ZoomOut();
}

void UIDesignerFrame::OnZoomFixed(wxCommandEvent& event)
{
	m_pImageEditor->Zoom(UIImageEditor::ZOOM_MIN);
}
