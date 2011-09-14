/*!
 * \file SnowEmmiter.h
 * \date 8-18-2011 13:48:43
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __SNOWEMMITER_H__
#define __SNOWEMMITER_H__

#include "IEmmiter.h"

class SnowEmmiter : public IEmmiter
{
public:
	enum CONST_DEFINE
	{
		PARTICLE_BUFFER_SIZE = 128,
	};

public:
	DECLARE_RTTI(SnowEmmiter, IEmmiter);

	SnowEmmiter();
	virtual ~SnowEmmiter();

	virtual IParticle* CreateParticle();
	virtual void RecycleParticle(IParticle* pParticle);

private:
	PARTICLE_CACHE_ITEM* FindUnusedItem();

private:
	PARTICLE_CACHE_ITEM m_ParticleCache[PARTICLE_BUFFER_SIZE];
	int m_nCurrIndex;

};
#endif // __SNOWEMMITER_H__
