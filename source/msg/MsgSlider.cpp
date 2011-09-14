/*!
 * \file Msgslider.cpp
 * \date 2011/09/05 16:15
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <msg/MsgSlider.h>
#include <msg/MsgID.h>

MsgSilder::MsgSilder(MsgSilder::SILDER_TYPE eType, int nCurrentPos)
: IMsgBase(MI_UI_SLIDER)
{
	m_eSilderType = eType;
	m_nCurrentPos = nCurrentPos;
}

MsgSilder::~MsgSilder()
{
	//TODO:
}

void MsgSilder::SetPosition(int nCurrentPos)
{
	m_nCurrentPos = nCurrentPos;
}
const int MsgSilder::GetPosition() const
{
	return m_nCurrentPos;
}

bool MsgSilder::IsSilderMove()const
{
	return (m_eSilderType == ST_MOVE);
}

bool MsgSilder::IsSilderBegin() const
{
	return (m_eSilderType == ST_BEGIN);
}

bool MsgSilder::IsSilderEnd() const
{
	return (m_eSilderType == ST_END);
}

