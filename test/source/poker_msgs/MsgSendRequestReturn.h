/*!
 * \file MsgSendRequestReturn.h
 * \date unknown
 * 
 * ��ҷ������󷵻صĽ��
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGSENDREQUESTRETURN_H__
#define __MSGSENDREQUESTRETURN_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgSendRequestReturn : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2145,
		MSG_SIZE = 319,
	};

public:
	DECLARE_RTTI(MsgSendRequestReturn, PokerMsgBase);

	MsgSendRequestReturn();
	virtual ~MsgSendRequestReturn();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;	// ���ID
	int64 nFriendUserId;	// ���ѵ����ID
	int64 nRequestId;	// ���ݿⷵ�صĸ�request��ΨһID
	uint unRequestType;	// ���������
	int nPlatformId;	// ��ҵ�½��ƽ̨id, 1��ʾfacebook, 2��ʾgoogle, 3��ʾigg, 4��ʾmsn, 5��ʾtwitter, 6��ʾyahoo
	char szNickName[32];	// ����ǳ�
	char szPlatformAccount[255];	// ��ҵ�½��ƽ̨�˺�

};

#endif // __MSGSENDREQUESTRETURN_H__
