/*!
 * \file Matrix4x4.cpp
 * \date 7-25-2011 12:02:26
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <math/Matrix4x4.h>

Matrix4x4::Matrix4x4()
{
	// TODO: 
}

Matrix4x4::~Matrix4x4()
{
	// TODO: 
}

void Matrix4x4::MakeIdentity()
{
	e[E11] = 1.0f; e[E12] = 0.0f; e[E13] = 0.0f; e[E14] = 0.0f;
	e[E21] = 0.0f; e[E22] = 1.0f; e[E23] = 0.0f; e[E24] = 0.0f;
	e[E31] = 0.0f; e[E32] = 0.0f; e[E33] = 1.0f; e[E34] = 0.0f;
	e[E41] = 0.0f; e[E42] = 0.0f; e[E43] = 0.0f; e[E44] = 1.0f;
}

void Matrix4x4::MakeZero()
{
	e[E11] = 0.0f; e[E12] = 0.0f; e[E13] = 0.0f; e[E14] = 0.0f;
	e[E21] = 0.0f; e[E22] = 0.0f; e[E23] = 0.0f; e[E24] = 0.0f;
	e[E31] = 0.0f; e[E32] = 0.0f; e[E33] = 0.0f; e[E34] = 0.0f;
	e[E41] = 0.0f; e[E42] = 0.0f; e[E43] = 0.0f; e[E44] = 0.0f;
}

void Matrix4x4::MakeOrtho(float left, float right, float bottom, float top, float near, float far)
{
	// 
	// [  2/(right-left)              0                           0                      0 ]
	// [  0                           2/(top-bottom)              0                      0 ]
	// [  0                           0                          -2/(far-near)           0 ]
	// [ -(right+left)/(right-left)  -(top+bottom)/(top-bottom)  -(far+near)/(far-near)  1 ]
	// 

	e[E11] = 2.0f/(right - left);
	e[E12] = 0.0f;
	e[E13] = 0.0f;
	e[E14] = 0.0f;

	e[E21] = 0.0f;
	e[E22] = 2.0f/(top - bottom);
	e[E23] = 0.0f;
	e[E24] = 0.0f;

	e[E31] = 0.0f;
	e[E32] = 0.0f;
	e[E33] = -2.0f/(far - near);
	e[E34] = 0.0f;

	e[E41] = -(right + left)/(right - left);
	e[E42] = -(top + bottom)/(top - bottom);
	e[E43] = -(far + near)/(far - near);
	e[E44] = 1.0f;
}

void Matrix4x4::MakeFrustum(float left, float right, float bottom, float top, float near, float far)
{
	// 
	// [ 2*near/(right-left)        0                           0                       0 ]
	// [ 0                          2*near/(top-bottom)         0                       0 ]
	// [ (right+left)/(right-left)  (top+bottom)/(top-bottom)  -(far+near)/(far-near)  -1 ]
	// [ 0                          0                          -2*far*near/(far-near)   0 ]
	// 
	e[E11] = 2.0f*near/(right - left);
	e[E12] = 0.0f;
	e[E13] = 0.0f;
	e[E14] = 0.0f;

	e[E21] = 0.0f;
	e[E22] = 2.0f*near/(top - bottom);
	e[E23] = 0.0f;
	e[E24] = 0.0f;

	e[E31] = (right+left)/(right-left);
	e[E32] = (top+bottom)/(top-bottom);
	e[E33] = -(far+near)/(far-near);
	e[E34] = -1.0f;

	e[E41] = 0.0f;
	e[E42] = 0.0f;
	e[E43] = -2*far*near/(far-near);
	e[E44] = 0.0f;
}

Matrix4x4& Matrix4x4::operator *=(const Matrix4x4& m)
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

	(*this = result);
	return (*this);
}

const float* Matrix4x4::GetAddress() const
{
	return e;
}
