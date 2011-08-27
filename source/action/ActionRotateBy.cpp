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
	m_vAxis = vAxis;
	m_fStartAngle = fStartAngle;
	m_foffAngle = fOffAngle;
	m_fTime = time;

	Reset();
}

ActionRotateBy::~ActionRotateBy()
{
	//TOD:
}

void ActionRotateBy::Reset()
{
	m_fCurrTime = 0.0f;
}

void ActionRotateBy::Update(float dt)
{
	if(!IsRunning()) return;

	m_fCurrTime += dt;
	//action end
	if(m_fCurrTime > m_fTime)
	{
		SetRotation(m_vAxis, m_fStartAngle + m_foffAngle);
		Stop();
		return;
	}

	float alpha = m_fCurrTime / m_fTime;
	SetRotation(m_vAxis, m_fStartAngle + alpha * m_foffAngle);
}

IActionBase* ActionRotateBy::Clone()
{
	return new ActionRotateBy(m_vAxis, m_fStartAngle, m_foffAngle, m_fTime);
}

IActionBase* ActionRotateBy::CloneInverse()
{
	return new ActionRotateBy(m_vAxis, m_fStartAngle + m_foffAngle, -m_foffAngle, m_fTime); 
}

float ActionRotateBy::GetTimeLength() const
{
	return m_fTime;
}
