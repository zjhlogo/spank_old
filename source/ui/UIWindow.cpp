/*!
 * \file UIWindow.cpp
 * \date 8-24-2011 15:04:58
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <ui/UIWindow.h>

UIWindow::UIWindow(UIWindow* pParent)
{
	m_pParent = pParent;
	if (m_pParent)
	{
		m_pParent->AddChild(this);
	}
}

UIWindow::~UIWindow()
{
	for (TV_WINDOW::iterator it = m_vChildren.begin(); it != m_vChildren.end(); ++it)
	{
		UIWindow* pWindow = (*it);
		SAFE_RELEASE(pWindow);
	}
	m_vChildren.clear();
}

UIWindow* UIWindow::GetParentWindow()
{
	return m_pParent;
}

void UIWindow::AddChild(UIWindow* pWindow)
{
	// TODO: check pWindow exist ?
	m_vChildren.push_back(pWindow);
}

void UIWindow::RemoveChild(UIWindow* pWindow)
{
	for (TV_WINDOW::iterator it = m_vChildren.begin(); it != m_vChildren.end(); ++it)
	{
		if ((*it) == pWindow)
		{
			m_vChildren.erase(it);
			SAFE_RELEASE(pWindow);
			return;
		}
	}
}

void UIWindow::UpdateChildrenWindow(float dt)
{
	for (TV_WINDOW::iterator it = m_vChildren.begin(); it != m_vChildren.end(); ++it)
	{
		UIWindow* pWindow = (*it);
		pWindow->Update(dt);
	}
}

void UIWindow::RenderChildrenWindow()
{
	for (TV_WINDOW::iterator it = m_vChildren.begin(); it != m_vChildren.end(); ++it)
	{
		UIWindow* pWindow = (*it);
		pWindow->Render();
	}
}
