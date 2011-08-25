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
	UIScreen();
	virtual ~UIScreen();

	virtual void Update(float dt);
	virtual void Render(const RenderParam& param);

private:
	// TODO: 

};
#endif // __UISCREEN_H__
