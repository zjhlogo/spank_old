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

class IMsgHandler
{
public:
	IMsgHandler() {};
	~IMsgHandler() {};
	// TODO: 
};

typedef bool (IMsgHandler::*MSG_CALLBACK)(uint nMsgID, IMsgBase* pMsg);

#endif // __IMSGHANDLER_H__
