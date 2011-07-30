/*!
 * \file ITexture.h
 * \date 7-22-2011 10:42:31
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ITEXTURE_H__
#define __ITEXTURE_H__

#include "IObject.h"

class ITexture : public IObject
{
public:
	enum SAMPLE_TYPE
	{
		SAMPLE_POINT = 0,
		SAMPLE_LINEAR,
	};

public:
	virtual uint GetWidth() const = 0;
	virtual uint GetHeight() const = 0;

};

#endif // __ITEXTURE_H__
