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

class ActionRotateTo:public IActionBase
{
public:
	ActionRotateTo(const Vector3& vAxis, const float& fStartAngle, const float& fEndAngle, float time);
	virtual ~ActionRotateTo();
public:
	virtual void Reset(void);
	virtual void Update(float dt);

	virtual IActionBase* Clone(void);
	virtual IActionBase* CloneInverse(void);

	virtual float GetTimeLength(void) const;
private:
	Quaternion m_qRotStart;
	Quaternion m_qRotEnd;

	Vector3 m_vAxis;
	float m_fStartAngle;
	float m_fEndAngle;

	float m_fTime;
	float m_fCurrTime;
};
#endif//__ACTIONROTATETO_H_