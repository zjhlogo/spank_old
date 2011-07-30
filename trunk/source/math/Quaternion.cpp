/*!
 * \file Quaternion.cpp
 * \date 7-28-2011 17:51:40
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <math/Quaternion.h>

Quaternion::Quaternion()
{
	// TODO: 
}

Quaternion::Quaternion(const Quaternion& q)
{
	x = q.x;
	y = q.y;
	z = q.z;
	w = q.w;
}

Quaternion::Quaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Quaternion::~Quaternion()
{
	// TODO: 
}
