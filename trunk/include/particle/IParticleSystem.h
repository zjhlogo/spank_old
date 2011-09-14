/*!
 * \file IParticleSystem.h
 * \date 8-18-2011 10:06:24
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IPARTICLESYSTEM_H__
#define __IPARTICLESYSTEM_H__

#include "../IRenderableObject.h"
#include "IEmmiter.h"
#include "IParticle.h"

class IParticleSystem : public IRenderableObject
{
public:
	DECLARE_RTTI(IParticleSystem, IRenderableObject);

	IParticleSystem();
	virtual ~IParticleSystem();

};
#endif // __IPARTICLESYSTEM_H__
