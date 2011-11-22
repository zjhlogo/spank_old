/*!
 * \file NetDataType.h
 * \date 19-11-2011 17:09:10
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __NETDATATYPE_H__
#define __NETDATATYPE_H__

#include <BaseType.h>

typedef struct NET_ITEM_INFO_tag
{
	int64 nItemId;		// ��Ʒ�����ݿ�����ID   -1: ��ʾ��
	int nItemType;		// ��ƷId 
	int64 nGiver;		// ������
	int64 nObtainTime;	// ��õ�ʱ��
	int64 nExpireTime;	// ����ʱ��
} NET_ITEM_INFO;

typedef struct NET_USER_INFO_tag
{
	int64 nUserId;			// ��ǰ�����������ID �������Զ����ڸ�ID
	int64 nCoins;			// ���ʲ�
	int64 nMostCoins;		// ���ʲ�����ʷ��߼�¼
	uchar nLevel;			// �ȼ�
	uchar nIsVip;			// �Ƿ�VIP
	char _dummy[2];			// ����λ
	uint nMuteTime;			// �ۼ�����ʱ��
	uint nLogoutTime;		// ����ʱ���
} NET_USER_INFO;

typedef struct NET_ROOM_INFO_tag
{
	int nRoomId;			// -1=����
	char nPlayers;
	char nSeats;
	char nObservers;
	char nRoomType;
	int64 nSmallBlind;
	int64 nMinBuyIn;
	int64 nMaxBuyIn;
	int64 nDefaultBuyIn;	// Ĭ������
	char nStatus;			// ״̬: 0.stopping 1.running 
	char nTitleId;			// ��һ�η�����ID, �������ͷ��䶼��, ShootOut��WeeklyTournament�Ķ���0
	char nSubtitleId;		// �ڶ��η�����ID, ֻ����ͨ(����)������, �������ͷ���Ϊ0
	char nSpecType;			// ��������
	int nTailNumber;		// β������, ���з��䶼��
} NET_ROOM_INFO;

typedef struct NET_FRIEND_STATUS_tag
{
	int64 nFriendUserId;	// �������ID 
	char nStatus;			// ״̬. 0: ����, 1: ��ͨ/���ٷ�����, 2: Sit&Go������, 3: ShootOut������, 4: Weekly Tournament������
	char _dummy[3];
	NET_ROOM_INFO stRoomInfo;
} NET_FRIEND_STATUS;

typedef struct NET_REQUEST_DATA_tag
{
	int64 nRequestId;		// REQUEST��ID
	int64 nUserId;			// ����REQUEST�����ID
	int64 nFriendId;		// ����REQUEST�ĺ���ID
	uint nRequestType;		// REQUEST����
} NET_REQUEST_DATA;

typedef struct NET_SEAT_INFO_tag
{
	int64 nBet;				// ���ϵĶ�ע
	int64 nCounter;			// Я���ĳ���
	int64 nUserId;			// �����û�ID, -1:��λΪ��
	char nLastOp;			// -4:����뿪��λ -3:�����뿪��λ -2: ������(û���뱾��) -1:���Ƶȴ���һ��, 1:����, 2:��ע, 3:��ע, 4:Сäע, 5:��äע, 6 all in
	char _dummy[3];
	int nTrinket;			// ��Ʒ
} NET_SEAT_INFO;

#endif // __NETDATATYPE_H__
