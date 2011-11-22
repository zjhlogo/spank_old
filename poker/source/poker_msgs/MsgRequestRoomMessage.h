/*!
 * \file MsgRequestRoomMessage.h
 * \date unknown
 * 
 * ��ҷ�����������ʾ
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTROOMMESSAGE_H__
#define __MSGREQUESTROOMMESSAGE_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestRoomMessage : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2027,
		MSG_SIZE = 148,
	};

public:
	DECLARE_RTTI(MsgRequestRoomMessage, PokerMsgBase);

	MsgRequestRoomMessage();
	virtual ~MsgRequestRoomMessage();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// �����ID
	short nMsgLength;	// ������Ϣ����.
	char _dummy[2];
	int64 nDest;	// Ŀ�����, ����ͬ�����ڵ���ҡ�-1: ������Ⱥ��
	char szMessage[128];	// ������Ϣ����

};

#endif // __MSGREQUESTROOMMESSAGE_H__
