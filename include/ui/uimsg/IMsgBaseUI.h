/*!
 * \file IMsgBaseUI.h
 * \date 9-15-2011 10:03:43
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IMSGBASEUI_H__
#define __IMSGBASEUI_H__

#include "../../msg/IMsgBase.h"
#include "../UIWindow.h"

class IMsgBaseUI : public IMsgBase
{
public:
	DECLARE_RTTI(IMsgBaseUI, IMsgBase);

	IMsgBaseUI(uint nMsgID, UIWindow* pSender);
	~IMsgBaseUI();

	UIWindow* GetSender();
	int GetSenderID() const;

private:
	UIWindow* m_pSender;

};
#endif // __IMSGBASEUI_H__
