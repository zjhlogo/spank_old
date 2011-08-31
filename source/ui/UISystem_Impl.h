/*!
 * \file UISystem_Impl.h
 * \date 8-24-2011 13:57:25
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __UISYSTEM_IMPL_H__
#define __UISYSTEM_IMPL_H__

#include <ui/IUISystem.h>
#include <vector>

class UISystem_Impl : public IUISystem
{
public:
	typedef std::vector<UIScreen*> TV_UISCREEN;

public:
	UISystem_Impl();
	virtual ~UISystem_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual void Update(float dt);
	virtual void Render();

	virtual UIScreen* GetCurrentScreen();
	virtual bool SetCurrentScreen(UIScreen* pUIScreen);

	virtual UIScreen* CreateUIScreen();
	virtual bool ReleaseUIScreen(UIScreen* pUIScreen);

	virtual bool ProcessTouchEvent(const Vector2& pos, UI_TOUCH_EVENT_TYPE eType);

private:
	bool FindUIScreen(UIScreen* pUIScreen);

private:
	TV_UISCREEN m_vUIScreen;
	UIScreen* m_pCurrScreen;

};

#endif // __UISYSTEM_IMPL_H__