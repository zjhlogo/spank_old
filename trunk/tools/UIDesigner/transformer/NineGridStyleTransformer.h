/*!
 * \file NineGridStyleTransformer.h
 * \date 2-14-2012 16:08:10
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __NINEGRIDSTYLETRANSFORMER_H__
#define __NINEGRIDSTYLETRANSFORMER_H__

#include <wx/treectrl.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include "../document/NineGridStyle.h"

class NineGridStyleTransformer
{
public:
	static NineGridStyleTransformer& GetInstance();

	bool Initialize(wxTreeCtrl* pTreeCtrl, wxPropertyGrid* pPropertyGrid);
	void UpdateListView();
	void UpdateProperty(NineGridStyle* pNineGrieStyle);

	void SetSelectedNineGridStyle(NineGridStyle* pNineGrieStyle);
	NineGridStyle* GetSelectedNineGridStyle();

protected:
	NineGridStyleTransformer();
	~NineGridStyleTransformer();

private:
	wxTreeCtrl* m_pListView;
	wxPropertyGrid* m_pPropertyGrid;

};
#endif // __NINEGRIDSTYLETRANSFORMER_H__
