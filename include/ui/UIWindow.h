/*!
 * \file UIWindow.h
 * \date 8-24-2011 14:52:03
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __UIWINDOW_H__
#define __UIWINDOW_H__

#include "../IObject.h"
#include "../math/Vector2.h"
#include "BaseTypeUI.h"
#include "RenderParam.h"

#include <vector>

class UIWindow : public IObject
{
public:
	typedef std::vector<UIWindow*> TV_WINDOW;

public:
	UIWindow(UIWindow* pParent);
	virtual ~UIWindow();

	virtual void Update(float dt) = 0;
	virtual void Render(const RenderParam& param) = 0;

	UIWindow* GetParentWindow();

	const Vector2& GetPosition() const;
	void SetPosition(const Vector2& pos);

	const Vector2& GetSize() const;
	void SetSize(const Vector2& size);

	bool ProcessTouchEvent(const Vector2& pos, UI_TOUCH_EVENT_TYPE eType);

	virtual bool OnClicked(const Vector2& pos);
	virtual bool OnTouchBegin(const Vector2& pos);
	virtual bool OnTouchMove(const Vector2& pos);
	virtual bool OnTouchEnd(const Vector2& pos);

protected:
	void AddChild(UIWindow* pWindow);
	void RemoveChild(UIWindow* pWindow);

	void UpdateChildrenWindow(float dt);
	void RenderChildrenWindow(const RenderParam& param);

	UIWindow* FindChildUnderPoint(const Vector2& pos);
	bool PointInRect(const Vector2& point, const Vector2& rectPos, const Vector2& rectSize);

private:
	UIWindow* m_pParent;
	TV_WINDOW m_vChildren;

	Vector2 m_vPosition;
	Vector2 m_vSize;

};
#endif // __UIWINDOW_H__
