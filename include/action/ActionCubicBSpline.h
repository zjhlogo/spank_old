/*!
 * \file ActionCubicBSpline.h
 * \date 2011/08/25 11:06
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __ACTIONCUBICBSPLINE_H_
#define __ACTIONCUBICBSPLINE_H_
#include "IActionBase.h"
#include <vector>
using namespace std;
class ActionCubicBSpline: public IActionBase
{
public:
	ActionCubicBSpline(float ftime);
	virtual ~ActionCubicBSpline();
public:
	/** Adds a control point to the end of the spline. */
	void AddPoint(const Vector3& Point);
	/** Gets the detail of one of the control points of the spline. */
	const Vector3& GetPoint(uint index);
	/** Gets the number of control points in the spline. */
	uint GetNumberPoints(void) const;
	/** Clears all the points in the spline. */
	void Clear(void);
	/** Updates a single point in the spline.*/
	void UpdatePoint(uint index, const Vector3& value);
	virtual void Reset(void);
	virtual void Update(float dt);
	virtual IActionBase* Clone(void);
	virtual IActionBase* CloneInverse(void);
	virtual float GetTimeLength(void) const;
private:
	Vector3 Interpolate(uint fromIndex, float t) const;
	void RecaleControlPoint();
private:
	float m_fTime;
	float m_fCurrenTime;
	vector<Vector3> m_vPoints;
	vector<Vector3> m_vConPoints;
};
#endif//__ACTIONCUBICBSPLINE_H_