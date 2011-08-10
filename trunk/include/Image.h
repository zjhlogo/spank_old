/*!
 * \file Image.h
 * \date 08-08-2011 21:36:54
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "IObject.h"

class Image : public IObject
{
public:
	Image(const char* pszImageFile);
	virtual ~Image();

	virtual uint GetWidth() const;
	virtual uint GetHeight() const;

	virtual void* GetPixelData();
	virtual uint GetBPP() const;

private:
	bool CreateImage(const char* pszImageFile);

private:
	uint m_nImageWidth;
	uint m_nImageHeight;
	uint m_nBPP;
	uchar* m_pPixelData;

};
#endif // __IMAGE_H__
