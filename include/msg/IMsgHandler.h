/*!
 * \file IMsgHandler.h
 * \date 8-10-2011 10:44:37
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IMSGHANDLER_H__
#define __IMSGHANDLER_H__

#include "BaseType.h"
#include "IMsgBase.h"
#include <map>

class IMsgHandler;
typedef bool (IMsgHandler::*MSG_CALLBACK)(IMsgBase* pMsg);

#define CAST_MSG_CALLBACK(x) reinterpret_cast<MSG_CALLBACK>(x)

class IMsgHandler
{
public:
	typedef struct CONNECTION_INFO_tag
	{
		uint nMsgID;
		IMsgHandler* pHandler;
		MSG_CALLBACK pCallback;
	} CONNECTION_INFO;

	typedef std::map<uint, CONNECTION_INFO> TM_CONNECTION_INFO;

public:
	IMsgHandler();
	virtual ~IMsgHandler();

	bool ConnectEvent(uint nMsgID, IMsgHandler* pHandler, MSG_CALLBACK pCallback);
	bool DisconnectEvent(uint nMsgID);

protected:
	bool CallEvent(IMsgBase& msgBase);

private:
	CONNECTION_INFO* FindConnectionInfo(uint nMsgID);

private:
	TM_CONNECTION_INFO m_ConnectionMap;

};

#endif // __IMSGHANDLER_H__
