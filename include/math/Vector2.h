/*!
 * \file Vector2.h
 * \date 08-08-2011 21:56:36
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __VECTOR2_H__
#define __VECTOR2_H__

class Vector2
{
public:
	Vector2();
	Vector2(const Vector2& v);
	Vector2(float x, float y);
	~Vector2();

	float Length() const;
	bool Normalize();

	Vector2& operator=(const Vector2& v);
	Vector2 operator-() const;
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator*=(float s);

public:
	float x;
	float y;

};

Vector2 operator+(const Vector2& v1, const Vector2& v2);
Vector2 operator-(const Vector2& v1, const Vector2& v2);
float operator*(const Vector2& v1, const Vector2& v2);

Vector2 operator*(float s, const Vector2& v);
Vector2 operator*(const Vector2& v, float s);

#endif // __VECTOR2_H__
