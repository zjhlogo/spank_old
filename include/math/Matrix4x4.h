/*!
 * \file Matrix4x4.h
 * \date 7-25-2011 11:31:39
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __MATRIX4X4_H__
#define __MATRIX4X4_H__

#include <math/Vector3.h>
#include <math/Vector4.h>

class Matrix4x4
{
public:
	enum GL_ELEMENT_ORDER
	{
		E11 = 0,  E12 = 1,  E13 = 2,  E14 = 3,
		E21 = 4,  E22 = 5,  E23 = 6,  E24 = 7,
		E31 = 8,  E32 = 9,  E33 = 10, E34 = 11,
		E41 = 12, E42 = 13, E43 = 14, E44 = 15,
	};

	Matrix4x4();
	Matrix4x4(const Matrix4x4& m);
	Matrix4x4(float e11, float e12, float e13, float e14,
			  float e21, float e22, float e23, float e24,
			  float e31, float e32, float e33, float e34,
			  float e41, float e42, float e43, float e44);
	~Matrix4x4();

	Matrix4x4& operator=(const Matrix4x4& m);

	Vector3 GetTranslate();

	Matrix4x4& SetTranslate(const Vector3& v);
	Matrix4x4& SetTranslate(float x, float y, float z);

	Matrix4x4& Translate(const Vector3& v);
	Matrix4x4& Translate(float x, float y, float z);

	Matrix4x4& Scale(const Vector3& v);
	Matrix4x4& Scale(float x, float y, float z);

	Matrix4x4& Transport();
	float Det();
	bool Invert();

	Vector3 GetAxisX();
	Vector3 GetAxisY();
	Vector3 GetAxisZ();

	Matrix4x4& operator+=(const Matrix4x4& m);
	Matrix4x4& operator-=(const Matrix4x4& m);
	Matrix4x4& operator*=(const Matrix4x4& m);

public:
	float e[16];

};

Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2);

Vector4 operator*(const Matrix4x4& m, const Vector4& v);
Vector4 operator*(const Vector4& v, const Matrix4x4& m);
#endif // __MATRIX4X4_H__
