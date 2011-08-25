/*!
 * \file ActionMoveBy.cpp
 * \date 8-22-2011 09:39:28
 * 
 * 
 * \author wbaoqing (wbaoqing@gmail.com)
 */
#include <action/ActionMoveBy.h>

ActionMoveBy::ActionMoveBy(const Vector3 &posStart, const Vector3 &posOff, float time)
{
	//TODO:
	m_vPostart = posStart;
	m_vPosoff = posOff;
	m_fTime = time;
	Reset();
}

ActionMoveBy::~ActionMoveBy()
{
	//TODO:
}

void ActionMoveBy::Reset(void)
{
	//TODO:
	m_fCurrTime = 0.0f;
}

void ActionMoveBy::Update(float dt)
{
	//TODO:
	if(! IsRunning()) return;
	m_fCurrTime += dt;
	//action end
	if(m_fCurrTime > m_fTime)
	{
		SetPosition(m_vPostart + m_vPosoff);
		Stop();
		return;
	}
	float alpha = m_fCurrTime / m_fTime;
	SetPosition(m_vPostart + alpha * m_vPosoff);

}

IActionBase* ActionMoveBy::Clone(void)
{
	//TODO:
	return new ActionMoveBy(m_vPostart, m_vPosoff, m_fTime);
}

IActionBase* ActionMoveBy::CloneInverse(void)
{
	//TODO:
	return new ActionMoveBy(m_vPostart + m_vPosoff, Vector3(-m_vPosoff.x, -m_vPosoff.y, -m_vPosoff.z), m_fTime);
}

float ActionMoveBy::GetTimeLength() const
{
	//TODO:
	return m_fTime;
}