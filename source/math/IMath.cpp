/*!
 * \file IMath.cpp
 * \date 7-25-2011 12:46:55
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <math/IMath.h>

const Vector3 IMath::VEC3_ZERO(0.0f, 0.0f, 0.0f);

const Vector3 IMath::VEC3_ONE(1.0f, 1.0f, 1.0f);

const Matrix4x4 IMath::MAT4X4_ZERO(0.0f, 0.0f, 0.0f, 0.0f,
                                   0.0f, 0.0f, 0.0f, 0.0f, 
                                   0.0f, 0.0f, 0.0f, 0.0f, 
                                   0.0f, 0.0f, 0.0f, 0.0f);

const Matrix4x4 IMath::MAT4X4_IDENTITY(1.0f, 0.0f, 0.0f, 0.0f,
                                       0.0f, 1.0f, 0.0f, 0.0f, 
                                       0.0f, 0.0f, 1.0f, 0.0f, 
                                       0.0f, 0.0f, 0.0f, 1.0f);

const Quaternion IMath::ROT_ZERO(0.0f, 0.0f, 0.0f, 0.0f);
