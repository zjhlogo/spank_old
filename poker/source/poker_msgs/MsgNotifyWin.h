/*!
 * \file MsgNotifyWin.h
 * \date unknown
 * 
 * ����֪ͨ��
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYWIN_H__
#define __MSGNOTIFYWIN_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyWin : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2016,
		MSG_SIZE = 20,
	};

public:
	DECLARE_RTTI(MsgNotifyWin, PokerMsgBase);

	MsgNotifyWin();
	virtual ~MsgNotifyWin();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	uchar nPoolId;	// ����Id, ���ΪΨһδ���Ƶ���Ӯ�����, ����Ϊ-1, ��ʾ���н���һ���Է���
	short nSeatIds;	// �񽱵�������λId, ��λ��ʾ. ��0λΪ1ʱ, ָ��0����λ�����������ء�����ָ�����.
	char _dummy;
	int64 nBonus;	// ����, ÿ���˴������������õĽ���

};

#endif // __MSGNOTIFYWIN_H__
