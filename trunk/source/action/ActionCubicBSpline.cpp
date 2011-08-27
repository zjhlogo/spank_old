/*!
 * \file ActionCubicBSpline.cpp
 * \date 2011/08/25 11:07
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <action/ActionCubicBSpline.h>
#include <util/IDebugUtil.h>
#include <math.h>
#include <math/IMath.h>

ActionCubicBSpline::ActionCubicBSpline(float ftime)
{
	m_fTime = ftime;

	Reset();
}

ActionCubicBSpline::~ActionCubicBSpline()
{
	//TODO:
}

void ActionCubicBSpline::AddPoint(const Vector3& Point)
{
	m_vPoints.push_back(Point);
}

const Vector3& ActionCubicBSpline::GetPoint(uint index)
{
	return m_vPoints[index];
}

uint ActionCubicBSpline::GetNumberPoints() const
{
	return m_vPoints.size();
}

void ActionCubicBSpline::Clear()
{
	m_vConPoints.clear();
	m_vPoints.clear();
}

void ActionCubicBSpline::UpdatePoint(uint index, const Vector3 &value)
{
	if(index > 0&& index < m_vConPoints.size())
	{
		m_vPoints[index] = value;
	}
}

void ActionCubicBSpline::Reset()
{
	m_fCurrenTime = 0.0f;
	RecaleControlPoint();
}

void ActionCubicBSpline::Update(float dt)
{
	if(!IsRunning()) return;

	m_fCurrenTime += dt;
	if( m_fCurrenTime > m_fTime)
	{
		SetPosition(m_vPoints[m_vPoints.size() - 1]);
		Stop();
		return;
	}

	if( m_vPoints.size() == 2)
	{
		float alpha = m_fCurrenTime / m_fTime;
		Vector3 Point = ((m_vPoints[0] * (1.0f - alpha)) + m_vPoints[1] *(alpha));
		SetPosition(Point);
		return;
	}

	float alpha = m_fCurrenTime / m_fTime;
	float fSeg = alpha * (m_vPoints.size() - 3);
	uint segIdx = (uint) fSeg;
	alpha = fSeg - segIdx;
	Vector3 Position = Interpolate(segIdx, alpha);
	Vector3 prvposition = GetPosition();
	Vector3 direct = Position - prvposition;
	if(direct.x < IMath::FLOAT_MIN)
	{
		SetPosition(Position);
		return;
	}
	direct.Normalize();
	SetPosition(Position);
	float Radian = atan2f(direct.y, direct.x);
	SetRotation(Vector3(0.0f, 0.0f, 1.0f), Radian);
}

IActionBase* ActionCubicBSpline::Clone()
{
	ActionCubicBSpline * pNewActionCubicBSpline =  new ActionCubicBSpline(*this);
	pNewActionCubicBSpline->Reset();
	return pNewActionCubicBSpline;
}

IActionBase* ActionCubicBSpline::CloneInverse()
{
	ActionCubicBSpline* pActionCubicBSpline = new ActionCubicBSpline(*this);
	pActionCubicBSpline->Clear();
	pActionCubicBSpline->m_vPoints.reserve(m_vPoints.size());
	pActionCubicBSpline->m_vPoints.assign(m_vPoints.rbegin(), m_vPoints.rend());
	pActionCubicBSpline->RecaleControlPoint();
	return pActionCubicBSpline;
}

float ActionCubicBSpline::GetTimeLength() const
{
	return m_fTime;
}

Vector3 ActionCubicBSpline::Interpolate(uint fromIndex, float t) const
{
	float ft0 = 1.0f - t;
	ft0 = ft0 * ft0 * ft0 / 6.0f;
	float ft1 = ((3.0f * t - 6.0f) * t * t +4.0f) / 6.0f;
	float ft2 = (((3.0f  - 3.0f * t) * t +3.0f) * t + 1.0f) / 6.0f;
	float ft3 = 1.0f - ft0 - ft1 - ft2;

	Vector3 result;
	result.x = m_vConPoints[fromIndex].x * ft0 + m_vConPoints[fromIndex + 1].x * ft1 + m_vConPoints[fromIndex + 2].x * ft2 + m_vConPoints[fromIndex + 3].x * ft3;
	result.y = m_vConPoints[fromIndex].y * ft0 + m_vConPoints[fromIndex + 1].y * ft1 + m_vConPoints[fromIndex + 2].y * ft2 + m_vConPoints[fromIndex + 3].y * ft3;
	result.z = m_vConPoints[fromIndex].z * ft0 + m_vConPoints[fromIndex + 1].z * ft1 + m_vConPoints[fromIndex + 2].z * ft2 + m_vConPoints[fromIndex + 3].z * ft3;

	return result;
}

void ActionCubicBSpline::RecaleControlPoint()
{
	// Can't do anything
	if(m_vPoints.size() < 3) return;
	
	if(m_vPoints.size() == 3)
	m_vPoints.push_back(m_vPoints[2]);
	
	m_vConPoints = m_vPoints;
	m_vConPoints.push_back(m_vPoints[0]);
	m_vConPoints.push_back(m_vPoints[1]);
	m_vConPoints.push_back(m_vPoints[2]);

	m_vConPoints[0].x = 6.0f * m_vConPoints[0].x - 4.0f * m_vConPoints[1].x - m_vConPoints[2].x;
	m_vConPoints[0].y = 6.0f * m_vConPoints[0].y - 4.0f * m_vConPoints[1].y - m_vConPoints[2].y;
	m_vConPoints[0].z = 6.0f * m_vConPoints[0].z - 4.0f * m_vConPoints[1].z - m_vConPoints[2].z;

	int nNumberPoints = m_vPoints.size() - 1;
	m_vConPoints[nNumberPoints].x = 6.0f * m_vConPoints[nNumberPoints].x 
								- 4.0f * m_vConPoints[nNumberPoints - 1].x
								- m_vConPoints[nNumberPoints - 2].x;
	m_vConPoints[nNumberPoints].y = 6.0f * m_vConPoints[nNumberPoints].y 
								- 4.0f * m_vConPoints[nNumberPoints - 1].y 
								- m_vConPoints[nNumberPoints - 2].y;
	m_vConPoints[nNumberPoints].z = 6.0f * m_vConPoints[nNumberPoints].z 
								- 4.0f * m_vConPoints[nNumberPoints - 1].z 
								- m_vConPoints[nNumberPoints - 2].z;
}
