/*!
 * \file ActionCompose.h
 * \date 8-19-2011 14:30:24
 * 
 * 
 * \author wbaoqing (wbaoqing@gmail.com)
 */
#include <action/ActionRotateTo.h>

ActionRotateTo::ActionRotateTo(const Vector3& vAxis, float fStartAngle, float fEndAngle, float time)
{
	m_vAxis = vAxis;
	m_fStartAngle = fStartAngle;
	m_fEndAngle = fEndAngle;
	m_fTime = time;

	Reset();
}

ActionRotateTo::~ActionRotateTo()
{
	//TODO:
}

void ActionRotateTo::Reset()
{
	m_fCurrTime = 0.0f;
}

void ActionRotateTo::Update(float dt)
{
	if(!IsRunning())return;

	m_fCurrTime += dt;
	//action end
	if (m_fCurrTime > m_fTime)
	{
		SetRotation(m_vAxis, m_fEndAngle);
		Stop();
		return;
	}

	float alpha = m_fCurrTime / m_fTime;
	SetRotation(m_vAxis, m_fStartAngle * (1.0f - alpha) + m_fEndAngle * alpha);
}

IActionBase* ActionRotateTo::Clone()
{
	return new ActionRotateTo(m_vAxis, m_fStartAngle, m_fEndAngle, m_fTime);
}

IActionBase* ActionRotateTo::CloneInverse()
{
	return new ActionRotateTo(m_vAxis, m_fEndAngle, m_fStartAngle, m_fTime);
}

float ActionRotateTo::GetTimeLength() const
{
	return m_fTime;
}
