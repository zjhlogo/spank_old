/*!
 * \file IEmmiter.h
 * \date 8-18-2011 10:39:44
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IEMMITER_H__
#define __IEMMITER_H__

#include "../IObject.h"
#include "IParticle.h"

class IEmmiter : public IObject
{
public:
	typedef struct PARTICLE_CACHE_ITEM_tag
	{
		bool bAllocated;
		IParticle* pParticle;
	} PARTICLE_CACHE_ITEM;

public:
	IEmmiter();
	virtual ~IEmmiter();

	void SetEmmitRate(float rate);
	float GetEmmitRate() const;

	int PopNumEmmit();

	void Update(float dt);

	virtual IParticle* CreateParticle() = 0;
	virtual void RecycleParticle(IParticle* pParticle) = 0;

private:
	float m_fEmmitRate;		// how many particle per second
	float m_fTotalEmmit;
	int m_nNumEmmit;

};
#endif // __IEMMITER_H__
