/*!
 * \file MsgNotice.h
 * \date unknown
 * 
 * ֪ͨ��Ϣ��
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTICE_H__
#define __MSGNOTICE_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotice : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2063,
		MSG_SIZE = 32,
	};

public:
	DECLARE_RTTI(MsgNotice, PokerMsgBase);

	MsgNotice();
	virtual ~MsgNotice();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int nType;	// ֪ͨ��Ϣ����, ���ھ���ʹ�õ�֪ͨģ�塣1: ÿ�յ�¼��� $Arg1 ��������; 2: ���ܽ�������� $Arg1 ����3: �����ֽ̳̻�� $Arg1 ���� �� $Arg2 ����ֵ 4: ͨ��������ȡ���� $Arg1 ������ $Arg2 ��������(0Ϊϵͳ���������� 1Ϊ���˳�������� 2Ϊ���걦��share������]
	int64 nArg1;	// ֪ͨ����1
	int64 nArg2;	// ֪ͨ����2
	uint nTimestamp;	// ʱ���

};

#endif // __MSGNOTICE_H__
