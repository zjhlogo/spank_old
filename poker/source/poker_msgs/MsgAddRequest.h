/*!
 * \file MsgAddRequest.h
 * \date unknown
 * 
 *     
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGADDREQUEST_H__
#define __MSGADDREQUEST_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgAddRequest : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2148,
		MSG_SIZE = 319,
	};

public:
	DECLARE_RTTI(MsgAddRequest, PokerMsgBase);

	MsgAddRequest();
	virtual ~MsgAddRequest();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nRequestId;	// REQUEST��ID
	int64 nUserId;	// ����REQUEST�����ID
	int64 nFriendId;	// ����REQUEST�ĺ���ID
	uint nRequestType;	// REQUEST����
	int nPlatformId;	// ��ҵ�½��ƽ̨id, 1��ʾfacebook, 2��ʾgoogle, 3��ʾigg, 4��ʾmsn, 5��ʾtwitter, 6��ʾyahoo
	char szNickName[32];	// ����ǳ�
	char szPlatAccount[255];	// ��ҵ�½��ƽ̨�˺�

};

#endif // __MSGADDREQUEST_H__
