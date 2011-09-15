/*!
 * \file MsgCheck.h
 * \date 2011/09/14 17:16
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __MSGCHECK_H__
#define __MSGCHECK_H__

#include "IMsgBaseUI.h"

class MsgCheck : public IMsgBaseUI
{
public:
	DECLARE_RTTI(MsgCheck, IMsgBaseUI);

	MsgCheck(bool bChecked, UIWindow* pSender);
	~MsgCheck();

	void SetChecked(bool bChecked);
	bool IsChecked() const;

private:
	bool m_bChecked;

};
#endif // __MSGCHECK_H__
