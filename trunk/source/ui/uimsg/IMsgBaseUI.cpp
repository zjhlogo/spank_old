/*!
 * \file IMsgBaseUI.cpp
 * \date 9-15-2011 10:03:48
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <ui/uimsg/IMsgBaseUI.h>
#include <msg/MsgID.h>

IMsgBaseUI::IMsgBaseUI(uint nMsgID, UIWindow* pSender)
:IMsgBase(nMsgID),
m_pSender(pSender)
{
	// TODO: 
}

IMsgBaseUI::~IMsgBaseUI()
{
	// TODO: 
}

UIWindow* IMsgBaseUI::GetSender()
{
	return m_pSender;
}

int IMsgBaseUI::GetSenderID() const
{
	return m_pSender->GetID();
}
