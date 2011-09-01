/*!
 * \file UIDesignerFrame.cpp
 * \date 8-31-2011 13:20:00
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "UIDesignerFrame.h"
#include "UIImageEditor.h"
#include <wx/menu.h>
#include <wx/treectrl.h>

UIDesignerFrame::UIDesignerFrame()
:wxFrame(NULL, wxID_ANY, wxT("UI Designer"), wxDefaultPosition, wxSize(800, 600))
{
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
	wxMenuBar* menuBar = new wxMenuBar;
	wxMenu* itemMenu3 = new wxMenu;
	{
		wxMenuItem* menuItem = new wxMenuItem(itemMenu3, ID_FILE_NEW, _("&New...\tCtrl+N"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(_T("images/document--plus.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		itemMenu3->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(itemMenu3, ID_FILE_OPEN, _("&Open...\tCtrl+O"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(_T("images/folder-horizontal-open.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		itemMenu3->Append(menuItem);
	}
	itemMenu3->AppendSeparator();
	itemMenu3->Append(ID_FILE_CLOSE, _("&Close"), wxEmptyString, wxITEM_NORMAL);
	itemMenu3->AppendSeparator();
	{
		wxMenuItem* menuItem = new wxMenuItem(itemMenu3, ID_FILE_SAVE, _("&Save\tCtrl+S"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(_T("images/disk.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		itemMenu3->Append(menuItem);
	}
	itemMenu3->Append(ID_FILE_SAVE_AS, _("Save &As...\tCtrl+Shift+S"), wxEmptyString, wxITEM_NORMAL);
	itemMenu3->AppendSeparator();
	itemMenu3->Append(ID_FILE_EXIT, _("E&xit\tAlt+F4"), wxEmptyString, wxITEM_NORMAL);
	menuBar->Append(itemMenu3, _("&File"));
	wxMenu* itemMenu13 = new wxMenu;
	itemMenu13->Append(ID_EDIT_UNDO, _("&Undo\tCtrl+Z"), wxEmptyString, wxITEM_NORMAL);
	itemMenu13->Append(ID_EDIT_REDO, _("&Redo\tCtrl+Y"), wxEmptyString, wxITEM_NORMAL);
	itemMenu13->AppendSeparator();
	itemMenu13->Append(ID_EDIT_COPY, _("&Copy\tCtrl+C"), wxEmptyString, wxITEM_NORMAL);
	itemMenu13->Append(ID_EDIT_CUT, _("Cu&t\tCtrl+X"), wxEmptyString, wxITEM_NORMAL);
	itemMenu13->Append(ID_EDIT_PAST, _("&Past\tCtrl+V"), wxEmptyString, wxITEM_NORMAL);
	itemMenu13->Append(ID_EDIT_DELETE, _("&Delete\tDel"), wxEmptyString, wxITEM_NORMAL);
	menuBar->Append(itemMenu13, _("&Edit"));
	wxMenu* itemMenu21 = new wxMenu;
	wxMenu* itemMenu22 = new wxMenu;
	{
		wxMenuItem* menuItem = new wxMenuItem(itemMenu22, ID_LAYOUT_ALIGN_LEFT, _("Align &Left"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(_T("images/shape_aling_left.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		itemMenu22->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(itemMenu22, ID_LAYOUT_ALIGN_RIGHT, _("Align &Right"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(_T("images/shape_aling_right.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		itemMenu22->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(itemMenu22, ID_LAYOUT_ALIGN_TOP, _("Align &Top"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(_T("images/shape_aling_top.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		itemMenu22->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(itemMenu22, ID_LAYOUT_ALIGN_BOTTOM, _("Align &Bottom"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(_T("images/shape_aling_bottom.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		itemMenu22->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(itemMenu22, ID_LAYOUT_ALIGN_CENTER, _("Align &Center"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(_T("images/shape_aling_center.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		itemMenu22->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(itemMenu22, ID_LAYOUT_ALIGN_MIDDLE, _("Align &Middle"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(_T("images/shape_aling_middle.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		itemMenu22->Append(menuItem);
	}
	itemMenu21->Append(ID_LAYOUT_ALIGN, _("&Align"), itemMenu22);
	wxMenu* itemMenu29 = new wxMenu;
	itemMenu29->Append(ID_LAYOUT_MOVE_LEFT, _("Move &Left"), wxEmptyString, wxITEM_NORMAL);
	itemMenu29->Append(ID_LAYOUT_MOVE_RIGHT, _("Move &Right"), wxEmptyString, wxITEM_NORMAL);
	itemMenu29->Append(ID_LAYOUT_MOVE_UP, _("Move &Up"), wxEmptyString, wxITEM_NORMAL);
	itemMenu29->Append(ID_LAYOUT_MOVE_DOWN, _("Move &Down"), wxEmptyString, wxITEM_NORMAL);
	itemMenu21->Append(ID_LAYOUT_MOVE, _("&Move"), itemMenu29);
	menuBar->Append(itemMenu21, _("&Layout"));
	wxMenu* itemMenu34 = new wxMenu;
	itemMenu34->Append(ID_VIEW_GRID, _("Show &Grid\tCtrl+G"), wxEmptyString, wxITEM_CHECK);
	itemMenu34->Check(ID_VIEW_GRID, true);
	itemMenu34->AppendSeparator();
	{
		wxMenuItem* menuItem = new wxMenuItem(itemMenu34, ID_VIEW_ZOOM_FIXED, _("Zoom &Fixed\tCtrl+1"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(_T("images/zoom.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		itemMenu34->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(itemMenu34, ID_VIEW_ZOOM_IN, _("Zoom &In\tCtrl++"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(_T("images/zoom_in.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		itemMenu34->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(itemMenu34, ID_VIEW_ZOOM_OUT, _("Zoom &Out\tCtrl+-"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(_T("images/zoom_out.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		itemMenu34->Append(menuItem);
	}
	menuBar->Append(itemMenu34, _("&View"));
	wxMenu* itemMenu40 = new wxMenu;
	itemMenu40->Append(ID_TOOL_PREFERENCES, _("&Preferences..."), wxEmptyString, wxITEM_NORMAL);
	menuBar->Append(itemMenu40, _("&Tools"));
	wxMenu* itemMenu42 = new wxMenu;
	itemMenu42->Append(ID_HELP_SUPPORT, _("&Support"), wxEmptyString, wxITEM_NORMAL);
	itemMenu42->AppendSeparator();
	itemMenu42->Append(ID_HELP_ABOUT, _("&About\tF1"), wxEmptyString, wxITEM_NORMAL);
	menuBar->Append(itemMenu42, _("&Help"));
	SetMenuBar(menuBar);
}

void UIDesignerFrame::CreateToolbar()
{
	wxAuiToolBar* itemAuiToolBar46 = new wxAuiToolBar( this, ID_TOOLBAR, wxDefaultPosition, wxDefaultSize, 0 );
	wxBitmap itemtool47Bitmap(wxT("images/document--plus.png"), wxBITMAP_TYPE_PNG);
	wxBitmap itemtool47BitmapDisabled;
	itemAuiToolBar46->AddTool(ID_FILE_NEW, wxEmptyString, itemtool47Bitmap, itemtool47BitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	wxBitmap itemtool48Bitmap(wxT("images/folder-horizontal-open.png"), wxBITMAP_TYPE_PNG);
	wxBitmap itemtool48BitmapDisabled;
	itemAuiToolBar46->AddTool(ID_FILE_OPEN, wxEmptyString, itemtool48Bitmap, itemtool48BitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	wxBitmap itemtool49Bitmap(wxT("images/disk.png"), wxBITMAP_TYPE_PNG);
	wxBitmap itemtool49BitmapDisabled;
	itemAuiToolBar46->AddTool(ID_FILE_SAVE, wxEmptyString, itemtool49Bitmap, itemtool49BitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	itemAuiToolBar46->AddSeparator();
	wxBitmap itemtool51Bitmap(wxT("images/shape_aling_left.png"), wxBITMAP_TYPE_PNG);
	wxBitmap itemtool51BitmapDisabled;
	itemAuiToolBar46->AddTool(ID_LAYOUT_ALIGN_LEFT, wxEmptyString, itemtool51Bitmap, itemtool51BitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	wxBitmap itemtool52Bitmap(wxT("images/shape_aling_right.png"), wxBITMAP_TYPE_PNG);
	wxBitmap itemtool52BitmapDisabled;
	itemAuiToolBar46->AddTool(ID_LAYOUT_ALIGN_RIGHT, wxEmptyString, itemtool52Bitmap, itemtool52BitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	wxBitmap itemtool53Bitmap(wxT("images/shape_aling_top.png"), wxBITMAP_TYPE_PNG);
	wxBitmap itemtool53BitmapDisabled;
	itemAuiToolBar46->AddTool(ID_LAYOUT_ALIGN_TOP, wxEmptyString, itemtool53Bitmap, itemtool53BitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	wxBitmap itemtool54Bitmap(wxT("images/shape_aling_bottom.png"), wxBITMAP_TYPE_PNG);
	wxBitmap itemtool54BitmapDisabled;
	itemAuiToolBar46->AddTool(ID_LAYOUT_ALIGN_BOTTOM, wxEmptyString, itemtool54Bitmap, itemtool54BitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	wxBitmap itemtool55Bitmap(wxT("images/shape_aling_center.png"), wxBITMAP_TYPE_PNG);
	wxBitmap itemtool55BitmapDisabled;
	itemAuiToolBar46->AddTool(ID_LAYOUT_ALIGN_CENTER, wxEmptyString, itemtool55Bitmap, itemtool55BitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	wxBitmap itemtool56Bitmap(wxT("images/shape_aling_middle.png"), wxBITMAP_TYPE_PNG);
	wxBitmap itemtool56BitmapDisabled;
	itemAuiToolBar46->AddTool(ID_LAYOUT_ALIGN_MIDDLE, wxEmptyString, itemtool56Bitmap, itemtool56BitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	itemAuiToolBar46->AddSeparator();
	wxBitmap itemtool58Bitmap(wxT("images/zoom.png"), wxBITMAP_TYPE_PNG);
	wxBitmap itemtool58BitmapDisabled;
	itemAuiToolBar46->AddTool(ID_VIEW_ZOOM_FIXED, wxEmptyString, itemtool58Bitmap, itemtool58BitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	wxBitmap itemtool59Bitmap(wxT("images/zoom_in.png"), wxBITMAP_TYPE_PNG);
	wxBitmap itemtool59BitmapDisabled;
	itemAuiToolBar46->AddTool(ID_VIEW_ZOOM_IN, wxEmptyString, itemtool59Bitmap, itemtool59BitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	wxBitmap itemtool60Bitmap(wxT("images/zoom_out.png"), wxBITMAP_TYPE_PNG);
	wxBitmap itemtool60BitmapDisabled;
	itemAuiToolBar46->AddTool(ID_VIEW_ZOOM_OUT, wxEmptyString, itemtool60Bitmap, itemtool60BitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	itemAuiToolBar46->Realize();
	m_auiManager.AddPane(itemAuiToolBar46, wxAuiPaneInfo()
		.Name(_T("Toolbar")).Top().Layer(1).Dockable(false).CaptionVisible(false).CloseButton(false).DestroyOnClose(false).Resizable(true).Floatable(false).Movable(false).PaneBorder(false));
}

void UIDesignerFrame::CreateProjectControl()
{
	wxTreeCtrl* itemTreeCtrl61 = new wxTreeCtrl( this, IDC_PROJECT, wxDefaultPosition, wxSize(100, 100), wxTR_SINGLE|wxNO_BORDER );
	m_auiManager.AddPane(itemTreeCtrl61, wxAuiPaneInfo()
		.Name(_T("Project")).Caption(_("Project")).BestSize(wxSize(300, 300)).Layer(1).CloseButton(false).DestroyOnClose(false).Resizable(true).Floatable(false).FloatingSize(wxSize(300, 500)).Movable(false));
}

void UIDesignerFrame::CreatePropertyControl()
{
	wxTextCtrl* itemTextCtrl62 = new wxTextCtrl( this, IDC_PROPERTY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxNO_BORDER );
	m_auiManager.AddPane(itemTextCtrl62, wxAuiPaneInfo()
		.Name(_T("Property")).Caption(_("Property")).Right().BestSize(wxSize(300, 300)).Position(1).CloseButton(false).DestroyOnClose(false).Resizable(true).Floatable(false).FloatingSize(wxSize(300, 500)).Movable(false));
}

void UIDesignerFrame::CreateInputView()
{
	UIImageEditor* pImageEditor = new UIImageEditor( this, ID_INPUT_VIEW, wxDefaultPosition, wxSize(200, 200), wxNO_BORDER );
	m_auiManager.AddPane(pImageEditor, wxAuiPaneInfo()
		.Name(_T("Input")).Caption(_("Input")).Centre().CaptionVisible(false).CloseButton(false).DestroyOnClose(false).Resizable(true).Floatable(false).Movable(false));

	pImageEditor->OpenBitmap(wxT("test.png"));
}

void UIDesignerFrame::CreateOutputView()
{
	wxWindow* itemWindow64 = new wxWindow( this, ID_OUTPUT_VIEW, wxDefaultPosition, wxSize(100, 100), wxNO_BORDER );
	m_auiManager.AddPane(itemWindow64, wxAuiPaneInfo()
		.Name(_T("Output")).Caption(_("Output")).Bottom().BestSize(wxSize(300, 300)).CloseButton(false).DestroyOnClose(false).Resizable(true).Floatable(false).FloatingSize(wxSize(500, 200)).Movable(false));
}
