/*!
 * \file MsgButtonClick.h
 * \date 2011/09/14 17:16
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __MSGBUTTONCLICK_H_
#define __MSGBUTTONCLICK_H_
#include "msg/IMsgBase.h"
#include "../math/IMath.h"
class MsgButtonSelect : public IMsgBase
{
public:
	DECLARE_RTTI(MsgButtonSelect, IMsgBase);

	MsgButtonSelect(bool bSelect);
	~MsgButtonSelect();
	bool IsSelect()const;

private:
	bool m_bSelect;
};
#endif//__MSGBUTTONCLICK_H_
