/*!
 * \file MsgRequestMakeFriend.h
 * \date unknown
 * 
 * ��ҼӺ��������
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTMAKEFRIEND_H__
#define __MSGREQUESTMAKEFRIEND_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestMakeFriend : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2018,
		MSG_SIZE = 20,
	};

public:
	DECLARE_RTTI(MsgRequestMakeFriend, PokerMsgBase);

	MsgRequestMakeFriend();
	virtual ~MsgRequestMakeFriend();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// �����ID
	char nSeatId;	// �Է�����λID
	char _dummy[3];
	int64 nFriendUserId;	// �Է���FacebookID

};

#endif // __MSGREQUESTMAKEFRIEND_H__
