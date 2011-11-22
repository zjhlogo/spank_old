/*!
 * \file MsgRequestRoomMembers.h
 * \date unknown
 * 
 * ���󷿼��ڳ�Ա��Ϣ
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTROOMMEMBERS_H__
#define __MSGREQUESTROOMMEMBERS_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestRoomMembers : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2032,
		MSG_SIZE = 16,
	};

public:
	DECLARE_RTTI(MsgRequestRoomMembers, PokerMsgBase);

	MsgRequestRoomMembers();
	virtual ~MsgRequestRoomMembers();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// ���ID
	int nRoomId;	// ����ID
	char nMemberType;	// ��Ա����, 0: ���г�Ա, 1: ������Ա, 2: �Թ۳�Ա
	char _dummy[3];	// ���󷿼��ڳ�Ա��Ϣ��

};

#endif // __MSGREQUESTROOMMEMBERS_H__
