/*!
 * \file FontMgr_Impl.cpp
 * \date 8-22-2011 15:34:18
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "UIResMgr_Impl.h"
#include "BitmapFont_Impl.h"
#include <msg/MsgID.h>
#include <msg/MsgCommon.h>
#include <IResourceMgr.h>
#include <util/StringUtil.h>
#include <util/IDebugUtil.h>

IUIResMgr& IUIResMgr::GetInstance()
{
	static UIResMgr_Impl s_UIResMgr_Impl;
	return s_UIResMgr_Impl;
}

UIResMgr_Impl::UIResMgr_Impl()
{
	m_pDefaultFont = NULL;
	StringUtil::ZeroMemory(m_pButtonStyle, sizeof(m_pButtonStyle));
	StringUtil::ZeroMemory(m_pCheckButtonStyle, sizeof(m_pCheckButtonStyle));
	StringUtil::ZeroMemory(m_pRadioButtonStyle, sizeof(m_pRadioButtonStyle));
}

UIResMgr_Impl::~UIResMgr_Impl()
{
	// TODO: 
}

bool UIResMgr_Impl::Initialize()
{
	m_pDefaultFont = CreateFont("40px_arial_black.fnt");
	if (!m_pDefaultFont) return false;

	if (!InitDefaultButtonStyle()) return false;
	if (!InitDefaultCheckButtonStyle()) return false;
	if (!InitDefaultRadioButtonStyle()) return false;

	return true;
}

void UIResMgr_Impl::Terminate()
{
	SAFE_RELEASE(m_pDefaultFont);
}

IFont* UIResMgr_Impl::CreateFont(const char* pszFontFile)
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
	pFont_Impl->ConnectEvent(MI_FONT_DESTROIED, this, CAST_MSG_CALLBACK(&UIResMgr_Impl::OnFontDestroied));
	// cache the texture
	m_mapFont.insert(std::make_pair(pszFontFile, pFont_Impl));

	return pFont_Impl;
}

IFont* UIResMgr_Impl::GetDefaultFont()
{
	return m_pDefaultFont;
}

IFont* UIResMgr_Impl::FindFont(const char* pszFontFile)
{
	TM_FONT::iterator itfound = m_mapFont.find(pszFontFile);
	if (itfound == m_mapFont.end()) return NULL;

	return itfound->second;
}

bool UIResMgr_Impl::OnFontDestroied(IMsgBase* pMsg)
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

bool UIResMgr_Impl::SetupDefaultButtonTextures(const IMAGE_PIECE** pPieceOut, int nPiece /*= DUS_BUTTON_NUM*/) const
{
	if (nPiece != DUS_BUTTON_NUM)
	{
		LOGE("boundary out of range");
		return false;
	}

	for (int i = 0; i < DUS_BUTTON_NUM; ++i)
	{
		pPieceOut[i] = m_pButtonStyle[i];
	}

	return true;
}

bool UIResMgr_Impl::SetupDefaultCheckButtonTextures(const IMAGE_PIECE** pPieceOut, int nPiece /*= DUS_CHECKBUTTON_NUM*/) const
{
	if (nPiece != DUS_CHECKBUTTON_NUM)
	{
		LOGE("boundary out of range");
		return false;
	}

	for (int i = 0; i < DUS_CHECKBUTTON_NUM; ++i)
	{
		pPieceOut[i] = m_pButtonStyle[i];
	}

	return true;
}

bool UIResMgr_Impl::SetupDefaultRadioButtonTextures(const IMAGE_PIECE** pPieceOut, int nPiece /*= DUS_RADIOBUTTON_NUM*/) const
{
	if (nPiece != DUS_RADIOBUTTON_NUM)
	{
		LOGE("boundary out of range");
		return false;
	}

	for (int i = 0; i < DUS_RADIOBUTTON_NUM; ++i)
	{
		pPieceOut[i] = m_pButtonStyle[i];
	}

	return true;
}

bool UIResMgr_Impl::InitDefaultButtonStyle()
{
	static const char* s_pszImagePieces[DUS_BUTTON_NUM] = 
	{
		"ui_button_default",
		"ui_button_pressed",
		"ui_button_disabled",
	};

	for (int i = 0; i < DUS_BUTTON_NUM; ++i)
	{
		m_pButtonStyle[i] = IResourceMgr::GetInstance().FindImagePiece(s_pszImagePieces[i]);
		if (!m_pButtonStyle[i]) return false;
	}

	return true;
}

bool UIResMgr_Impl::InitDefaultCheckButtonStyle()
{
	static const char* s_pszImagePieces[DUS_CHECKBUTTON_NUM] = 
	{
		"ui_checkbutton_check",
		"ui_checkbutton_check_pressed",
		"ui_checkbutton_check_disabled",
		"ui_checkbutton_uncheck",
		"ui_checkbutton_uncheck_pressed",
		"ui_checkbutton_uncheck_disabled",
	};

	for (int i = 0; i < DUS_CHECKBUTTON_NUM; ++i)
	{
		m_pCheckButtonStyle[i] = IResourceMgr::GetInstance().FindImagePiece(s_pszImagePieces[i]);
		if (!m_pCheckButtonStyle[i]) return false;
	}

	return true;
}

bool UIResMgr_Impl::InitDefaultRadioButtonStyle()
{
	static const char* s_pszImagePieces[DUS_RADIOBUTTON_NUM] = 
	{
		"ui_radiobutton_check",
		"ui_radiobutton_check_pressed",
		"ui_radiobutton_check_disabled",
		"ui_radiobutton_uncheck",
		"ui_radiobutton_uncheck_pressed",
		"ui_radiobutton_uncheck_disabled",
	};

	for (int i = 0; i < DUS_RADIOBUTTON_NUM; ++i)
	{
		m_pRadioButtonStyle[i] = IResourceMgr::GetInstance().FindImagePiece(s_pszImagePieces[i]);
		if (!m_pRadioButtonStyle[i]) return false;
	}

	return true;
}
