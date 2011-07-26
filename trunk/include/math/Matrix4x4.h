/*!
 * \file Matrix4x4.h
 * \date 7-25-2011 11:31:39
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __MATRIX4X4_H__
#define __MATRIX4X4_H__

class Matrix4x4
{
public:
	// open gl matrix elements order
	enum OGL_ELEMENT_ORDER
	{
		E11 = 0, E12 = 4, E13 = 8,  E14 = 12,
		E21 = 1, E22 = 5, E23 = 9,  E24 = 13,
		E31 = 2, E32 = 6, E33 = 10, E34 = 14,
		E41 = 3, E42 = 7, E43 = 11, E44 = 15,
	};

	Matrix4x4();
	~Matrix4x4();

	void MakeIdentity();
	void MakeZero();

	void MakeOrtho(float left, float right, float bottom, float top, float near, float far);
	void MakeFrustum(float left, float right, float bottom, float top, float near, float far);

	Matrix4x4& operator*=(const Matrix4x4& mat);

	const float* GetAddress() const;

public:
	float e[16];

};
#endif // __MATRIX4X4_H__
