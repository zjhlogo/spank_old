/*!
 * \file UIWindow.cpp
 * \date 8-24-2011 15:04:58
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <ui/UIWindow.h>
#include <math/IMath.h>

UIWindow::UIWindow(UIWindow* pParent)
{
	m_nID = 0;
	m_vPosition = IMath::VEC2_ZERO;
	m_vSize = IMath::VEC2_ZERO;

	m_PaddingLeftTop = Vector2(0.0f, 0.0f);
	m_PaddingRightBottom = Vector2(0.0f, 0.0f);

	m_MarginLeftTop = IMath::VEC2_ZERO;
	m_MarginRightBottom = IMath::VEC2_ZERO;

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

int UIWindow::GetID() const
{
	return m_nID;
}

void UIWindow::SetID(int nID)
{
	m_nID = nID;
}

const Vector2& UIWindow::GetPosition() const
{
	return m_vPosition;
}

void UIWindow::SetPosition(const Vector2& pos)
{
	m_vPosition = pos;
}

const Vector2& UIWindow::GetSize() const
{
	return m_vSize;
}

void UIWindow::SetSize(const Vector2& size)
{
	m_vSize = size;
 	m_vSize += m_PaddingLeftTop;
 	m_vSize += m_PaddingRightBottom;
}

void UIWindow::SetPadding(float left, float top, float right, float bottom)
{
	m_PaddingLeftTop.x = left;
	m_PaddingLeftTop.y = top;
	m_PaddingRightBottom.x = right;
	m_PaddingRightBottom.y = bottom;
}

const Vector2& UIWindow::GetPaddingLeftTop() const
{
	return m_PaddingLeftTop;
}

const Vector2& UIWindow::GetPaddingRightBottom() const
{
	return m_PaddingRightBottom;
}

void UIWindow::SetMargin(float left, float top, float right, float bottom)
{
	m_MarginLeftTop.x = left;
	m_MarginLeftTop.y = top;
	m_MarginRightBottom.x = right;
	m_MarginRightBottom.y = bottom;
}

const Vector2& UIWindow::GetMarginLeftTop() const
{
	return m_MarginLeftTop;
}

const Vector2& UIWindow::GetMarginRightBottom() const
{
	return m_MarginRightBottom;
}

bool UIWindow::ProcessTouchEvent(const Vector2& pos, UI_TOUCH_EVENT_TYPE eType)
{
	UIWindow* pWindow = FindChildUnderPoint(pos);
	if (pWindow)
	{
		Vector2 localPos = pos - pWindow->GetPosition();
		return pWindow->ProcessTouchEvent(localPos, eType);
	}

	bool bProcessed = false;

	switch (eType)
	{
	case UTET_BEGIN:
		{
			bProcessed = OnTouchBegin(pos);
		}
		break;
	case UTET_MOVE:
		{
			bProcessed = OnTouchMove(pos);
		}
		break;
	case UTET_END:
		{
			if (OnTouchEnd(pos)) bProcessed = true;
			if (OnClicked(pos)) bProcessed = true;
		}
		break;
	}

	return bProcessed;
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

void UIWindow::RenderChildrenWindow(const RenderParam& param)
{
	RenderParam childParam = param;
	childParam.m_vBasePos += m_vPosition;
	childParam.m_vBaseSize = m_vSize;

	for (TV_WINDOW::iterator it = m_vChildren.begin(); it != m_vChildren.end(); ++it)
	{
		UIWindow* pWindow = (*it);
		pWindow->Render(childParam);
	}
}

bool UIWindow::OnClicked(const Vector2& pos)
{
	// TODO: 
	return true;
}

bool UIWindow::OnTouchBegin(const Vector2& pos)
{
	// TODO: 
	return true;
}

bool UIWindow::OnTouchMove(const Vector2& pos)
{
	// TODO: 
	return true;
}

bool UIWindow::OnTouchEnd(const Vector2& pos)
{
	// TODO: 
	return true;
}

UIWindow* UIWindow::FindChildUnderPoint(const Vector2& pos)
{
	for (TV_WINDOW::reverse_iterator it = m_vChildren.rbegin(); it != m_vChildren.rend(); ++it)
	{
		UIWindow* pWindow = (*it);
		if (PointInRect(pos, pWindow->GetPosition(), pWindow->GetSize())) return pWindow;
	}

	return NULL;
}

bool UIWindow::PointInRect(const Vector2& point, const Vector2& rectPos, const Vector2& rectSize)
{
	if (point.x < rectPos.x
		|| point.x > rectPos.x + rectSize.x
		|| point.y < rectPos.y
		|| point.y > rectPos.y + rectSize.y) return false;

	return true;
}
