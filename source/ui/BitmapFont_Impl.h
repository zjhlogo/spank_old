/*!
 * \file BitmapFont_Impl.h
 * \date 8-22-2011 14:26:19
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __BITMAPFONT_IMPL_H__
#define __BITMAPFONT_IMPL_H__

#include <ui/IFont.h>
#include <tinyxml-2.6.2/tinyxml.h>
#include <vector>
#include <map>

class BitmapFont_Impl : public IFont
{
public:
	typedef std::vector<ITexture*> TV_TEXTURE;
	typedef std::map<int, CHAR_INFO> TM_CHAR_INFO;
	typedef std::map<int, float> TM_KERNING;

public:
	BitmapFont_Impl(const char* pszFontFile);
	virtual ~BitmapFont_Impl();

	virtual float GetLineHeight() const;
	virtual const CHAR_INFO* GetCharInfo(int nID) const;
	virtual float GetKerning(int nFirstID, int nSecondID) const;

private:
	bool CreateBitmapFont(const char* pszFontFile);
	bool ParseCommonInfo(TiXmlElement* pElmCommon);

	bool CreateTextures(TiXmlElement* pElmPages);
	void DestroyTextures();

	bool CreateCharsInfo(TiXmlElement* pElmChars);
	bool CreateControlCharsInfo();
	void DestroyCharsInfo();

	bool CreateKerningsInfo(TiXmlElement* pElmKernings);
	void DestroyKerningsInfo();
	int HashKerningID(int nFirstID, int nSecondID) const;

	void FreeFont();

private:
	float m_fLineHeight;
	int m_nPageCount;
	TV_TEXTURE m_vTextures;
	TM_CHAR_INFO m_mapCharInfo;
	TM_KERNING m_mapKerning;

};
#endif // __BITMAPFONT_IMPL_H__
