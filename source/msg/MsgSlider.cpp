/*!
 * \file Msgslider.cpp
 * \date 2011/09/05 16:15
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <msg/MsgSlider.h>
#include <msg/MsgID.h>

MsgSilder::MsgSilder(MsgSilder::SILDER_TYPE eType, float fPercent)
: IMsgBase(MI_UI_SLIDER)
{
	m_eSilderType = eType;
	m_fPercent = fPercent;
}

MsgSilder::~MsgSilder()
{
	//TODO:
}

void MsgSilder::SetPercent(float percent)
{
	m_fPercent = percent;
}
const float MsgSilder::GetPercent() const
{
	return m_fPercent;
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

