/*!
 * \file MsgNotifyMaxCounterRecord.h
 * \date unknown
 * 
 * ֪ͨ�ͻ���Ӯ�ó������¼�¼
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYMAXCOUNTERRECORD_H__
#define __MSGNOTIFYMAXCOUNTERRECORD_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyMaxCounterRecord : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2103,
		MSG_SIZE = 52,
	};

public:
	DECLARE_RTTI(MsgNotifyMaxCounterRecord, PokerMsgBase);

	MsgNotifyMaxCounterRecord();
	virtual ~MsgNotifyMaxCounterRecord();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int64 nOldRecordUserId;	// �ɼ�¼userId ���Ϊ0��ʾ��μ�¼�ǵ�һ��
	int64 nOldRecordCounter;	// �ɼ�¼����
	int64 nNewRecordUserId;	// �¼�¼userId
	int64 nNewRecordCounter;	// �¼�¼����
	int64 nSmallBlind;	// 0: ��ʾ��μ�¼��ȫ����¼ ��Ϊ0: ��ʾ��Сäע���ͷ���ļ�¼
	int nCount;	// �ڼ����Ƽ�¼ ȫ����¼��ͳ�Ƹ���

};

#endif // __MSGNOTIFYMAXCOUNTERRECORD_H__
