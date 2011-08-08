/*!
 * \file IImage.h
 * \date 08-08-2011 21:36:54
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IIMAGE_H__
#define __IIMAGE_H__

#include "IObject.h"

class IImage : public IObject
{
public:
	virtual uint GetWidth() const = 0;
	virtual uint GetHeight() const = 0;

	virtual void* GetPixelData() = 0;
	virtual uint GetBPP() const = 0;

};
#endif // __IIMAGE_H__
