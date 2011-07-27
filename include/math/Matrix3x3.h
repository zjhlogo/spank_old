#ifndef _MATRIX3X3_H_
#define _MATRIX3X3_H_
#include <math/Vector3.h>

class Matirx3x3
{
public:
	// open gl matrix elements order
	enum OGL_ELEMENT_ORDER
	{
		E11 = 0, E12 = 3, E13 = 6,
		E21 = 1, E22 = 4, E23 = 7,  
		E31 = 2, E32 = 5, E33 = 8
	};
	Matirx3x3();
	~Matirx3x3();

	void MakeIdentity();
	void MakeZero();

	void MakeRotateZ(float radian);
	void MakeRotateX(float radian);
	void MakeRotateY(float radian);
	void MakeScale(float x, float y, float z);
	
	Matirx3x3& operator *=(const Matirx3x3& mat);
	const float* GetAddress() const;
	float Matirx3x3Det();

public:
	float e[9];
};

Matirx3x3 operator* (const Matirx3x3& m1, const Matirx3x3& m2);
Vector3   operator* (const Matirx3x3& mat, const Vector3& vec);
#endif//_MATRIX3X3_H_