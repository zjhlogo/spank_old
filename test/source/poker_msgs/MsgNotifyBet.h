/*!
 * \file MsgNotifyBet.h
 * \date unknown
 * 
 * ֪ͨ��ע
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYBET_H__
#define __MSGNOTIFYBET_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyBet : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2010,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgNotifyBet, PokerMsgBase);

	MsgNotifyBet();
	virtual ~MsgNotifyBet();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	char nSeatId;	// ��λID
	char nTime;	// ʣ��ȴ�ʱ��, ��λΪ��
	char nTotalTime;	// �ܵĵȴ�ʱ��, ���ڲ��ŵ���ʱ����
	char _dummy;	// ����λ.

};

#endif // __MSGNOTIFYBET_H__
