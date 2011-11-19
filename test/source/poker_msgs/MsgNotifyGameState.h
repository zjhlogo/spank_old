/*!
 * \file MsgNotifyGameState.h
 * \date unknown
 * 
 * ��Ϸ����֪ͨ��
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYGAMESTATE_H__
#define __MSGNOTIFYGAMESTATE_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyGameState : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2012,
		MSG_SIZE = 16,
	};

public:
	DECLARE_RTTI(MsgNotifyGameState, PokerMsgBase);

	MsgNotifyGameState();
	virtual ~MsgNotifyGameState();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	char nBankerSeat;	// ׯ����λID
	char nSmallBlindSeat;	// Сäע��λID
	char nBigBlindSeat;	// ��äע��λID
	char nGameStatus;	// ��Ϸ״̬, 0: δ����, 1: �ѿ���.
	char nRoomStatus;	// ����״̬: 0: stopping 1: running 
	uchar nHandCards[2];	// ��ҵ�ǰ������, ��ΧΪ0~51, ��ʾ52�����е�һ��, ��������, ��Ϊ255.
	char _dummy;

};

#endif // __MSGNOTIFYGAMESTATE_H__
