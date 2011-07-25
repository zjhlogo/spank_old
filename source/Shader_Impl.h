/*!
 * \file Shader_Impl.h
 * \date 7-25-2011 10:14:30
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __SHADER_IMPL_H__
#define __SHADER_IMPL_H__

#include <IShader.h>
#include <util/StreamReader.h>
#include <GLES2/gl2.h>
#include <map>

class Shader_Impl : public IShader
{
public:
	typedef std::map<int, const Matrix4x4*> TM_MATRIX4X4;
	typedef std::map<int, ITexture*> TM_TEXTURE;

public:
	Shader_Impl(StreamReader* pVertexShader, StreamReader* pFregmentShader);
	virtual ~Shader_Impl();

	virtual bool SetMatrix4x4(const char* pszParamName, const Matrix4x4* pMat);
	virtual bool SetTexture(const char* pszParamName, ITexture* pTexture);
	virtual void Commit();

private:
	bool CreateShader(StreamReader* pVertexShader, StreamReader* pFregmentShader);
	void FreeShader();
	GLuint LoadShader(const char* pszShaderSource, GLenum eType);

private:
	GLuint m_glVertexShader;
	GLuint m_glFragmentShader;
	GLuint m_glProgramObject;

	TM_MATRIX4X4 m_mapMatrix4x4;
	TM_TEXTURE m_mapTexture;

};
#endif // __SHADER_IMPL_H__
