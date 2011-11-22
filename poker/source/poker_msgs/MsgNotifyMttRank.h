/*!
 * \file MsgNotifyMttRank.h
 * \date unknown
 * 
 * ֪ͨshootout�ȼ�
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYMTTRANK_H__
#define __MSGNOTIFYMTTRANK_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyMttRank : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2173,
		MSG_SIZE = 15,
	};

public:
	DECLARE_RTTI(MsgNotifyMttRank, PokerMsgBase);

	MsgNotifyMttRank();
	virtual ~MsgNotifyMttRank();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	char nRank[3];	// Rank Ϊ -1ʱ, ��ʶ��ǰ�ȼ�������~
	int nBonus[3];	// Bonus Ϊ -1ʱ, ��ʶ��ǰ������~

};

#endif // __MSGNOTIFYMTTRANK_H__
