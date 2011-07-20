/*!
 * \file MessageHandler.cpp
 * \date 20-05-2011 22:00:06
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <MessageHandler.h>
#include <MessageMgr.h>

MessageHandler::MessageHandler()
{

}

MessageHandler::~MessageHandler()
{

}

bool MessageHandler::RegisterMessage(int nMsgID, MSG_FUNC pFunc)
{
	return MessageMgr::GetInstance().RegisterMessage(nMsgID, this, pFunc);
}

bool MessageHandler::UnregisterMessage(int nMsgID)
{
	return MessageMgr::GetInstance().UnregisterMessage(nMsgID, this);
}
