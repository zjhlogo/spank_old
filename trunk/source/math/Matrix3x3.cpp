#include <math/Matrix3x3.h>
#include <math.h>

Matirx3x3::Matirx3x3()
{
	//TODO:
}

Matirx3x3::~Matirx3x3()
{
	//TODO:
}

void Matirx3x3::MakeIdentity()
{
	e[E11] = 1.0f; e[E12] = 0.0f; e[E13] = 0.0f;
	e[E21] = 0.0f; e[E22] = 1.0f; e[E23] = 0.0f;
	e[E31] = 0.0f; e[E32] = 0.0f; e[E33] = 1.0f;
}

void Matirx3x3::MakeZero()
{
	e[E11] = 0.0f; e[E12] = 0.0f; e[E13] = 0.0f;
	e[E21] = 0.0f; e[E22] = 0.0f; e[E23] = 0.0f;
	e[E31] = 0.0f; e[E32] = 0.0f; e[E33] = 0.0f;
}

void Matirx3x3::MakeRotateZ(float radian)
{	
	//
	//[cos(r)  -sin(r)  0]
	//[sin(r)   cos(r)  0]
	//[  0	 	  0	  	1]
	//
	float cr = cosf(radian);
	float sr = sinf(radian);
	
	e[E11] = cr;	e[E12] =-sr;	e[E13] = 0.0f;
	e[E21] = sr;	e[E22] = cr;	e[E23] = 0.0f;
	e[E31] = 0.0f;	e[E32] = 0.0f;	e[E33] = 1.0f;

}

void Matirx3x3::MakeRotateY(float radian)
{
	//
	//[cos(r)	0  sin(r)]
	//[  0		1	0	 ]
	//[-sin(r)	0  cos(r)]
	//

	float cr = cosf(radian);
	float sr = cosf(radian);

	e[E11] = cr;	e[E12] = 0.0f; e[E13] = sr;
	e[E21] = 0.0f;	e[E22] = 1.0f; e[E23] = 0.0f;
	e[E31] =-sr;	e[E32] = 0.0f; e[E33] = cr;
}

void Matirx3x3::MakeRotateX(float radian)
{
	//
	//[1	0		    0  ]
	//[0	cos(r)	-sin(r)]
	//[0	sin(r)	cos(r) ]
	//

	float cr = cosf(radian);
	float sr = sinf(radian);

	e[E11] = 1.0f; e[E12] = 0.0f; e[E13] = 0.0f;
	e[E21] = 0.0f; e[E22] = cr;   e[E23] =-sr;
	e[E31] = 0.0f; e[E32] = sr;	  e[E33] = cr;
}

void Matirx3x3::MakeScale(float x, float y, float z)
{
	e[E11] = x;	e[E12] = 0;	e[E13] = 0;
	e[E21] = 0; e[E22] = y; e[E23] = 0;
	e[E31] = 0; e[E32] = 0; e[E33] = z;
}

Matirx3x3& Matirx3x3::operator*=(const Matirx3x3& mat)
{
	// “矩阵A与B的乘积矩阵C的第i行第j列的元素c(ij)等于A的第i行于B的第j列的对应元素乘积的和。”（实用数学手册，科学出版社，第二版）
	Matirx3x3 result;
	result.e[E11] = e[E11]*mat.e[E11] + e[E12]*mat.e[E21] + e[E13]*mat.e[E31];
	result.e[E12] = e[E11]*mat.e[E12] + e[E12]*mat.e[E22] + e[E13]*mat.e[E32];
	result.e[E13] = e[E11]*mat.e[E13] + e[E12]*mat.e[E23] + e[E13]*mat.e[E33];

	result.e[E21] = e[E21]*mat.e[E11] + e[E22]*mat.e[E21] + e[E23]*mat.e[E31];
	result.e[E22] = e[E21]*mat.e[E12] +	e[E22]*mat.e[E22] + e[E23]*mat.e[E32];
	result.e[E23] = e[E21]*mat.e[E13] + e[E22]*mat.e[E23] + e[E23]*mat.e[E33];

	result.e[E31] = e[E31]*mat.e[E11] + e[E32]*mat.e[E21] + e[E33]*mat.e[E31];
	result.e[E32] = e[E31]*mat.e[E12] + e[E32]*mat.e[E22] + e[E33]*mat.e[E32];
	result.e[E33] = e[E31]*mat.e[E13] + e[E32]*mat.e[E23] + e[E33]*mat.e[E33];

	(*this) = result;
	return (*this);
}

