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
#include <Image.h>
#include <GLES2/gl2.h>

class Texture_Impl : public ITexture
{
public:
	Texture_Impl(const char* pszFileName, SAMPLE_TYPE eSample);
	virtual ~Texture_Impl();

	virtual uint GetWidth() const;
	virtual uint GetHeight() const;

	GLuint GetGLTextureID() const;

private:
	bool LoadTextureFromFile(const char* pszFileName, SAMPLE_TYPE eSample);

	bool CreateGLTexture(Image* pImage, SAMPLE_TYPE eSample);
	void FreeGLTexture();

private:
	uint m_nTextureWidth;
	uint m_nTextureHeight;
	GLuint m_nGLTextureID;

};
#endif // __TEXTURE_IMPL_H__
