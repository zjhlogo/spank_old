/*!
 * \file MsgRespBuyItem.h
 * \date unknown
 * 
 * �𸴹�����ߵ�����
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGRESPBUYITEM_H__
#define __MSGRESPBUYITEM_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRespBuyItem : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2082,
		MSG_SIZE = 24,
	};

public:
	DECLARE_RTTI(MsgRespBuyItem, PokerMsgBase);

	MsgRespBuyItem();
	virtual ~MsgRespBuyItem();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// ������Id
	int nItemType;	// ���򵽵���Ʒ���� -1: ��ʾ����ʧ��
	int64 nCashCouponId;	// ����ʹ�õĴ���ȯId -1: ��ʾ��
	int nCashCouponBalance;	// ����ʹ�õĴ���ȯ��� -1: ��ʾ��

};

#endif // __MSGRESPBUYITEM_H__
