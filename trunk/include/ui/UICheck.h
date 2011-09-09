/*!
 * \file UICheck.h
 * \date 2011/09/09 11:23
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __UICHECK_H_
#define __UICHECK_H_
#include "ui/UIButton.h"

class UICheck : public UIButton
{

public:
	UICheck(UIWindow* pParent);
	virtual ~UICheck();

	virtual bool OnTouchBegin(const Vector2& pos);
	virtual bool OnTouchMove(const Vector2& pos);
	virtual bool OnTouchEnd(const Vector2& pos);
	virtual bool OnClicked(const Vector2& pos);
};
#endif//__UICHECK_H_