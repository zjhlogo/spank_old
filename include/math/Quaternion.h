/*!
 * \file Quaternion.h
 * \date 7-28-2011 17:51:34
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "Vector3.h"

class Quaternion
{
public:
	Quaternion();
	Quaternion(const Quaternion& q);
	Quaternion(float x, float y, float z, float w);
	Quaternion(const Vector3& vDir, float fRadian);
	~Quaternion();

	float Length();
	bool Normalize();
	float GetRadian() const;

	Quaternion& operator=(const Quaternion& q);
	Quaternion& operator*=(const Quaternion& q);
	Quaternion operator-() const;

public:
	float x;
	float y;
	float z;
	float w;

};

Quaternion operator*(const Quaternion& q1, const Quaternion& q2);

#endif // __QUATERNION_H__
