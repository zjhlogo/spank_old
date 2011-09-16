/*!
 * \file ActionQuadraticMove.h
 * \date 2011/09/16 11:27
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __ACTIONTWEENMOVE_H_
#define __ACTIONTWEENMOVE_H_

#include "IActionBase.h"
class ActionQuadMove : public IActionBase
{
public:
	DECLARE_RTTI(ActionQuadMove, IActionBase);
public:
	ActionQuadMove(uint eType,const Vector3& posStart, const Vector3& posEnd, float time);
	virtual void Reset() ;
	virtual void Update(float dt) ;

	virtual IActionBase* Clone() ;
	virtual IActionBase* CloneInverse();
	
	virtual float GetTimeLength() const;
private:
	Vector3 Tween();
private:
	Vector3 m_vPosStart;
	Vector3 m_vPosEnd;
	float m_fTime;

	float m_fCurrTime;
	uint m_eType;
};
#endif//__ACTIONTWEENMOVE_H_