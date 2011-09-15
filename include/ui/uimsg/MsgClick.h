/*!
 * \file MsgClick.h
 * \date 2011/09/05 14:10
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __MSGCLICK_H__
#define __MSGCLICK_H__

#include "IMsgBaseUI.h"

class MsgClick : public IMsgBaseUI
{
public:
	DECLARE_RTTI(MsgClick, IMsgBaseUI);

	MsgClick(UIWindow* pSender);
	~MsgClick();

};

#endif // __MSGCLICK_H__
