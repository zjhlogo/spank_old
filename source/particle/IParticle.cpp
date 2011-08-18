/*!
 * \file IParticle.cpp
 * \date 8-18-2011 10:31:46
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <particle/IParticle.h>

IParticle::IParticle()
{
	m_bAlive = false;
}

IParticle::~IParticle()
{
	// TODO: 
}

bool IParticle::IsAlive() const
{
	return m_bAlive;
}

void IParticle::Start()
{
	SetAlive(true);
}

void IParticle::Stop()
{
	SetAlive(false);
}

bool IParticle::SetAlive(bool alive)
{
	bool difference = (m_bAlive != alive);
	m_bAlive = alive;
	return difference;
}
