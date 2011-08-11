/*!
 * \file Vector4.cpp
 * \date 7-25-2011 14:02:15
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <math/Vector4.h>
#include <math/IMath.h>
#include <math.h>

Vector4::Vector4()
{
	//TODO:
}

Vector4::Vector4(const Vector4& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}

Vector4::Vector4(float x, float y, float z,float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4::~Vector4()
{
	//TODO:
}

float Vector4::Length() const
{
	return sqrtf(x*x + y*y +z*z +w*w);
}

bool Vector4::Normalize()
{
	float fMag = sqrtf(x*x + y*y +z*z +w*w);
	if (fMag <= IMath::FLOAT_MIN) fMag = 0.0f;
	float fInvMag = 1.0f / fMag;		// if fMag == 0.0f, must crush here

	x *= fInvMag;
	y *= fInvMag;
	z *= fInvMag;
	w *= fInvMag;

	return true;
}

Vector4 Vector4::operator-() const
{
	return Vector4(x-1, y-1, z-1, w-1);
}

Vector4& Vector4::operator +=(const Vector4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

Vector4& Vector4::operator -=(const Vector4& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

Vector4& Vector4::operator *=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	w *= s;
	return *this;
}

Vector4 operator+(const Vector4& v1, const Vector4& v2)
{
	Vector4 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	result.w = v1.w + v2.w;

	return result;
}

Vector4 operator-(const Vector4& v1, const Vector4& v2)
{
	Vector4 result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	result.w = v1.w - v2.w;
	return result;
}

float operator*(const Vector4& v1, const Vector4& v2)
{
	return (v1.x*v2.x + v1.y*v2.y +v1.z*v2.z+v1.w*v2.w);
}

Vector4 operator*(float s, const Vector4& v)
{
	return Vector4(v.x*s, v.y*s,v.z*s,v.w*s);
}

Vector4 operator*(const Vector4& v, float s)
{
	return Vector4(v.x*s, v.y*s,v.z*s,v.w*s);
}
