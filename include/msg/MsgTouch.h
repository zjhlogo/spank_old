/*!
 * \file MsgTouch.h
 * \date 8-16-2011 11:11:34
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __MSGTOUCH_H__
#define __MSGTOUCH_H__

#include "IMsgBase.h"
#include "../math/IMath.h"

class MsgTouch : public IMsgBase
{
public:
	enum TOUCH_TYPE
	{
		TT_UNKNOWN = 0,
		TT_BEGIN,
		TT_MOVE,
		TT_END,
	};

public:
	MsgTouch(TOUCH_TYPE eType, int nIndex, const Vector2& pos);
	MsgTouch(TOUCH_TYPE eType, int nIndex, float x, float y);
	~MsgTouch();

	void SetPosition(const Vector2& pos);
	void SetPosition(float x, float y);
	const Vector2& GetPosition() const;

	int GetIndex() const;

	bool IsTouchBegin() const;
	bool IsTouchMove() const;
	bool IsTouchEnd() const;

private:
	TOUCH_TYPE m_eTouchType;
	int m_nIndex;
	Vector2 m_vPosition;

};
#endif // __MSGTOUCH_H__
