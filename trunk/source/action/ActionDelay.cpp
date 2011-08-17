/*!
 * \file ActionDelay.cpp
 * \date 8-17-2011 15:49:12
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <action/ActionDelay.h>

ActionDelay::ActionDelay(float delay)
{
	m_fDelayTime = delay;
	Reset();
}

ActionDelay::~ActionDelay()
{
	// TODO: 
}

void ActionDelay::Reset()
{
	m_fCurrTime = 0.0f;
}

void ActionDelay::Update(float dt)
{
	if (!IsRunning()) return;

	m_fCurrTime += dt;
	if (m_fCurrTime > m_fDelayTime)
	{
		Stop();
	}
}

IActionBase* ActionDelay::Clone()
{
	return new ActionDelay(m_fDelayTime);
}

IActionBase* ActionDelay::CloneInverse()
{
	return new ActionDelay(m_fDelayTime);
}

float ActionDelay::GetTimeLength() const
{
	return m_fDelayTime;
}
