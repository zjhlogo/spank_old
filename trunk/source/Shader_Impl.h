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
#include <StreamReader.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <map>

class Shader_Impl : public IShader
{
public:
	Shader_Impl(StreamReader* pVertexShader, StreamReader* pFregmentShader, VertexAttribute* pVertexAttribute);
	virtual ~Shader_Impl();

	virtual bool SetMatrix4x4(const char* pszParamName, const Matrix4x4& m);
	virtual bool SetVector4(const char* pszParamName, const Vector4& v);
	virtual bool SetTexture(const char* pszParamName, ITexture* pTexture, uint nIndex = 0);
	virtual const VertexAttribute* GetVertexAttribute() const;
	virtual void Reset();
	virtual bool Commit(const void* pVerts);

private:
	bool CreateShader(StreamReader* pVertexShader, StreamReader* pFregmentShader, VertexAttribute* pVertexAttribute);
	void FreeShader();
	GLuint LoadShader(const char* pszShaderSource, GLenum eType);
	GLenum GetGLType(ATTRIBUTE_ITEM_TYPE eType);

private:
	VertexAttribute* m_pVertexAttribute;
	GLuint m_glVertexShader;
	GLuint m_glFragmentShader;
	GLuint m_glProgramObject;

};
#endif // __SHADER_IMPL_H__
