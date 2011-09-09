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
	virtual ~UIButton(void);
	void SetText(char* pszText);
	void SetNormalTexture(ITexture* pTexture);
	void SetCheckedTexture(ITexture* pTexture);

	virtual void Render(const RenderParam& param);
	virtual void Update(float dt);


	bool GetCheckState() const;
	void SetCheckedState(bool bflag);

	virtual bool OnClicked(const Vector2& pos);
	virtual bool OnTouchBegin(const Vector2& pos);
	virtual bool OnTouchMove(const Vector2& pos);
	virtual bool OnTouchEnd(const Vector2& pos);
private:
	UIString* m_pString;
	ITexture* m_pNormalTexture;
	ITexture* m_pCheckedTexture;
	bool m_bCheckState;
};
#endif//__UIBUTTON_H_