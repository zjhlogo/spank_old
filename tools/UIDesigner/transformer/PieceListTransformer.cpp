/*!
 * \file PieceListTransformer.cpp
 * \date 2-14-2012 1:25:18
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "PieceListTransformer.h"
#include "../DesignerFrame.h"
#include "../document/ImagePieceDocument.h"

PieceListTransformer::PieceListTransformer()
{
	m_pListView = NULL;
	m_pPropertyGrid = NULL;
}

PieceListTransformer::~PieceListTransformer()
{
	// TODO: 
}

PieceListTransformer& PieceListTransformer::GetInstance()
{
	static PieceListTransformer s_ImagePieceListTransformer;
	return s_ImagePieceListTransformer;
}

bool PieceListTransformer::Initialize(wxTreeCtrl* pTreeCtrl, wxPropertyGrid* pPropertyGrid)
{
	m_pListView = pTreeCtrl;
	m_pPropertyGrid = pPropertyGrid;
	return true;
}

void PieceListTransformer::UpdateListView()
{
	m_pListView->DeleteAllItems();
	wxTreeItemId rootItem = m_pListView->AddRoot(wxT("PieceList"));

	const ImagePieceDocument::TM_PIECE_INFO& pieceInfoMap = ImagePieceDocument::GetInstance().GetPieceInfoMap();
	for (ImagePieceDocument::TM_PIECE_INFO::const_iterator it = pieceInfoMap.begin(); it != pieceInfoMap.end(); ++it)
	{
		PieceInfo* pPieceInfo = it->second;
		wxTreeItemId itemId = m_pListView->AppendItem(rootItem, pPieceInfo->GetId());
		((PieceInfo*)pPieceInfo)->SetTreeItemId(itemId);
	}
	m_pListView->ExpandAll();
}

void PieceListTransformer::UpdateProperty(const PieceInfo* pPieceInfo)
{
	m_pPropertyGrid->Clear();
	DesignerFrame::GetInstance().SetCurrPropertyType(DesignerFrame::PT_UNKNOWN);
	if (!pPieceInfo) return;

	m_pPropertyGrid->Append(new wxStringProperty("id", "id", pPieceInfo->GetId()));
	m_pPropertyGrid->Append(new wxStringProperty("image_id", "image_id", pPieceInfo->GetImageInfo()->GetId()))->Enable(false);

	m_pPropertyGrid->Append(new wxPropertyCategory("position", "position"));
	m_pPropertyGrid->Append(new wxIntProperty("x", "x", pPieceInfo->GetRect().x))->Enable(false);
	m_pPropertyGrid->Append(new wxIntProperty("y", "y", pPieceInfo->GetRect().y))->Enable(false);

	m_pPropertyGrid->Append(new wxPropertyCategory("size", "size"));
	m_pPropertyGrid->Append(new wxIntProperty("width", "width", pPieceInfo->GetRect().width))->Enable(false);
	m_pPropertyGrid->Append(new wxIntProperty("height", "height", pPieceInfo->GetRect().height))->Enable(false);

	DesignerFrame::GetInstance().SetCurrPropertyType(DesignerFrame::PT_PIECE);
}

void PieceListTransformer::PropertyChanged(const wxPGProperty* pProperty)
{
	const PieceInfo* pPieceInfo = GetSelectedPieceInfo();
	if (!pPieceInfo) return;

	if (pProperty->GetName() == "id")
	{
		wxString strNewId = pProperty->GetValueAsString();
		if (ImagePieceDocument::GetInstance().RenamePieceInfoId(pPieceInfo, strNewId))
		{
			PieceListTransformer::GetInstance().UpdateListView();
			PieceListTransformer::GetInstance().SetSelectedPieceInfo(pPieceInfo);
		}
	}
}

void PieceListTransformer::SetSelectedPieceInfo(const PieceInfo* pPieceInfo)
{
	if (!pPieceInfo) return;

	m_pListView->SelectItem(pPieceInfo->GetTreeItemId(), true);
}

const PieceInfo* PieceListTransformer::GetSelectedPieceInfo()
{
	wxString strPieceId = m_pListView->GetItemText(m_pListView->GetSelection());
	const PieceInfo* pPieceInfo = ImagePieceDocument::GetInstance().FindPieceInfo(strPieceId);
	return pPieceInfo;
}
