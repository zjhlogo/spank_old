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
		CT_PRESSED,
		CT_NORMAL,
	};
public:
	MsgClick(CLICK_TYPE eType, const Vector2& pos);
	MsgClick(CLICK_TYPE eType, const float x, float y);
	~MsgClick();

	void SetPosition(const Vector2& Position);
	void SetPosition(const float x, const float y);
	const Vector2& GetPosition(void) const;
	
	bool IsPressed() const;
	bool IsNormal() const;
private:
	CLICK_TYPE m_eClieckType;
	Vector2 m_vPosition;
	
};
#endif//__MSGCLICK_H_