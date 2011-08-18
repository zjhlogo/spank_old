/*!
 * \file IEmmiter.cpp
 * \date 8-18-2011 10:43:37
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <particle/IEmmiter.h>

IEmmiter::IEmmiter()
{
	m_fEmmitRate = 1.0f;
	m_fTotalEmmit = 0.0f;
	m_nNumEmmit = 0;
}

IEmmiter::~IEmmiter()
{
	// TODO: 
}

void IEmmiter::SetEmmitRate(float rate)
{
	m_fEmmitRate = rate;
}

float IEmmiter::GetEmmitRate() const
{
	return m_fEmmitRate;
}

int IEmmiter::PopNumEmmit()
{
	int temp = m_nNumEmmit;
	m_nNumEmmit = 0;
	return temp;
}

void IEmmiter::Update(float dt)
{
	m_fTotalEmmit += (m_fEmmitRate * dt);
	if (m_fTotalEmmit > 1.0f)
	{
		int nCount = (int)m_fTotalEmmit;
		m_nNumEmmit += nCount;
		m_fTotalEmmit -= nCount;
	}
}
