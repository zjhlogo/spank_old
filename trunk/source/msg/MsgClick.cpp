/*!
 * \file MsgClick.cpp
 * \date 2011/09/05 14:10
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <msg/MsgClick.h>
#include <msg/MsgID.h>

MsgClick::MsgClick(MsgClick::CLICK_TYPE eType, const float x, float y)
:IMsgBase(MI_UI_CLICKED)
{
	m_eClieckType = eType;
	m_vPosition.x = x;
	m_vPosition.y = y;
}

MsgClick::MsgClick(MsgClick::CLICK_TYPE eType, const Vector2 &pos)
:IMsgBase(MI_UI_CLICKED)
{
	m_eClieckType = eType;
	m_vPosition = pos;
}

MsgClick::~MsgClick()
{
	//TODO:
}

void MsgClick::SetPosition(const float x, const float y)
{
	m_vPosition.x = x;
	m_vPosition.y = y;
}

void MsgClick::SetPosition(const Vector2 &Position)
{
	m_vPosition = Position;
}
const Vector2& MsgClick::GetPosition() const
{
	return m_vPosition;
}

bool MsgClick::IsPressed() const
{
	 return (m_eClieckType == CT_PRESSED);
}

bool MsgClick::IsNormal() const
{
	return (m_eClieckType == CT_PRESSED);
}