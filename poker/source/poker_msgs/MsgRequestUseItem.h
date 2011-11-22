/*!
 * \file MsgRequestUseItem.h
 * \date unknown
 * 
 * �ͻ�������ʹ�õ���
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTUSEITEM_H__
#define __MSGREQUESTUSEITEM_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestUseItem : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2104,
		MSG_SIZE = 16,
	};

public:
	DECLARE_RTTI(MsgRequestUseItem, PokerMsgBase);

	MsgRequestUseItem();
	virtual ~MsgRequestUseItem();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int64 nItemId;	// Ҫʹ�õ���ƷId -1: ��ʾȡ����Ʒ

};

#endif // __MSGREQUESTUSEITEM_H__
