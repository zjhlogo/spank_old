/*!
 * \file OGLRenderer.h
 * \date 7-19-2011 11:01:42
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __OGLRENDERER_H__
#define __OGLRENDERER_H__

#include <GLES2/gl2.h>

class OGLRenderer
{
public:
	static OGLRenderer& GetInstance();

	bool Initialize(int width, int height);
	void Terminate();

	void RenderTest();

private:
	OGLRenderer();
	~OGLRenderer();

	GLuint LoadShader(const char* pszShaderSource, GLenum eType);

private:
	GLuint m_glVertexShader;
	GLuint m_glFragmentShader;
	GLuint m_glProgramObject;
	GLuint m_glPositionHandler;
	char* m_pszVertexShader;
	char* m_pszFregmentShader;

};
#endif // __OGLRENDERER_H__
