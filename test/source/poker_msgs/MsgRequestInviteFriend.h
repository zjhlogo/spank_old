/*!
 * \file MsgRequestInviteFriend.h
 * \date unknown
 * 
 * ���������Ѽ��뷿��
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTINVITEFRIEND_H__
#define __MSGREQUESTINVITEFRIEND_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestInviteFriend : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2030,
		MSG_SIZE = 20,
	};

public:
	DECLARE_RTTI(MsgRequestInviteFriend, PokerMsgBase);

	MsgRequestInviteFriend();
	virtual ~MsgRequestInviteFriend();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// ���ID
	int64 nFriendUserId;	// ������ĺ������ID
	int nRoomId;	// ��ҵ�ǰ��RoomId

};

#endif // __MSGREQUESTINVITEFRIEND_H__
