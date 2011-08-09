/*!
 * \file IMath.cpp
 * \date 7-25-2011 12:46:55
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <math/IMath.h>
#include <math.h>

const float IMath::FLOAT_MIN = 0.000001f;

const Vector2 IMath::VEC2_ZERO(0.0f, 0.0f);
const Vector3 IMath::VEC3_ZERO(0.0f, 0.0f, 0.0f);
const Vector4 IMath::VEC4_ZERO(0.0f, 0.0f, 0.0f, 0.0f);
const Vector2 IMath::VEC2_ONE(1.0f, 1.0f);
const Vector3 IMath::VEC3_ONE(1.0f, 1.0f, 1.0f);
const Vector4 IMath::VEC4_ONE(1.0f, 1.0f, 1.0f, 1.0f);

static const Matrix4x4 MAT4X4_ZERO;
static const Matrix2x2 MAT2X2_IDENTITY;
static const Matrix3x3 MAT3X3_IDENTITY;
static const Matrix4x4 MAT4X4_IDENTITY;

const Matrix2x2 IMath::MAT2X2_ZERO(0.0f, 0.0f, 
								   0.0f, 0.0f);
const Matrix3x3 IMath::MAT3X3_ZERO(0.0f, 0.0f, 0.0f, 
								   0.0f, 0.0f, 0.0f, 
								   0.0f, 0.0f, 0.0f);
const Matrix4x4 IMath::MAT4X4_ZERO(0.0f, 0.0f, 0.0f, 0.0f,
                                   0.0f, 0.0f, 0.0f, 0.0f,
                                   0.0f, 0.0f, 0.0f, 0.0f,
                                   0.0f, 0.0f, 0.0f, 0.0f);
const Matrix2x2 IMath::MAT2X2_IDENTITY(1.0f, 0.0f, 
									   0.0f, 1.0f);
const Matrix3x3 IMath::MAT3X3_IDENTITY(1.0f, 0.0f, 0.0f, 
									   0.0f, 1.0f, 0.0f, 
									   0.0f, 0.0f, 1.0f);
const Matrix4x4 IMath::MAT4X4_IDENTITY(1.0f, 0.0f, 0.0f, 0.0f,
                                       0.0f, 1.0f, 0.0f, 0.0f,
                                       0.0f, 0.0f, 1.0f, 0.0f,
                                       0.0f, 0.0f, 0.0f, 1.0f);

const Quaternion IMath::ROT_ZERO(0.0f, 0.0f, 0.0f, 0.0f);

void IMath::BuildZeroMatrix(Matrix2x2& matOut)
{
	//
	// [ 0   0 ]
	// [ 0   0 ]
	//
	matOut.e[Matrix2x2::E11] = 0.0f; matOut.e[Matrix2x2::E12] = 0.0f;
	matOut.e[Matrix2x2::E21] = 0.0f; matOut.e[Matrix2x2::E22] = 0.0f;
}

void IMath::BuildZeroMatrix(Matrix3x3& matOut)
{
	//
	// [ 0   0   0 ]
	// [ 0   0   0 ]
	// [ 0   0   0 ]
	//
	matOut.e[Matrix3x3::E11] = 0.0f; matOut.e[Matrix3x3::E12] = 0.0f; matOut.e[Matrix3x3::E13] = 0.0f;
	matOut.e[Matrix3x3::E21] = 0.0f; matOut.e[Matrix3x3::E22] = 0.0f; matOut.e[Matrix3x3::E23] = 0.0f;
	matOut.e[Matrix3x3::E31] = 0.0f; matOut.e[Matrix3x3::E32] = 0.0f; matOut.e[Matrix3x3::E33] = 0.0f;
}

void IMath::BuildZeroMatrix(Matrix4x4& matOut)
{
	//
	// [ 0   0   0   0 ]
	// [ 0   0   0   0 ]
	// [ 0   0   0   0 ]
	// [ 0   0   0   0 ]
	//
	matOut.e[Matrix4x4::E11] = 0.0f; matOut.e[Matrix4x4::E12] = 0.0f; matOut.e[Matrix4x4::E13] = 0.0f; matOut.e[Matrix4x4::E14] = 0.0f;
	matOut.e[Matrix4x4::E21] = 0.0f; matOut.e[Matrix4x4::E22] = 0.0f; matOut.e[Matrix4x4::E23] = 0.0f; matOut.e[Matrix4x4::E24] = 0.0f;
	matOut.e[Matrix4x4::E31] = 0.0f; matOut.e[Matrix4x4::E32] = 0.0f; matOut.e[Matrix4x4::E33] = 0.0f; matOut.e[Matrix4x4::E34] = 0.0f;
	matOut.e[Matrix4x4::E41] = 0.0f; matOut.e[Matrix4x4::E42] = 0.0f; matOut.e[Matrix4x4::E43] = 0.0f; matOut.e[Matrix4x4::E44] = 0.0f;
}

void IMath::BuildIdentityMatrix(Matrix2x2& matOut)
{
	//
	// [ 1   0 ]
	// [ 0   1 ]
	//
	matOut.e[Matrix2x2::E11] = 1.0f; matOut.e[Matrix2x2::E12] = 0.0f;
	matOut.e[Matrix2x2::E21] = 0.0f; matOut.e[Matrix2x2::E22] = 1.0f;
}

void IMath::BuildIdentityMatrix(Matrix3x3& matOut)
{
	//
	// [ 1   0   0 ]
	// [ 0   1   0 ]
	// [ 0   0   1 ]
	//
	matOut.e[Matrix3x3::E11] = 1.0f; matOut.e[Matrix3x3::E12] = 0.0f; matOut.e[Matrix3x3::E13] = 0.0f;
	matOut.e[Matrix3x3::E21] = 0.0f; matOut.e[Matrix3x3::E22] = 1.0f; matOut.e[Matrix3x3::E23] = 0.0f;
	matOut.e[Matrix3x3::E31] = 0.0f; matOut.e[Matrix3x3::E32] = 0.0f; matOut.e[Matrix3x3::E33] = 1.0f;
}

void IMath::BuildIdentityMatrix(Matrix4x4& matOut)
{
	//
	// [ 1   0   0   0 ]
	// [ 0   1   0   0 ]
	// [ 0   0   1   0 ]
	// [ 0   0   0   1 ]
	//
	matOut.e[Matrix4x4::E11] = 1.0f; matOut.e[Matrix4x4::E12] = 0.0f; matOut.e[Matrix4x4::E13] = 0.0f; matOut.e[Matrix4x4::E14] = 0.0f;
	matOut.e[Matrix4x4::E21] = 0.0f; matOut.e[Matrix4x4::E22] = 1.0f; matOut.e[Matrix4x4::E23] = 0.0f; matOut.e[Matrix4x4::E24] = 0.0f;
	matOut.e[Matrix4x4::E31] = 0.0f; matOut.e[Matrix4x4::E32] = 0.0f; matOut.e[Matrix4x4::E33] = 1.0f; matOut.e[Matrix4x4::E34] = 0.0f;
	matOut.e[Matrix4x4::E41] = 0.0f; matOut.e[Matrix4x4::E42] = 0.0f; matOut.e[Matrix4x4::E43] = 0.0f; matOut.e[Matrix4x4::E44] = 1.0f;
}

void IMath::BuildTranslateMatrix(Matrix4x4& matOut, const Vector3& v)
{
	//
	// [ 0  0  0  x ]
	// [ 0  0  0  y ]
	// [ 0  0  0  z ]
	// [ 0  0  0  1 ]
	//
	matOut.e[Matrix4x4::E11] = 0.0f; matOut.e[Matrix4x4::E12] = 0.0f; matOut.e[Matrix4x4::E13] = 0.0f; matOut.e[Matrix4x4::E14] = v.x;
	matOut.e[Matrix4x4::E21] = 0.0f; matOut.e[Matrix4x4::E22] = 0.0f; matOut.e[Matrix4x4::E23] = 0.0f; matOut.e[Matrix4x4::E24] = v.y;
	matOut.e[Matrix4x4::E31] = 0.0f; matOut.e[Matrix4x4::E32] = 0.0f; matOut.e[Matrix4x4::E33] = 0.0f; matOut.e[Matrix4x4::E34] = v.z;
	matOut.e[Matrix4x4::E41] = 0.0f; matOut.e[Matrix4x4::E42] = 0.0f; matOut.e[Matrix4x4::E43] = 0.0f; matOut.e[Matrix4x4::E44] = 1.0f;
}

void IMath::BuildRotateMatrixX(Matrix3x3& matOut, float fRadian)
{
	//
	// [ 1     0        0    ]
	// [ 0   cos(r)  -sin(r) ]
	// [ 0   sin(r)   cos(r) ]
	//
	float cr = cosf(fRadian);
	float sr = sinf(fRadian);

	matOut.e[Matrix3x3::E11] = 1.0f; matOut.e[Matrix3x3::E12] = 0.0f; matOut.e[Matrix3x3::E13] = 0.0f;
	matOut.e[Matrix3x3::E21] = 0.0f; matOut.e[Matrix3x3::E22] = cr;   matOut.e[Matrix3x3::E23] =-sr;
	matOut.e[Matrix3x3::E31] = 0.0f; matOut.e[Matrix3x3::E32] = sr;   matOut.e[Matrix3x3::E33] = cr;
}

void IMath::BuildRotateMatrixX(Matrix4x4& matOut, float fRadian)
{
	//
	// [ 1     0        0     0 ]
	// [ 0   cos(r)  -sin(r)  0 ]
	// [ 0   sin(r)   cos(r)  0 ]
	// [ 0     0        0     1 ]
	//
	float cr = cosf(fRadian);
	float sr = sinf(fRadian);

	matOut.e[Matrix4x4::E11] = 1.0f; matOut.e[Matrix4x4::E12] = 0.0f; matOut.e[Matrix4x4::E13] = 0.0f; matOut.e[Matrix4x4::E14] = 0.0f;
	matOut.e[Matrix4x4::E21] = 0.0f; matOut.e[Matrix4x4::E22] = cr;   matOut.e[Matrix4x4::E23] =-sr;   matOut.e[Matrix4x4::E24] = 0.0f;
	matOut.e[Matrix4x4::E31] = 0.0f; matOut.e[Matrix4x4::E32] = sr;   matOut.e[Matrix4x4::E33] = cr;   matOut.e[Matrix4x4::E34] = 0.0f;
	matOut.e[Matrix4x4::E41] = 0.0f; matOut.e[Matrix4x4::E42] = 0.0f; matOut.e[Matrix4x4::E43] = 0.0f; matOut.e[Matrix4x4::E44] = 1.0f;
}

void IMath::BuildRotateMatrixY(Matrix3x3& matOut, float fRadian)
{
	//
	// [  cos(r)   0   sin(r) ]
	// [    0      1     0    ]
	// [ -sin(r)   0   cos(r) ]
	//
	float cr = cosf(fRadian);
	float sr = cosf(fRadian);

	matOut.e[Matrix3x3::E11] = cr;   matOut.e[Matrix3x3::E12] = 0.0f; matOut.e[Matrix3x3::E13] = sr;
	matOut.e[Matrix3x3::E21] = 0.0f; matOut.e[Matrix3x3::E22] = 1.0f; matOut.e[Matrix3x3::E23] = 0.0f;
	matOut.e[Matrix3x3::E31] =-sr;   matOut.e[Matrix3x3::E32] = 0.0f; matOut.e[Matrix3x3::E33] = cr;
}

void IMath::BuildRotateMatrixY(Matrix4x4& matOut, float fRadian)
{
	//
	//[  cos(r)  0  sin(r)   0 ]
	//[    0     1    0      0 ]
	//[ -sin(r)  0  cos(r)   0 ]
	//[    0     0    0      1 ]
	//
	float cr = cosf(fRadian);
	float sr = sinf(fRadian);

	matOut.e[Matrix4x4::E11] = cr;   matOut.e[Matrix4x4::E12] = 0.0f; matOut.e[Matrix4x4::E13] = sr;   matOut.e[Matrix4x4::E14] = 0.0f;
	matOut.e[Matrix4x4::E21] = 0.0f; matOut.e[Matrix4x4::E22] = 1.0f; matOut.e[Matrix4x4::E23] = 0.0f; matOut.e[Matrix4x4::E24] = 0.0f;
	matOut.e[Matrix4x4::E31] =-sr;   matOut.e[Matrix4x4::E32] = 0.0f; matOut.e[Matrix4x4::E33] = cr;   matOut.e[Matrix4x4::E34] = 0.0f;
	matOut.e[Matrix4x4::E41] = 0.0f; matOut.e[Matrix4x4::E42] = 0.0f; matOut.e[Matrix4x4::E43] = 0.0f; matOut.e[Matrix4x4::E44] = 1.0f;
}

void IMath::BuildRotateMatrixZ(Matrix3x3& matOut, float fRadian)
{
	//
	// [ cos(r)  -sin(r)  0 ]
	// [ sin(r)   cos(r)  0 ]
	// [   0        0     1 ]
	//
	float cr = cosf(fRadian);
	float sr = sinf(fRadian);

	matOut.e[Matrix3x3::E11] = cr;   matOut.e[Matrix3x3::E12] =-sr;   matOut.e[Matrix3x3::E13] = 0.0f;
	matOut.e[Matrix3x3::E21] = sr;   matOut.e[Matrix3x3::E22] = cr;   matOut.e[Matrix3x3::E23] = 0.0f;
	matOut.e[Matrix3x3::E31] = 0.0f; matOut.e[Matrix3x3::E32] = 0.0f; matOut.e[Matrix3x3::E33] = 1.0f;
}

void IMath::BuildRotateMatrixZ(Matrix4x4& matOut, float fRadian)
{
	// 
	// [ cos(r)  -sin(r)  0  0 ]
	// [ sin(r)   cos(r)  0  0 ]
	// [   0        0     1  0 ]
	// [   0        0     0  1 ]
	// 
	float cr = cosf(fRadian);
	float sr = sinf(fRadian);

	matOut.e[Matrix4x4::E11] = cr;   matOut.e[Matrix4x4::E12] =-sr;   matOut.e[Matrix4x4::E13] = 0.0f; matOut.e[Matrix4x4::E14] = 0.0f;
	matOut.e[Matrix4x4::E21] = sr;   matOut.e[Matrix4x4::E22] = cr;   matOut.e[Matrix4x4::E23] = 0.0f; matOut.e[Matrix4x4::E24] = 0.0f;
	matOut.e[Matrix4x4::E31] = 0.0f; matOut.e[Matrix4x4::E32] = 0.0f; matOut.e[Matrix4x4::E33] = 1.0f; matOut.e[Matrix4x4::E34] = 0.0f;
	matOut.e[Matrix4x4::E41] = 0.0f; matOut.e[Matrix4x4::E42] = 0.0f; matOut.e[Matrix4x4::E43] = 0.0f; matOut.e[Matrix4x4::E44] = 1.0f;
}

void IMath::BuildRotateMatrix(Matrix3x3& matOut, const Vector3& vx, const Vector3& vy, const Vector3& vz)
{
	//
	// [ vx.x  vy.x  vz.x ]
	// [ vx.y  vy.y  vz.y ]
	// [ vx.z  vy.z  vz.z ]
	//
	matOut.e[Matrix3x3::E11] = vx.x; matOut.e[Matrix3x3::E12] = vy.x; matOut.e[Matrix3x3::E13] = vz.x;
	matOut.e[Matrix3x3::E21] = vx.y; matOut.e[Matrix3x3::E22] = vy.y; matOut.e[Matrix3x3::E23] = vz.y;
	matOut.e[Matrix3x3::E31] = vx.z; matOut.e[Matrix3x3::E32] = vy.z; matOut.e[Matrix3x3::E33] = vz.z;
}

void IMath::BuildRotateMatrix(Matrix4x4& matOut, const Vector3& vx, const Vector3& vy, const Vector3& vz)
{
	//
	// [ vx.x  vy.x  vz.x  0 ]
	// [ vx.y  vy.y  vz.y  0 ]
	// [ vx.z  vy.z  vz.z  0 ]
	// [  0     0     0    1 ]
	//
	matOut.e[Matrix4x4::E11] = vx.x; matOut.e[Matrix4x4::E12] = vy.x; matOut.e[Matrix4x4::E13] = vz.x; matOut.e[Matrix4x4::E14] = 0.0f;
	matOut.e[Matrix4x4::E21] = vx.y; matOut.e[Matrix4x4::E22] = vy.y; matOut.e[Matrix4x4::E23] = vz.y; matOut.e[Matrix4x4::E24] = 0.0f;
	matOut.e[Matrix4x4::E31] = vx.z; matOut.e[Matrix4x4::E32] = vy.z; matOut.e[Matrix4x4::E33] = vz.z; matOut.e[Matrix4x4::E34] = 0.0f;
	matOut.e[Matrix4x4::E41] = 0.0f; matOut.e[Matrix4x4::E42] = 0.0f; matOut.e[Matrix4x4::E43] = 0.0f; matOut.e[Matrix4x4::E44] = 1.0f;
}

void IMath::BuildOrthoMatrix(Matrix4x4& matOut, float left, float right, float bottom, float top, float near, float far)
{
	// 
	// [        2/(right-left)                    0                         0            0 ]
	// [              0                    2/(top-bottom)                   0            0 ]
	// [              0                           0                  -2/(far-near)       0 ]
	// [ -(right+left)/(right-left)  -(top+bottom)/(top-bottom)  -(far+near)/(far-near)  1 ]
	// 
	matOut.e[Matrix4x4::E11] = 2.0f/(right - left);
	matOut.e[Matrix4x4::E12] = 0.0f;
	matOut.e[Matrix4x4::E13] = 0.0f;
	matOut.e[Matrix4x4::E14] = 0.0f;

	matOut.e[Matrix4x4::E21] = 0.0f;
	matOut.e[Matrix4x4::E22] = 2.0f/(top - bottom);
	matOut.e[Matrix4x4::E23] = 0.0f;
	matOut.e[Matrix4x4::E24] = 0.0f;

	matOut.e[Matrix4x4::E31] = 0.0f;
	matOut.e[Matrix4x4::E32] = 0.0f;
	matOut.e[Matrix4x4::E33] = -2.0f/(far - near);
	matOut.e[Matrix4x4::E34] = 0.0f;

	matOut.e[Matrix4x4::E41] = -(right + left)/(right - left);
	matOut.e[Matrix4x4::E42] = -(top + bottom)/(top - bottom);
	matOut.e[Matrix4x4::E43] = -(far + near)/(far - near);
	matOut.e[Matrix4x4::E44] = 1.0f;
}

void IMath::BuildFrustumMatrix(Matrix4x4& matOut, float left, float right, float bottom, float top, float near, float far)
{
	// 
	// [    2*near/(right-left)                0                         0              0 ]
	// [           0                   2*near/(top-bottom)               0              0 ]
	// [ (right+left)/(right-left)  (top+bottom)/(top-bottom)  -(far+near)/(far-near)  -1 ]
	// [           0                           0               -2*far*near/(far-near)   0 ]
	// 
	matOut.e[Matrix4x4::E11] = 2.0f*near/(right - left);
	matOut.e[Matrix4x4::E12] = 0.0f;
	matOut.e[Matrix4x4::E13] = 0.0f;
	matOut.e[Matrix4x4::E14] = 0.0f;

	matOut.e[Matrix4x4::E21] = 0.0f;
	matOut.e[Matrix4x4::E22] = 2.0f*near/(top - bottom);
	matOut.e[Matrix4x4::E23] = 0.0f;
	matOut.e[Matrix4x4::E24] = 0.0f;

	matOut.e[Matrix4x4::E31] = (right+left)/(right-left);
	matOut.e[Matrix4x4::E32] = (top+bottom)/(top-bottom);
	matOut.e[Matrix4x4::E33] = -(far+near)/(far-near);
	matOut.e[Matrix4x4::E34] = -1.0f;

	matOut.e[Matrix4x4::E41] = 0.0f;
	matOut.e[Matrix4x4::E42] = 0.0f;
	matOut.e[Matrix4x4::E43] = -2*far*near/(far-near);
	matOut.e[Matrix4x4::E44] = 0.0f;
}
