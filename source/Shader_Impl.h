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
#include <IVertexAttribute.h>
#include <util/StreamReader.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <map>

class Shader_Impl : public IShader
{
public:
	typedef std::map<int, const Matrix4x4*> TM_MATRIX4X4;
	typedef std::map<int, ITexture*> TM_TEXTURE;

public:
	Shader_Impl(StreamReader* pVertexShader, StreamReader* pFregmentShader, const IVertexAttribute::ATTRIBUTE_ITEM* pAttrItems);
	virtual ~Shader_Impl();

	virtual bool SetMatrix4x4(const char* pszParamName, const Matrix4x4* pMat);
	virtual bool SetTexture(const char* pszParamName, ITexture* pTexture);
	virtual bool Commit(const void* pVerts);

private:
	bool CreateShader(StreamReader* pVertexShader, StreamReader* pFregmentShader, const IVertexAttribute::ATTRIBUTE_ITEM* pAttrItems);
	void FreeShader();
	GLuint LoadShader(const char* pszShaderSource, GLenum eType);
	GLenum GetGLType(IVertexAttribute::ATTRIBUTE_TYPE eType);

private:
	IVertexAttribute* m_pVertexAttribute;
	GLuint m_glVertexShader;
	GLuint m_glFragmentShader;
	GLuint m_glProgramObject;

	TM_MATRIX4X4 m_mapMatrix4x4;
	TM_TEXTURE m_mapTexture;

};
#endif // __SHADER_IMPL_H__
