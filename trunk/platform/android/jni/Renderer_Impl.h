/*!
 * \file Renderer_Impl.h
 * \date 7-20-2011 17:35:27
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __RENDERER_IMPL_H__
#define __RENDERER_IMPL_H__

#include <IRenderer.h>
#include <GLES2/gl2.h>

class Renderer_Impl : public IRenderer
{
public:
	Renderer_Impl();
	virtual ~Renderer_Impl();

	virtual bool Initialize(int width, int height);
	virtual void Terminate();

	virtual void RenderTest();

private:
	GLuint LoadShader(const char* pszShaderSource, GLenum eType);

private:
	GLuint m_glVertexShader;
	GLuint m_glFragmentShader;
	GLuint m_glProgramObject;
	GLuint m_glPositionHandler;
	char* m_pszVertexShader;
	char* m_pszFregmentShader;

};
#endif // __RENDERER_IMPL_H__
