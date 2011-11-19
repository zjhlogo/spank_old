/*!
 * \file MsgNotifyAcceptFriend.h
 * \date unknown
 * 
 * ��ʾ������ĳ����λ������ѳ�Ϊ����
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYACCEPTFRIEND_H__
#define __MSGNOTIFYACCEPTFRIEND_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyAcceptFriend : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2021,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgNotifyAcceptFriend, PokerMsgBase);

	MsgNotifyAcceptFriend();
	virtual ~MsgNotifyAcceptFriend();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// ���ID
	char nSourceSeatId;	// ����Ӻ�������������λID
	char nDestSeatId;	// �յ���������������λID
	char _dummy[2];

};

#endif // __MSGNOTIFYACCEPTFRIEND_H__
