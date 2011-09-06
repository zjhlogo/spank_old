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

public:
	UIButton(UIWindow* pParent);
	virtual ~UIButton(void);
	
	void SetText(const char* pszText);
	void SetNormalTexture(ITexture* pTexture);
	void SetPressedTexture(ITexture* pTexture);

	virtual void Update(float dt);
	virtual void Render(const RenderParam& param);

	virtual bool OnClicked(const Vector2& pos);
	virtual bool OnTouchBegin(const Vector2& pos);
	virtual bool OnTouchMove(const Vector2& pos);
	virtual bool OnTouchEnd(const Vector2& pos);
	void SetVisual(bool IsVisual);

private:
	UIString* m_pString;
	ITexture* m_pNormaldTexture;
	ITexture* m_pPressedtexture;
	MsgClick::CLICK_TYPE m_State;
	bool m_bIsVisual;
};
#endif//__UIBUTTON_H_