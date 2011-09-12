/*!
 * \file MsgClick.h
 * \date 2011/09/05 14:10
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __MSGCLICK_H__
#define __MSGCLICK_H__

#include "IMsgBase.h"
#include "../ui/UIWindow.h"

class MsgClick : public IMsgBase
{
public:
	MsgClick(UIWindow* pSender);
	~MsgClick();

	UIWindow* GetSender();
	int GetSenderID() const;

private:
	UIWindow* m_pSender;

};

#endif // __MSGCLICK_H__
