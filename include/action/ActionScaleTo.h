/*!
 * \file ActionCompose.h
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
	ActionScaleTo(const Vector3& ScaleStart, const Vector3& ScaleEnd, float time);
	~ActionScaleTo();
public:
	virtual void Reset(void);
	virtual void Update(float dt);

	virtual IActionBase* Clone(void);
	virtual IActionBase* CloneInverse(void);

	virtual float GetTimeLength(void) const;
private:
	Vector3 m_vScaleStart;
	Vector3 m_vScaleEnd;

	float m_fTime;
	float m_fCurrTime;
};
#endif//__ACTIONSCALETO_H_