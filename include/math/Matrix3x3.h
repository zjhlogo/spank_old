/*!
 * \file Matrix3x3.h
 * \date 29-07-2011 23:17:39
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __MATRIX3X3_H__
#define __MATRIX3X3_H__

#include <math/Vector3.h>

/*
 * class Matrix3x3
 *
 */
class Matrix3x3
{
public:
	enum GL_ELEMENT_ORDER
	{
		E11 = 0, E12 = 1, E13 = 3,
		E21 = 3, E22 = 4, E23 = 5,
		E31 = 6, E32 = 7, E33 = 8,
	};

public:
	Matrix3x3();
	Matrix3x3(const Matrix3x3& m);
	Matrix3x3(float e11, float e12, float e13,
			  float e21, float e22, float e23,
			  float e31, float e32, float e33);
	~Matrix3x3();

	Matrix3x3& operator=(const Matrix3x3& m);

	Matrix3x3& Scale(const Vector3& v);
	Matrix3x3& Scale(float x, float y, float z);

	Matrix3x3& Transport();
	float Det();
	bool Invert();

	Vector3 GetAxisX();
	Vector3 GetAxisY();
	Vector3 GetAxisZ();

	Matrix3x3& operator*=(const Matrix3x3& m);
	Matrix3x3& operator+=(const Matrix3x3& m);
	Matrix3x3& operator-=(const Matrix3x3& m);

public:
	float e[9];

};

Matrix3x3 operator*(const Matrix3x3& m1, const Matrix3x3& m2);
Matrix3x3 operator+(const Matrix3x3& m1, const Matrix3x3& m2);
Matrix3x3 operator-(const Matrix3x3& m1, const Matrix3x3& m2);

Vector3 operator*(const Matrix3x3& m, const Vector3& v);

#endif // __MATRIX3X3_H__
