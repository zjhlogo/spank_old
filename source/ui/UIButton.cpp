/*!
 * \file UIButton.cpp
 * \date 2011/09/05 9:32
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <ui/UIButton.h>
#include <ui/IRendererUI.h>
#include <ui/IUIResMgr.h>
#include <msg/MsgID.h>
#include <util/IDebugUtil.h>
#include <util/StringUtil.h>

UIButton::UIButton(UIWindow *pParent)
:UIWindow(pParent)
{
	m_pString = new UIString(NULL);

	// load default state styles
	IUIResMgr::GetInstance().SetupDefaultButtonTextures(m_pStyle);
	AdjustSize();
}

UIButton::~UIButton()
{
	SAFE_DELETE(m_pString);
}

void UIButton::Update(float dt)
{
	// TODO: 
}

void UIButton::Render(const RenderParam& param)
{
 	Vector2 posAbs = param.m_vBasePos + GetPosition();

	if (!IsEnable() || !param.IsEnable())
	{
		// render disabled state
		IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_BUTTON_DISABLED]);
		// TODO: render string disabled state
		m_pString->Render(posAbs);
	}
	else if (IsPressed())
	{
		// render pressed state
		IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_BUTTON_PRESSED]);
		// TODO: render string pressed state
		m_pString->Render(posAbs);
	}
	else
	{
		// render default state
		IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_BUTTON_DEFAULT]);
		// TODO: render string pressed state
		m_pString->Render(posAbs);
	}
}

Vector2 UIButton::GetBestSize()
{
	Vector2 sizeMax = m_pString->GetSize();
	if (sizeMax.x < m_pStyle[DUS_BUTTON_DEFAULT]->width) sizeMax.x = m_pStyle[DUS_BUTTON_DEFAULT]->width;
	if (sizeMax.y < m_pStyle[DUS_BUTTON_DEFAULT]->height) sizeMax.y = m_pStyle[DUS_BUTTON_DEFAULT]->height;
	return sizeMax;
}

void UIButton::SetText(const char* pszText)
{
	m_pString->SetText(pszText);
	AdjustSize();
}

bool UIButton::SetButtonTexture(const IMAGE_PIECE* pImagePiece, int nIndex)
{
	if (nIndex < 0 || nIndex >= DUS_BUTTON_NUM) return false;

	m_pStyle[nIndex] = pImagePiece;
	AdjustSize();

	return true;
}

bool UIButton::OnClicked(const Vector2& pos)
{
	MsgClick msgClick(this);
	CallEvent(msgClick);
	return true;
}
