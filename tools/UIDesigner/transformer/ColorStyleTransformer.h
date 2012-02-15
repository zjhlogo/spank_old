/*!
 * \file ColorStyleTransformer.h
 * \date 2-14-2012 17:00:43
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __COLORSTYLETRANSFORMER_H__
#define __COLORSTYLETRANSFORMER_H__

#include <wx/treectrl.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include "../document/ColorStyle.h"

class ColorStyleTransformer
{
public:
	static ColorStyleTransformer& GetInstance();

	bool Initialize(wxTreeCtrl* pTreeCtrl, wxPropertyGrid* pPropertyGrid);
	void UpdateListView();
	void UpdateProperty(ColorStyle* pColorStyle);
	void PropertyChanged(wxPGProperty* pProperty);

	void SetSelectedColorStyle(ColorStyle* pColorStyle);
	ColorStyle* GetSelectedColorStyle();

protected:
	ColorStyleTransformer();
	~ColorStyleTransformer();

private:
	wxTreeCtrl* m_pListView;
	wxPropertyGrid* m_pPropertyGrid;

};
#endif // __COLORSTYLETRANSFORMER_H__
