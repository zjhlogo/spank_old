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

class UISystem_Impl : public IUISystem
{
public:
	UISystem_Impl();
	virtual ~UISystem_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual void Update(float dt);
	virtual void Render();

	virtual UIScreen* GetCurrentScreen();
	virtual bool AddScreen(UIScreen* pScreen);

private:
	UIScreen* m_pDefaultScreen;
	UIScreen* m_pCurrScreen;

};

#endif // __UISYSTEM_IMPL_H__
