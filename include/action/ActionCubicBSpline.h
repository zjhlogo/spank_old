/*!
 * \file ActionCubicBSpline.h
 * \date 2011/08/25 11:06
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __ACTIONCUBICBSPLINE_H__
#define __ACTIONCUBICBSPLINE_H__

#include "IActionBase.h"
#include <vector>

class ActionCubicBSpline : public IActionBase
{
public:
	typedef std::vector<Vector3> TV_VECTOR3;

public:
	ActionCubicBSpline(float ftime);
	virtual ~ActionCubicBSpline();

	/** Adds a control point to the end of the spline. */
	void AddPoint(const Vector3& Point);

	/** Gets the detail of one of the control points of the spline. */
	const Vector3& GetPoint(uint index);

	/** Gets the number of control points in the spline. */
	uint GetNumberPoints() const;

	/** Clears all the points in the spline. */
	void Clear();

	/** Updates a single point in the spline.*/
	void UpdatePoint(uint index, const Vector3& value);

	virtual void Reset();
	virtual void Update(float dt);
	virtual IActionBase* Clone();
	virtual IActionBase* CloneInverse();
	virtual float GetTimeLength() const;

private:
	Vector3 Interpolate(uint fromIndex, float t) const;
	void RecaleControlPoint();

private:
	float m_fTime;
	float m_fCurrenTime;

	TV_VECTOR3 m_vPoints;
	TV_VECTOR3 m_vConPoints;

};
#endif // __ACTIONCUBICBSPLINE_H__
