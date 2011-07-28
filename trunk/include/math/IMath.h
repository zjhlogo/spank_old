/*!
 * \file IMath.h
 * \date 7-25-2011 12:46:46
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IMATH_H__
#define __IMATH_H__

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Quaternion.h"

class IMath
{
public:
	// TODO: 

public:
	static const Vector3 VEC3_ZERO;
	static const Matrix4x4 MAT4X4_ZERO;
	static const Matrix4x4 MAT4X4_IDENTITY;
	static const Quaternion ROT_ZERO;

};
#endif // __IMATH_H__
