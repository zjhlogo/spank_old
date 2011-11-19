/*!
 * \file MsgRespFriendInfo.h
 * \date unknown
 * 
 * ���ߺ���/������Ϣ��ÿ��һ�����ɷ����
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGRESPFRIENDINFO_H__
#define __MSGRESPFRIENDINFO_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRespFriendInfo : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2023,
		MSG_SIZE = 52,
	};

public:
	DECLARE_RTTI(MsgRespFriendInfo, PokerMsgBase);

	MsgRespFriendInfo();
	virtual ~MsgRespFriendInfo();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// ���ID
	int64 nFriendUserId;	// ����ID
	char nInFacebook;	// �Ƿ� Facebook ����
	uchar nLevel;	// �ȼ�
	char _dummy[2];	// ����λ
	int64 nCoins;	// ���ʲ�
	int64 nMostCoins;	// ���ʲ�����ʷ��߼�¼
	int nCash;	// ��ֵ
	uint nLogoutTime;
	int64 nWinThisWeek;	// ����Ӯ��

};

#endif // __MSGRESPFRIENDINFO_H__
