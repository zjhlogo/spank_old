/*!
 * \file ClipBitmapStyle.h
 * \date 2-14-2012 16:43:17
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __CLIPBITMAPSTYLE_H__
#define __CLIPBITMAPSTYLE_H__

#include "IStyle.h"
#include "PieceInfo.h"
#include <tinyxml-2.6.2/tinyxml.h>

class ClipBitmapStyle : public IStyle
{
public:
	ClipBitmapStyle();
	~ClipBitmapStyle();

	bool LoadFromXml(TiXmlElement* pElmClipBitmapStyle);
	bool SaveToXml(TiXmlElement* pElmClipBitmapStyleList);

	bool SetStatePiece(const PieceInfo* pPieceInfo, STYLE_STATE eState);
	const PieceInfo* GetStatePiece(STYLE_STATE eState) const;

private:
	const PieceInfo* LoadStateInfo(TiXmlElement* pElmClipBitmapStyle, const wxString& strState, const PieceInfo* pDefaultPieceInfo);
	bool SaveStateInfo(TiXmlElement* pElmClipBitmapStyle, const wxString& strState, const PieceInfo* pPieceInfo);

private:
	const PieceInfo* m_PieceInfo[SS_NUM];

};
#endif // __CLIPBITMAPSTYLE_H__
