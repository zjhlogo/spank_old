/*!
 * \file ActionDelay.h
 * \date 8-17-2011 15:49:06
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ACTIONDELAY_H__
#define __ACTIONDELAY_H__

#include "IActionBase.h"

class ActionDelay : public IActionBase
{
public:
	ActionDelay(float delay);
	virtual ~ActionDelay();

	virtual void Reset();
	virtual void Update(float dt);

	virtual IActionBase* Clone();
	virtual IActionBase* CloneInverse();

	virtual float GetTimeLength() const;

private:
	float m_fDelayTime;
	float m_fCurrTime;

};
#endif // __ACTIONDELAY_H__
