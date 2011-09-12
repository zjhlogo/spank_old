/*!
 * \file UICheckButton.h
 * \date 2011/09/09 11:23
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __UICHECKBUTTON_H__
#define __UICHECKBUTTON_H__

#include "UIWindow.h"
#include "UIString.h"

class UICheckButton : public UIWindow
{
public:
	UICheckButton(UIWindow* pParent);
	virtual ~UICheckButton();

	virtual void Update(float dt);
	virtual void Render(const RenderParam& param);

	void SetText(const char* pszText);
	void SetStyle(const char* pszStyle);

	void SetCheck(bool bCheck);
	bool GetCheck() const;

	virtual bool OnClicked(const Vector2& pos);

private:
	UIString* m_pString;
	bool m_bCheck;

};
#endif // __UICHECKBUTTON_H__
