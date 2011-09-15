/*!
 * \file Msgslider.cpp
 * \date 2011/09/05 16:15
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <ui/uimsg/MsgSlider.h>
#include <ui/uimsg/UIMsgID.h>

MsgSlider::MsgSlider(SLIDER_TYPE eType, int nPos, UIWindow* pSender)
:IMsgBaseUI(UMI_SLIDER, pSender)
{
	m_eSliderType = eType;
	m_nPos = nPos;
}

MsgSlider::~MsgSlider()
{
	//TODO:
}

void MsgSlider::SetPosition(int nCurrentPos)
{
	m_nPos = nCurrentPos;
}

int MsgSlider::GetPosition() const
{
	return m_nPos;
}

bool MsgSlider::IsPositionChanged() const
{
	return (m_eSliderType == ST_POSITION);
}

bool MsgSlider::IsTracking() const
{
	return (m_eSliderType == ST_TRACKING);
}
