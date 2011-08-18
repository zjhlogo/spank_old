/*!
 * \file SnowEmmiter.cpp
 * \date 8-18-2011 14:41:46
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <particle/SnowEmmiter.h>
#include <particle/SnowParticle.h>
#include <util/StringUtil.h>
#include <util/ScreenUtil.h>

SnowEmmiter::SnowEmmiter()
{
	StringUtil::ZeroMemory(m_ParticleCache, sizeof(m_ParticleCache));
	m_nCurrIndex = 0;
	SetEmmitRate(10.0f);
}

SnowEmmiter::~SnowEmmiter()
{
	for (int i = 0; i < PARTICLE_BUFFER_SIZE; ++i)
	{
		if (!m_ParticleCache[i].pParticle)
		{
			SAFE_DELETE(m_ParticleCache[i].pParticle);
		}
	}
}

IParticle* SnowEmmiter::CreateParticle()
{
	PARTICLE_CACHE_ITEM* pItem = FindUnusedItem();
	if (!pItem) return NULL;

	if (!pItem->pParticle) pItem->pParticle = new SnowParticle();
	pItem->bAllocated = true;
	SnowParticle* pSnowParticle = (SnowParticle*)pItem->pParticle;
	pSnowParticle->Reset();

	float fHalfScreenWidth = ScreenUtil::GetInstance().GetScreenWidth() / 2.0f;
	float fHalfScreenHeight = ScreenUtil::GetInstance().GetScreenHeight() / 2.0f;

	pSnowParticle->m_vPosition.x = IMath::Random(-fHalfScreenWidth, fHalfScreenWidth);
	pSnowParticle->m_vPosition.y = fHalfScreenHeight;
	pSnowParticle->m_vPosition.z = 0.0f;

	pSnowParticle->m_vSize.x = IMath::Random(5.0f, 10.0f);
	pSnowParticle->m_vSize.y = pSnowParticle->m_vSize.x;
	pSnowParticle->m_vSize.z = 0.0f;

	pSnowParticle->m_vVeclity.x = IMath::Random(-5.0f, 20.0f);
	pSnowParticle->m_vVeclity.y = IMath::Random(-20.0f, -80.0f);
	pSnowParticle->m_vVeclity.z = 0.0f;

	return pSnowParticle;
}

void SnowEmmiter::RecycleParticle(IParticle* pParticle)
{
	for (int i = 0; i < PARTICLE_BUFFER_SIZE; ++i)
	{
		if (m_ParticleCache[i].pParticle == pParticle)
		{
			m_ParticleCache[i].bAllocated = false;
			return;
		}
	}
}

IEmmiter::PARTICLE_CACHE_ITEM* SnowEmmiter::FindUnusedItem()
{
	for (int i = 0; i < PARTICLE_BUFFER_SIZE; ++i)
	{
		int nIndex = (m_nCurrIndex + i) % PARTICLE_BUFFER_SIZE;
		if (!m_ParticleCache[nIndex].bAllocated)
		{
			m_nCurrIndex = (nIndex + 1) % PARTICLE_BUFFER_SIZE;
			return &m_ParticleCache[nIndex];
		}
	}

	return NULL;
}
