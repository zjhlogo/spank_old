/*!
 * \file MsgNotifySmallBlind.h
 * \date unknown
 * 
 * ��֪�ͻ���Сäע��ֵ
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYSMALLBLIND_H__
#define __MSGNOTIFYSMALLBLIND_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifySmallBlind : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2091,
		MSG_SIZE = 16,
	};

public:
	DECLARE_RTTI(MsgNotifySmallBlind, PokerMsgBase);

	MsgNotifySmallBlind();
	virtual ~MsgNotifySmallBlind();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int64 nSmallBlind;

};

#endif // __MSGNOTIFYSMALLBLIND_H__
