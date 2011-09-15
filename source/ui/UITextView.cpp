/*!
 * \file UITextView.cpp
 * \date 8-24-2011 15:23:06
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <ui/UITextView.h>
#include <ui/IRendererUI.h>
#include <ui/IUIResMgr.h>
#include <util/IDebugUtil.h>
#include <ui/uimsg/MsgClick.h>

UITextView::UITextView(UIWindow* pParent, const char* pszText)
:UIWindow(pParent)
{
	m_pString = new UIString(NULL);
	SetText(pszText);
}

UITextView::~UITextView()
{
	SAFE_DELETE(m_pString);
}

void UITextView::SetText(const char* pszText)
{
	m_pString->SetText(pszText);
	AdjustSize();
}

void UITextView::Update(float dt)
{
	// TODO: 
}

void UITextView::Render(const RenderParam& param)
{
	RenderBorder(param);
 	Vector2 posAbs = param.m_vBasePos + GetPosition();
	m_pString->Render(posAbs);
}

Vector2 UITextView::GetBestSize()
{
	return m_pString->GetSize();
}

bool UITextView::OnClicked(const Vector2& pos)
{
	MsgClick msgClick(this);
	CallEvent(msgClick);
	return true;
}
