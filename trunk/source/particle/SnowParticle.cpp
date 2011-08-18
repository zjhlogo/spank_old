/*!
 * \file SnowParticle.cpp
 * \date 8-18-2011 10:27:38
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <particle/SnowParticle.h>
#include <util/ScreenUtil.h>

SnowParticle::SnowParticle()
{
	Reset();
}

SnowParticle::~SnowParticle()
{
	// TODO: 
}

void SnowParticle::Reset()
{
	// TODO: 
}

void SnowParticle::Update(float dt)
{
	if (!IsAlive()) return;

	// update the position
	m_vPosition += (m_vVeclity * dt);

	if (IsOutsideScreen())
	{
		Stop();
	}
}

bool SnowParticle::IsOutsideScreen()
{
	float fHalfScreenWidth = ScreenUtil::GetInstance().GetScreenWidth() / 2.0f;
	float fHalfScreenHeight = ScreenUtil::GetInstance().GetScreenHeight() / 2.0f;

	if (m_vPosition.x + m_vSize.x < -fHalfScreenWidth
		|| m_vPosition.x - m_vSize.x > fHalfScreenWidth
		|| m_vPosition.y + m_vSize.y < -fHalfScreenHeight
		|| m_vPosition.y - m_vSize.y > fHalfScreenHeight)
	{
		return true;
	}

	return false;
}
