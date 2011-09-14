/*!
 * \file ActionScaleBy.h
 * \date 2011/08/22 11:31
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __ACTIONSCALEBY_H__
#define __ACTIONSCALEBY_H__

#include "IActionBase.h"

class ActionScaleBy : public IActionBase
{
public: 
	DECLARE_RTTI(ActionScaleBy, IActionBase);

	ActionScaleBy(const Vector3& ScaleStart, const Vector3& ScaleOff, float time);
	virtual ~ActionScaleBy();

	virtual void Reset();
	virtual void Update(float dt);

	virtual IActionBase* Clone();
	virtual IActionBase* CloneInverse();

	virtual float GetTimeLength() const;

private:
	Vector3 m_vScaleStart;
	Vector3 m_vScaleOff;
	
	float m_fTime;
	float m_fCurrTime;

};

#endif // __ACTIONSCALEBY_H__
