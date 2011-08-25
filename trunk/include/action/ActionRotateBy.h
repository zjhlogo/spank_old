/*!
 * \file ActionRotateBy..h
 * \date 8-22-2011 10:12:54
 * 
 * 
 * \author wbaoqing (zjhlogo@gmail.com)
 */
#ifndef __ACTIONROTATEBY_H_
#define __ACTIONROTATEBY_H_
#include "IActionBase.h"
class ActionRotateBy: public IActionBase
{
public: 
	ActionRotateBy(const Vector3& vAxis, const float& fStartAngle, const float& fOffAngle, float time);
	~ActionRotateBy();
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
	float m_foffAngle;
	float m_fTime;
	float m_fCurrTime;
};
#endif//__ACTIONROTATEBY_H_