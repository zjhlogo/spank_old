/*!
 * \file FontMgr_Impl.cpp
 * \date 8-22-2011 15:34:18
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "FontMgr_Impl.h"
#include "BitmapFont_Impl.h"
#include <msg/MsgID.h>
#include <msg/MsgCommon.h>

IFontMgr& IFontMgr::GetInstance()
{
	static FontMgr_Impl s_FontMgr_Impl;
	return s_FontMgr_Impl;
}

FontMgr_Impl::FontMgr_Impl()
{
	m_pDefaultFont = NULL;
}

FontMgr_Impl::~FontMgr_Impl()
{
	// TODO: 
}

bool FontMgr_Impl::Initialize()
{
	m_pDefaultFont = CreateFont("12px_Tahoma.fnt");
	if (!m_pDefaultFont) return false;

	return true;
}

void FontMgr_Impl::Terminate()
{
	SAFE_RELEASE(m_pDefaultFont);
}

IFont* FontMgr_Impl::CreateFont(const char* pszFontFile)
{
	IFont* pFont = FindFont(pszFontFile);
	if (pFont)
	{
		pFont->IncRef();
		return pFont;
	}

	BitmapFont_Impl* pFont_Impl = new BitmapFont_Impl(pszFontFile);
	if (!pFont_Impl || !pFont_Impl->IsOK())
	{
		SAFE_DELETE(pFont_Impl);
		return NULL;
	}

	// connect the destroy event
	pFont_Impl->ConnectEvent(MI_FONT_DESTROIED, this, CAST_MSG_CALLBACK(&FontMgr_Impl::OnFontDestroied));
	// cache the texture
	m_mapFont.insert(std::make_pair(pszFontFile, pFont_Impl));

	return pFont_Impl;
}

IFont* FontMgr_Impl::GetDefaultFont()
{
	return m_pDefaultFont;
}

IFont* FontMgr_Impl::FindFont(const char* pszFontFile)
{
	TM_FONT::iterator itfound = m_mapFont.find(pszFontFile);
	if (itfound == m_mapFont.end()) return NULL;

	return itfound->second;
}

bool FontMgr_Impl::OnFontDestroied(IMsgBase* pMsg)
{
	MsgCommon* pMsgCommon = (MsgCommon*)pMsg;
	IFont* pFont = (IFont*)pMsgCommon->GetObject();
	if (!pFont) return false;

	for (TM_FONT::iterator it = m_mapFont.begin(); it != m_mapFont.end(); ++it)
	{
		if (it->second == pFont)
		{
			m_mapFont.erase(it);
			return true;
		}
	}

	return false;
}
