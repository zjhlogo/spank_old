/*!
 * \file IParticle.h
 * \date 8-18-2011 10:11:32
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IPARTICLE_H__
#define __IPARTICLE_H__

#include "../IObject.h"
#include "../math/IMath.h"

class IParticle : public IObject
{
public:
	DECLARE_RTTI(IParticle, IObject);

	IParticle();
	virtual ~IParticle();

	virtual void Reset() = 0;
	virtual void Update(float dt) = 0;

	bool IsAlive() const;

	void Start();
	void Stop();

private:
	bool SetAlive(bool alive);

private:
	bool m_bAlive;

};
#endif // __IPARTICLE_H__
