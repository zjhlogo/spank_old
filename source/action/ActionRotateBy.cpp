/*!
 * \file ActionRotateBy.cpp
 * \date 8-22-2011 10:12:54
 * 
 * 
 * \author wbaoqing (zjhlogo@gmail.com)
 */
#include <action/ActionRotateBy.h>
ActionRotateBy::ActionRotateBy(const Vector3& vAxis, const float& fStartAngle, const float& fOffAngle, float time)
{
	//TODO:
	m_qRotStart = Quaternion(vAxis, fStartAngle);
	m_qRotEnd = Quaternion(vAxis, fStartAngle + fOffAngle);
	m_vAxis = vAxis;
	m_fStartAngle = fStartAngle;
	m_foffAngle = fOffAngle;
	m_fTime = time;
	Reset();
}

ActionRotateBy::~ActionRotateBy(void)
{
	//TOD:
}

void ActionRotateBy::Reset(void)
{
	//TODO:
	m_fCurrTime = 0.0f;
}

void ActionRotateBy::Update(float dt)
{
	//TODO:
	if(!IsRunning()) return;

	m_fCurrTime += dt;
	//action end
	if(m_fCurrTime > m_fTime)
	{
		SetRotation(m_qRotEnd);
		Stop();
		return;
	}

	float alpha = m_fCurrTime / m_fTime;
	SetRotation(m_vAxis,m_fStartAngle + alpha * m_foffAngle);
}

IActionBase* ActionRotateBy::Clone(void)
{
	return new ActionRotateBy(m_vAxis, m_fStartAngle, m_foffAngle, m_fTime);
}

IActionBase* ActionRotateBy::CloneInverse(void)
{
	return new ActionRotateBy(m_vAxis, m_fStartAngle + m_foffAngle, -m_foffAngle, m_fTime); 
}

float ActionRotateBy::GetTimeLength(void) const
{
	return m_fTime;
}