Matirx3x3& Matirx3x3::operator+=(const Matirx3x3& mat)
{
	
	Matirx3x3 result;
	result.e[E11] = e[E11] + mat.e[E11]; 
	result.e[E12] = e[E12] + mat.e[E12]; 
	result.e[E13] = e[E13] + mat.e[E13]; 

	result.e[E21] = e[E21] + mat.e[E21]; 
	result.e[E22] = e[E22] + mat.e[E22]; 
	result.e[E23] = e[E23] + mat.e[E23]; 

	result.e[E31] = e[E31] + mat.e[E31]; 
	result.e[E32] = e[E32] + mat.e[E32]; 
	result.e[E33] = e[E33] + mat.e[E33]; 
	
	(*this = result);
	return *this;
}

Matirx3x3& Matirx3x3::operator-=(const Matirx3x3& mat)
{
	Matirx3x3 result;
	result.e[E11] = e[E11] - mat.e[E11]; 
	result.e[E12] = e[E12] - mat.e[E12]; 
	result.e[E13] = e[E13] - mat.e[E13]; 

	result.e[E21] = e[E21] - mat.e[E21]; 
	result.e[E22] = e[E22] - mat.e[E22]; 
	result.e[E23] = e[E23] - mat.e[E23]; 

	result.e[E31] = e[E31] - mat.e[E31]; 
	result.e[E32] = e[E32] - mat.e[E32]; 
	result.e[E33] = e[E33] - mat.e[E33]; 

	(*this = result);
	return *this;
}

void Matirx3x3::Invert()
{
	//求行列式
	float v1 = e[E11]*e[E22]*e[E33] + e[E12]*e[E23]*e[E31] + e[E13]*e[E21]*e[E32]; 
	float v2 = e[E13]*e[E22]*e[E31] + e[E23]*e[E32]*e[E11] + e[E33]*e[E12]*e[E21];
	float det = v1 - v2;
	if( det < 0.00001 && det > -0.00001)
		return;
	//伴随矩阵
	Matirx3x3 adjoint;

	adjoint.e[E11] = e[E22]*e[E33] - e[E23]*e[E32];
	adjoint.e[E22] = e[E11]*e[E33] - e[E13]*e[E31];
	adjoint.e[E33] = e[E11]*e[E22] - e[E12]*e[E21];

	adjoint.e[E12] = -(e[E12]*e[E33] - e[E13]*e[E32]);//(-1^)(x+y) == -1;
	adjoint.e[E13] =  (e[E12]*e[E23] - e[E13]*e[E22]);//(-1^)(x+y) == 1;

	adjoint.e[E21] = -(e[E21]*e[E33] - e[E23]*e[E31]);
	adjoint.e[E23] = -(e[E11]*e[E23] - e[E13]*e[E21]);

	adjoint.e[E31] =  (e[E21]*e[E32] -e[E22]*e[E31]);
	adjoint.e[E32] = -(e[E11]*e[E32] -e[E12]*e[E31]);
	
	e[E11] = adjoint.e[E11] / det; 
	e[E12] = adjoint.e[E12] / det;
	e[E13] = adjoint.e[E13] / det;

	e[E21] = adjoint.e[E21] / det;
	e[E22] = adjoint.e[E22] / det;
	e[E23] = adjoint.e[E23] / det;

	e[E31] = adjoint.e[E31] / det;
	e[E32] = adjoint.e[E32] / det;
	e[E33] = adjoint.e[E33] / det;
}

Matirx3x3 operator*(const Matirx3x3& m1, const Matirx3x3& m2)
{
	Matirx3x3 result;

	result.e[Matirx3x3::E11] = m1.e[Matirx3x3::E11]*m2.e[Matirx3x3::E11] + m1.e[Matirx3x3::E12]*m2.e[Matirx3x3::E21] + m1.e[Matirx3x3::E13]*m2.e[Matirx3x3::E31];
	result.e[Matirx3x3::E12] = m1.e[Matirx3x3::E11]*m2.e[Matirx3x3::E12] + m1.e[Matirx3x3::E12]*m2.e[Matirx3x3::E22] + m1.e[Matirx3x3::E13]*m2.e[Matirx3x3::E32];
	result.e[Matirx3x3::E13] = m1.e[Matirx3x3::E11]*m2.e[Matirx3x3::E13] + m1.e[Matirx3x3::E12]*m2.e[Matirx3x3::E23] + m1.e[Matirx3x3::E13]*m2.e[Matirx3x3::E33];

	result.e[Matirx3x3::E21] = m1.e[Matirx3x3::E21]*m2.e[Matirx3x3::E11] + m1.e[Matirx3x3::E22]*m2.e[Matirx3x3::E21] + m1.e[Matirx3x3::E23]*m2.e[Matirx3x3::E31];
	result.e[Matirx3x3::E22] = m1.e[Matirx3x3::E21]*m2.e[Matirx3x3::E12] + m1.e[Matirx3x3::E22]*m2.e[Matirx3x3::E22] + m1.e[Matirx3x3::E23]*m2.e[Matirx3x3::E32];
	result.e[Matirx3x3::E23] = m1.e[Matirx3x3::E21]*m2.e[Matirx3x3::E13] + m1.e[Matirx3x3::E22]*m2.e[Matirx3x3::E23] + m1.e[Matirx3x3::E23]*m2.e[Matirx3x3::E33];

	result.e[Matirx3x3::E31] = m1.e[Matirx3x3::E31]*m2.e[Matirx3x3::E11] + m1.e[Matirx3x3::E32]*m2.e[Matirx3x3::E21] + m1.e[Matirx3x3::E33]*m2.e[Matirx3x3::E31];
	result.e[Matirx3x3::E32] = m1.e[Matirx3x3::E31]*m2.e[Matirx3x3::E12] + m1.e[Matirx3x3::E32]*m2.e[Matirx3x3::E22] + m1.e[Matirx3x3::E33]*m2.e[Matirx3x3::E32];
	result.e[Matirx3x3::E33] = m1.e[Matirx3x3::E31]*m2.e[Matirx3x3::E13] + m1.e[Matirx3x3::E32]*m2.e[Matirx3x3::E23] + m1.e[Matirx3x3::E33]*m2.e[Matirx3x3::E33];
	
	return result;
}

