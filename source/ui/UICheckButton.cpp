/*!
 * \file UICheckButton.cpp
 * \date 2011/09/09 11:23
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <ui/UICheckButton.h>
#include <ui/IRendererUI.h>
#include <msg/MsgClick.h>

UICheckButton::UICheckButton(UIWindow* pParent)
:UIWindow(pParent)
{
	m_pString = new UIString(NULL);
	m_bCheck = false;
}

UICheckButton::~UICheckButton()
{
	SAFE_DELETE(m_pString);
}

void UICheckButton::Update(float dt)
{
	// TODO: 
}

void UICheckButton::Render(const RenderParam& param)
{
	// TODO: 
}

void UICheckButton::SetText(const char* pszText)
{
	// TODO: 
}

void UICheckButton::SetStyle(const char* pszStyle)
{
	// TODO: 
}

void UICheckButton::SetCheck(bool bCheck)
{
	m_bCheck = bCheck;
}

bool UICheckButton::GetCheck() const
{
	return m_bCheck;
}

bool UICheckButton::OnClicked(const Vector2& pos)
{
	m_bCheck = !m_bCheck;
	// TODO: notify msg event
	return true;
}
