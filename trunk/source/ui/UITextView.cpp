/*!
 * \file UITextView.cpp
 * \date 8-24-2011 15:23:06
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <ui/UITextView.h>

UITextView::UITextView(UIWindow* pParent, const char* pszText)
:UIWindow(pParent)
{
	m_pString = new UIString(pszText);
}

UITextView::~UITextView()
{
	SAFE_DELETE(m_pString);
}

void UITextView::SetText(const char* pszText)
{
	m_pString->SetText(pszText);
}

void UITextView::Update(float dt)
{
	// TODO: 
}

void UITextView::Render()
{
	m_pString->Render();
}
