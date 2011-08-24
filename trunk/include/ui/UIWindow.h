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
#include <vector>

class UIWindow : public IObject
{
public:
	typedef std::vector<UIWindow*> TV_WINDOW;

public:
	UIWindow(UIWindow* pParent);
	virtual ~UIWindow();

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	UIWindow* GetParentWindow();

protected:
	void AddChild(UIWindow* pWindow);
	void RemoveChild(UIWindow* pWindow);

	void UpdateChildrenWindow(float dt);
	void RenderChildrenWindow();

private:
	UIWindow* m_pParent;
	TV_WINDOW m_vChildren;

};
#endif // __UIWINDOW_H__
