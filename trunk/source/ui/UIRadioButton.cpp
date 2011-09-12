/*!
 * \file UIRadioButton.cpp
 * \date 2011/09/08 10:17
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <ui/UIRadioButton.h>
#include <ui/IRendererUI.h>
#include <msg/MsgClick.h>

UIRadioButton::UIRadioButton(UIWindow* pParent)
:UIWindow(pParent)
{
	m_nGroupID = 1;
	m_pString = new UIString(NULL);
}

UIRadioButton::~UIRadioButton()
{
	SAFE_DELETE(m_pString);
}

void UIRadioButton::Update(float dt)
{
	// TODO: 
}

void UIRadioButton::Render(const RenderParam& param)
{
	// TODO: 
}

void UIRadioButton::SetGroupID(int nGroup)
{
	m_nGroupID = nGroup;
	// TODO: join to a new group
}

int UIRadioButton::GetGroupID() const
{
	return m_nGroupID;
}

void UIRadioButton::SetText(const char* pszText)
{
	m_pString->SetText(pszText);
	// TODO: adjust size
}

void UIRadioButton::SetStyle(const char* pszStyle)
{
	// TODO: 
}

bool UIRadioButton::OnClicked(const Vector2& pos)
{
	// TODO: 
	return false;
}
