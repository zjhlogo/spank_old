/*!
 * \file MsgClick.cpp
 * \date 2011/09/05 14:10
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <msg/MsgClick.h>
#include <msg/MsgID.h>

MsgClick::MsgClick(UIWindow* pSender)
:IMsgBase(MI_UI_CLICKED)
{
	m_pSender = pSender;
}


MsgClick::~MsgClick()
{
	//TODO:
}

UIWindow* MsgClick::GetSender()
{
	return m_pSender;
}

int MsgClick::GetSenderID() const
{
	return m_pSender->GetID();
}
