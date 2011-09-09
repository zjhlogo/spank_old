/*!
 * \file MsgClick.cpp
 * \date 2011/09/05 14:10
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <msg/MsgClick.h>
#include <msg/MsgID.h>

MsgClick::MsgClick(MsgClick::CLICK_TYPE eType, int nButtonID)
:IMsgBase(MI_UI_CLICKED)
{
	m_eClieckType = eType;
	m_nButtonID = nButtonID;
}


MsgClick::~MsgClick()
{
	//TODO:
}

int MsgClick::GetButtonID() const
{
	return m_nButtonID;
}
bool MsgClick::IsCheck()const
{
	return (m_eClieckType == CT_CHECK);
}

bool MsgClick::ISNormal() const
{
	return (m_eClieckType == CT_NORMAL);
}