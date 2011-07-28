/*!
 * \file Quaternion.h
 * \date 7-28-2011 17:51:34
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __QUATERNION_H__
#define __QUATERNION_H__

class Quaternion
{
public:
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	~Quaternion();

	// TODO: 

public:
	float x;
	float y;
	float z;
	float w;

};

#endif // __QUATERNION_H__
