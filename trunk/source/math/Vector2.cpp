/*!
 * \file Vector2.cpp
 * \date 08-08-2011 21:56:44
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <math/Vector2.h>
#include <math/IMath.h>
#include <math.h>

Vector2::Vector2()
{
	// TODO: 
}

Vector2::Vector2(const Vector2& v)
{
	x = v.x;
	y = v.y;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::~Vector2()
{
	// TODO: 
}

float Vector2::Length() const
{
	return sqrtf(x*x+y*y);
}

bool Vector2::Normalize()
{
	float fMag = sqrtf(x*x+y*y);
	if (fMag <= IMath::FLOAT_MIN) fMag = 0.0f;
	float fInvMag = 1.0f / fMag;		// if fMag == 0.0f, must crush here

	x *= fInvMag;
	y *= fInvMag;

	return true;
}

Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

Vector2& Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;
	return (*this);
}

Vector2& Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
	return (*this);
}

Vector2& Vector2::operator*=(float s)
{
	x *= s;
	y *= s;
	return (*this);
}

Vector2 operator+(const Vector2& v1, const Vector2& v2)
{
	return Vector2(v1.x+v2.x, v1.y+v2.y);
}

Vector2 operator-(const Vector2& v1, const Vector2& v2)
{
	return Vector2(v1.x-v2.x, v1.y-v2.y);
}

float operator*(const Vector2& v1, const Vector2& v2)
{
	return (v1.x*v2.x + v1.y*v2.y);
}

Vector2 operator*(float s, const Vector2& v)
{
	return Vector2(v.x*s, v.y*s);
}

Vector2 operator*(const Vector2& v, float s)
{
	return Vector2(v.x*s, v.y*s);
}
