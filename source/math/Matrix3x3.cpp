/*!
 * \file Matrix3x3.cpp
 * \date 29-07-2011 23:17:42
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <math/Matrix3x3.h>
#include <math/IMath.h>
#include <math.h>

Matrix3x3::Matrix3x3()
{
	//TODO:
}

Matrix3x3::Matrix3x3(const Matrix3x3& m)
{
	e[E11] = m.e[E11]; e[E12] = m.e[E12]; e[E13] = m.e[E13];
	e[E21] = m.e[E21]; e[E22] = m.e[E22]; e[E23] = m.e[E23];
	e[E31] = m.e[E31]; e[E32] = m.e[E32]; e[E33] = m.e[E33];
}

Matrix3x3::Matrix3x3(float e11, float e12, float e13,
					 float e21, float e22, float e23,
					 float e31, float e32, float e33)
{
	e[E11] = e11; e[E12] = e12; e[E13] = e13;
	e[E21] = e21; e[E22] = e22; e[E23] = e23;
	e[E31] = e31; e[E32] = e32; e[E33] = e33;
}

Matrix3x3::~Matrix3x3()
{
	//TODO:
}

Matrix3x3& Matrix3x3::operator=(const Matrix3x3& m)
{
	e[E11] = m.e[E11]; e[E12] = m.e[E12]; e[E13] = m.e[E13];
	e[E21] = m.e[E21]; e[E22] = m.e[E22]; e[E23] = m.e[E23];
	e[E31] = m.e[E31]; e[E32] = m.e[E32]; e[E33] = m.e[E33];
	return (*this);
}

Matrix3x3& Matrix3x3::Scale(const Vector3& v)
{
	//
	// [ *x    N/E   N/E ]
	// [ N/E   *y    N/E ]
	// [ N/E   N/E   *z  ]
	//
	e[E11] *= v.x;
	e[E22] *= v.y;
	e[E33] *= v.z;
	return (*this);
}

Matrix3x3& Matrix3x3::Scale(float x, float y, float z)
{
	//
	// [ *x    N/E   N/E ]
	// [ N/E   *y    N/E ]
	// [ N/E   N/E   *z  ]
	//
	e[E11] *= x;
	e[E22] *= y;
	e[E33] *= z;
	return (*this);
}

Matrix3x3& Matrix3x3::Transport()
{
	float temp = 0.0f;

	temp = e[E12]; e[E12] = e[E21]; e[E21] = temp;
	temp = e[E13]; e[E13] = e[E31]; e[E31] = temp;
	temp = e[E23]; e[E23] = e[E32]; e[E32] = temp;

	return (*this);
}

float Matrix3x3::Det()
{
	//求行列式
	float fV1 = e[E11]*e[E22]*e[E33] + e[E12]*e[E23]*e[E31] + e[E13]*e[E21]*e[E32];
	float fV2 = e[E13]*e[E22]*e[E31] + e[E23]*e[E32]*e[E11] + e[E33]*e[E12]*e[E21];
	return fV1 - fV2;
}

bool Matrix3x3::Invert()
{
	//求行列式
	float fV1 = e[E11]*e[E22]*e[E33] + e[E12]*e[E23]*e[E31] + e[E13]*e[E21]*e[E32];
	float fV2 = e[E13]*e[E22]*e[E31] + e[E23]*e[E32]*e[E11] + e[E33]*e[E12]*e[E21];
	float fDet = fV1 - fV2;
	if (fabsf(fDet) <= IMath::FLOAT_MIN) fDet = 0.0f;
	float fInvDet = 1.0f / fDet;		// can be crush here, if fDet == 0.0f

	//伴随矩阵
	Matrix3x3 matAdjoint;
	matAdjoint.e[E11] =   e[E22]*e[E33] - e[E23]*e[E32];
	matAdjoint.e[E22] =   e[E11]*e[E33] - e[E13]*e[E31];
	matAdjoint.e[E33] =   e[E11]*e[E22] - e[E12]*e[E21];

	matAdjoint.e[E12] = -(e[E12]*e[E33] - e[E13]*e[E32]);
	matAdjoint.e[E13] =  (e[E12]*e[E23] - e[E13]*e[E22]);

	matAdjoint.e[E21] = -(e[E21]*e[E33] - e[E23]*e[E31]);
	matAdjoint.e[E23] = -(e[E11]*e[E23] - e[E13]*e[E21]);

	matAdjoint.e[E31] =  (e[E21]*e[E32] - e[E22]*e[E31]);
	matAdjoint.e[E32] = -(e[E11]*e[E32] - e[E12]*e[E31]);

	e[E11] = matAdjoint.e[E11] * fInvDet;
	e[E12] = matAdjoint.e[E12] * fInvDet;
	e[E13] = matAdjoint.e[E13] * fInvDet;

	e[E21] = matAdjoint.e[E21] * fInvDet;
	e[E22] = matAdjoint.e[E22] * fInvDet;
	e[E23] = matAdjoint.e[E23] * fInvDet;

	e[E31] = matAdjoint.e[E31] * fInvDet;
	e[E32] = matAdjoint.e[E32] * fInvDet;
	e[E33] = matAdjoint.e[E33] * fInvDet;
	return true;
}

Vector3 Matrix3x3::GetAxisX()
{
	//
	// [  x   N/E  N/E  N/E ]
	// [  y   N/E  N/E  N/E ]
	// [  z   N/E  N/E  N/E ]
	// [ N/E  N/E  N/E  N/E ]
	//
	return Vector3(e[E11], e[E21], e[E31]);
}

Vector3 Matrix3x3::GetAxisY()
{
	//
	// [ N/E   x   N/E  N/E ]
	// [ N/E   y   N/E  N/E ]
	// [ N/E   z   N/E  N/E ]
	// [ N/E  N/E  N/E  N/E ]
	//
	return Vector3(e[E12], e[E22], e[E32]);
}

Vector3 Matrix3x3::GetAxisZ()
{
	//
	// [ N/E  N/E   x   N/E ]
	// [ N/E  N/E   y   N/E ]
	// [ N/E  N/E   z   N/E ]
	// [ N/E  N/E  N/E  N/E ]
	//
	return Vector3(e[E13], e[E23], e[E33]);
}

Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& m)
{
	// “矩阵A与B的乘积矩阵C的第i行第j列的元素c(ij)等于A的第i行于B的第j列的对应元素乘积的和。”（实用数学手册，科学出版社，第二版）
	Matrix3x3 result;
	result.e[E11] = e[E11]*m.e[E11] + e[E12]*m.e[E21] + e[E13]*m.e[E31];
	result.e[E12] = e[E11]*m.e[E12] + e[E12]*m.e[E22] + e[E13]*m.e[E32];
	result.e[E13] = e[E11]*m.e[E13] + e[E12]*m.e[E23] + e[E13]*m.e[E33];

	result.e[E21] = e[E21]*m.e[E11] + e[E22]*m.e[E21] + e[E23]*m.e[E31];
	result.e[E22] = e[E21]*m.e[E12] + e[E22]*m.e[E22] + e[E23]*m.e[E32];
	result.e[E23] = e[E21]*m.e[E13] + e[E22]*m.e[E23] + e[E23]*m.e[E33];

	result.e[E31] = e[E31]*m.e[E11] + e[E32]*m.e[E21] + e[E33]*m.e[E31];
	result.e[E32] = e[E31]*m.e[E12] + e[E32]*m.e[E22] + e[E33]*m.e[E32];
	result.e[E33] = e[E31]*m.e[E13] + e[E32]*m.e[E23] + e[E33]*m.e[E33];

	(*this) = result;
	return (*this);
}

Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& m)
{
	e[E11] += m.e[E11]; e[E12] += m.e[E12]; e[E13] += m.e[E13];
	e[E21] += m.e[E21]; e[E22] += m.e[E22]; e[E23] += m.e[E23];
	e[E31] += m.e[E31]; e[E32] += m.e[E32]; e[E33] += m.e[E33];
	return (*this);
}

Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& m)
{
	e[E11] -= m.e[E11]; e[E12] -= m.e[E12]; e[E13] -= m.e[E13];
	e[E21] -= m.e[E21]; e[E22] -= m.e[E22]; e[E23] -= m.e[E23];
	e[E31] -= m.e[E31]; e[E32] -= m.e[E32]; e[E33] -= m.e[E33];
	return (*this);
}

Matrix3x3 operator*(const Matrix3x3& m1, const Matrix3x3& m2)
{
	Matrix3x3 result;

	result.e[Matrix3x3::E11] = m1.e[Matrix3x3::E11]*m2.e[Matrix3x3::E11] + m1.e[Matrix3x3::E12]*m2.e[Matrix3x3::E21] + m1.e[Matrix3x3::E13]*m2.e[Matrix3x3::E31];
	result.e[Matrix3x3::E12] = m1.e[Matrix3x3::E11]*m2.e[Matrix3x3::E12] + m1.e[Matrix3x3::E12]*m2.e[Matrix3x3::E22] + m1.e[Matrix3x3::E13]*m2.e[Matrix3x3::E32];
	result.e[Matrix3x3::E13] = m1.e[Matrix3x3::E11]*m2.e[Matrix3x3::E13] + m1.e[Matrix3x3::E12]*m2.e[Matrix3x3::E23] + m1.e[Matrix3x3::E13]*m2.e[Matrix3x3::E33];

	result.e[Matrix3x3::E21] = m1.e[Matrix3x3::E21]*m2.e[Matrix3x3::E11] + m1.e[Matrix3x3::E22]*m2.e[Matrix3x3::E21] + m1.e[Matrix3x3::E23]*m2.e[Matrix3x3::E31];
	result.e[Matrix3x3::E22] = m1.e[Matrix3x3::E21]*m2.e[Matrix3x3::E12] + m1.e[Matrix3x3::E22]*m2.e[Matrix3x3::E22] + m1.e[Matrix3x3::E23]*m2.e[Matrix3x3::E32];
	result.e[Matrix3x3::E23] = m1.e[Matrix3x3::E21]*m2.e[Matrix3x3::E13] + m1.e[Matrix3x3::E22]*m2.e[Matrix3x3::E23] + m1.e[Matrix3x3::E23]*m2.e[Matrix3x3::E33];

	result.e[Matrix3x3::E31] = m1.e[Matrix3x3::E31]*m2.e[Matrix3x3::E11] + m1.e[Matrix3x3::E32]*m2.e[Matrix3x3::E21] + m1.e[Matrix3x3::E33]*m2.e[Matrix3x3::E31];
	result.e[Matrix3x3::E32] = m1.e[Matrix3x3::E31]*m2.e[Matrix3x3::E12] + m1.e[Matrix3x3::E32]*m2.e[Matrix3x3::E22] + m1.e[Matrix3x3::E33]*m2.e[Matrix3x3::E32];
	result.e[Matrix3x3::E33] = m1.e[Matrix3x3::E31]*m2.e[Matrix3x3::E13] + m1.e[Matrix3x3::E32]*m2.e[Matrix3x3::E23] + m1.e[Matrix3x3::E33]*m2.e[Matrix3x3::E33];
	
	return result;
}

Matrix3x3 operator+(const Matrix3x3& m1, const Matrix3x3& m2)
{
	Matrix3x3 result;
	result.e[Matrix3x3::E11] = m1.e[Matrix3x3::E11] + m2.e[Matrix3x3::E11]; 
	result.e[Matrix3x3::E12] = m1.e[Matrix3x3::E12] + m2.e[Matrix3x3::E12]; 
	result.e[Matrix3x3::E13] = m1.e[Matrix3x3::E13] + m2.e[Matrix3x3::E13]; 

	result.e[Matrix3x3::E21] = m1.e[Matrix3x3::E21] + m2.e[Matrix3x3::E21]; 
	result.e[Matrix3x3::E22] = m1.e[Matrix3x3::E22] + m2.e[Matrix3x3::E22]; 
	result.e[Matrix3x3::E23] = m1.e[Matrix3x3::E23] + m2.e[Matrix3x3::E23]; 

	result.e[Matrix3x3::E31] = m1.e[Matrix3x3::E31] + m2.e[Matrix3x3::E31]; 
	result.e[Matrix3x3::E32] = m1.e[Matrix3x3::E32] + m2.e[Matrix3x3::E32]; 
	result.e[Matrix3x3::E33] = m1.e[Matrix3x3::E33] + m2.e[Matrix3x3::E33]; 

	return result;
}

Matrix3x3 operator-(const Matrix3x3& m1, const Matrix3x3& m2)
{
	Matrix3x3 result;
	result.e[Matrix3x3::E11] = m1.e[Matrix3x3::E11] - m2.e[Matrix3x3::E11]; 
	result.e[Matrix3x3::E12] = m1.e[Matrix3x3::E12] - m2.e[Matrix3x3::E12]; 
	result.e[Matrix3x3::E13] = m1.e[Matrix3x3::E13] - m2.e[Matrix3x3::E13]; 

	result.e[Matrix3x3::E21] = m1.e[Matrix3x3::E21] - m2.e[Matrix3x3::E21]; 
	result.e[Matrix3x3::E22] = m1.e[Matrix3x3::E22] - m2.e[Matrix3x3::E22]; 
	result.e[Matrix3x3::E23] = m1.e[Matrix3x3::E23] - m2.e[Matrix3x3::E23]; 

	result.e[Matrix3x3::E31] = m1.e[Matrix3x3::E31] - m2.e[Matrix3x3::E31]; 
	result.e[Matrix3x3::E32] = m1.e[Matrix3x3::E32] - m2.e[Matrix3x3::E32]; 
	result.e[Matrix3x3::E33] = m1.e[Matrix3x3::E33] - m2.e[Matrix3x3::E33]; 

	return result;
}

Vector3 operator*(const Matrix3x3& m, const Vector3& v)
{
	Vector3 result;

	result.x = m.e[Matrix3x3::E11]* v.x + m.e[Matrix3x3::E12]* v.y + m.e[Matrix3x3::E13]*v.z;
	result.y = m.e[Matrix3x3::E21]* v.x + m.e[Matrix3x3::E22]* v.y + m.e[Matrix3x3::E23]*v.z;
	result.z = m.e[Matrix3x3::E31]* v.x + m.e[Matrix3x3::E32]* v.y + m.e[Matrix3x3::E33]*v.z;

	return result;
}
