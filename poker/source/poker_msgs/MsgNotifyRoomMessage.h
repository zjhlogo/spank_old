/*!
 * \file MsgNotifyRoomMessage.h
 * \date unknown
 * 
 * ֪ͨ�����ڵ�������Ϣ
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYROOMMESSAGE_H__
#define __MSGNOTIFYROOMMESSAGE_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyRoomMessage : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2028,
		MSG_SIZE = 29,
	};

public:
	DECLARE_RTTI(MsgNotifyRoomMessage, PokerMsgBase);

	MsgNotifyRoomMessage();
	virtual ~MsgNotifyRoomMessage();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// ���ID
	int64 nSenderUserId;	// ����������Ϣ�����ID
	short nMsgLength;	// ������Ϣ����.
	char _dummy[2];
	int64 nDest;	// Ŀ�����, ����ͬ�����ڵ���ҡ�-1: ������Ⱥ��
	char nMessage;	// ������Ϣ����

};

#endif // __MSGNOTIFYROOMMESSAGE_H__
