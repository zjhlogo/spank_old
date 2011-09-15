/*!
 * \file MsgCheck.cpp
 * \date 2011/09/14 17:16
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <ui/uimsg/MsgCheck.h>
#include <ui/uimsg/UIMsgID.h>

MsgCheck::MsgCheck(bool bChecked, UIWindow* pSender)
:IMsgBaseUI(UMI_CHECKED, pSender)
{
	SetChecked(bChecked);
}

MsgCheck::~MsgCheck()
{
	//TODO:
}

void MsgCheck::SetChecked(bool bChecked)
{
	m_bChecked = bChecked;
}

bool MsgCheck::IsChecked() const
{
	return m_bChecked;
}
