/*!
 * \file MsgRequestBuyItem.h
 * \date unknown
 * 
 * ����������Ʒ
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTBUYITEM_H__
#define __MSGREQUESTBUYITEM_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestBuyItem : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2075,
		MSG_SIZE = 24,
	};

public:
	DECLARE_RTTI(MsgRequestBuyItem, PokerMsgBase);

	MsgRequestBuyItem();
	virtual ~MsgRequestBuyItem();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int nItemType;	// ������Ʒ������
	char nBuyMethod;	// ����ʽ, 1: ����chip�۸�, 2: ����chip�۸�, 3: VIPchip�۸�, 4: ����gold�۸�, 5: ����gold�۸�, 6: VIPgold�۸� 
	char nDestSeatId;	// ���͵�Ŀ����λId -2: ������, -1: �͸�ȫ��, 0-8: Ŀ����λId
	char _dummy[2];
	int64 nCashCouponId;	// ���ʹ�ô���ȯ�Ļ����ʹ���ȯ��Id ����Ϊ-1

};

#endif // __MSGREQUESTBUYITEM_H__
