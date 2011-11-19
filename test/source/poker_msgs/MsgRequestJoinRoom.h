/*!
 * \file MsgRequestJoinRoom.h
 * \date unknown
 * 
 * ������뷿��
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTJOINROOM_H__
#define __MSGREQUESTJOINROOM_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestJoinRoom : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2005,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgRequestJoinRoom, PokerMsgBase);

	MsgRequestJoinRoom();
	virtual ~MsgRequestJoinRoom();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int nRoomId;	// -1: ��ʾ�뿪���� -10 ���ٽ��� low -11 ���ٽ��� mid -12 ���ٽ��� high -20 ����MTT �ȼ�1 -21 ����MTT�ȼ�2 -22 ����MTT�ȼ�3 -30 ���� �ܽ����� -510 ���ٽ���5�˷�

};

#endif // __MSGREQUESTJOINROOM_H__
