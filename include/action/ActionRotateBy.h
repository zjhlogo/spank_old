/*!
 * \file ActionRotateBy..h
 * \date 8-22-2011 10:12:54
 * 
 * 
 * \author wbaoqing (zjhlogo@gmail.com)
 */
#ifndef __ACTIONROTATEBY_H__
#define __ACTIONROTATEBY_H__

#include "IActionBase.h"

class ActionRotateBy: public IActionBase
{
public: 
	ActionRotateBy(const Vector3& vAxis, const float& fStartAngle, const float& fOffAngle, float time);
	virtual ~ActionRotateBy();

	virtual void Reset();
	virtual void Update(float dt);
	virtual IActionBase* Clone();
	virtual IActionBase* CloneInverse();
	virtual float GetTimeLength() const;

private:
	Vector3 m_vAxis;
	float m_fStartAngle;
	float m_foffAngle;
	float m_fTime;
	float m_fCurrTime;

};

#endif // __ACTIONROTATEBY_H__
