/*!
 * \file MsgMgr.h
 * \date 8-10-2011 10:40:55
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __MSGMGR_H__
#define __MSGMGR_H__

#include "../IMgr.h"
#include "../IMutex.h"
#include "IMsgBase.h"
#include <map>
#include <queue>

class MsgMgr : public IMgr
{
public:
	typedef struct SUBSCRIBE_INFO_tag
	{
		uint nMsgID;
		IMsgHandler* pHandler;
		MSG_CALLBACK pCallback;
	} SUBSCRIBE_INFO;

	typedef std::multimap<uint, SUBSCRIBE_INFO> TM_SUBSCRIBE_INFO;

	typedef struct MESSAGE_INFO_tag
	{
		uint nMsgID;
		IMsgBase* pMsg;
	} MESSAGE_INFO;

	typedef std::queue<MESSAGE_INFO> TQ_MESSAGE_INFO;

public:
	MsgMgr();
	virtual ~MsgMgr();

	static MsgMgr& GetInstance();

	virtual bool Initialize();
	virtual void Terminate();

	void SendMessage(IMsgBase* pMsg);
	void DispatchMessage();

	bool SubscribeMessage(uint nMsgID, IMsgHandler* pHandler, MSG_CALLBACK pCallback);
	bool UnsubscribeMessage(uint nMsgID, IMsgHandler* pHandler);
	bool UnsubscribeMessage(IMsgHandler* pHandler);

private:
	TM_SUBSCRIBE_INFO::iterator FindSubscribeInfo(uint nMsgID, IMsgHandler* pHandler);
	bool DispatchOneMessage(MESSAGE_INFO& msgInfo);

private:
	IMutex* m_pMutex;
	TM_SUBSCRIBE_INFO m_SubscribeMsgMap;
	TQ_MESSAGE_INFO m_MsgQueue;

};
#endif // __MSGMGR_H__
