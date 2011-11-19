/*!
 * \file MsgRespAcceptFreeChips.h
 * \date unknown
 * 
 * ���ܺ��ѵ���ѳ���Ļظ�
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGRESPACCEPTFREECHIPS_H__
#define __MSGRESPACCEPTFREECHIPS_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRespAcceptFreeChips : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2049,
		MSG_SIZE = 26,
	};

public:
	DECLARE_RTTI(MsgRespAcceptFreeChips, PokerMsgBase);

	MsgRespAcceptFreeChips();
	virtual ~MsgRespAcceptFreeChips();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	char nResult;	// ���������0: �ɹ�, 1: ��ѳ��벻����, �ͻ��˿����Ϊ��ID�Ѿ�����, 2: �Ѵﵽ���ս�������, ����������
	char _dummy;	// ����
	int64 nUserId;	// ��ҵ�ID
	int64 nRequsetId;	// �����ID
	int64 nGeneratedChips;	// ���ɵĳ�����

};

#endif // __MSGRESPACCEPTFREECHIPS_H__
