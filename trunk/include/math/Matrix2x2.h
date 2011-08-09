/*!
 * \file Matrix2x2.h
 * \date 08-08-2011 22:07:55
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __MATRIX2X2_H__
#define __MATRIX2X2_H__

#include "Vector2.h"

class Matrix2x2
{
public:
	enum GL_ELEMENT_ORDER
	{
		E11 = 0, E12 = 1,
		E21 = 2, E22 = 3,
	};

public:
	Matrix2x2();
	Matrix2x2(const Matrix2x2& m);
	Matrix2x2(float e11, float e12,
			  float e21, float e22);
	~Matrix2x2();

	Matrix2x2& operator=(const Matrix2x2& m);

	Matrix2x2& Scale(const Vector2& v);
	Matrix2x2& Scale(float x, float y);

	Matrix2x2& Transport();
	float Det();
	bool Invert();

	Matrix2x2& operator*=(const Matrix2x2& m);
	Matrix2x2& operator+=(const Matrix2x2& m);
	Matrix2x2& operator-=(const Matrix2x2& m);

public:
	float e[4];

};

Matrix2x2 operator*(const Matrix2x2& m1, const Matrix2x2& m2);
Matrix2x2 operator+(const Matrix2x2& m1, const Matrix2x2& m2);
Matrix2x2 operator-(const Matrix2x2& m1, const Matrix2x2& m2);

Vector2 operator*(const Matrix2x2& m, const Vector2& v);
#endif // __MATRIX2X2_H__
