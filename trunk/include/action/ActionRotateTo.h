/*!
 * \file ActionRotateto.h
 * \date 8-19-2011 14:30:24
 * 
 * 
 * \author wbaoqing (wbaoqing@gmail.com)
 */
#ifndef __ACTIONROTATETO_H_
#define __ACTIONROTATETO_H_

#include "IActionBase.h"

class ActionRotateTo : public IActionBase
{
public:
	DECLARE_RTTI(ActionRotateTo, IActionBase);

	ActionRotateTo(const Vector3& vAxis, float fStartAngle, float fEndAngle, float time);
	virtual ~ActionRotateTo();

	virtual void Reset();
	virtual void Update(float dt);

	virtual IActionBase* Clone();
	virtual IActionBase* CloneInverse();

	virtual float GetTimeLength() const;

private:
	Vector3 m_vAxis;
	float m_fStartAngle;
	float m_fEndAngle;

	float m_fTime;
	float m_fCurrTime;

};

#endif//__ACTIONROTATETO_H_
