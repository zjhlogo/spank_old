/*!
 * \file SnowParticle.h
 * \date 8-18-2011 10:27:02
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __SNOWPARTICLE_H__
#define __SNOWPARTICLE_H__

#include "IParticle.h"
#include "../math/IMath.h"

class SnowParticle : public IParticle
{
public:
	DECLARE_RTTI(SnowParticle, IParticle);

	SnowParticle();
	virtual ~SnowParticle();

	virtual void Reset();
	virtual void Update(float dt);

private:
	inline bool IsOutsideScreen();

public:
	Vector3 m_vPosition;
	Vector3 m_vSize;
	Vector3 m_vVeclity;

};
#endif // __SNOWPARTICLE_H__
