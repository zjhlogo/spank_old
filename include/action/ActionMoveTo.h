/*!
 * \file ActionMoveTo.h
 * \date 8-16-2011 12:29:19
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ACTIONMOVETO_H__
#define __ACTIONMOVETO_H__

#include "IActionBase.h"

class ActionMoveTo : public IActionBase
{
public:
	ActionMoveTo(const Vector3& posStart, const Vector3& posEnd, float time);
	virtual ~ActionMoveTo();
public:

	virtual void Reset(void);
	virtual void Update(float dt);

	virtual IActionBase* Clone(void);
	virtual IActionBase* CloneInverse(void);

	virtual float GetTimeLength(void) const;

private:
	Vector3 m_vPosStart;
	Vector3 m_vPosEnd;
	float m_fTime;

	float m_fCurrTime;

};
#endif // __ACTIONMOVETO_H__
