/*!
 * \file MsgUserStatus.h
 * \date unknown
 * 
 * ������ҵ�ǰ��λ�ã���������Ӧ��ԭ��
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGUSERSTATUS_H__
#define __MSGUSERSTATUS_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgUserStatus : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2058,
		MSG_SIZE = 16,
	};

public:
	DECLARE_RTTI(MsgUserStatus, PokerMsgBase);

	MsgUserStatus();
	virtual ~MsgUserStatus();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	char nStatus;	// λ����Ϣ, 0: ����, 1: ��ͨ����, 2: SitNGo����, 3: MTT����, 4: �ܽ���������
	char nReason;	// �����ʾ, 0: ����ʾ, 1: �������, ���뿪����, 2: MTT��������/����, 3: ������������, 4: ���޴˷���, �޷�����, 5: MTT��������, 6: �ܽ������������� 7: �Զ�ѡ��ʧ��, 8: ��������, 9: �ʽ���, 10: RoomServer�ر�, 11: �����ڴ����ſɼ����ܽ�����
	char _dummy[2];
	int nRoomId;	// ����ID

};

#endif // __MSGUSERSTATUS_H__
