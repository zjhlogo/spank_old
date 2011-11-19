/*!
 * \file MsgSendRoleRequestList.h
 * \date unknown
 * 
 * ����ҷ���requests�б�
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGSENDROLEREQUESTLIST_H__
#define __MSGSENDROLEREQUESTLIST_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgSendRoleRequestList : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2143,
		MSG_SIZE = 330,
	};

public:
	DECLARE_RTTI(MsgSendRoleRequestList, PokerMsgBase);

	MsgSendRoleRequestList();
	virtual ~MsgSendRoleRequestList();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 UserId;	// ��ҵ�ID
	bool bTail;	// �Ƿ��β
	char _dummy;	// ռλ��
	NET_REQUEST_DATA stRequestList[10];	// ��ҵ�REQUEST �б�

};

#endif // __MSGSENDROLEREQUESTLIST_H__
