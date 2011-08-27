/*!
 * \file UITextView.cpp
 * \date 8-24-2011 15:23:06
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <ui/UITextView.h>
#include <ui/IRendererUI.h>
#include <util/IDebugUtil.h>
#include <msg/MsgCommon.h>
#include <msg/MsgID.h>

UITextView::UITextView(UIWindow* pParent, const char* pszText)
:UIWindow(pParent)
{
	m_pString = new UIString(pszText);
	SetSize(m_pString->GetSize());
}

UITextView::~UITextView()
{
	SAFE_DELETE(m_pString);
}

void UITextView::SetText(const char* pszText)
{
	m_pString->SetText(pszText);
	SetSize(m_pString->GetSize());
}

void UITextView::Update(float dt)
{
	// TODO: 
}

void UITextView::Render(const RenderParam& param)
{
	Vector2 pos = param.m_vBasePos + GetPosition();
	const Vector2& size = GetSize();
	IRendererUI::GetInstance().DrawLineRect(pos, size);

	pos += GetPaddingLeftTop();
 	m_pString->Render(pos);
}

bool UITextView::OnClicked(const Vector2& pos)
{
	MsgCommon msgCommon(MI_UI_CLICKED);
	msgCommon.SetObject(this);
	CallEvent(msgCommon);

	return true;
}
