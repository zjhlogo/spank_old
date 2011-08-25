/*!
 * \file Matrix4x4.cpp
 * \date 7-25-2011 12:02:26
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <math/Matrix4x4.h>
#include <math/IMath.h>
#include <math.h>

Matrix4x4::Matrix4x4()
{
	// TODO: 
}

Matrix4x4::Matrix4x4(const Matrix4x4& m)
{
	e[E11] = m.e[E11]; e[E12] = m.e[E12]; e[E13] = m.e[E13]; e[E14] = m.e[E14];
	e[E21] = m.e[E21]; e[E22] = m.e[E22]; e[E23] = m.e[E23]; e[E24] = m.e[E24];
	e[E31] = m.e[E31]; e[E32] = m.e[E32]; e[E33] = m.e[E33]; e[E34] = m.e[E34];
	e[E41] = m.e[E41]; e[E42] = m.e[E42]; e[E43] = m.e[E43]; e[E44] = m.e[E44];
}

Matrix4x4::Matrix4x4(float e11, float e12, float e13, float e14,
					 float e21, float e22, float e23, float e24,
					 float e31, float e32, float e33, float e34,
					 float e41, float e42, float e43, float e44)
{
	e[E11] = e11; e[E12] = e12; e[E13] = e13; e[E14] = e14;
	e[E21] = e21; e[E22] = e22; e[E23] = e23; e[E24] = e24;
	e[E31] = e31; e[E32] = e32; e[E33] = e33; e[E34] = e34;
	e[E41] = e41; e[E42] = e42; e[E43] = e43; e[E44] = e44;
}

Matrix4x4::~Matrix4x4()
{
	// TODO: 
}

Matrix4x4& Matrix4x4::operator=(const Matrix4x4& m)
{
	e[E11] = m.e[E11]; e[E12] = m.e[E12]; e[E13] = m.e[E13]; e[E14] = m.e[E14];
	e[E21] = m.e[E21]; e[E22] = m.e[E22]; e[E23] = m.e[E23]; e[E24] = m.e[E24];
	e[E31] = m.e[E31]; e[E32] = m.e[E32]; e[E33] = m.e[E33]; e[E34] = m.e[E34];
	e[E41] = m.e[E41]; e[E42] = m.e[E42]; e[E43] = m.e[E43]; e[E44] = m.e[E44];
	return (*this);
}

Vector3 Matrix4x4::GetTranslate()
{
	//
	// [ N/E  N/E  N/E   x  ]
	// [ N/E  N/E  N/E   y  ]
	// [ N/E  N/E  N/E   z  ]
	// [ N/E  N/E  N/E  N/E ]
	//
	return Vector3(e[E14], e[E24], e[E34]);
}

Matrix4x4& Matrix4x4::SetTranslate(const Vector3& v)
{
	//
	// [ N/E  N/E  N/E   x  ]
	// [ N/E  N/E  N/E   y  ]
	// [ N/E  N/E  N/E   z  ]
	// [ N/E  N/E  N/E  N/E ]
	//
	e[E14] = v.x;
	e[E24] = v.y;
	e[E34] = v.z;
	return (*this);
}

Matrix4x4& Matrix4x4::SetTranslate(float x, float y, float z)
{
	//
	// [ N/E  N/E  N/E   x  ]
	// [ N/E  N/E  N/E   y  ]
	// [ N/E  N/E  N/E   z  ]
	// [ N/E  N/E  N/E  N/E ]
	//
	e[E14] = x;
	e[E24] = y;
	e[E34] = z;
	return (*this);
}

Matrix4x4& Matrix4x4::Translate(const Vector3& v)
{
	//
	// [ N/E  N/E  N/E  +x  ]
	// [ N/E  N/E  N/E  +y  ]
	// [ N/E  N/E  N/E  +z  ]
	// [ N/E  N/E  N/E  N/E ]
	//
	e[E14] += v.x;
	e[E24] += v.y;
	e[E34] += v.z;
	return (*this);
}

Matrix4x4& Matrix4x4::Translate(float x, float y, float z)
{
	//
	// [ N/E  N/E  N/E  +x  ]
	// [ N/E  N/E  N/E  +y  ]
	// [ N/E  N/E  N/E  +z  ]
	// [ N/E  N/E  N/E  N/E ]
	//
	e[E14] += x;
	e[E24] += y;
	e[E34] += z;
	return (*this);
}

Matrix4x4& Matrix4x4::Scale(const Vector3& v)
{
	//
	// [ *x    N/E   N/E   N/E ]
	// [ N/E   *y    N/E   N/E ]
	// [ N/E   N/E   *z    N/E ]
	// [ N/E   N/E   N/E   N/E ]
	//
	e[E11] *= v.x;
	e[E22] *= v.y;
	e[E33] *= v.z;
	return (*this);
}

Matrix4x4& Matrix4x4::Scale(float x, float y, float z)
{
	//
	// [ *x    N/E   N/E   N/E ]
	// [ N/E   *y    N/E   N/E ]
	// [ N/E   N/E   *z    N/E ]
	// [ N/E   N/E   N/E   N/E ]
	//
	e[E11] *= x;
	e[E22] *= y;
	e[E33] *= z;
	return (*this);
}

Matrix4x4& Matrix4x4::Transport()
{
	float temp = 0.0f;

	temp = e[E12]; e[E12] = e[E21]; e[E21] = temp;
	temp = e[E13]; e[E13] = e[E31]; e[E31] = temp;
	temp = e[E14]; e[E14] = e[E41]; e[E41] = temp;
	temp = e[E23]; e[E23] = e[E32]; e[E32] = temp;
	temp = e[E24]; e[E24] = e[E42]; e[E42] = temp;
	temp = e[E34]; e[E34] = e[E43]; e[E43] = temp;

	return (*this);
}

float Matrix4x4::Det()
{
	float fA0 = e[E11]*e[E22] - e[E12]*e[E21];
	float fA1 = e[E11]*e[E23] - e[E13]*e[E21];
	float fA2 = e[E11]*e[E24] - e[E14]*e[E21];
	float fA3 = e[E12]*e[E23] - e[E13]*e[E22];
	float fA4 = e[E12]*e[E24] - e[E14]*e[E22];
	float fA5 = e[E13]*e[E24] - e[E14]*e[E23];

	float fB0 = e[E31]*e[E42] - e[E32]*e[E41];
	float fB1 = e[E31]*e[E43] - e[E33]*e[E41];
	float fB2 = e[E31]*e[E44] - e[E34]*e[E41];
	float fB3 = e[E32]*e[E43] - e[E33]*e[E42];
	float fB4 = e[E32]*e[E44] - e[E34]*e[E42];
	float fB5 = e[E33]*e[E44] - e[E34]*e[E43];

	return fA0*fB5 - fA1*fB4 + fA2*fB3 + fA3*fB2 - fA4*fB1 + fA5*fB0;
}

bool Matrix4x4::Invert()
{
	float fA0 = e[E11]*e[E22] - e[E12]*e[E21];
	float fA1 = e[E11]*e[E23] - e[E13]*e[E21];
	float fA2 = e[E11]*e[E24] - e[E14]*e[E21];
	float fA3 = e[E12]*e[E23] - e[E13]*e[E22];
	float fA4 = e[E12]*e[E24] - e[E14]*e[E22];
	float fA5 = e[E13]*e[E24] - e[E14]*e[E23];

	float fB0 = e[E31]*e[E42] - e[E32]*e[E41];
	float fB1 = e[E31]*e[E43] - e[E33]*e[E41];
	float fB2 = e[E31]*e[E44] - e[E34]*e[E41];
	float fB3 = e[E32]*e[E43] - e[E33]*e[E42];
	float fB4 = e[E32]*e[E44] - e[E34]*e[E42];
	float fB5 = e[E33]*e[E44] - e[E34]*e[E43];

	float fDet = fA0*fB5 - fA1*fB4 + fA2*fB3 + fA3*fB2 - fA4*fB1 + fA5*fB0;
	if (fabsf(fDet) <= IMath::FLOAT_MIN) fDet = 0.0f;
	float fInvDet = 1.0f / fDet;		// can be crush here, if fDet == 0.0f

	Matrix4x4 matAdjoint;

	matAdjoint.e[E11] = +e[E22]*fB5 - e[E23]*fB4 + e[E24]*fB3; 
	matAdjoint.e[E12] = -e[E12]*fB5 + e[E13]*fB4 - e[E14]*fB3;
	matAdjoint.e[E13] = +e[E42]*fA5 - e[E43]*fA4 + e[E44]*fA3;
	matAdjoint.e[E14] = -e[E32]*fA5 + e[E33]*fA4 - e[E34]*fA3;

	matAdjoint.e[E21] = -e[E21]*fB5 + e[E23]*fB2 - e[E24]*fB1;
	matAdjoint.e[E22] = +e[E11]*fB5 - e[E13]*fB2 + e[E14]*fB1;
	matAdjoint.e[E23] = -e[E41]*fA5 + e[E43]*fA2 - e[E44]*fA1;
	matAdjoint.e[E24] = +e[E31]*fA5 - e[E33]*fA2 + e[E34]*fA1;

	matAdjoint.e[E31] = +e[E21]*fB4 - e[E22]*fB2 + e[E24]*fB0;
	matAdjoint.e[E32] = -e[E11]*fB4 + e[E12]*fB2 - e[E14]*fB0;
	matAdjoint.e[E33] = +e[E41]*fA4 - e[E42]*fA2 + e[E44]*fA0;

	matAdjoint.e[E34] = -e[E31]*fA4 + e[E32]*fA2 - e[E34]*fA0;

	matAdjoint.e[E41] = -e[E21]*fB3 + e[E22]*fB1 - e[E23]*fB0;
	matAdjoint.e[E42] = +e[E11]*fB3 - e[E12]*fB1 + e[E13]*fB0;
	matAdjoint.e[E43] = -e[E41]*fA3 + e[E42]*fA1 - e[E43]*fA0;
	matAdjoint.e[E44] = +e[E31]*fA3 - e[E32]*fA1 + e[E33]*fA0;

	e[E11] = matAdjoint.e[E11] * fInvDet;
	e[E12] = matAdjoint.e[E12] * fInvDet;
	e[E13] = matAdjoint.e[E13] * fInvDet;
	e[E14] = matAdjoint.e[E14] * fInvDet;

	e[E21] = matAdjoint.e[E21] * fInvDet;
	e[E22] = matAdjoint.e[E22] * fInvDet;
	e[E23] = matAdjoint.e[E23] * fInvDet;
	e[E24] = matAdjoint.e[E24] * fInvDet;

	e[E31] = matAdjoint.e[E31] * fInvDet;
	e[E32] = matAdjoint.e[E32] * fInvDet;
	e[E33] = matAdjoint.e[E33] * fInvDet;
	e[E34] = matAdjoint.e[E34] * fInvDet;

	e[E41] = matAdjoint.e[E41] * fInvDet;
	e[E42] = matAdjoint.e[E42] * fInvDet;
	e[E43] = matAdjoint.e[E43] * fInvDet;
	e[E44] = matAdjoint.e[E44] * fInvDet;

	return true;
}

Vector3 Matrix4x4::GetAxisX()
{
	//
	// [  x   N/E  N/E  N/E ]
	// [  y   N/E  N/E  N/E ]
	// [  z   N/E  N/E  N/E ]
	// [ N/E  N/E  N/E  N/E ]
	//
	return Vector3(e[E11], e[E21], e[E31]);
}

Vector3 Matrix4x4::GetAxisY()
{
	//
	// [ N/E   x   N/E  N/E ]
	// [ N/E   y   N/E  N/E ]
	// [ N/E   z   N/E  N/E ]
	// [ N/E  N/E  N/E  N/E ]
	//
	return Vector3(e[E12], e[E22], e[E32]);
}

Vector3 Matrix4x4::GetAxisZ()
{
	//
	// [ N/E  N/E   x   N/E ]
	// [ N/E  N/E   y   N/E ]
	// [ N/E  N/E   z   N/E ]
	// [ N/E  N/E  N/E  N/E ]
	//
	return Vector3(e[E13], e[E23], e[E33]);
}

Matrix4x4& Matrix4x4::operator +=(const Matrix4x4& m)
{
	Matrix4x4 result;

	result.e[E11] = e[E11] + m.e[E11];
	result.e[E12] = e[E12] + m.e[E12];
	result.e[E13] = e[E13] + m.e[E13];
	result.e[E14] = e[E14] + m.e[E14];

	result.e[E21] = e[E21] + m.e[E21];
	result.e[E22] = e[E22] + m.e[E22];
	result.e[E23] = e[E23] + m.e[E23];
	result.e[E24] = e[E24] + m.e[E24];

	result.e[E31] = e[E31] + m.e[E31];
	result.e[E32] = e[E32] + m.e[E32];
	result.e[E33] = e[E33] + m.e[E33];
	result.e[E34] = e[E34] + m.e[E34];

	result.e[E41] = e[E41] + m.e[E41];
	result.e[E42] = e[E42] + m.e[E42];
	result.e[E43] = e[E43] + m.e[E43];
	result.e[E44] = e[E44] + m.e[E44];

	(*this) = result;
	return (*this);
}
Matrix4x4& Matrix4x4::operator -=(const Matrix4x4& m)
{	
	Matrix4x4 result;

	result.e[E11] = e[E11] - m.e[E11];
	result.e[E12] = e[E12] - m.e[E12];
	result.e[E13] = e[E13] - m.e[E13];
	result.e[E14] = e[E14] - m.e[E14];

	result.e[E21] = e[E21] - m.e[E21];
	result.e[E22] = e[E22] - m.e[E22];
	result.e[E23] = e[E23] - m.e[E23];
	result.e[E24] = e[E24] - m.e[E24];

	result.e[E31] = e[E31] - m.e[E31];
	result.e[E32] = e[E32] - m.e[E32];
	result.e[E33] = e[E33] - m.e[E33];
	result.e[E34] = e[E34] - m.e[E34];

	result.e[E41] = e[E41] - m.e[E41];
	result.e[E42] = e[E42] - m.e[E42];
	result.e[E43] = e[E43] - m.e[E43];
	result.e[E44] = e[E44] - m.e[E44];

	(*this) = result;
	return (*this);
}

Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& m)
{
	// “矩阵A与B的乘积矩阵C的第i行第j列的元素c(ij)等于A的第i行于B的第j列的对应元素乘积的和。”（实用数学手册，科学出版社，第二版）
	Matrix4x4 result;
	result.e[E11] = e[E11]*m.e[E11] + e[E12]*m.e[E21] + e[E13]*m.e[E31] + e[E14]*m.e[E41];
	result.e[E12] = e[E11]*m.e[E12] + e[E12]*m.e[E22] + e[E13]*m.e[E32] + e[E14]*m.e[E42];
	result.e[E13] = e[E11]*m.e[E13] + e[E12]*m.e[E23] + e[E13]*m.e[E33] + e[E14]*m.e[E43];
	result.e[E14] = e[E11]*m.e[E14] + e[E12]*m.e[E24] + e[E13]*m.e[E34] + e[E14]*m.e[E44];

	result.e[E21] = e[E21]*m.e[E11] + e[E22]*m.e[E21] + e[E23]*m.e[E31] + e[E24]*m.e[E41];
	result.e[E22] = e[E21]*m.e[E12] + e[E22]*m.e[E22] + e[E23]*m.e[E32] + e[E24]*m.e[E42];
	result.e[E23] = e[E21]*m.e[E13] + e[E22]*m.e[E23] + e[E23]*m.e[E33] + e[E24]*m.e[E43];
	result.e[E24] = e[E21]*m.e[E14] + e[E22]*m.e[E24] + e[E23]*m.e[E34] + e[E24]*m.e[E44];

	result.e[E31] = e[E31]*m.e[E11] + e[E32]*m.e[E21] + e[E33]*m.e[E31] + e[E34]*m.e[E41];
	result.e[E32] = e[E31]*m.e[E12] + e[E32]*m.e[E22] + e[E33]*m.e[E32] + e[E34]*m.e[E42];
	result.e[E33] = e[E31]*m.e[E13] + e[E32]*m.e[E23] + e[E33]*m.e[E33] + e[E34]*m.e[E43];
	result.e[E34] = e[E31]*m.e[E14] + e[E32]*m.e[E24] + e[E33]*m.e[E34] + e[E34]*m.e[E44];

	result.e[E41] = e[E41]*m.e[E11] + e[E42]*m.e[E21] + e[E43]*m.e[E31] + e[E44]*m.e[E41];
	result.e[E42] = e[E41]*m.e[E12] + e[E42]*m.e[E22] + e[E43]*m.e[E32] + e[E44]*m.e[E42];
	result.e[E43] = e[E41]*m.e[E13] + e[E42]*m.e[E23] + e[E43]*m.e[E33] + e[E44]*m.e[E43];
	result.e[E44] = e[E41]*m.e[E14] + e[E42]*m.e[E24] + e[E43]*m.e[E34] + e[E44]*m.e[E44];

	(*this) = result;
	return (*this);
}

Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;
	result.e[Matrix4x4::E11] = m1.e[Matrix4x4::E11] + m2.e[Matrix4x4::E11];
	result.e[Matrix4x4::E12] = m1.e[Matrix4x4::E12] + m2.e[Matrix4x4::E12];
	result.e[Matrix4x4::E13] = m1.e[Matrix4x4::E13] + m2.e[Matrix4x4::E13];
	result.e[Matrix4x4::E14] = m1.e[Matrix4x4::E14] + m2.e[Matrix4x4::E14];

	result.e[Matrix4x4::E21] = m1.e[Matrix4x4::E21] + m2.e[Matrix4x4::E21];
	result.e[Matrix4x4::E22] = m1.e[Matrix4x4::E22] + m2.e[Matrix4x4::E22];
	result.e[Matrix4x4::E23] = m1.e[Matrix4x4::E23] + m2.e[Matrix4x4::E23];
	result.e[Matrix4x4::E24] = m1.e[Matrix4x4::E24] + m2.e[Matrix4x4::E24];

	result.e[Matrix4x4::E31] = m1.e[Matrix4x4::E31] + m2.e[Matrix4x4::E31];
	result.e[Matrix4x4::E32] = m1.e[Matrix4x4::E32] + m2.e[Matrix4x4::E32];
	result.e[Matrix4x4::E33] = m1.e[Matrix4x4::E33] + m2.e[Matrix4x4::E33];
	result.e[Matrix4x4::E34] = m1.e[Matrix4x4::E34] + m2.e[Matrix4x4::E34];

	result.e[Matrix4x4::E41] = m1.e[Matrix4x4::E41] + m2.e[Matrix4x4::E41];
	result.e[Matrix4x4::E42] = m1.e[Matrix4x4::E42] + m2.e[Matrix4x4::E42];
	result.e[Matrix4x4::E43] = m1.e[Matrix4x4::E43] + m2.e[Matrix4x4::E43];
	result.e[Matrix4x4::E44] = m1.e[Matrix4x4::E44] + m2.e[Matrix4x4::E44];

	return result;
}

Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;
	result.e[Matrix4x4::E11] = m1.e[Matrix4x4::E11] - m2.e[Matrix4x4::E11];
	result.e[Matrix4x4::E12] = m1.e[Matrix4x4::E12] - m2.e[Matrix4x4::E12];
	result.e[Matrix4x4::E13] = m1.e[Matrix4x4::E13] - m2.e[Matrix4x4::E13];
	result.e[Matrix4x4::E14] = m1.e[Matrix4x4::E14] - m2.e[Matrix4x4::E14];

	result.e[Matrix4x4::E21] = m1.e[Matrix4x4::E21] - m2.e[Matrix4x4::E21];
	result.e[Matrix4x4::E22] = m1.e[Matrix4x4::E22] - m2.e[Matrix4x4::E22];
	result.e[Matrix4x4::E23] = m1.e[Matrix4x4::E23] - m2.e[Matrix4x4::E23];
	result.e[Matrix4x4::E24] = m1.e[Matrix4x4::E24] - m2.e[Matrix4x4::E24];

	result.e[Matrix4x4::E31] = m1.e[Matrix4x4::E31] - m2.e[Matrix4x4::E31];
	result.e[Matrix4x4::E32] = m1.e[Matrix4x4::E32] - m2.e[Matrix4x4::E32];
	result.e[Matrix4x4::E33] = m1.e[Matrix4x4::E33] - m2.e[Matrix4x4::E33];
	result.e[Matrix4x4::E34] = m1.e[Matrix4x4::E34] - m2.e[Matrix4x4::E34];

	result.e[Matrix4x4::E41] = m1.e[Matrix4x4::E41] - m2.e[Matrix4x4::E41];
	result.e[Matrix4x4::E42] = m1.e[Matrix4x4::E42] - m2.e[Matrix4x4::E42];
	result.e[Matrix4x4::E43] = m1.e[Matrix4x4::E43] - m2.e[Matrix4x4::E43];
	result.e[Matrix4x4::E44] = m1.e[Matrix4x4::E44] - m2.e[Matrix4x4::E44];

	return result;
}

Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2)
{
	// “矩阵A与B的乘积矩阵C的第i行第j列的元素c(ij)等于A的第i行于B的第j列的对应元素乘积的和。”（实用数学手册，科学出版社，第二版）
	Matrix4x4 result;
	result.e[Matrix4x4::E11] = m1.e[Matrix4x4::E11]*m2.e[Matrix4x4::E11] + m1.e[Matrix4x4::E12]*m2.e[Matrix4x4::E21] + m1.e[Matrix4x4::E13]*m2.e[Matrix4x4::E31] + m1.e[Matrix4x4::E14]*m2.e[Matrix4x4::E41];
	result.e[Matrix4x4::E12] = m1.e[Matrix4x4::E11]*m2.e[Matrix4x4::E12] + m1.e[Matrix4x4::E12]*m2.e[Matrix4x4::E22] + m1.e[Matrix4x4::E13]*m2.e[Matrix4x4::E32] + m1.e[Matrix4x4::E14]*m2.e[Matrix4x4::E42];
	result.e[Matrix4x4::E13] = m1.e[Matrix4x4::E11]*m2.e[Matrix4x4::E13] + m1.e[Matrix4x4::E12]*m2.e[Matrix4x4::E23] + m1.e[Matrix4x4::E13]*m2.e[Matrix4x4::E33] + m1.e[Matrix4x4::E14]*m2.e[Matrix4x4::E43];
	result.e[Matrix4x4::E14] = m1.e[Matrix4x4::E11]*m2.e[Matrix4x4::E14] + m1.e[Matrix4x4::E12]*m2.e[Matrix4x4::E24] + m1.e[Matrix4x4::E13]*m2.e[Matrix4x4::E34] + m1.e[Matrix4x4::E14]*m2.e[Matrix4x4::E44];

	result.e[Matrix4x4::E21] = m1.e[Matrix4x4::E21]*m2.e[Matrix4x4::E11] + m1.e[Matrix4x4::E22]*m2.e[Matrix4x4::E21] + m1.e[Matrix4x4::E23]*m2.e[Matrix4x4::E31] + m1.e[Matrix4x4::E24]*m2.e[Matrix4x4::E41];
	result.e[Matrix4x4::E22] = m1.e[Matrix4x4::E21]*m2.e[Matrix4x4::E12] + m1.e[Matrix4x4::E22]*m2.e[Matrix4x4::E22] + m1.e[Matrix4x4::E23]*m2.e[Matrix4x4::E32] + m1.e[Matrix4x4::E24]*m2.e[Matrix4x4::E42];
	result.e[Matrix4x4::E23] = m1.e[Matrix4x4::E21]*m2.e[Matrix4x4::E13] + m1.e[Matrix4x4::E22]*m2.e[Matrix4x4::E23] + m1.e[Matrix4x4::E23]*m2.e[Matrix4x4::E33] + m1.e[Matrix4x4::E24]*m2.e[Matrix4x4::E43];
	result.e[Matrix4x4::E24] = m1.e[Matrix4x4::E21]*m2.e[Matrix4x4::E14] + m1.e[Matrix4x4::E22]*m2.e[Matrix4x4::E24] + m1.e[Matrix4x4::E23]*m2.e[Matrix4x4::E34] + m1.e[Matrix4x4::E24]*m2.e[Matrix4x4::E44];

	result.e[Matrix4x4::E31] = m1.e[Matrix4x4::E31]*m2.e[Matrix4x4::E11] + m1.e[Matrix4x4::E32]*m2.e[Matrix4x4::E21] + m1.e[Matrix4x4::E33]*m2.e[Matrix4x4::E31] + m1.e[Matrix4x4::E34]*m2.e[Matrix4x4::E41];
	result.e[Matrix4x4::E32] = m1.e[Matrix4x4::E31]*m2.e[Matrix4x4::E12] + m1.e[Matrix4x4::E32]*m2.e[Matrix4x4::E22] + m1.e[Matrix4x4::E33]*m2.e[Matrix4x4::E32] + m1.e[Matrix4x4::E34]*m2.e[Matrix4x4::E42];
	result.e[Matrix4x4::E33] = m1.e[Matrix4x4::E31]*m2.e[Matrix4x4::E13] + m1.e[Matrix4x4::E32]*m2.e[Matrix4x4::E23] + m1.e[Matrix4x4::E33]*m2.e[Matrix4x4::E33] + m1.e[Matrix4x4::E34]*m2.e[Matrix4x4::E43];
	result.e[Matrix4x4::E34] = m1.e[Matrix4x4::E31]*m2.e[Matrix4x4::E14] + m1.e[Matrix4x4::E32]*m2.e[Matrix4x4::E24] + m1.e[Matrix4x4::E33]*m2.e[Matrix4x4::E34] + m1.e[Matrix4x4::E34]*m2.e[Matrix4x4::E44];

	result.e[Matrix4x4::E41] = m1.e[Matrix4x4::E41]*m2.e[Matrix4x4::E11] + m1.e[Matrix4x4::E42]*m2.e[Matrix4x4::E21] + m1.e[Matrix4x4::E43]*m2.e[Matrix4x4::E31] + m1.e[Matrix4x4::E44]*m2.e[Matrix4x4::E41];
	result.e[Matrix4x4::E42] = m1.e[Matrix4x4::E41]*m2.e[Matrix4x4::E12] + m1.e[Matrix4x4::E42]*m2.e[Matrix4x4::E22] + m1.e[Matrix4x4::E43]*m2.e[Matrix4x4::E32] + m1.e[Matrix4x4::E44]*m2.e[Matrix4x4::E42];
	result.e[Matrix4x4::E43] = m1.e[Matrix4x4::E41]*m2.e[Matrix4x4::E13] + m1.e[Matrix4x4::E42]*m2.e[Matrix4x4::E23] + m1.e[Matrix4x4::E43]*m2.e[Matrix4x4::E33] + m1.e[Matrix4x4::E44]*m2.e[Matrix4x4::E43];
	result.e[Matrix4x4::E44] = m1.e[Matrix4x4::E41]*m2.e[Matrix4x4::E14] + m1.e[Matrix4x4::E42]*m2.e[Matrix4x4::E24] + m1.e[Matrix4x4::E43]*m2.e[Matrix4x4::E34] + m1.e[Matrix4x4::E44]*m2.e[Matrix4x4::E44];

	return result;
}

Vector4 operator*(const Matrix4x4& m, const Vector4& v)
{
	Vector4 result;

	result.x = m.e[Matrix4x4::E11]*v.x + m.e[Matrix4x4::E12]*v.y + m.e[Matrix4x4::E13]*v.z + m.e[Matrix4x4::E14]*v.w;
	result.y = m.e[Matrix4x4::E21]*v.x + m.e[Matrix4x4::E22]*v.y + m.e[Matrix4x4::E23]*v.z + m.e[Matrix4x4::E24]*v.w;
	result.z = m.e[Matrix4x4::E31]*v.x + m.e[Matrix4x4::E32]*v.y + m.e[Matrix4x4::E33]*v.z + m.e[Matrix4x4::E34]*v.w;
	result.w = m.e[Matrix4x4::E41]*v.x + m.e[Matrix4x4::E42]*v.y + m.e[Matrix4x4::E43]*v.z + m.e[Matrix4x4::E44]*v.w;

	return result;
}
Vector4 operator*(const Vector4& v, const Matrix4x4& m)
{
	Vector4 result;

	result.x = v.x * m.e[Matrix4x4::E11] + v.y * m.e[Matrix4x4::E21] + v.z * m.e[Matrix4x4::E31] + v.w * m.e[Matrix4x4::E41];
	result.y = v.x * m.e[Matrix4x4::E12] + v.y * m.e[Matrix4x4::E22] + v.z * m.e[Matrix4x4::E32] + v.w * m.e[Matrix4x4::E42];
	result.z = v.x * m.e[Matrix4x4::E13] + v.y * m.e[Matrix4x4::E23] + v.z * m.e[Matrix4x4::E33] + v.w * m.e[Matrix4x4::E43];
	result.w = v.x * m.e[Matrix4x4::E14] + v.y * m.e[Matrix4x4::E24] + v.z * m.e[Matrix4x4::E34] + v.w * m.e[Matrix4x4::E44];
	return result;
}

