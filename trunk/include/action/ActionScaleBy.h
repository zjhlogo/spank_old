/*!
 * \file ActionScaleBy.h
 * \date 2011/08/22 11:31
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include "IActionBase.h"
#ifndef __ACTIONSCALEBY_H_
#define __ACTIONSCALEBY_H_
class ActionScaleBy: public IActionBase
{
public: 
	ActionScaleBy(const Vector3& ScaleStart, const Vector3& ScaleOff, float time);
	~ActionScaleBy();
public:
	virtual void Reset(void);
	virtual void Update(float dt);

	virtual IActionBase* Clone(void);
	virtual IActionBase* CloneInverse(void);

	virtual float GetTimeLength(void) const;
private:
	Vector3 m_vScaleStart;
	Vector3 m_vScaleOff;
	
	float m_fTime;
	float m_fCurrTime;

};
#endif//__ACTIONSCALEBY_H_