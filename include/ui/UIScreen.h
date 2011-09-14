/*!
 * \file UIScreen.h
 * \date 8-24-2011 15:07:51
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __UISCREEN_H__
#define __UISCREEN_H__

#include "UIWindow.h"

class UIScreen : public UIWindow
{
public:
	DECLARE_RTTI(UIScreen, UIWindow);

	UIScreen();
	virtual ~UIScreen();

	virtual void Update(float dt);
	virtual void Render(const RenderParam& param);
	virtual Vector2 GetBestSize();

private:
	// TODO: 

};
#endif // __UISCREEN_H__
