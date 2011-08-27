/*!
 * \file UIScreen.cpp
 * \date 8-24-2011 15:08:54
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <ui/UIScreen.h>

UIScreen::UIScreen()
:UIWindow(NULL)
{
	m_bOK = true;
}

UIScreen::~UIScreen()
{
	// TODO: 
}

void UIScreen::Update(float dt)
{
	UpdateChildrenWindow(dt);
}

void UIScreen::Render(const RenderParam& param)
{
	RenderChildrenWindow(param);
}
