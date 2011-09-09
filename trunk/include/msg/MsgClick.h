#ifndef __MSGCLICK_H_
#define __MSGCLICK_H_

#include "IMsgBase.h"
#include "../math/IMath.h"
class MsgClick: public IMsgBase
{
public:
	enum CLICK_TYPE
	{
		CT_UNKONWN= 0,
		CT_CHECK,
		CT_NORMAL,
	};
public:
	MsgClick(CLICK_TYPE eType, int nButtonID);
	~MsgClick();

	int GetButtonID() const;
	bool IsCheck()const;
	bool ISNormal()const;
private:
	CLICK_TYPE m_eClieckType;
	int m_nButtonID;
};
#endif//__MSGCLICK_H_