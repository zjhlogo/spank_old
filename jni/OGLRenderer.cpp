/*!
 * \file OGLRenderer.cpp
 * \date 7-19-2011 11:04:59
 *
 *
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "OGLRenderer.h"
#include "DebugUtil.h"

static const char g_szVertexShader[] =
	"attribute vec4 vPosition;\n"
	"void main() {\n"
	"  gl_Position = vPosition;\n"
	"}\n";

static const char g_szFragmentShader[] =
	"precision mediump float;\n"
	"void main() {\n"
	"  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
	"}\n";

OGLRenderer::OGLRenderer()
{
	m_glVertexShader = 0;
	m_glFragmentShader = 0;
	m_glProgramObject = 0;
	m_glPositionHandler = 0;
}

OGLRenderer::~OGLRenderer()
{
	// TODO:
}

OGLRenderer& OGLRenderer::GetInstance()
{
	static OGLRenderer s_oglRenderer;
	return s_oglRenderer;
}

bool OGLRenderer::Initialize(int width, int height)
{
	Terminate();

	m_glVertexShader = LoadShader(g_szVertexShader, GL_VERTEX_SHADER);
	if (!m_glVertexShader)
	{
		LOGE("Load Vertex Shader Failed");
		return false;
	}

	m_glFragmentShader = LoadShader(g_szFragmentShader, GL_FRAGMENT_SHADER);
	if (!m_glFragmentShader)
	{
		LOGE("Load Fragment Shader Failed");
		return false;
	}

	m_glProgramObject = glCreateProgram();
	if (!m_glProgramObject)
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
		if (nErrorLength > 1)
		{
			char* pszErrorLog = new char[nErrorLength];
			glGetProgramInfoLog(m_glProgramObject, nErrorLength, NULL, pszErrorLog);
			LOGI("Error linking program: %s\n", pszErrorLog);
			delete[] pszErrorLog;
		}

		glDeleteProgram(m_glProgramObject);
		return false;
	}

	m_glPositionHandler = glGetAttribLocation(m_glProgramObject, "vPosition");
	glViewport(0, 0, width, height);
	return true;
}

void OGLRenderer::Terminate()
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

	m_glPositionHandler = 0;
}

void OGLRenderer::RenderTest()
{
	static const GLfloat s_vVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f };
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_glProgramObject);
	glVertexAttribPointer(m_glPositionHandler, 2, GL_FLOAT, GL_FALSE, 0, s_vVertices);
	glEnableVertexAttribArray(m_glPositionHandler);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

GLuint OGLRenderer::LoadShader(const char* pszShaderSource, GLenum eType)
{
	GLuint glShader = glCreateShader(eType);
	if (glShader == 0) return 0;

	glShaderSource(glShader, 1, &pszShaderSource, NULL);
	glCompileShader(glShader);

	// check the compile status
	GLint glCompiled = 0;
	glGetShaderiv(glShader, GL_COMPILE_STATUS, &glCompiled);
	if (glCompiled == 0)
	{
		GLint nErrorLength = 0;
		glGetShaderiv(glShader, GL_INFO_LOG_LENGTH, &nErrorLength);
		if (nErrorLength > 1)
		{
			char* pszErrorLog = new char[nErrorLength];
			glGetShaderInfoLog(glShader, nErrorLength, NULL, pszErrorLog);
			LOGI("Error compiling shader: %s\n", pszErrorLog);
			delete[] pszErrorLog;
		}

		glDeleteShader(glShader);
		return 0;
	}

	return glShader;
}
