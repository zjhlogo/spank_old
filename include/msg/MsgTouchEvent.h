/*!
 * \file MsgTouchEvent.h
 * \date 8-10-2011 13:49:15
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __MSGTOUCHEVENT_H__
#define __MSGTOUCHEVENT_H__

#include "IMsgBase.h"
#include "../math/Vector2.h"

class MsgTouchEvent : public IMsgBase
{
public:
	enum TOUCH_EVENT_TYPE
	{
		TET_UNKNOWN = 0,
		TET_BEGIN,
		TET_MOVE,
		TET_END,
	};

public:
	MsgTouchEvent(TOUCH_EVENT_TYPE eType, int nIndex, const Vector2& pos);
	MsgTouchEvent(TOUCH_EVENT_TYPE eType, int nIndex, float x, float y);
	~MsgTouchEvent();

	void SetPosition(const Vector2& pos);
	void SetPosition(float x, float y);
	const Vector2& GetPosition() const;

	int GetIndex() const;

	bool IsTouchBegin() const;
	bool IsTouchMove() const;
	bool IsTouchEnd() const;

private:
	TOUCH_EVENT_TYPE m_eTouchType;
	int m_nIndex;
	Vector2 m_vPosition;

};

#endif // __MSGTOUCHEVENT_H__
