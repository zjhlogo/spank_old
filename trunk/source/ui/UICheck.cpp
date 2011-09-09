/*!
 * \file UICheck.cpp
 * \date 2011/09/09 11:23
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <ui/UICheck.h>
#include <ui/IRendererUI.h>
#include <msg/MsgClick.h>
UICheck::UICheck( UIWindow* pParent )
:UIButton(pParent)
{
	
}

UICheck::~UICheck()
{
	//TODO:
}

bool UICheck::OnTouchBegin( const Vector2& pos )
{
	
	if(GetCheckState())
	{
		SetCheckedState(false);
		MsgClick msgclick(MsgClick::CT_NORMAL, GetID());
		CallEvent(msgclick);
	}
	else
	{
		SetCheckedState(true);
		MsgClick msgclick(MsgClick::CT_CHECK, GetID());
		CallEvent(msgclick);
	}
	return true;
}

bool UICheck::OnTouchMove( const Vector2& pos )
{
	return true;
}

bool UICheck::OnTouchEnd( const Vector2& pos )
{
	return true;
}

bool UICheck::OnClicked( const Vector2& pos )
{
	return true;
}




