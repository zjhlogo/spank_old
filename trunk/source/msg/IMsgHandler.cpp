/*!
 * \file IMsgHandler.cpp
 * \date 8-16-2011 11:25:02
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <msg/IMsgHandler.h>
#include <util/IDebugUtil.h>

IMsgHandler::IMsgHandler()
{
	// TODO: 
}

IMsgHandler::~IMsgHandler()
{
	// TODO: 
}

bool IMsgHandler::CallEvent(IMsgBase& msgBase)
{
	CONNECTION_INFO* pInfo = FindConnectionInfo(msgBase.GetMsgID());
	if (!pInfo) return false;

	IMsgHandler* pHandler = pInfo->pHandler;
	MSG_CALLBACK pCallback = pInfo->pCallback;

	bool bOK = (pHandler->*pCallback)(&msgBase);
	return bOK;
}

bool IMsgHandler::ConnectEvent(uint nMsgID, IMsgHandler* pHandler, MSG_CALLBACK pCallback)
{
	if (nMsgID == 0 || !pHandler || !pCallback) return false;

	if (FindConnectionInfo(nMsgID))
	{
		LOGE("connect event failed, duplicate event connection");
		return false;
	}

	CONNECTION_INFO info = {nMsgID, pHandler, pCallback};
	m_ConnectionMap.insert(std::make_pair(nMsgID, info));
	return true;
}

bool IMsgHandler::DisconnectEvent(uint nMsgID)
{
	TM_CONNECTION_INFO::iterator itfound = m_ConnectionMap.find(nMsgID);
	if (itfound == m_ConnectionMap.end()) return false;

	m_ConnectionMap.erase(itfound);
	return true;
}

IMsgHandler::CONNECTION_INFO* IMsgHandler::FindConnectionInfo(uint nMsgID)
{
	TM_CONNECTION_INFO::iterator itfound = m_ConnectionMap.find(nMsgID);
	if (itfound == m_ConnectionMap.end()) return NULL;

	return &(itfound->second);
}
