/*!
 * \file ActionScaleTo.h
 * \date 8-19-2011 16:38:43
 * 
 * 
 * \author wbaoqing (wbaoqing@gmail.com)
 */
#ifndef __ACTIONSCALETO_H_
#define __ACTIONSCALETO_H_

#include "IActionBase.h"

class ActionScaleTo : public IActionBase
{
public:
	DECLARE_RTTI(ActionScaleTo, IActionBase);

	ActionScaleTo(const Vector3& ScaleStart, const Vector3& ScaleEnd, float time);
	virtual ~ActionScaleTo();

	virtual void Reset();
	virtual void Update(float dt);

	virtual IActionBase* Clone();
	virtual IActionBase* CloneInverse();

	virtual float GetTimeLength() const;

private:
	Vector3 m_vScaleStart;
	Vector3 m_vScaleEnd;

	float m_fTime;
	float m_fCurrTime;
};

#endif // __ACTIONSCALETO_H__
