/*!
 * \file ActionCompose.h
 * \date 8-19-2011 14:30:24
 * 
 * 
 * \author wbaoqing (wbaoqing@gmail.com)
 */
#ifndef __ACTIONROTATETO_H_
#define __ACTIONROTATETO_H_
#include "IActionBase.h"

class ActionRoateTo:public IActionBase
{
public:
	ActionRoateTo(const Vector3& rkAxis, const float& fStartAngle, const float& fEndAngle, float time);
	virtual ~ActionRoateTo();
public:
	virtual void Reset(void);
	virtual void Update(float dt);

	virtual IActionBase* Clone(void);
	virtual IActionBase* CloneInverse(void);

	virtual float GetTimeLength(void) const;
private:
	Quaternion m_qRotStart;
	Quaternion m_qRotEnd;

	Vector3 m_rkAxis;
	float m_fStartAngle;
	float m_fEndAngle;

	float m_fTime;
	float m_fCurrTime;
};
#endif//__ACTIONROTATETO_H_