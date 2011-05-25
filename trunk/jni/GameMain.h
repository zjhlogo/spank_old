/*!
 * \file GameMain.h
 * \date 17-05-2011 21:07:31
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __GAMEMAIN_H__
#define __GAMEMAIN_H__

#include "MessageHandler.h"
#include <EGL/egl.h>
#include <android/input.h>
#include <GLES2/gl2.h>

class GameMain : public MessageHandler
{
public:
	GameMain();
	virtual ~GameMain();

	void Run();

	void Update(float dt);
	void Render();

private:
	bool OnActivityCreated(int nMsgID, StreamReader* pReader);
	bool OnActivityDestroy(int nMsgID, StreamReader* pReader);
	bool OnActivityStart(int nMsgID, StreamReader* pReader);
	bool OnActivityResume(int nMsgID, StreamReader* pReader);
	bool OnActivitySaveInstanceState(int nMsgID, StreamReader* pReader);
	bool OnActivityPause(int nMsgID, StreamReader* pReader);
	bool OnActivityStop(int nMsgID, StreamReader* pReader);
	bool OnActivityConfigurationChanged(int nMsgID, StreamReader* pReader);
	bool OnActivityLowMemory(int nMsgID, StreamReader* pReader);
	bool OnWindowFocusChanged(int nMsgID, StreamReader* pReader);
	bool OnNativeWindowCreated(int nMsgID, StreamReader* pReader);
	bool OnNativeWindowDestroy(int nMsgID, StreamReader* pReader);
	bool OnInputQueueCreated(int nMsgID, StreamReader* pReader);
	bool OnInputQueueDestroy(int nMsgID, StreamReader* pReader);
	bool OnKeyEvent();
	bool OnMotionEvent(float x, float y);

	bool InitializeDevice(ANativeWindow* window);
	void TerminateDevice();

	bool InitializeOpenGL();
	void TerminateOpenGL();

	GLuint LoadShader(const char* pszShader, GLenum eType);

	void DispatchInputEvents();

private:
	bool m_bShutdown;
	EGLDisplay m_eglDisplay;
	EGLSurface m_eglSurface;
	EGLContext m_eglContext;
	AInputQueue* m_pInputQueue;
	int m_nScreenWidth;
	int m_nScreenHeight;

	GLuint m_glVertexShader;
	GLuint m_glFragmentShader;
	GLuint m_glProgramObject;
	GLuint m_glPositionHandler;

	bool m_bRendererInitialized;

};
#endif // __GAMEMAIN_H__
