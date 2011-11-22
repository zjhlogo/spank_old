/*!
 * \file MsgUpdateVolidatePlayerInfo.h
 * \date unknown
 * 
 * ���³���������Ϣ
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGUPDATEVOLIDATEPLAYERINFO_H__
#define __MSGUPDATEVOLIDATEPLAYERINFO_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgUpdateVolidatePlayerInfo : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2068,
		MSG_SIZE = 40,
	};

public:
	DECLARE_RTTI(MsgUpdateVolidatePlayerInfo, PokerMsgBase);

	MsgUpdateVolidatePlayerInfo();
	virtual ~MsgUpdateVolidatePlayerInfo();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// ���ID
	uchar nLevel;	// �ȼ�
	char _dummy[3];
	int64 nCoins;	// ���ʲ�
	int64 nWinThisWeek;	// ����Ӯ��
	int nCash;	// ��ֵ
	uint nExp;	// ����ֵ
	int nTrinket;	// ��Ʒ

};

#endif // __MSGUPDATEVOLIDATEPLAYERINFO_H__
