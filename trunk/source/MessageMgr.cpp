/*!
 * \file MessageMgr.cpp
 * \date 20-05-2011 21:55:10
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <MessageMgr.h>

MessageMgr::MessageMgr()
{
	m_bInitialized = false;
	memset(&m_Mutex, 0, sizeof(m_Mutex));
}

MessageMgr::~MessageMgr()
{
	Terminate();
}

MessageMgr& MessageMgr::GetInstance()
{
	static MessageMgr s_Handler;
	return s_Handler;
}

bool MessageMgr::Initialize()
{
	if (pthread_mutex_init(&m_Mutex, NULL) != 0) return false;
	m_bInitialized = true;
	return true;
}

void MessageMgr::Terminate()
{
	m_bInitialized = false;
	pthread_mutex_destroy(&m_Mutex);
}

void MessageMgr::Lock()
{
	pthread_mutex_lock(&m_Mutex);
}

void MessageMgr::Unlock()
{
	pthread_mutex_unlock(&m_Mutex);
}

void MessageMgr::PushMessage(MsgBase& msg)
{
	if (!m_bInitialized) return;

	Lock();
	MESSAGE_DATA* pMsgData = CreateMessageData(&msg);
	m_MsgQueues.push(pMsgData);
	Unlock();
}

void MessageMgr::DispatchMessage()
{
	if (!m_bInitialized) return;
	Lock();
	while (!m_MsgQueues.empty())
	{
		MESSAGE_DATA* pMsgData = m_MsgQueues.front();
		m_MsgQueues.pop();

		DispatchOneMessage(pMsgData);

		DeleteMessageData(pMsgData);
	}
	Unlock();
}

bool MessageMgr::DispatchOneMessage(MESSAGE_DATA* pMsgData)
{
	int nFailedCount = 0;
	bool bResult = false;

	StreamReader stmReader(pMsgData->pWriter->GetBuffer(), pMsgData->pWriter->GetBufferSize());

	std::pair<TM_MESSAGE_INFO::iterator, TM_MESSAGE_INFO::iterator> range = m_MsgInfoMap.equal_range(pMsgData->nMsgID);
	for (TM_MESSAGE_INFO::iterator it = range.first; it != range.second; ++it)
	{
		MESSAGE_INFO& msgInfo = it->second;

		MessageHandler* pHandler = msgInfo.pHandler;
		MSG_FUNC pFunc = msgInfo.pFunc;

		stmReader.Reset();
		bResult = (pHandler->*pFunc)(pMsgData->nMsgID, &stmReader);

		if (!bResult) ++nFailedCount;
	}

	return (bResult && nFailedCount == 0);
}

bool MessageMgr::RegisterMessage(int nMsgID, MessageHandler* pHandler, MSG_FUNC pFunc)
{
	if (!m_bInitialized) return false;

	// check existing
	TM_MESSAGE_INFO::iterator it = FindMsgInfo(nMsgID, pHandler);
	if (it != m_MsgInfoMap.end()) return false;

	MESSAGE_INFO msgInfo;
	msgInfo.nMsgID = nMsgID;
	msgInfo.pHandler = pHandler;
	msgInfo.pFunc = pFunc;
	m_MsgInfoMap.insert(std::make_pair(nMsgID, msgInfo));

	return true;
}

bool MessageMgr::UnregisterMessage(int nMsgID, MessageHandler* pHandler)
{
	if (!m_bInitialized) return false;

	TM_MESSAGE_INFO::iterator it = FindMsgInfo(nMsgID, pHandler);
	if (it == m_MsgInfoMap.end()) return false;

	m_MsgInfoMap.erase(it);
	return true;
}

MessageMgr::TM_MESSAGE_INFO::iterator MessageMgr::FindMsgInfo(int nMsgID, MessageHandler* pHandler)
{
	std::pair<TM_MESSAGE_INFO::iterator, TM_MESSAGE_INFO::iterator> range = m_MsgInfoMap.equal_range(nMsgID);
	for (TM_MESSAGE_INFO::iterator it = range.first; it != range.second; ++it)
	{
		MESSAGE_INFO& msgInfo = it->second;
		if (msgInfo.pHandler == pHandler) return it;
	}

	return m_MsgInfoMap.end();
}

MessageMgr::MESSAGE_DATA* MessageMgr::CreateMessageData(MsgBase* pMsgBase)
{
	MESSAGE_DATA* pMsgData = new MESSAGE_DATA;
	pMsgData->nMsgID = pMsgBase->GetID();
	pMsgData->pWriter = new StreamWriter();
	pMsgBase->ToBuffer(pMsgData->pWriter);
	return pMsgData;
}

void MessageMgr::DeleteMessageData(MESSAGE_DATA* pMsgData)
{
	delete pMsgData->pWriter;
	delete pMsgData;
}
