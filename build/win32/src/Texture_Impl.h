/*!
 * \file Texture_Impl.h
 * \date 7-22-2011 10:48:15
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __TEXTURE_IMPL_H__
#define __TEXTURE_IMPL_H__

#include <ITexture.h>

class Texture_Impl : public ITexture
{
public:
	Texture_Impl(const char* pszFileName);
	virtual ~Texture_Impl();

	virtual uint GetWidth() const;
	virtual uint GetHeight() const;

private:
	bool LoadTextureFromFile(const char* pszFileName);
	void FreeTextureData();

private:
	uint m_nWidth;
	uint m_nHeight;
	uchar* m_pTextureDataRGBA;

};
#endif // __TEXTURE_IMPL_H__
