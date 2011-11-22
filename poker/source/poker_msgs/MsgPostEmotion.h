/*!
 * \file MsgPostEmotion.h
 * \date unknown
 * 
 * �����ͱ���
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGPOSTEMOTION_H__
#define __MSGPOSTEMOTION_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgPostEmotion : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2050,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgPostEmotion, PokerMsgBase);

	MsgPostEmotion();
	virtual ~MsgPostEmotion();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// ���ID
	short nEmotionId;	// ����ID, ʵ�ʱ����ɿͻ���ָ��
	char _dummy[2];	// ����λ

};

#endif // __MSGPOSTEMOTION_H__