Vector3 operator*(const Matirx3x3& mat, const Vector3& vec)
{
	Vector3 result;

	result.x = mat.e[Matirx3x3::E11]* vec.x + mat.e[Matirx3x3::E12]* vec.y + mat.e[Matirx3x3::E13]*vec.z;
	result.y = mat.e[Matirx3x3::E21]* vec.x + mat.e[Matirx3x3::E22]* vec.y + mat.e[Matirx3x3::E23]*vec.z;
	result.z = mat.e[Matirx3x3::E31]* vec.x + mat.e[Matirx3x3::E32]* vec.y + mat.e[Matirx3x3::E33]*vec.z;

	return result;
}

Matirx3x3 operator+(const Matirx3x3& m1, const Matirx3x3& m2)
{

	Matirx3x3 result;
	result.e[Matirx3x3::E11] = m1.e[Matirx3x3::E11] + m2.e[Matirx3x3::E11]; 
	result.e[Matirx3x3::E12] = m1.e[Matirx3x3::E12] + m2.e[Matirx3x3::E12]; 
	result.e[Matirx3x3::E13] = m1.e[Matirx3x3::E13] + m2.e[Matirx3x3::E13]; 

	result.e[Matirx3x3::E21] = m1.e[Matirx3x3::E21] + m2.e[Matirx3x3::E21]; 
	result.e[Matirx3x3::E22] = m1.e[Matirx3x3::E22] + m2.e[Matirx3x3::E22]; 
	result.e[Matirx3x3::E23] = m1.e[Matirx3x3::E23] + m2.e[Matirx3x3::E23]; 

	result.e[Matirx3x3::E31] = m1.e[Matirx3x3::E31] + m2.e[Matirx3x3::E31]; 
	result.e[Matirx3x3::E32] = m1.e[Matirx3x3::E32] + m2.e[Matirx3x3::E32]; 
	result.e[Matirx3x3::E33] = m1.e[Matirx3x3::E33] + m2.e[Matirx3x3::E33]; 
	
	return result;
}

Matirx3x3 operator-(const Matirx3x3& m1, const Matirx3x3& m2)
{
	Matirx3x3 result;
	result.e[Matirx3x3::E11] = m1.e[Matirx3x3::E11] - m2.e[Matirx3x3::E11]; 
	result.e[Matirx3x3::E12] = m1.e[Matirx3x3::E12] - m2.e[Matirx3x3::E12]; 
	result.e[Matirx3x3::E13] = m1.e[Matirx3x3::E13] - m2.e[Matirx3x3::E13]; 

	result.e[Matirx3x3::E21] = m1.e[Matirx3x3::E21] - m2.e[Matirx3x3::E21]; 
	result.e[Matirx3x3::E22] = m1.e[Matirx3x3::E22] - m2.e[Matirx3x3::E22]; 
	result.e[Matirx3x3::E23] = m1.e[Matirx3x3::E23] - m2.e[Matirx3x3::E23]; 

	result.e[Matirx3x3::E31] = m1.e[Matirx3x3::E31] - m2.e[Matirx3x3::E31]; 
	result.e[Matirx3x3::E32] = m1.e[Matirx3x3::E32] - m2.e[Matirx3x3::E32]; 
	result.e[Matirx3x3::E33] = m1.e[Matirx3x3::E33] - m2.e[Matirx3x3::E33]; 

	return result;
}
