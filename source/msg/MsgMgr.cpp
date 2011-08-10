/*!
 * \file MsgMgr.cpp
 * \date 8-10-2011 11:39:44
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <msg/MsgMgr.h>

MsgMgr& MsgMgr::GetInstance()
{
	static MsgMgr s_MsgMgr;
	return s_MsgMgr;
}

MsgMgr::MsgMgr()
{
	m_pMutex = NULL;
}

MsgMgr::~MsgMgr()
{
	// TODO: 
}

bool MsgMgr::Initialize()
{
	m_pMutex = IMutex::CreateMutexObject();
	return true;
}

void MsgMgr::Terminate()
{
	SAFE_RELEASE(m_pMutex);
}

void MsgMgr::SendMessage(IMsgBase* pMsg)
{
	if (!m_pMutex) return;

	m_pMutex->Lock();
	MESSAGE_INFO msgInfo = {pMsg->GetMsgID(), pMsg};
	m_MsgQueue.push(msgInfo);
	m_pMutex->Unlock();
}

void MsgMgr::DispatchMessage()
{
	if (!m_pMutex) return;

	m_pMutex->Lock();
	while (!m_MsgQueue.empty())
	{
		MESSAGE_INFO& msgInfo = m_MsgQueue.front();
		DispatchOneMessage(msgInfo);
		SAFE_DELETE(msgInfo.pMsg);
		m_MsgQueue.pop();
	}
	m_pMutex->Unlock();
}

bool MsgMgr::SubscribeMessage(uint nMsgID, IMsgHandler* pHandler, MSG_CALLBACK pCallback)
{
	if (!m_pMutex) return false;

	// check existing
	TM_SUBSCRIBE_INFO::iterator itfound = FindSubscribeInfo(nMsgID, pHandler);
	if (itfound != m_SubscribeMsgMap.end()) return false;

	SUBSCRIBE_INFO subscribeInfo;
	subscribeInfo.nMsgID = nMsgID;
	subscribeInfo.pHandler = pHandler;
	subscribeInfo.pCallback = pCallback;
	m_SubscribeMsgMap.insert(std::make_pair(nMsgID, subscribeInfo));

	return true;
}

bool MsgMgr::UnsubscribeMessage(uint nMsgID, IMsgHandler* pHandler)
{
	if (!m_pMutex) return false;

	TM_SUBSCRIBE_INFO::iterator itfound = FindSubscribeInfo(nMsgID, pHandler);
	if (itfound == m_SubscribeMsgMap.end()) return false;

	m_SubscribeMsgMap.erase(itfound);
	return true;
}

bool MsgMgr::UnsubscribeMessage(IMsgHandler* pHandler)
{
	// TODO: 
	return false;
}

MsgMgr::TM_SUBSCRIBE_INFO::iterator MsgMgr::FindSubscribeInfo(uint nMsgID, IMsgHandler* pHandler)
{
	std::pair<TM_SUBSCRIBE_INFO::iterator, TM_SUBSCRIBE_INFO::iterator> range = m_SubscribeMsgMap.equal_range(nMsgID);
	for (TM_SUBSCRIBE_INFO::iterator it = range.first; it != range.second; ++it)
	{
		SUBSCRIBE_INFO& subscribeInfo = it->second;
		if (subscribeInfo.pHandler == pHandler) return it;
	}

	return m_SubscribeMsgMap.end();
}

bool MsgMgr::DispatchOneMessage(MESSAGE_INFO& msgInfo)
{
	int nFailedCount = 0;
	bool bResult = false;

	std::pair<TM_SUBSCRIBE_INFO::iterator, TM_SUBSCRIBE_INFO::iterator> range = m_SubscribeMsgMap.equal_range(msgInfo.nMsgID);
	for (TM_SUBSCRIBE_INFO::iterator it = range.first; it != range.second; ++it)
	{
		SUBSCRIBE_INFO& subscribeInfo = it->second;

		IMsgHandler* pHandler = subscribeInfo.pHandler;
		MSG_CALLBACK pCallback = subscribeInfo.pCallback;

		bResult = (pHandler->*pCallback)(msgInfo.nMsgID, msgInfo.pMsg);

		if (!bResult) ++nFailedCount;
	}

	return (bResult && nFailedCount == 0);
}
