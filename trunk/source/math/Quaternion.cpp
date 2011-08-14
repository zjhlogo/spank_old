/*!
 * \file Quaternion.cpp
 * \date 7-28-2011 17:51:40
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <math/Quaternion.h>
#include <math/IMath.h>
#include <math.h>

Quaternion::Quaternion()
{
	// TODO: 
}

Quaternion::Quaternion(const Quaternion& q)
{
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
}

Quaternion::Quaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Quaternion::Quaternion(const Vector3& vDir, float fRadian)
{
	Vector3 vNorm = vDir;
	vNorm.Normalize();

	float fhr = fRadian / 2.0f;
	float sc = sinf(fhr);
	x = vNorm.x*sc;
	y = vNorm.y*sc;
	z = vNorm.z*sc;
	w = cosf(fhr);
}

Quaternion::~Quaternion()
{
	// TODO: 
}

float Quaternion::Length()
{
	return sqrtf(x*x+y*y+z*z+w*w);
}

bool Quaternion::Normalize()
{
	float fMag = sqrtf(x*x+y*y+z*z+w*w);
	if (fMag <= IMath::FLOAT_MIN) fMag = 0.0f;
	float fInvMag = 1.0f / fMag;

	x *= fInvMag;
	y *= fInvMag;
	z *= fInvMag;
	w *= fInvMag;

	return true;
}

float Quaternion::GetRadian() const
{
	return (2.0f * acosf(w));
}

Quaternion& Quaternion::operator*=(const Quaternion& q)
{
	float prd_0 = (z - y) * (q.y - q.z);
	float prd_1 = (w + x) * (q.w + q.x);
	float prd_2 = (w - x) * (q.y + q.z);
	float prd_3 = (y + z) * (q.w - q.x);
	float prd_4 = (z - x) * (q.x - q.y);
	float prd_5 = (z + x) * (q.x + q.y);
	float prd_6 = (w + y) * (q.w - q.z);
	float prd_7 = (w - y) * (q.w + q.z);
	float prd_8 = prd_5 + prd_6 + prd_7;
	float prd_9 = 0.5f * (prd_4 + prd_8);

	x = prd_1 + prd_9 - prd_8;
	y = prd_2 + prd_9 - prd_7;
	z = prd_3 + prd_9 - prd_6;
	w = prd_0 + prd_9 - prd_5;
	return (*this);
}

Quaternion Quaternion::operator-() const
{
	return Quaternion(-x, -y, -z, w);
}

Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
{
	float prd_0 = (q1.z - q1.y) * (q2.y - q2.z);
	float prd_1 = (q1.w + q1.x) * (q2.w + q2.x);
	float prd_2 = (q1.w - q1.x) * (q2.y + q2.z);
	float prd_3 = (q1.y + q1.z) * (q2.w - q2.x);
	float prd_4 = (q1.z - q1.x) * (q2.x - q2.y);
	float prd_5 = (q1.z + q1.x) * (q2.x + q2.y);
	float prd_6 = (q1.w + q1.y) * (q2.w - q2.z);
	float prd_7 = (q1.w - q1.y) * (q2.w + q2.z);
	float prd_8 = prd_5 + prd_6 + prd_7;
	float prd_9 = 0.5f * (prd_4 + prd_8);

	return Quaternion(prd_1 + prd_9 - prd_8,
					  prd_2 + prd_9 - prd_7,
					  prd_3 + prd_9 - prd_6,
					  prd_0 + prd_9 - prd_5);
}
