/*!
 * \file UIButton.h
 * \date 2011/09/05 9:31
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */

#ifndef __UIBUTTON_H_
#define __UIBUTTON_H_

#include <ui/UIWindow.h>
#include <ui/UIString.h>
#include <msg/MsgClick.h>
#include <ITexture.h>

class UIButton : public UIWindow
{
public:
	UIButton(UIWindow* pParent);
	virtual ~UIButton();

	virtual void Update(float dt);
	virtual void Render(const RenderParam& param);

	void SetText(const char* pszText);
	void SetStyle(const char* pszStyle);

	virtual bool OnClicked(const Vector2& pos);

private:
	UIString* m_pString;

};
#endif//__UIBUTTON_H_
