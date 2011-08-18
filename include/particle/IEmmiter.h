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
	IEmmiter();
	virtual ~IEmmiter();

	void SetEmmitRate(float rate);
	float GetEmmitRate() const;

	void Update(float dt);

	virtual IParticle* CreateParticle() = 0;
	virtual void RecycleParticle() = 0;

private:
	float m_fEmmitRate;

};
#endif // __IEMMITER_H__
