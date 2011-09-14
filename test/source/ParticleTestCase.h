/*!
 * \file ParticleTestCase.h
 * \date 27-08-2011 05:22:40
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __PARTICLETESTCASE_H__
#define __PARTICLETESTCASE_H__

#include "TestCase.h"
#include <particle/SnowParticleSystem.h>

class ParticleTestCase : public TestCase
{
public:
	DECLARE_RTTI(ParticleTestCase, TestCase);

	ParticleTestCase();
	virtual ~ParticleTestCase();

	virtual bool Initialize(UIScreen* pUIScreen);
	virtual void Terminate();

	virtual void Update(float dt);
	virtual void Render();

private:
	SnowParticleSystem* m_pSnow;

};
#endif // __PARTICLETESTCASE_H__
