/*!
 * \file UIRadio.cpp
 * \date 2011/09/08 10:17
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <ui/UIRadio.h>
#include <ui/IRendererUI.h>
#include <msg/MsgClick.h>
UIRadio::UIRadio(UIWindow* pParent)
:UIButton(pParent)
{
	//TODO:

}

UIRadio::~UIRadio()
{
	
}

bool UIRadio::OnTouchBegin( const Vector2& pos )
{
	SetCheckedState(true);
	return true;
	//Add Msg sent;
}

bool UIRadio::OnClicked( const Vector2& pos )
{
	SetCheckedState(true);
	return true;
}

bool UIRadio::OnTouchEnd( const Vector2& pos )
{
	return true;
}

bool UIRadio::OnTouchMove( const Vector2& pos )
{
	return true;
}



