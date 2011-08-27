/*!
 * \file ActionBySpline.h
 * \date 2011/08/22 15:40
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __ACTIONBYSPLINE_H__
#define __ACTIONBYSPLINE_H__

#include "IActionBase.h"
#include <math/IMath.h>
#include <vector>

class ActionBySpline :public IActionBase
{
public:
	typedef std::vector<Vector3> TV_VECTOR3;

public:
	ActionBySpline(float time);
	virtual ~ActionBySpline();

	/** Adds a control point to the end of the spline. */
	void AddPoint(const Vector3& Point);

	/** Gets the detail of one of the control points of the spline. */
	const Vector3& GetPoint(uint index);

	/** Gets the number of control points in the spline. */
	uint GetNumberPoints(void) const;

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
	void RecalcTangents();

private:
	TV_VECTOR3 m_vPoints;
	TV_VECTOR3 m_vTangents;
	Matrix4x4 m_matCoeffs;					// Matrix of coefficients 

	bool m_bClosed;
	float m_fTime;
	float m_fCurrenTime;

};
#endif // __ACTIONBYSPLINE_H__
