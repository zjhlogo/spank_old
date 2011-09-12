/*!
 * \file BitmapFont_Impl.cpp
 * \date 8-22-2011 14:27:09
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "BitmapFont_Impl.h"
#include <util/IFileUtil.h>
#include <ITextureMgr.h>
#include <msg/MsgCommon.h>
#include <msg/MsgID.h>

BitmapFont_Impl::BitmapFont_Impl(const char* pszFontFile)
{
	m_fLineHeight = 0.0f;
	m_nPageCount = 0;

	m_bOK = CreateBitmapFont(pszFontFile);
}

BitmapFont_Impl::~BitmapFont_Impl()
{
	MsgCommon msgCommon(MI_FONT_DESTROIED);
	msgCommon.SetObject(this);
	CallEvent(msgCommon);
	FreeFont();
}

float BitmapFont_Impl::GetLineHeight() const
{
	return m_fLineHeight;
}

const CHAR_INFO* BitmapFont_Impl::GetCharInfo(int nID) const
{
	TM_CHAR_INFO::const_iterator itfound = m_mapCharInfo.find(nID);
	if (itfound != m_mapCharInfo.end())
	{
		return &itfound->second;
	}

	return NULL;
}

float BitmapFont_Impl::GetKerning(int nFirstID, int nSecondID) const
{
	int nHaskKey = HashKerningID(nFirstID, nSecondID);

	TM_KERNING::const_iterator itfound = m_mapKerning.find(nHaskKey);
	if (itfound != m_mapKerning.end())
	{
		return itfound->second;
	}

	return 0.0f;
}

bool BitmapFont_Impl::CreateBitmapFont(const char* pszFontFile)
{
	StreamReader* pReader = IFileUtil::GetInstance().LoadFile(pszFontFile);
	if (!pReader) return false;

	TiXmlDocument doc;
	doc.Parse((const char*)pReader->GetBuffer());
	SAFE_RELEASE(pReader);

	if (doc.Error()) return false;

	TiXmlElement* pElmFont = doc.RootElement();
	if (!pElmFont) return false;

	TiXmlElement* pElmCommon = pElmFont->FirstChildElement("common");
	if (!pElmCommon) return false;
	if (!ParseCommonInfo(pElmCommon)) return false;

	TiXmlElement* pElmPages = pElmFont->FirstChildElement("pages");
	if (!pElmPages) return false;
	if (!CreateTextures(pElmPages)) return false;

	TiXmlElement* pElmCharsInfo = pElmFont->FirstChildElement("chars");
	if (!pElmCharsInfo) return false;
	if (!CreateCharsInfo(pElmCharsInfo)) return false;
	if (!CreateControlCharsInfo()) return false;

	TiXmlElement* pElmKerningsInfo = pElmFont->FirstChildElement("kernings");
	if (pElmKerningsInfo)
	{
		if (!CreateKerningsInfo(pElmKerningsInfo)) return false;
	}

	return true;
}

bool BitmapFont_Impl::ParseCommonInfo(TiXmlElement* pElmCommon)
{
	int temp = 0;
	if (!pElmCommon->Attribute("lineHeight", &temp)) return false;
	m_fLineHeight = (float)temp;

	if (!pElmCommon->Attribute("pages", &m_nPageCount)) return false;

	return true;
}

bool BitmapFont_Impl::CreateTextures(TiXmlElement* pElmPages)
{
	DestroyTextures();

	TiXmlElement* pElmPage = pElmPages->FirstChildElement("page");

	for (int i = 0; i < m_nPageCount && pElmPage != NULL; ++i, pElmPage = pElmPage->NextSiblingElement("page"))
	{
		const char* pszTextureFile = pElmPage->Attribute("file");
		if (!pszTextureFile) return false;

		ITexture* pTexture = ITextureMgr::GetInstance().CreateTexture(pszTextureFile);
		if (!pTexture) return false;

		m_vTextures.push_back(pTexture);
	}

	return true;
}

void BitmapFont_Impl::DestroyTextures()
{
	for (TV_TEXTURE::iterator it = m_vTextures.begin(); it != m_vTextures.end(); ++it)
	{
		ITexture* pTexture = (*it);
		SAFE_RELEASE(pTexture);
	}
	m_vTextures.clear();
}

bool BitmapFont_Impl::CreateCharsInfo(TiXmlElement* pElmChars)
{
	DestroyCharsInfo();

	int nCount = 0;
	if (!pElmChars->Attribute("count", &nCount)) return false;

	int temp = 0;
	TiXmlElement* pElmChar = pElmChars->FirstChildElement("char");

	for (int i = 0; i < nCount && pElmChar != NULL; ++i, pElmChar = pElmChar->NextSiblingElement("char"))
	{
		CHAR_INFO CharInfo;
		if (!pElmChar->Attribute("id", &CharInfo.nID)) return false;

		int posX = 0;
		if (!pElmChar->Attribute("x", &posX)) return false;

		int posY = 0;
		if (!pElmChar->Attribute("y", &posY)) return false;

		if (!pElmChar->Attribute("width", &temp)) return false;
		CharInfo.width = (float)temp;

		if (!pElmChar->Attribute("height", &temp)) return false;
		CharInfo.height = (float)temp;

		if (!pElmChar->Attribute("xoffset", &temp)) return false;
		CharInfo.offsetx = (float)temp;

		if (!pElmChar->Attribute("yoffset", &temp)) return false;
		CharInfo.offsety = (float)temp;

		if (!pElmChar->Attribute("xadvance", &temp)) return false;
		CharInfo.advance = (float)temp;

		int nPage = 0;
		if (!pElmChar->Attribute("page", &nPage)) return false;
		if (nPage >= (int)m_vTextures.size()) return false;

		CharInfo.pTexture = m_vTextures[nPage];
		CharInfo.nRef = 0;

		float fTextureWidth = (float)CharInfo.pTexture->GetWidth();
		float fTextureHeight = (float)CharInfo.pTexture->GetHeight();

		CharInfo.u = (posX)/fTextureWidth;
		CharInfo.v = (fTextureHeight-posY-CharInfo.height)/fTextureHeight;		// invert the y-axis for opengl
		CharInfo.du = (CharInfo.width)/fTextureWidth;
		CharInfo.dv = (CharInfo.height)/fTextureHeight;

		m_mapCharInfo.insert(std::make_pair(CharInfo.nID, CharInfo));
	}

	return true;
}

bool BitmapFont_Impl::CreateControlCharsInfo()
{
	const CHAR_INFO* pCharInfo = GetCharInfo(-1);
	CHAR_INFO CharInfoReturn = (*pCharInfo);
	CharInfoReturn.nID = '\n';

	m_mapCharInfo.insert(std::make_pair(CharInfoReturn.nID, CharInfoReturn));
	return true;
}

void BitmapFont_Impl::DestroyCharsInfo()
{
	m_mapCharInfo.clear();
}

bool BitmapFont_Impl::CreateKerningsInfo(TiXmlElement* pElmKernings)
{
	DestroyKerningsInfo();

	int nCount = 0;
	if (!pElmKernings->Attribute("count", &nCount)) return false;

	TiXmlElement* pElmKerning = pElmKernings->FirstChildElement("kerning");

	for (int i = 0; i < nCount && pElmKerning != NULL; ++i, pElmKerning = pElmKerning->NextSiblingElement("kerning"))
	{
		int nFirstID = 0;
		int nSecondID = 0;
		if (!pElmKerning->Attribute("first", &nFirstID)) return false;
		if (!pElmKerning->Attribute("second", &nSecondID)) return false;

		int temp = 0;
		if (!pElmKerning->Attribute("amount", &temp)) return false;
		float fOffset = (float)temp;

		int nHaskKey = HashKerningID(nFirstID, nSecondID);

		m_mapKerning.insert(std::make_pair(nHaskKey, fOffset));
	}

	return true;
}

void BitmapFont_Impl::DestroyKerningsInfo()
{
	m_mapKerning.clear();
}

int BitmapFont_Impl::HashKerningID(int nFirstID, int nSecondID) const
{
	int nHashKey = (nFirstID << 16) | (nSecondID & 0x0000FFFF);
	return nHashKey;
}

void BitmapFont_Impl::FreeFont()
{
	DestroyTextures();
	DestroyCharsInfo();
	DestroyKerningsInfo();
}
