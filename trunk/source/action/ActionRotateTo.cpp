/*!
 * \file ActionCompose.h
 * \date 8-19-2011 14:30:24
 * 
 * 
 * \author wbaoqing (wbaoqing@gmail.com)
 */
#include <action/ActionRotateTo.h>

ActionRoateTo::ActionRoateTo(const Vector3& rkAxis, const float& fStartAngle, const float& fEndAngle, float time)
{
	m_qRotStart = Quaternion(rkAxis, fStartAngle);
	m_qRotEnd = Quaternion(rkAxis, fEndAngle);

	m_vAxis = rkAxis;
	m_fStartAngle = fStartAngle;
	m_fEndAngle = fEndAngle;
	m_fTime = time;
	Reset();
	
}
ActionRoateTo::~ActionRoateTo()
{
	//TODO:
};

void ActionRoateTo::Reset(void)
{
	//TODO:
	m_fCurrTime = 0.0f;
}

void ActionRoateTo::Update(float dt)
{
	//TODO
	if(!IsRunning())return;

	m_fCurrTime += dt;
	//action end
	if (m_fCurrTime > m_fTime)
	{
		SetRotation(m_qRotStart);
		Stop();
		return;
	}
	float alpha = m_fCurrTime / m_fTime;
	SetRotation(m_vAxis,m_fStartAngle * (1.0f -alpha) + m_fEndAngle * alpha);
}
IActionBase* ActionRoateTo::Clone(void)
{
	//TODO:
	
	return new ActionRoateTo(m_vAxis, m_fStartAngle, m_fEndAngle, m_fTime);
}

IActionBase* ActionRoateTo::CloneInverse(void)
{
	//TODO;
	
	return new ActionRoateTo(m_vAxis, m_fEndAngle, m_fStartAngle, m_fTime);
}

float ActionRoateTo::GetTimeLength(void) const
{
	return m_fTime;
}