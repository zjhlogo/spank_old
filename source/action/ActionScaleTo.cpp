/*!
 * \file ActionCompose.h
 * \date 8-19-2011 16:38:43
 * 
 * 
 * \author wbaoqing (wbaoqing@gmail.com)
 */
#include "action/ActionScaleTo.h"
ActionScaleTo::ActionScaleTo(const Vector3& ScaleStart, const Vector3& ScaleEnd, float time)
{
	//TODO:
	m_vScaleStart = ScaleStart;
	m_vScaleEnd = ScaleEnd;
	m_fTime = time;

	Reset();
}
ActionScaleTo::~ActionScaleTo()
{
	//TODO:
}
void ActionScaleTo::Reset(void)
{
	//TODO:
	m_fCurrTime = 0.0;
}
void ActionScaleTo::Update(float dt)
{
	//TODO:
	if(!IsRunning())return;
	m_fCurrTime += dt;
	// action end
	if( m_fCurrTime > m_fTime)
	{
		SetScale(m_vScaleEnd);
		Stop();
		return;
	}
	// changing the position
	float alpha = m_fCurrTime / m_fTime;
	SetScale(m_vScaleStart * (1.0f - alpha) + m_vScaleEnd * alpha);
}

IActionBase* ActionScaleTo::Clone(void)
{
	//TODO:
	return new ActionScaleTo(m_vScaleStart, m_vScaleEnd, m_fTime);
}

IActionBase* ActionScaleTo::CloneInverse(void)
{
	//TODO:
	return new ActionScaleTo(m_vScaleEnd, m_vScaleStart, m_fTime);
}	

float ActionScaleTo::GetTimeLength() const
{
	return m_fTime;
}