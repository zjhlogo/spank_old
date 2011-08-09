
/*!
 * \file Vector4.h
 * \date 7-25-2011 14:02:06
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __VECTOR4_H__
#define __VECTOR4_H__

class Vector4
{
public:
	Vector4();
	Vector4(const Vector4& v);
	Vector4(float x, float y, float z, float w);
	~Vector4();

	float Length() const;
	bool Normalize();

	Vector4 operator-() const;

	Vector4& operator+=(const Vector4& v);
	Vector4& operator-=(const Vector4& v);
	Vector4& operator*=(float s);

public:
	float x;
	float y;
	float z;
	float w;

};
Vector4 operator+(const Vector4& v1, const Vector4& v2);
Vector4 operator-(const Vector4& v1, const Vector4& v2);
float operator*(const Vector4& v1, const Vector4& v2);

Vector4 operator*(float s, const Vector4& v);
Vector4 operator*(const Vector4& v, float s);

#endif // __VECTOR4_H__
