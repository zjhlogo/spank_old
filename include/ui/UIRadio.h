/*!
 * \file UIRadio.h
 * \date 2011/09/08 10:16
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __UIRADIO_H_
#define __UIRADIO_H_

#include<ui/UIButton.h>

class UIRadio :public UIButton
{
public:
	UIRadio(UIWindow* pParent);
	virtual ~UIRadio();
	
	virtual bool OnClicked(const Vector2& pos);
	virtual bool OnTouchEnd(const Vector2& pos);
	virtual bool OnTouchMove(const Vector2& pos);
	virtual bool OnTouchBegin(const Vector2& pos);
};
#endif//__UIRADIO_H_