/*!
 * \file Shader_Impl.cpp
 * \date 7-25-2011 10:15:07
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Shader_Impl.h"
#include "Texture_Impl.h"
#include <IDebugUtil.h>
#include <IShaderMgr.h>

Shader_Impl::Shader_Impl(StreamReader* pVertexShader, StreamReader* pFregmentShader, const IVertexAttribute::ATTRIBUTE_ITEM* pAttrItems)
{
	m_pVertexAttribute = NULL;
	m_glVertexShader = 0;
	m_glFragmentShader = 0;
	m_glProgramObject = 0;

	m_bOK = CreateShader(pVertexShader, pFregmentShader, pAttrItems);
}

Shader_Impl::~Shader_Impl()
{
	FreeShader();
}

bool Shader_Impl::SetMatrix4x4(const char* pszParamName, const Matrix4x4* pMat)
{
	if (!pszParamName || !pMat) return false;

	int location = glGetUniformLocation(m_glProgramObject, pszParamName);
	if (location == -1) return false;

	glUniformMatrix4fv(location, 1, GL_FALSE, pMat->GetAddress());
	return true;
}

bool Shader_Impl::SetTexture(const char* pszParamName, ITexture* pTexture, uint nIndex /* = 0 */)
{
	if (!pszParamName || !pTexture) return false;

	int location = glGetUniformLocation(m_glProgramObject, pszParamName);
	if (location == -1) return false;

	Texture_Impl* pTexture_Impl = (Texture_Impl*)pTexture;
	glActiveTexture(GL_TEXTURE0+nIndex);
	glBindTexture(GL_TEXTURE_2D, pTexture_Impl->GetGLTextureID());
	glUniform1i(location, nIndex);

	return true;
}

void Shader_Impl::Reset()
{
	// TODO: 
}

bool Shader_Impl::Commit(const void* pVerts)
{
	// setup vertex attributes
	int nNumAttrs = m_pVertexAttribute->GetNumAttributeItems();
	for (int i = 0; i < nNumAttrs; ++i)
	{
		const IVertexAttribute::ATTRIBUTE_ITEM* pAttrItem = m_pVertexAttribute->GetAttributeItem(i);
		GLenum eType = GetGLType(pAttrItem->eItemType);
		glVertexAttribPointer(i, pAttrItem->nSize, eType, GL_FALSE, m_pVertexAttribute->GetStride(), ((const uchar*)pVerts)+pAttrItem->nOffset);
		glEnableVertexAttribArray(i);
		glBindAttribLocation(m_glProgramObject, i, pAttrItem->szParamName);
	}

	glUseProgram(m_glProgramObject);
	return true;
}

bool Shader_Impl::CreateShader(StreamReader* pVertexShader, StreamReader* pFregmentShader, const IVertexAttribute::ATTRIBUTE_ITEM* pAttrItems)
{
	m_pVertexAttribute = IShaderMgr::GetInstance().CreateVertexAttribute(pAttrItems);
	if (!m_pVertexAttribute) return false;

	m_glVertexShader = LoadShader((const char*)pVertexShader->GetBuffer(), GL_VERTEX_SHADER);
	if (m_glVertexShader == 0)
	{
		LOGE("create vertex shader failed");
		return false;
	}

	m_glFragmentShader = LoadShader((const char*)pFregmentShader->GetBuffer(), GL_FRAGMENT_SHADER);
	if (m_glFragmentShader == 0)
	{
		LOGE("create fregment shader failed");
		return false;
	}

	m_glProgramObject = glCreateProgram();
	if (m_glProgramObject == 0)
	{
		LOGE("create shader program failed");
		return false;
	}

	glAttachShader(m_glProgramObject, m_glVertexShader);
	glAttachShader(m_glProgramObject, m_glFragmentShader);
	glLinkProgram(m_glProgramObject);

	GLint glLinked = 0;
	glGetProgramiv(m_glProgramObject, GL_LINK_STATUS, &glLinked);
	if (glLinked != GL_TRUE)
	{
		GLint nErrorLength = 0;
		glGetProgramiv(m_glProgramObject, GL_INFO_LOG_LENGTH, &nErrorLength);
		if (nErrorLength > 0)
		{
			char* pszErrorLog = new char[nErrorLength];
			glGetProgramInfoLog(m_glProgramObject, nErrorLength, NULL, pszErrorLog);
			LOGE("error linking program: %s", pszErrorLog);
			delete[] pszErrorLog;
		}

		glDeleteProgram(m_glProgramObject);
		return false;
	}

	return true;
}

void Shader_Impl::FreeShader()
{
	if (m_glProgramObject)
	{
		glDeleteProgram(m_glProgramObject);
		m_glProgramObject = 0;
	}

	if (m_glVertexShader)
	{
		glDeleteShader(m_glVertexShader);
		m_glVertexShader = 0;
	}

	if (m_glFragmentShader)
	{
		glDeleteShader(m_glFragmentShader);
		m_glFragmentShader = 0;
	}

	SAFE_RELEASE(m_pVertexAttribute);
}

GLuint Shader_Impl::LoadShader(const char* pszShaderSource, GLenum eType)
{
	GLuint glShader = glCreateShader(eType);
	if (glShader == 0) return 0;

	glShaderSource(glShader, 1, &pszShaderSource, NULL);
	glCompileShader(glShader);

	// check the compile status
	GLint glCompiled = 0;
	glGetShaderiv(glShader, GL_COMPILE_STATUS, &glCompiled);
	if (glCompiled != GL_TRUE)
	{
		GLint nErrorLength = 0;
		glGetShaderiv(glShader, GL_INFO_LOG_LENGTH, &nErrorLength);
		if (nErrorLength > 0)
		{
			char* pszErrorLog = new char[nErrorLength];
			glGetShaderInfoLog(glShader, nErrorLength, NULL, pszErrorLog);
			LOGE("error compiling shader: %s", pszErrorLog);
			delete[] pszErrorLog;
		}

		glDeleteShader(glShader);
		return 0;
	}

	return glShader;
}

GLenum Shader_Impl::GetGLType(IVertexAttribute::ATTRIBUTE_TYPE eType)
{
	static const GLenum s_GLType[IVertexAttribute::NUM_AT] = 
	{
		GL_FLOAT,			// AT_UNKNOWN,
		GL_BYTE,			// AT_BYTE,
		GL_UNSIGNED_BYTE,	// AT_UNSIGNED_BYTE,
		GL_SHORT,			// AT_SHORT,
		GL_UNSIGNED_SHORT,	// AT_UNSIGNED_SHORT,
		GL_FLOAT,			// AT_FLOAT,
		GL_FIXED,			// AT_FIXED,
		GL_HALF_FLOAT_OES,	// AT_HALF_FLOAT_OES,
	};

	if (eType < IVertexAttribute::AT_UNKNOWN || eType >= IVertexAttribute::NUM_AT) return GL_FLOAT;
	return s_GLType[eType];
}
