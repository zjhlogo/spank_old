/*!
 * \file IUISystem.h
 * \date 8-24-2011 13:57:38
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IUISYSTEM_H__
#define __IUISYSTEM_H__

#include "../IMgr.h"
#include "UIScreen.h"

class IUISystem : public IMgr
{
public:
	static IUISystem& GetInstance();

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	virtual UIScreen* GetCurrentScreen() = 0;
	virtual bool AddScreen(UIScreen* pScreen) = 0;

};
#endif // __IUISYSTEM_H__
