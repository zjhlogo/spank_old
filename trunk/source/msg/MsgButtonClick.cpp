/*!
 * \file MsgButtonClick.cpp
 * \date 2011/09/14 17:16
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <msg/MsgButtonClick.h>
#include <msg/MsgID.h>
MsgButtonClick::MsgButtonClick( BUTTON_CLICK_TYPE eType, const Vector2& Pos )
:IMsgBase(MI_UI_BUTTON_CLICK)
{
	m_eType = eType;
	m_vPosition = Pos;
}

MsgButtonClick::MsgButtonClick( BUTTON_CLICK_TYPE eType, float x, float y )
:IMsgBase(MI_UI_BUTTON_CLICK)
{
	m_eType = eType;
	m_vPosition.x = x;
	m_vPosition.y = y;
}

MsgButtonClick::~MsgButtonClick()
{
	//TODO:
}

void MsgButtonClick::SetPosition( const Vector2& Pos )
{
	m_vPosition = Pos;
}

void MsgButtonClick::SetPosition( float x, float y )
{	
	m_vPosition.x = x;
	m_vPosition.y = y;
}

const Vector2& MsgButtonClick::GetPosition() const
{
	return m_vPosition;
}
