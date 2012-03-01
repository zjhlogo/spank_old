/*!
 * \file ImageInfo.h
 * \date 2-13-2012 19:34:28
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IMAGEINFO_H__
#define __IMAGEINFO_H__

#include <wx/wx.h>
#include <wx/treectrl.h>
#include <wx/xml/xml.h>

class ImageInfo
{
public:
	ImageInfo();
	~ImageInfo();

	bool LoadFromXml(wxXmlNode* pNodeImage);
	bool SaveToXml(wxXmlNode* pNodeImageList);
	bool SaveImage();

	void SetId(const wxString& strId);
	const wxString& GetId() const;

	void SetPath(const wxString& strPath);
	const wxString& GetPath() const;

	bool SetBitmap(wxBitmap* pBitmap);
	const wxBitmap* GetBitmap();

	void SetTreeItemId(const wxTreeItemId& itemId);
	const wxTreeItemId& GetTreeItemId() const;

	bool ClearBitmapArea(const wxRect& rect);

private:
	bool LoadImageFromFile();

private:
	wxString m_strId;
	wxString m_strPath;
	wxBitmap* m_pBitmap;
	bool m_bLoaded;
	bool m_bIsModified;
	wxTreeItemId m_TreeItemId;

};
#endif // __IMAGEINFO_H__
