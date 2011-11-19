/*!
 * \file MsgSendRequest.h
 * \date unknown
 * 
 * ����ҷ�������
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGSENDREQUEST_H__
#define __MSGSENDREQUEST_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgSendRequest : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2144,
		MSG_SIZE = 20,
	};

public:
	DECLARE_RTTI(MsgSendRequest, PokerMsgBase);

	MsgSendRequest();
	virtual ~MsgSendRequest();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// ���ID
	int64 nFriendUserId;	// ���ѵ�ID
	uint nRType;	// ��������� 

};

#endif // __MSGSENDREQUEST_H__
