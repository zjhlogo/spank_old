/*!
 * \file MsgInitPlayerInfo.h
 * \date unknown
 * 
 * ��¼ʱ��ʼ���������Ϣ
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGINITPLAYERINFO_H__
#define __MSGINITPLAYERINFO_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgInitPlayerInfo : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2067,
		MSG_SIZE = 70,
	};

public:
	DECLARE_RTTI(MsgInitPlayerInfo, PokerMsgBase);

	MsgInitPlayerInfo();
	virtual ~MsgInitPlayerInfo();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// ���ID
	uchar nLevel;	// �ȼ�
	uchar nFlags;	// ��־λ��0λ: �Ƿ��˿, (1λ: �Ƿ������ǩ, 2λ: �Ƿ������ʼ�, 3λ: �Ƿ�����NewsFeed), 4λ: �Ƿ�VIP, 5λ: �Ƿ�GM ע, Ŀǰ1, 2, 3, 4λ�Ѿ�ʧЧ��
	uchar nShootOutRank;	// MTTĿǰ�ȼ�
	char nShootOutPlace[3];	// MTT��ʷ������Ϣ
	int64 nCoins;	// ���ʲ�
	int64 nMostCoins;	// ���ʲ�����ʷ��߼�¼
	int64 nWinThisWeek;	// ����Ӯ��
	int nCash;	// ��ֵ
	uint nExp;	// ����ֵ
	int64 nChampionInBuddiesLastWeek;	// ���ܴ�Ӯ�ҵ����ID
	int64 nMostWinInBuddiesLastWeek;	// ���ܴ�Ӯ�ҵ�Ӯ��
	int nTrinket;
	uint nTutorialFlags;	// ���ֽ̳���ɶȱ�־λ

};

#endif // __MSGINITPLAYERINFO_H__
