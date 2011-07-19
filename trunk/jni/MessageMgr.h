/*!
 * \file MessageMgr.h
 * \date 20-05-2011 21:55:02
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __MESSAGEMGR_H__
#define __MESSAGEMGR_H__

#include <queue>
#include <map>
#include <pthread.h>
#include "msg/MsgBase.h"
#include "MessageHandler.h"

class MessageMgr
{
public:
	typedef struct MESSAGE_INFO_tag
	{
		int nMsgID;
		MessageHandler* pHandler;
		MSG_FUNC pFunc;
	} MESSAGE_INFO;

	typedef std::multimap<int, MESSAGE_INFO> TM_MESSAGE_INFO;

	typedef struct MESSAGE_DATA_tag
	{
		int nMsgID;
		StreamWriter* pWriter;
	} MESSAGE_DATA;

	typedef std::queue<MESSAGE_DATA*> TQ_MESSAGE_DATA;

public:
	MessageMgr();
	~MessageMgr();

	static MessageMgr& GetInstance();

	bool Initialize();
	void Terminate();

	void PushMessage(MsgBase& msg);
	void DispatchMessage();

	bool RegisterMessage(int nMsgID, MessageHandler* pHandler, MSG_FUNC pFunc);
	bool UnregisterMessage(int nMsgID, MessageHandler* pHandler);

private:
	void Lock();
	void Unlock();

	bool DispatchOneMessage(MESSAGE_DATA* pMsgData);
	TM_MESSAGE_INFO::iterator FindMsgInfo(int nMsgID, MessageHandler* pHandler);

	MESSAGE_DATA* CreateMessageData(MsgBase* pMsgBase);
	void DeleteMessageData(MESSAGE_DATA* pMsgData);

private:
	pthread_mutex_t m_Mutex;
	TQ_MESSAGE_DATA m_MsgQueues;
	TM_MESSAGE_INFO m_MsgInfoMap;
	bool m_bInitialized;

};
#endif // __MESSAGEMGR_H__
