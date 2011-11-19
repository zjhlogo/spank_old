/*!
 * \file MsgRoomInfo.h
 * \date unknown
 * 
 * ���뷿���Ļظ�
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGROOMINFO_H__
#define __MSGROOMINFO_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRoomInfo : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2006,
		MSG_SIZE = 420,
	};

public:
	DECLARE_RTTI(MsgRoomInfo, PokerMsgBase);

	MsgRoomInfo();
	virtual ~MsgRoomInfo();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// Ŀ���û���Id
	NET_ROOM_INFO stRoomInfo;	// ������Ϣ
	NET_SEAT_INFO stSeats[9];	// ��λ��Ϣ 0 Ϊ�ƹ����ֱߵ�һ��
	char nBanker;	// ׯ����λ, ����Ϸδ��ʼ, ��Ϊ-1.
	char nSmallBlind;	// Сäע��λ, ����Ϸδ��ʼ, ��Ϊ-1.
	char nBigBlind;	// ��äע��λ, ����Ϸδ��ʼ, ��Ϊ-1.
	char nPublicCards[5];	// ���Ź���, û�е�λ��Ϊ-1.
	int64 nPools[8];	// 8������, û�еĵط�Ϊ0.
	uchar nHandCards[2];	// ��ҵ�ǰ������, ��������, ��Ϊ255��
	char _dummy[2];

};

#endif // __MSGROOMINFO_H__
