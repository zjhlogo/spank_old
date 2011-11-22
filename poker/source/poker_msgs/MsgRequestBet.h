/*!
 * \file MsgRequestBet.h
 * \date unknown
 * 
 * �����ע��
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTBET_H__
#define __MSGREQUESTBET_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestBet : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2011,
		MSG_SIZE = 20,
	};

public:
	DECLARE_RTTI(MsgRequestBet, PokerMsgBase);

	MsgRequestBet();
	virtual ~MsgRequestBet();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	uchar nSeatId;	// ��λID
	char _dummy[3];
	int64 nBet;	// ��ע�ĳ���, -1Ϊ����, ����ʱ�������ڵ�����

};

#endif // __MSGREQUESTBET_H__
