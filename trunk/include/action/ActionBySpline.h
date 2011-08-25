/*!
 * \file ActionBySpline.h
 * \date 2011/08/22 15:40
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __ACTIONBYSPLINE_H_
#define __ACTIONBYSPLINE_H_

#include <math/IMath.h>
#include <BaseType.h>
#include <IShader.h>
#include <IShaderMgr.h>
#include <ITexture.h>
#include <ITextureMgr.h>
#include <vector>
#include "IActionBase.h"
class ActionBySpline :public IActionBase
{
public:
	ActionBySpline(float time);
	ActionBySpline(const ActionBySpline& ActBySpline);
	virtual ~ActionBySpline();

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
	Vector3 interpolate(uint fromIndex, float t) const;
	void setAutoCalculate(bool autoCalc);
	void recalcTangents(void);
private:
	std::vector<Vector3> m_vPoints;
	
	std::vector<Vector3> m_vTangents;
	VATTR_POS_UV* pVerts;
	IShader* m_pShader;
	ITexture* m_pTexTure;
	/// Matrix of coefficients 
	Matrix4x4 m_matCoeffs;
	bool m_bClosed;
	float m_fTime;
	float m_fCurrenTime;
};

#endif//__ACTIONBYSPLINE_H_