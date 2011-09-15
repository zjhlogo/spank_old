/*!
 * \file IUISystem.h
 * \date 8-24-2011 13:57:38
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IUISYSTEM_H__
#define __IUISYSTEM_H__

#include "../ISingleton.h"
#include "UIScreen.h"

class IUISystem : public ISingleton
{
public:
	DECLARE_RTTI(IUISystem, ISingleton);

	static IUISystem& GetInstance();

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	virtual UIScreen* GetCurrentScreen() = 0;
	virtual bool SetCurrentScreen(UIScreen* pUIScreen) = 0;

	virtual UIScreen* CreateUIScreen() = 0;
	virtual bool ReleaseUIScreen(UIScreen* pUIScreen) = 0;

	virtual bool CaptureMouse(UIWindow* pWindow) = 0;
	virtual bool ReleaseMouse() = 0;

	virtual bool ProcessTouchEvent(const Vector2& pos, UI_TOUCH_EVENT_TYPE eType) = 0;

};
#endif // __IUISYSTEM_H__
