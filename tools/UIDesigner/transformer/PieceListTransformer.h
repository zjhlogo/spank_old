/*!
 * \file PieceListTransformer.h
 * \date 2-14-2012 1:25:10
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __PIECELISTTRANSFORMER_H__
#define __PIECELISTTRANSFORMER_H__

#include <wx/treectrl.h>
#include "../document/PieceInfo.h"

class PieceListTransformer
{
public:
	static PieceListTransformer& GetInstance();

	bool Initialize(wxTreeCtrl* pTreeCtrl);
	void UpdateListView();

	PieceInfo* GetSelectedPieceInfo();
	void SetSelectedItem(PieceInfo* pPieceInfo);

protected:
	PieceListTransformer();
	~PieceListTransformer();

private:
	wxTreeCtrl* m_pListView;

};
#endif // __PIECELISTTRANSFORMER_H__