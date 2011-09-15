/*!
 * \file Msgslider.cpp
 * \date 2011/09/05 16:15
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <ui/uimsg/MsgSlider.h>
#include <ui/uimsg/UIMsgID.h>

MsgSlider::MsgSlider(SILDER_TYPE eType, int nCurrentPos, UIWindow* pSender)
:IMsgBaseUI(UMI_SLIDER, pSender)
{
	m_eSilderType = eType;
	m_nCurrentPos = nCurrentPos;
}

MsgSlider::~MsgSlider()
{
	//TODO:
}

void MsgSlider::SetPosition(int nCurrentPos)
{
	m_nCurrentPos = nCurrentPos;
}

const int MsgSlider::GetPosition() const
{
	return m_nCurrentPos;
}

bool MsgSlider::IsSilderMove()const
{
	return (m_eSilderType == ST_MOVE);
}

bool MsgSlider::IsSilderBegin() const
{
	return (m_eSilderType == ST_BEGIN);
}

bool MsgSlider::IsSilderEnd() const
{
	return (m_eSilderType == ST_END);
}
