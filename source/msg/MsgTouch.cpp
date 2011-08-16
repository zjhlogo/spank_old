/*!
 * \file MsgTouch.cpp
 * \date 8-16-2011 11:11:39
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <msg/MsgTouch.h>
#include <msg/MsgID.h>

MsgTouch::MsgTouch(TOUCH_TYPE eType, int nIndex, const Vector2& pos)
:IMsgBase(MI_TOUCH)
{
	m_eTouchType = eType;
	m_nIndex = nIndex;
	SetPosition(pos);
}

MsgTouch::MsgTouch(TOUCH_TYPE eType, int nIndex, float x, float y)
:IMsgBase(MI_TOUCH)
{
	m_eTouchType = eType;
	m_nIndex = nIndex;
	SetPosition(x, y);
}

MsgTouch::~MsgTouch()
{
	// TODO: 
}

void MsgTouch::SetPosition(const Vector2& pos)
{
	m_vPosition.x = pos.x;
	m_vPosition.y = pos.y;
}

void MsgTouch::SetPosition(float x, float y)
{
	m_vPosition.x = x;
	m_vPosition.y = y;
}

const Vector2& MsgTouch::GetPosition() const
{
	return 	m_vPosition;
}

int MsgTouch::GetIndex() const
{
	return m_nIndex;
}

bool MsgTouch::IsTouchBegin() const
{
	return (m_eTouchType == TT_BEGIN);
}

bool MsgTouch::IsTouchMove() const
{
	return (m_eTouchType == TT_MOVE);
}

bool MsgTouch::IsTouchEnd() const
{
	return (m_eTouchType == TT_END);
}
