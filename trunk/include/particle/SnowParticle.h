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

class SnowParticle : public IParticle
{
public:
	SnowParticle();
	virtual ~SnowParticle();

	virtual void Update(float dt);

};
#endif // __SNOWPARTICLE_H__
