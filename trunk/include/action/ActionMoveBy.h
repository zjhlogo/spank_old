/*!
 * \file ActionMoveBy.h
 * \date 8-22-2011 09:39:28
 * 
 * 
 * \author wbaoqing (wbaoqing@gmail.com)
 */
#ifndef __ACTIONMOVEBY_H__
#define __ACTIONMOVEBY_H__

#include "IActionBase.h"

class ActionMoveBy :public IActionBase
{
public:
	ActionMoveBy(const Vector3& posStart, const Vector3& posOff, float time);
	virtual ~ActionMoveBy();

	virtual void Reset();
	virtual void Update(float dt);
	virtual IActionBase* Clone();
	virtual IActionBase* CloneInverse();
	virtual float GetTimeLength() const;

private:
	Vector3 m_vPostart;
	Vector3 m_vPosoff;
	float m_fTime;
	float m_fCurrTime;

};
#endif // __ACTIONMOVEBY_H__
