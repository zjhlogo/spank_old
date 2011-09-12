/*!
 * \file UIButton.cpp
 * \date 2011/09/05 9:32
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <ui/UIButton.h>
#include <ui/IRendererUI.h>
#include <msg/MsgID.h>
#include <util/IDebugUtil.h>

UIButton::UIButton(UIWindow *pParent)
:UIWindow(pParent)
{
	m_pString = new UIString(NULL);
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
// 	Vector2 posAbs = param.m_vBasePos + GetPosition();
// 	IRendererUI::GetInstance().DrawRect(posAbs, quad);
// 
// 	if(m_pString != NULL)
// 	{
// 		IRendererUI::GetInstance().Flush();
// 
// 		posAbs += GetPaddingLeftTop();
// 		if(m_pString!=NULL)
// 			m_pString->Render(posAbs);
// 	}
}

void UIButton::SetText(const char* pszText)
{
	m_pString->SetText(pszText);
}

void UIButton::SetStyle(const char* pszStyle)
{
	// TODO: 
}

bool UIButton::OnClicked(const Vector2& pos)
{
	MsgClick msgClick(this);
	CallEvent(msgClick);
	return true;
}
