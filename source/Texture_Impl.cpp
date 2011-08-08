/*!
 * \file Texture_Impl.cpp
 * \date 7-22-2011 10:49:11
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Texture_Impl.h"
#include <IFileMgr.h>
#include <GLES2/gl2.h>

Texture_Impl::Texture_Impl(const char* pszFileName, SAMPLE_TYPE eSample)
{
	m_nTextureWidth = 0;
	m_nTextureHeight = 0;
	m_nGLTextureID = 0;

	m_bOK = LoadTextureFromFile(pszFileName, eSample);
}

Texture_Impl::~Texture_Impl()
{
	FreeGLTexture();
}

uint Texture_Impl::GetWidth() const
{
	return m_nTextureWidth;
}

uint Texture_Impl::GetHeight() const
{
	return m_nTextureHeight;
}

GLuint Texture_Impl::GetGLTextureID() const
{
	return m_nGLTextureID;
}

bool Texture_Impl::LoadTextureFromFile(const char* pszFileName, SAMPLE_TYPE eSample)
{
	StreamReader* pTextureStream = IFileMgr::GetInstance().LoadImageFile(pszFileName, &m_nTextureWidth, &m_nTextureHeight);
	if (!pTextureStream) return false;

	// create gl texture
	bool bOK = CreateGLTexture(m_nTextureWidth, m_nTextureHeight, eSample, pTextureStream->GetBuffer());

	// free texture data
	SAFE_RELEASE(pTextureStream);

	return bOK;
}

bool Texture_Impl::CreateGLTexture(uint width, uint height, SAMPLE_TYPE eSample, const void* pTextureData)
{
	FreeGLTexture();

	glGenTextures(1, &m_nGLTextureID);
	if (m_nGLTextureID == 0) return false;

	glBindTexture(GL_TEXTURE_2D, m_nGLTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pTextureData);

	if (eSample == SAMPLE_POINT)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	return true;
}

void Texture_Impl::FreeGLTexture()
{
	if (m_nGLTextureID != 0)
	{
		glDeleteTextures(1, &m_nGLTextureID);
		m_nGLTextureID = 0;
	}
}
