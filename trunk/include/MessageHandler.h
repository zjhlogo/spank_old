/*!
 * \file MessageHandler.h
 * \date 20-05-2011 21:56:13
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __MESSAGEHANDLER_H__
#define __MESSAGEHANDLER_H__

#include "util/StreamReader.h"

class MessageHandler;
typedef bool (MessageHandler::*MSG_FUNC)(int nMsgID, StreamReader* pReader);

class MessageHandler
{
public:
	MessageHandler();
	virtual ~MessageHandler();

	virtual bool RegisterMessage(int nMsgID, MSG_FUNC pFunc);
	virtual bool UnregisterMessage(int nMsgID);

};
#endif // __MESSAGEHANDLER_H__
