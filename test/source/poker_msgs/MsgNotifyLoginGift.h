/*!
 * \file MsgNotifyLoginGift.h
 * \date unknown
 * 
 * ������¼������ȡ��
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYLOGINGIFT_H__
#define __MSGNOTIFYLOGINGIFT_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyLoginGift : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2064,
		MSG_SIZE = 28,
	};

public:
	DECLARE_RTTI(MsgNotifyLoginGift, PokerMsgBase);

	MsgNotifyLoginGift();
	virtual ~MsgNotifyLoginGift();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// ���ID
	char nContinuousLogin;	// ������¼����(7��Ϊ����)
	char nLastContinuousLogin;	// �ϴ�������¼����
	char _dummy[2];
	int64 _dummy1[2];	// ���ͻ��˱�����ռλ��, �ڿͻ������޸ĺ�Ӧ��ɾȥ��

};

#endif // __MSGNOTIFYLOGINGIFT_H__
