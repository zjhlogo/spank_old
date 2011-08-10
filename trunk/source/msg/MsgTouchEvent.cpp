/*!
 * \file MsgTouchEvent.cpp
 * \date 8-10-2011 13:49:21
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <msg/MsgTouchEvent.h>
#include <msg/MsgID.h>

MsgTouchEvent::MsgTouchEvent(TOUCH_EVENT_TYPE eType, int nIndex, const Vector2& pos)
:IMsgBase(MI_TOUCH_EVENT)
{
	m_eTouchType = eType;
	m_nIndex = nIndex;
	SetPosition(pos);
}

MsgTouchEvent::MsgTouchEvent(TOUCH_EVENT_TYPE eType, int nIndex, float x, float y)
:IMsgBase(MI_TOUCH_EVENT)
{
	m_eTouchType = eType;
	m_nIndex = nIndex;
	SetPosition(x, y);
}

MsgTouchEvent::~MsgTouchEvent()
{
	// TODO: 
}

void MsgTouchEvent::SetPosition(const Vector2& pos)
{
	m_vPosition.x = pos.x;
	m_vPosition.y = pos.y;
}

void MsgTouchEvent::SetPosition(float x, float y)
{
	m_vPosition.x = x;
	m_vPosition.y = y;
}

const Vector2& MsgTouchEvent::GetPosition() const
{
	return 	m_vPosition;
}

int MsgTouchEvent::GetIndex() const
{
	return m_nIndex;
}

bool MsgTouchEvent::IsTouchBegin() const
{
	return (m_eTouchType == TET_BEGIN);
}

bool MsgTouchEvent::IsTouchMove() const
{
	return (m_eTouchType == TET_MOVE);
}

bool MsgTouchEvent::IsTouchEnd() const
{
	return (m_eTouchType == TET_END);
}
