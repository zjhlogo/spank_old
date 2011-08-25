/*!
 * \file UISystem_Impl.cpp
 * \date 8-24-2011 14:50:17
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "UISystem_Impl.h"
#include <ui/IRendererUI.h>
#include <util/ScreenUtil.h>

IUISystem& IUISystem::GetInstance()
{
	static UISystem_Impl s_UISystem_Impl;
	return s_UISystem_Impl;
}

UISystem_Impl::UISystem_Impl()
{
	m_pDefaultScreen = NULL;
	m_pCurrScreen = NULL;
}

UISystem_Impl::~UISystem_Impl()
{
	// TODO: 
}

bool UISystem_Impl::Initialize()
{
	m_pDefaultScreen = new UIScreen();
	m_pCurrScreen = m_pDefaultScreen;
	return true;
}

void UISystem_Impl::Terminate()
{
	SAFE_RELEASE(m_pDefaultScreen);
	m_pCurrScreen = NULL;
}

void UISystem_Impl::Update(float dt)
{
	m_pCurrScreen->Update(dt);
}

void UISystem_Impl::Render()
{
	RenderParam param(IMath::VEC2_ZERO, ScreenUtil::GetInstance().GetScreenSize());
	m_pCurrScreen->Render(param);
}

UIScreen* UISystem_Impl::GetCurrentScreen()
{
	return m_pCurrScreen;
}

bool UISystem_Impl::AddScreen(UIScreen* pScreen)
{
	// TODO: 
	return false;
}

bool UISystem_Impl::ProcessTouchEvent(const Vector2& pos, UI_TOUCH_EVENT_TYPE eType)
{
	return m_pCurrScreen->ProcessTouchEvent(pos, eType);
}
