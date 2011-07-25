/*!
 * \file Shader_Impl.cpp
 * \date 7-25-2011 10:15:07
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Shader_Impl.h"
#include <IDebugUtil.h>
#include "Texture_Impl.h"

Shader_Impl::Shader_Impl(StreamReader* pVertexShader, StreamReader* pFregmentShader)
{
	m_glVertexShader = 0;
	m_glFragmentShader = 0;
	m_glProgramObject = 0;

	m_bOK = CreateShader(pVertexShader, pFregmentShader);
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

	m_mapMatrix4x4.insert(std::make_pair(location, pMat));
	return true;
}

bool Shader_Impl::SetTexture(const char* pszParamName, ITexture* pTexture)
{
	if (!pszParamName || !pTexture) return false;

	int location = glGetUniformLocation(m_glProgramObject, pszParamName);
	if (location == -1) return false;

	m_mapTexture.insert(std::make_pair(location, pTexture));
	return true;
}

void Shader_Impl::Commit()
{
	for (TM_MATRIX4X4::iterator it = m_mapMatrix4x4.begin(); it != m_mapMatrix4x4.end(); ++it)
	{
		int location = it->first;
		const Matrix4x4* pMat = it->second;
		glUniformMatrix4fv(location, 16, GL_FALSE, pMat->GetAddress());
	}
	m_mapMatrix4x4.clear();

	int nIndex = 0;
	for (TM_TEXTURE::iterator it = m_mapTexture.begin(); it != m_mapTexture.end(); ++it)
	{
		int location = it->first;
		Texture_Impl* pTexture_Impl = (Texture_Impl*)it->second;
		glActiveTexture(GL_TEXTURE0+nIndex);
		glBindTexture(GL_TEXTURE_2D, pTexture_Impl->GetGLTextureID());
		glUniform1i(location, nIndex);
		++nIndex;
	}
	m_mapTexture.clear();
}

bool Shader_Impl::CreateShader(StreamReader* pVertexShader, StreamReader* pFregmentShader)
{
	m_glVertexShader = LoadShader((const char*)pVertexShader->GetBuffer(), GL_VERTEX_SHADER);
	if (m_glVertexShader == 0)
	{
		LOGE("Create Vertex Shader Failed");
		return false;
	}

	m_glFragmentShader = LoadShader((const char*)pFregmentShader->GetBuffer(), GL_FRAGMENT_SHADER);
	if (m_glFragmentShader == 0)
	{
		LOGE("Create Fregment Shader Failed");
		return false;
	}

	m_glProgramObject = glCreateProgram();
	if (m_glProgramObject == 0)
	{
		LOGE("Create Program Failed");
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
			LOGI("Error linking program: %s", pszErrorLog);
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
			LOGI("Error compiling shader: %s", pszErrorLog);
			delete[] pszErrorLog;
		}

		glDeleteShader(glShader);
		return 0;
	}

	return glShader;
}
