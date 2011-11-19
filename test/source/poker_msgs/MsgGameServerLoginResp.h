/*!
 * \file MsgGameServerLoginResp.h
 * \date unknown
 * 
 * ����GameServer��Ϣ����
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGGAMESERVERLOGINRESP_H__
#define __MSGGAMESERVERLOGINRESP_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgGameServerLoginResp : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 1005,
		MSG_SIZE = 20,
	};

public:
	DECLARE_RTTI(MsgGameServerLoginResp, PokerMsgBase);

	MsgGameServerLoginResp();
	virtual ~MsgGameServerLoginResp();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int nLoginResult;	// 0: ��½�ɹ�, 1: GameServerδ����, 2: GameServer��������, 3: UserServerδ����, 4: DbServerδ����, 5: ���ݶ�ȡ������, 6: ID���ڵ�¼��, 7: ��֤ʧ��, 8: ��֤��ʱ, 9: �û�δ��װ��Ϸ(fql��permission��)
	int64 nUserId;
	int64 nIggId;

};

#endif // __MSGGAMESERVERLOGINRESP_H__
