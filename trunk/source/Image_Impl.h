/*!
 * \file Image_Impl.h
 * \date 08-08-2011 22:57:42
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IMAGE_IMPL_H__
#define __IMAGE_IMPL_H__

#include <IImage.h>

class Image_Impl : public IImage
{
public:
	Image_Impl();
	virtual ~Image_Impl();

	virtual uint GetWidth() const;
	virtual uint GetHeight() const;

	virtual void* GetPixelData();
	virtual uint GetBPP() const;

};
#endif // __IMAGE_IMPL_H__
