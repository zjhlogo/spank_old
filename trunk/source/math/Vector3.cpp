/*!
 * \file Vector3.cpp
 * \date 7-25-2011 14:01:54
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <math/Vector3.h>
#include <math.h>

Vector3::Vector3()
{
	// TODO: 
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::~Vector3()
{
	// TODO: 
}

float Vector3::GetLength() const
{
	return sqrtf(x*x+y*y+z*z);
}

float Vector3::GetSquaredLength() const
{
	return x*x+y*y+z*z;
}

void Vector3::Normalize()
{
	float fMag = GetLength();

	if (fMag > 0.0f)
	{
		float fInvMag = 1.0f/fMag;

		x *= fInvMag;
		y *= fInvMag;
		z *= fInvMag;
	}
}

Vector3& Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return (*this);
}

Vector3& Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return (*this);
}

Vector3& Vector3::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	return (*this);
}

Vector3& Vector3::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	return (*this);
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z);
}

Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x-v2.x, v1.y-v2.y, v1.z-v2.z);
}

float operator*(const Vector3& v1, const Vector3& v2)
{
	return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}

Vector3 operator*(float s, const Vector3& v)
{
	return Vector3(v.x*s, v.y*s, v.z*s);
}

Vector3 operator*(const Vector3& v, float s)
{
	return Vector3(v.x*s, v.y*s, v.z*s);
}

Vector3 operator/(const Vector3& v, float s)
{
	return Vector3(v.x/s, v.y/s, v.z/s);
}

Vector3 operator^(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.y*v2.z-v1.z*v2.y, -v1.x*v2.z+v1.z*v2.x, v1.x*v2.y-v1.y*v2.x);
}
